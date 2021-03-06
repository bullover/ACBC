#include "alixcom.h"
#include <sstream>
#include <thread>
#include "Error/ACBCError.h"

Alixcom::Alixcom():m_AlixTCPStream(nullptr)
{

}

void Alixcom::AlixConfig()
{
//    if(m_AlixTCPStream==nullptr)
//    {
        //std::string addr("localhost") ;
        std::string addr("192.168.0.148") ;
        auto connector = TCPConnector();
        //m_AlixTCPStream.reset(connector.Connect(9999,addr));
        m_AlixTCPStream.reset(connector.Connect(1491,addr));
//    }

    if(m_AlixTCPStream == nullptr)
    {
        throw ACBCError(ACBCError::Error_t::FATAL,"AlixConfig ","Not Connected" );
    }
}

void Alixcom::AlixWrite(std::unique_ptr<SensorDataFast> &SD)
{
    std::stringstream ss;
    //ss<<std::fixed<<std::setprecision(2);
    ss << "w0" << SD->MV1Out << char (0xd);
    m_AlixTCPStream->Send(ss.str());
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    ss.str("");
    ss << "w1" << SD->MV2Out << char(0xd);
    m_AlixTCPStream->Send(ss.str());
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
}

///AlixReadSlow is for senors which dont have to be updated very fast
/// (Thermo ,Humidity, MotorValves , Volume)
void Alixcom::AlixReadSlow(std::unique_ptr<SensorData> &SD)
{
    ///@ Thermo Sensors
    std::stringstream ss;   
    std::string RecvString;
    std::string::size_type sz;
    ///default receive if timout appeard and value order is shifted
    if(m_AlixTCPStream->Receive(RecvString,100,char(0xd))==0)
        throw ACBCError(ACBCError::Error_t::FATAL,"AlixConfig ","Connection Lost" );
    RecvString.clear();

    //ss<<std::fixed<<std::setprecision(2);
    ss << "x" << char (0xd);
    m_AlixTCPStream->Send(ss.str());


    if(m_AlixTCPStream->Receive(RecvString,3000,char(0xd))!=-3)
    {


        for(int i=0 ; i<5 ;i++)
        {
            //Depends on the format Alix is sending the string and at the end
            try{
                SD->ThermoValue[i] = std::stof(RecvString,&sz);
                RecvString.erase(RecvString.begin(),RecvString.begin()+sz);
            }catch(const std::out_of_range& ia)
            {
                std::cerr << "Out of Range error: " << ia.what() << '\n';
            }catch (const std::invalid_argument& ia)
            {
                std::cerr << "Invalid argument thermo: " << ia.what() << '\n';
            }
        }
    }

    ///@ Humidity Sensors
    ss.str("");
    ss << "h0" << char (0xd);
    m_AlixTCPStream->Send(ss.str());
    RecvString.clear();
    if(m_AlixTCPStream->Receive(RecvString,1000,char(0xd))!=-3)
    {
        try{
            SD->H0TempValue = std::stof(RecvString,&sz);
            RecvString.erase(RecvString.begin(),RecvString.begin()+sz);
            SD->H0Value = std::stof (RecvString);
        }catch(const std::out_of_range& ia)
        {
            std::cerr << "Out of Range error: " << ia.what() << '\n';
        }catch (const std::invalid_argument& ia)
        {
            std::cerr << "Invalid argument h0: " << ia.what() << '\n';
        }
    }
    ss.str("");
    ss << "h1" << char (0xd);
    m_AlixTCPStream->Send(ss.str());
    RecvString.clear();
    if(m_AlixTCPStream->Receive(RecvString,1000,char(0xd))!=-3)
    {
        try{
            SD->H1TempValue = std::stof(RecvString,&sz);
            SD->H1Value = std::stof (RecvString.substr(sz));
        }catch(const std::out_of_range& ia)
        {
            std::cerr << "Out of Range error: " << ia.what() << '\n';
        }catch (const std::invalid_argument& ia)
        {
            std::cerr << "Invalid argument h1: " << ia.what() << '\n';
        }
    }

    ss.str("");
    ss << "h2" << char (0xd);
    m_AlixTCPStream->Send(ss.str());
    RecvString.clear();
    if(m_AlixTCPStream->Receive(RecvString,1000,char(0xd))!=-3)
    {
        try{
            SD->H2TempValue = std::stof(RecvString,&sz);
            SD->H2Value = std::stof (RecvString.substr(sz));
        }catch(const std::out_of_range& ia)
        {
            std::cerr << "Out of Range error: " << ia.what() << '\n';
        }catch (const std::invalid_argument& ia)
        {
            std::cerr << "Invalid argument h2: " << ia.what() << '\n';
        }
    }
    ss.str("");
    ss << "h3" << char (0xd);
    m_AlixTCPStream->Send(ss.str());
    RecvString.clear();
    if(m_AlixTCPStream->Receive(RecvString,1000,char(0xd))!=-3)
    {
        try{
            SD->H3TempValue = std::stof(RecvString,&sz);
            SD->H3Value = std::stof (RecvString.substr(sz));
        }catch(const std::out_of_range& ia)
        {
            std::cerr << "Out of Range error: " << ia.what() << '\n';
        }catch (const std::invalid_argument& ia)
        {
            std::cerr << "Invalid argument h3: " << ia.what() << '\n';
        }
    }

    ///@ Volume Sensor
    ss.str("");
    ss << "g" << char (0xd);
    m_AlixTCPStream->Send(ss.str());
    RecvString.clear();
    if(m_AlixTCPStream->Receive(RecvString,1000,char(0xd))!=-3)
    {
        try{
            SD->VolValue = (std::stof(RecvString)*49.5)-47.5;
        }catch(const std::out_of_range& ia)
        {
            std::cerr << "Out of Range error: " << ia.what() << '\n';
        }catch (const std::invalid_argument& ia)
        {
            std::cerr << "Invalid argument g: " << ia.what() << '\n';
        }
    }

}

