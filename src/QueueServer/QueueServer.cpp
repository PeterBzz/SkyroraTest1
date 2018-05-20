
#include "QueueServer.h"

void* QueueServer(void* args)
{
	QueueServerSettings settings = *static_cast<QueueServerSettings*>(args);

	mqd_t mq;
	ssize_t bytes_read;
    struct mq_attr attr;
    char buffer[settings.maxMessageLength + 1];

    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = settings.maxMessageLength;
    attr.mq_curmsgs = 0;

    mq = mq_open(settings.queueName.c_str(), O_CREAT | O_RDONLY | O_NONBLOCK, 0644, &attr);

    boost::posix_time::ptime timer;
    int clientsCount = 0;
    int maxPeriod = settings.minSensorPeriod_ms;
    for(int i = 0; i < settings.sourcesCount; i++)
    {
        if(settings.dataSources[i].connectionType == sendingPeriodically)
        {
            clientsCount++;
        }
        if(maxPeriod < settings.dataSources[i].period_ms)
        {
            maxPeriod = settings.dataSources[i].period_ms;
        }
    }

    timer = boost::posix_time::microsec_clock::universal_time();
    int updatedClientsCount = 0;
    while(true)
	{
		memset(buffer, 0x00, sizeof(buffer));
        bytes_read = mq_receive(mq, buffer, settings.maxMessageLength, NULL);
        if(bytes_read >= 0)
		{
			printf("SERVER: Received message: %s\n", buffer);
            int index = stoi(buffer);
            int timeSinceLastTelemetryFrame_ms = (boost::posix_time::microsec_clock::universal_time() - timer).total_milliseconds();
            if(settings.dataSources[index].isUpdatedSinseLastTelemetryFrame == false)
            {
                settings.dataSources[index].isUpdatedSinseLastTelemetryFrame = true;
                updatedClientsCount++;
            }
            if(updatedClientsCount == clientsCount && timeSinceLastTelemetryFrame_ms > maxPeriod)
            {
                stringstream ss;
                ss << boost::posix_time::microsec_clock::universal_time() << " ";
                updatedClientsCount = 0;
                for(int i = 0; i < settings.sourcesCount; i++)
                {
                    settings.dataSources[i].isUpdatedSinseLastTelemetryFrame = false;
                    if(i != 0)
                    {
                        ss << " ";
                    }
                    ss << settings.dataSources[i].GetDataString();
                }
                ss << endl;
                WriteTelemetry("output/file.txt", ss.str());
                cout << ss.str();
            }
		}
		else
		{
			// printf("SERVER: None \n");
		}

		fflush(stdout);
		usleep(settings.period_ms * 1e3);
    }

    mq_close(mq);
    mq_unlink(settings.queueName.c_str());

    return NULL;
}
