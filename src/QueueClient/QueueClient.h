
#ifndef QueueClient_H
#define QueueClient_H

#include <stdio.h>
#include <mqueue.h>
#include <unistd.h>
#include <sstream>

#include "../DataSource/DataSource.h"

using namespace std;

struct QueueClientSettings
{
	DataSource dataSource;
	string queueName;
	int maxMessageLength;
};

void* QueueClient(void* args);

#endif
