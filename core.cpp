#include "core.h"
#include "Error/ACBCError.h"

Core::Core():m_CoreMutex(),m_CoreMutexRead(),m_CoreMutexReadFast(),m_CoreState(CoreState_t::IDLE),
             m_CoreDataSlow(CoreStateDataReady::READY),m_CoreDataFast(CoreStateDataReady::READY),m_txtFile(nullptr),m_Counter(0),m_BoolExit(true)
{
    m_uptr_CoreThread = std::make_unique<std::thread>(&Core::CoreThread,this);
    m_uptr_CoreAlixCom = std::make_unique<Alixcom>();
    m_uptr_CoreSensorData = std::make_unique<SensorData>();
    m_uptr_CoreBufferData = std::make_unique<SensorData>();
    m_uptr_GUISensorData = std::make_unique<SensorData>();
    m_uptr_CoreSensorDataFast = std::make_unique<SensorDataFast>();
    m_uptr_CoreBufferDataFast = std::make_unique<SensorDataFast>();
    m_uptr_GUISensorDataFast = std::make_unique<SensorDataFast>();
}
Core::~Core()
{
    //m_txtFile.flush();
    //m_txtFile.close();
    if (this->m_uptr_CoreThread->joinable()) m_uptr_CoreThread->join();
}

void Core::FlowControl()
{
    switch (GetState()) {
        case CoreState_t::IDLE:
            this->CoreIdle();
            break;
        case CoreState_t::CONFIGURE:
            this->CoreConfig();
            break;
        case  CoreState_t::START:
            this->CoreRun();
            break;
        case CoreState_t::STOP:
            this->CoreStop();
            break;
        case CoreState_t::RESET:
            this->CoreConfig();
            break;
        case CoreState_t::ERROR:
            this->CoreError();
            break;
        case CoreState_t::EXIT:
            this->CoreExit();
            break;

    }

}

void Core::CoreThread()
{
    while (m_BoolExit)
    {
        this->FlowControl();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        m_Counter > 10000 ? m_Counter = 0 : m_Counter++;
    }
    if(m_uptr_CoreAlixCom->CheckAlixTCPStream())
    {
        m_uptr_CoreAlixCom->AlixEndConn();
    }
}

void Core::CoreConfig()
{
//    std::stringstream ss;
    //std::time_t result= std::time(nullptr);
//    char buffer [40];
//    time_t rawtime;
//    time (&rawtime);
//    struct tm * timeinfo;
//    timeinfo = localtime (&rawtime);

//    strftime (buffer,40,"%c",timeinfo);

//    ss <<buffer<<"logfile.csv";

//    if(m_txtFile.is_open())
//    {
//        m_txtFile.close();
//    }
    try
    {

        m_uptr_CoreAlixCom->AlixConfig();
        this->SetCoreState(CoreState_t::START);

        //m_txtFile.open(ss.str(),std::fstream::out);

    }catch(const ACBCError& rError)
    {
        this->SetCoreState(CoreState_t::ERROR);
        std::cerr << "CoreConfig: " << rError.What() << '\n';

    }

}

void Core::CoreRun()
{
    this->m_uptr_CoreAlixCom->AlixWrite(this->m_uptr_CoreSensorDataFast);

    this->m_uptr_CoreAlixCom->AlixReadFast(this->m_uptr_CoreSensorDataFast);

    //this->CoreWriteLOGFile();

    this->CoreDataSwapFast();


    if(m_Counter % 3 == 0)
    {
        this->m_uptr_CoreAlixCom->AlixReadSlow(this->m_uptr_CoreSensorData);
        this->CoreDataSwap();

    }




}

void Core::CoreStop()
{
 std::this_thread::sleep_for(std::chrono::milliseconds(500));
}



void Core::CoreIdle()
{
 std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

void Core::CoreError()
{

   std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

void Core::CoreExit()
{
    this->m_BoolExit = false;
}

