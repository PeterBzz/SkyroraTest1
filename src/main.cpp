
#include <pthread.h>

#include "DataSource/DataSource.h"
#include "QueueServer/QueueServer.h"
#include "QueueClient/QueueClient.h"

using namespace std;

int main()
{

	srand (time(NULL));

	const int sourcesCount = 10;
	const int maxMessageLength = 1024;
	const int minSensorPeriod_ms = 10;
	const int maxSensorPeriod_ms = 1000;
	const string queueName = "/queue";

	DataSource dataSources[sourcesCount];
    QueueClientSettings clientSettings[sourcesCount];
	for(int i = 0; i < sourcesCount; i++)
	{
		ConnectionType connectionType = (ConnectionType)(rand() % 2);
		pthread_t thread;
		boost::variant<float, double, int16_t, int32_t> data;
		switch(rand() % 4)
		{
			case 0:
			{
                data = (float)i;
				break;
			}
			case 1:
			{
                data = (double)i;
				break;
			}
			case 2:
			{
                data = (int16_t)i;
				break;
			}
			case 3:
			{
                data = (int32_t)i;
				break;
			}
			default:
				break;
		}
        dataSources[i] = DataSource(connectionType,
            rand() % (maxSensorPeriod_ms - minSensorPeriod_ms) + minSensorPeriod_ms,
            data,
            &thread);
		if(connectionType == sendingPeriodically)
		{
			clientSettings[i] = QueueClientSettings
			{
				.dataSource = dataSources[i],
				.queueName = queueName,
				.maxMessageLength = maxMessageLength
			};
			pthread_create(&thread, NULL, &QueueClient, &clientSettings[i]);
		}
		cout << dataSources[i].ToString();
	}

	pthread_t server;
	QueueServerSettings settings = QueueServerSettings
	{
		.minSensorPeriod_ms = minSensorPeriod_ms,
		.maxSensorPeriod_ms = maxSensorPeriod_ms,
		.queueName = queueName,
		.maxMessageLength = maxMessageLength,
		.period_ms = minSensorPeriod_ms,
        .dataSources = dataSources,
        .sourcesCount = sourcesCount
	};
	pthread_create(&server, NULL, &QueueServer, &settings);
	pthread_join(server, NULL);
	for(int i = 0; i < sourcesCount; i++)
	{
		if(!dataSources[i].thread)
		{
			pthread_join(dataSources[i].thread, NULL);
		}
	}

	cin.get();
	return EXIT_SUCCESS;

}
