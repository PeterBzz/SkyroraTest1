
#include "QueueClient.h"

void* QueueClient(void* args)
{
	QueueClientSettings* settings = static_cast<QueueClientSettings*>(args);
	mqd_t mq = mq_open(settings->queueName.c_str(), O_WRONLY);
    while(true)
	{
		//printf("CLIENT: Send message... \n");
        mq_send(mq, settings->dataSource.GetDataString().c_str(), settings->maxMessageLength, 0);

		fflush(stdout);
		usleep(settings->dataSource.GetPeriodMs() * 1e3);
    }
    mq_close(mq);
    return NULL;
}
