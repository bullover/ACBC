#ifndef STRUCTS_H
#define STRUCTS_H

#endif // STRUCTS_H

#include <vector>
#include <array>


struct SensorData
{
    SensorData():H0Value(0),H1Value(0),H2Value(0),H3Value(0),
                 H0TempValue(0),H1TempValue(0),H2TempValue(0),H3TempValue(0),
                 VolValue(0),DP0(0),DP1(0),DP2(0),DP3(0)

    {
        ThermoValue.fill(0);
    }

    std::array<float,5> ThermoValue;

    float H0Value;
    float H1Value;
    float H2Value;
    float H3Value;

    float H0TempValue;
    float H1TempValue;
    float H2TempValue;
    float H3TempValue;

    float VolValue;

    float DP0;
    float DP1;
    float DP2;
    float DP3;

};

struct SensorDataFast
{
    SensorDataFast(): P1Value(0),P2Value(0),P3Value(0),
                      MassValue(0),
                      MV1Value(0),MV2Value(0),
                      MV1Out(0),MV2Out(0)
    {
    }
    float P1Value;
    float P2Value;
    float P3Value;

    float MassValue;

    float MV1Value;
    float MV2Value;

    float MV1Out;
    float MV2Out;


};
