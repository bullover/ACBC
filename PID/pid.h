#ifndef PID_H
#define PID_H

/// this PID is made for Sampling rate of 1sec if other sampling rates used
/// the have to be considered by chosing Kp Ki and Kd!

class PID
{
public:
    PID();
    ~PID();
    void SetPID(float w, float Kp, float Ki, float Kd, float Imax, float Imin);
    void UpdatePID(float x);
    float GetOut();

private:
    float m_w;
    float m_e;
    float m_eold;
    float m_Kp;
    float m_Ki;
    float m_Kd;
    float m_I;
    float m_Out;
    float m_Imax;
    float m_Imin;
    const float m_OutMax;
    const float m_OutMin;

};

#endif // PID_H
