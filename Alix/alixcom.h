#ifndef ALIXCOM_H
#define ALIXCOM_H

#include "Socket/TCPConnector.h"
#include "Socket/TCPStream.h"
#include "datastructs/structs.h"
#include <memory>

class Alixcom
{
public:
    Alixcom();

    void AlixConfig();
    void AlixWrite(std::unique_ptr<SensorDataFast> &SD);
    void AlixReadSlow(std::unique_ptr<SensorData> &SD);
    void AlixReadFast(std::unique_ptr<SensorDataFast> &SD);
    void AlixEndConn();
private:
    std::unique_ptr<TCPStream> m_AlixTCPStream;
};

#endif // ALIXCOM_H
