#ifndef LOGFILE_H
#define LOGFILE_H
#include <fstream>
#include "Alix/alixcom.h"


class LogFile
{
public:
    LogFile();
    ~LogFile();
    bool LogFileCreate(const std::string FilePath);
    void LogFileWrite(const SensorData *SD,const SensorDataFast *SDF, std::string TimeStamp);

    bool CheckLogFile();
private:
     std::fstream m_LogFile;
};

#endif // LOGFILE_H
