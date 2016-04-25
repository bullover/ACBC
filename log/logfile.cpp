#include "logfile.h"
#include <time.h>
#include <sstream>


LogFile::LogFile():m_LogFile(nullptr)
{

}

LogFile::~LogFile()
{   
 m_LogFile.close();
}

bool LogFile::LogFileCreate(const std::string FilePath)
{
    std::stringstream ss;


//    std::time_t result= std::time(nullptr);
    char buffer [40];
    time_t rawtime;
    time (&rawtime);
    struct tm * timeinfo;
    timeinfo = localtime (&rawtime);

    strftime (buffer,40,"%c",timeinfo);

    ss <<FilePath << buffer << "logfile.csv";

    if(m_LogFile.is_open())
    {
        m_LogFile.close();
    }

     m_LogFile.open(ss.str(),std::fstream::out);

     if(m_LogFile == nullptr)
     {
         return false;
     }else
     {

         m_LogFile << "Time,T1[C°],T2[C°],T3[C°],T4[C°],Heater[C°],H1[%],H2[%],H3[%],H4[%],H1[C°],H2[C°],H3[C°],H4[C°]"
                      ",P1[bar],P2[bar],P3[bar],MF[g/s],MV1[V],MV2[V],V[l/min],MVout1[mA],MVout[mA]\n";


         return true;
     }

}

void LogFile::LogFileWrite(const SensorData *SD,const SensorDataFast *SDF,std::string TimeStamp)
{

    if(m_LogFile == nullptr)
        return void();

    m_LogFile << TimeStamp << ","
              << SD->ThermoValue[0]<< "," << SD->ThermoValue[1]<< ","
              << SD->ThermoValue[2] << ","<< SD->ThermoValue[3]<< ","
              << SD->ThermoValue[4]<< ","
              << SD->H0Value<< ","<< SD->H1Value<< ","
              << SD->H2Value<< ","<< SD->H3Value<< ","
              << SD->H0TempValue<< ","<< SD->H1TempValue<< ","
              << SD->H2TempValue<< ","<< SD->H3TempValue<< ","
              << SDF->P1Value<< "," << SDF->P2Value<< ","
              << SDF->P3Value<< ","
              << SDF->MassValue<< ","
              << SDF->MV1Value<< ","<< SDF->MV2Value<< ","
              << SD->VolValue<< ","
              << SDF->MV1Out << ","<< SDF->MV2Out <<'\n';



}

bool LogFile::CheckLogFile()
{
    if(this->m_LogFile.is_open())
    {
        return true;
    }else
    {
        return false;
    }
}
