
#ifndef DataSource_H
#define DataSource_H

#include <iostream>
#include <sstream>
#include <boost/variant.hpp>

#include "../ConnectionType/ConnectionType.h"

using namespace std;

class DataSource
{

	private:
		boost::variant<float, double, int16_t, int32_t> data;

	public:
		int period_ms;
		ConnectionType connectionType;
		bool isUpdatedSinseLastTelemetryFrame;
		pthread_t thread;
		DataSource();
		DataSource(ConnectionType connectionType,
			int period_ms,
			boost::variant<float, double, int16_t, int32_t> data,
			pthread_t* thread);
		string ToString();
		void SetData(boost::variant<float, double, int16_t, int32_t> data);
		string GetDataString();
		int GetPeriodMs();

};

#endif
