#include "pid.h"

PID::PID():m_w(0),m_e(0),m_eold(0),m_Kp(0),m_Ki(0),m_Kd(0),m_I(0),m_Out(0),m_Imax(0),m_Imin(0),
    m_OutMax(10),m_OutMin(0)
{

}

PID::~PID()
{

}

void PID::SetPID(float w=0, float Kp=0, float Ki=0, float Kd=0,float Imax=100,float Imin = 100)
{
    m_w = w;
    m_Kp = Kp;
    m_Ki = Ki;
    m_Kd = Kd;
    m_I = 0;
    m_e = 0;
    m_eold = 0;
    m_Imax = Imax;
    m_Imin = Imin;
}

void PID::UpdatePID(float x)
{
    m_e = m_w-x;
    m_Out += m_Kp*m_e+m_Ki*m_I+m_Kd*(m_e-m_eold);
    m_eold = m_e;
    m_I += m_e;
    if(m_I > m_Imax)
        m_I = m_Imax;
    if(m_I < m_Imin)
        m_I = m_Imin;
    if(m_Out < m_OutMin)
        m_Out = m_OutMin;
    if(m_Out > m_OutMax)
        m_Out = m_OutMax;
}

float PID::GetOut()
{
    return m_Out;
}