/// AlixReadFast is for Sensors which are updated faster
/// (Pressure- , Massflow sensors)
void Alixcom::AlixReadFast(std::unique_ptr<SensorDataFast> &SD)
{
    std::stringstream ss;
    std::string RecvString;

    ///default receive if timout appeard and value order is shifted
    if(m_AlixTCPStream->Receive(RecvString,100,char(0xd))==0)
        throw ACBCError(ACBCError::Error_t::FATAL,"AlixConfig ","Connection Lost" );
    RecvString.clear();
    /// Pressure Sensors
    ss << "p0" << char (0xd);
    m_AlixTCPStream->Send(ss.str());
   //int i =  m_AlixTCPStream->Receive(RecvString,1000,char(0xd));
    if(m_AlixTCPStream->Receive(RecvString,1000,char(0xd))!=-3)
    {
        try{
            SD->P1Value = (std::stof(RecvString)*15)-8.5;
        }catch(const std::out_of_range& ia)
        {
            std::cerr << "Out of Range error: " << ia.what() << '\n';
        }catch (const std::invalid_argument& ia)
        {
            std::cerr << "Invalid argument p0: " << ia.what() << '\n';
        }
    }
    ss.str("");
    RecvString.clear();
    ss << "p1" << char (0xd);
    m_AlixTCPStream->Send(ss.str());
    if(m_AlixTCPStream->Receive(RecvString,1000,char(0xd))!=-3)
    {
        try{
            SD->P2Value = (std::stof(RecvString)*15)-8.5;
        }catch(const std::out_of_range& ia)
        {
            std::cerr << "Out of Range error: " << ia.what() << '\n';
        }catch (const std::invalid_argument& ia)
        {
            std::cerr << "Invalid argument p1: " << ia.what() << '\n';
        }
    }

    ss.str("");
    RecvString.clear();
    ss << "p2" << char (0xd);
    m_AlixTCPStream->Send(ss.str());
    if(m_AlixTCPStream->Receive(RecvString,1000,char(0xd))!=-3)
    {
        try{
            SD->P3Value = (std::stof(RecvString)*15)-8.5;
        }catch(const std::out_of_range& ia)
        {
            std::cerr << "Out of Range error: " << ia.what() << '\n';
        }catch (const std::invalid_argument& ia)
        {
            std::cerr << "Invalid argument p2: " << ia.what() << '\n';
        }
    }
    ///MassFlow Sensor
    ss.str("");
    RecvString.clear();
    ss << "m" << char (0xd);
    m_AlixTCPStream->Send(ss.str());
    if(m_AlixTCPStream->Receive(RecvString,1000,char(0xd))!=-3)
    {
        try{
            SD->MassValue=20*(std::stof(RecvString)-4)/16;
        }catch(const std::out_of_range& ia)
        {
            std::cerr << "Out of Range error: " << ia.what() << '\n';
        }catch (const std::invalid_argument& ia)
        {
            std::cerr << "Invalid argument m: " << ia.what() << '\n';
        }
    }
    ///@ Valves
    ss.str("");
    ss << "v0" << char (0xd);
    m_AlixTCPStream->Send(ss.str());
    RecvString.clear();
    if(m_AlixTCPStream->Receive(RecvString,1000,char(0xd))!=-3)
    {
        try{
            SD->MV1Value = std::stof(RecvString);
        }catch(const std::out_of_range& ia)
        {
            std::cerr << "Out of Range error: " << ia.what() << '\n';
        }catch (const std::invalid_argument& ia)
        {
            std::cerr << "Invalid argument v0: " << ia.what() << '\n';
        }
    }
    ss.str("");
    ss << "v1" << char (0xd);
    m_AlixTCPStream->Send(ss.str());
    RecvString.clear();
    if(m_AlixTCPStream->Receive(RecvString,1000,char(0xd))!=-3)
    {
        try{
            SD->MV2Value = std::stof(RecvString);
        }catch(const std::out_of_range& ia)
        {
            std::cerr << "Out of Range error: " << ia.what() << '\n';
        }catch (const std::invalid_argument& ia)
        {
            std::cerr << "Invalid argument v0: " << ia.what() << '\n';
        }
    }
}

void Alixcom::AlixEndConn()
{
    std::stringstream ss;

    /// Pressure Sensors
    ss << "quit" << char (0xd);
    m_AlixTCPStream->Send(ss.str());

}
