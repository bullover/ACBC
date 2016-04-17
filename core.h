#ifndef CORE_H
#define CORE_H

#include "datastructs/states.h"
#include <thread>
#include <mutex>
#include "Alix/alixcom.h"
#include <fstream>

class Core
{
public:
    Core();
     ~Core();
    void FlowControl();
    void CoreThread();
    void CoreConfig();
    void CoreRun();
    void CoreStop();
    void CoreIdle();
    void CoreError();
    void CoreExit();

    SensorData p_DataPackage1;
    SensorData p_DataPackage2;

private:
     std::unique_ptr<Alixcom> m_uptr_CoreAlixCom;
     std::unique_ptr<std::thread> m_uptr_CoreThread;
     std::unique_ptr<SensorData> m_uptr_CoreSensorData;
     std::unique_ptr<SensorData> m_uptr_CoreBufferData;
     std::unique_ptr<SensorData> m_uptr_GUISensorData;
     std::unique_ptr<SensorDataFast> m_uptr_CoreSensorDataFast;
     std::unique_ptr<SensorDataFast> m_uptr_CoreBufferDataFast;
     std::unique_ptr<SensorDataFast> m_uptr_GUISensorDataFast;
     std::mutex m_CoreMutex;
     std::mutex m_CoreMutexRead;
     std::mutex m_CoreMutexReadFast;
 //  std::mutex m_CoreMutexDataReady;
     CoreState_t m_CoreState;
     CoreStateDataReady m_CoreDataSlow;
     CoreStateDataReady m_CoreDataFast;
     std::fstream m_txtFile;
     unsigned int m_Counter;
     bool m_BoolExit;



public:

     /// States
     inline CoreState_t GetState() noexcept
     {
         std::lock_guard<std::mutex> lock(m_CoreMutex);
         return this->m_CoreState;
     }

     inline void SetCoreState(CoreState_t State) noexcept
     {
         std::lock_guard<std::mutex> lock(m_CoreMutex);
         this->m_CoreState = State;
     }

     ///DATA swap SLOW
     inline void CoreDataSwap()
     {
        std::lock_guard<std::mutex> lock(m_CoreMutexRead);
        std::swap(m_uptr_CoreSensorData,m_uptr_CoreBufferData);
        m_CoreDataSlow=CoreStateDataReady::READY;


     }

     inline const SensorData* GetData()
     {
         std::lock_guard<std::mutex> lock(m_CoreMutexRead);
         if(m_CoreDataSlow==CoreStateDataReady::READY)
         {
            m_CoreDataSlow=CoreStateDataReady::PROC;
            std::swap(m_uptr_GUISensorData,m_uptr_CoreBufferData);
            return this->m_uptr_GUISensorData.get();
         }else
         {
            return this->m_uptr_GUISensorData.get();
         }
     }


     ///DATA swap FAST
     inline void CoreDataSwapFast()
     {
        std::lock_guard<std::mutex> lock(m_CoreMutexReadFast);
        std::swap(m_uptr_CoreSensorDataFast,m_uptr_CoreBufferDataFast);
        m_CoreDataFast=CoreStateDataReady::READY;
     }

     inline const SensorDataFast* GetDataFast()
     {
         std::lock_guard<std::mutex> lock(m_CoreMutexReadFast);
         if(m_CoreDataFast==CoreStateDataReady::READY)
         {
                m_CoreDataFast=CoreStateDataReady::PROC;
                std::swap(m_uptr_GUISensorDataFast,m_uptr_CoreBufferDataFast);
                return this->m_uptr_GUISensorDataFast.get();
         }else
         {

             return this->m_uptr_GUISensorDataFast.get();
         }
     }

//     inline void SetReadyStateFastReady()
//     {
//         std::lock_guard<std::mutex> lock(m_CoreMutexReadFast);
//          m_CoreDataFast=CoreStateDataReady::PROC;
//     }

//     inline void SetReadyStateReady()
//     {
//         std::lock_guard<std::mutex> lock(m_CoreMutexRead);
//         m_CoreDataSlow=CoreStateDataReady::PROC;
//     }

//     inline SetDataFastRead(CoreStateDataReady State)
//     {
//         std::lock_guard<std::mutex> lock(m_CoreMutexDataReady);
//         std
//     }



//     inline void CoreWriteLOGFile()
//     {
//         //std::asctime(std::localtime(&result))
//         time_t rawtime;
//           struct tm * timeinfo;
//           char buffer [15];

//           time (&rawtime);
//           timeinfo = localtime (&rawtime);

//         strftime (buffer,15,"%a %I:%M:%S %p.",timeinfo);
//         //std::time_t result = std::time(nullptr);
//         m_txtFile << buffer << ","
//                   << m_uptr_CoreSensorData->ThermoValue[0]<< "," << m_uptr_CoreSensorData->ThermoValue[1]<< ","
//                   << m_uptr_CoreSensorData->ThermoValue[2] << ","<< m_uptr_CoreSensorData->ThermoValue[3]<< ","
//                   << m_uptr_CoreSensorData->ThermoValue[4]<< ","
//                   << m_uptr_CoreSensorData->H0Value<< ","<< m_uptr_CoreSensorData->H1Value<< ","
//                   << m_uptr_CoreSensorData->H2Value<< ","<< m_uptr_CoreSensorData->H3Value<< ","
//                   << m_uptr_CoreSensorData->H0TempValue<< ","<< m_uptr_CoreSensorData->H1TempValue<< ","
//                   << m_uptr_CoreSensorData->H2TempValue<< ","<< m_uptr_CoreSensorData->H3TempValue<< ","
//                   << m_uptr_CoreSensorDataFast->P1Value<< "," << m_uptr_CoreSensorDataFast->P2Value<< ","
//                   << m_uptr_CoreSensorDataFast->P3Value<< ","
//                   << m_uptr_CoreSensorDataFast->MassValue<< ","
//                   << m_uptr_CoreSensorDataFast->MV1Value<< ","<< m_uptr_CoreSensorDataFast->MV2Value<< ","
//                   << m_uptr_CoreSensorData->VolValue<< ","
//                   << m_uptr_CoreSensorDataFast->MV1Out << ","<< m_uptr_CoreSensorDataFast->MV2Out <<'\n';
//         m_txtFile.flush();
//     }


};


#endif // CORE_H
