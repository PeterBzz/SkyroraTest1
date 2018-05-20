
#ifndef QueueServer_H
#define QueueServer_H

#include <stdio.h>
#include <sstream>
#include <mqueue.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <boost/date_time.hpp>

#include "../DataSource/DataSource.h"
#include "../FileWriter/FileWriter.h"

using namespace std;

struct QueueServerSettings
{
	int minSensorPeriod_ms;
	int maxSensorPeriod_ms;
	string queueName;
	int maxMessageLength;
	int period_ms;
	DataSource* dataSources;
	int sourcesCount;
};

void* QueueServer(void* args);

#endif
