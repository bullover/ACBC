#ifndef STATES_H
#define STATES_H

#endif // STATES_H

enum class CoreSubStatesRead_t
{
    ReqData,
    ProcData,


};

enum class CoreSubStateWrite_t
{
    WriteData,
    NoWriteData
};

enum class CoreState_t
{
    IDLE,
    START,
    STOP,
    RESET,
    CONFIGURE,
    ERROR,
    EXIT

};

enum class CoreStateDataReady
{
    READY,
    PROC
};


