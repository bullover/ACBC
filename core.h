#ifndef CORE_H
#define CORE_H

#include "datastructs/states.h"
#include <thread>
#include <mutex>
#include "Alix/alixcom.h"
#include <fstream>
#include <math.h>

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
  //   std::fstream m_txtFile;
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

     inline SensorDataFast* GetDataFast()
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

     inline void CalcDP(std::unique_ptr<SensorData> &SD)
     {
             float H = 0;
             H = (log10(SD->H0Value)-2)/0.4343+(17.62*SD->H0TempValue)/(243.12+SD->H0TempValue);
             SD->DP0 = 243.12*H/(17.62-H);
             H = (log10(SD->H1Value)-2)/0.4343+(17.62*SD->H1TempValue)/(243.12+SD->H1TempValue);
             SD->DP1 = 243.12*H/(17.62-H);
             H = (log10(SD->H2Value)-2)/0.4343+(17.62*SD->H2TempValue)/(243.12+SD->H2TempValue);
             SD->DP2 = 243.12*H/(17.62-H);
             H = (log10(SD->H3Value)-2)/0.4343+(17.62*SD->H3TempValue)/(243.12+SD->H3TempValue);
             SD->DP3 = 243.12*H/(17.62-H);
     }

};


#endif // CORE_H
