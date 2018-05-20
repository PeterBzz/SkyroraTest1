
#include "DataSource.h"

DataSource::DataSource() : connectionType(sendingPeriodically), period_ms(1000), thread(NULL),
    isUpdatedSinseLastTelemetryFrame(false)
{
    this->data = 0;
}
DataSource::DataSource(ConnectionType connectionType,
    int period_ms,
    boost::variant<float, double, int16_t, int32_t> data,
    pthread_t* thread) : connectionType(connectionType), period_ms(period_ms), data(data), thread(*thread),
        isUpdatedSinseLastTelemetryFrame(false) {}
string DataSource::ToString()
{
    stringstream strStream;
    strStream << "Data: " << data
        << " Type: " << data.type().name()
        << " Period: " << period_ms
        << " Connection: " << connectionType
        << endl;
    return strStream.str();
}
void DataSource::SetData(boost::variant<float, double, int16_t, int32_t> data)
{
    this->data = data;
}
string DataSource::GetDataString()
{
    stringstream ss;
    ss << this->data;
    return ss.str();
}
int DataSource::GetPeriodMs()
{
    return this->period_ms;
}
