#ifndef ACBCGUI_H
#define ACBCGUI_H

#include <QMainWindow>
#include <QTimer>
#include <LED/qledindicator.h>
#include "core.h"
#include "Tempgraph/tempplot.h"

namespace Ui {
    class ACBCGui;
    }

class ACBCGui : public QMainWindow
{
    Q_OBJECT

public:
    explicit ACBCGui(QWidget *parent = 0);
    ~ACBCGui();

    void Start();
    void Stop();
    void Reset();
    void Quit();
    void Mute();
    void Info();
    void UpdateData();

private:
    Ui::ACBCGui *ui;

    ///Core
    Core m_Core;
    QTimer *ptr_timer;
    const SensorData *m_ptr_Sensordata;
    const SensorDataFast *m_ptr_SensordataFast;
    double m_TotalCO2;



    ///LEDs
    QLedIndicator *Led_T5;
    QLedIndicator *Led_H1;
    QLedIndicator *Led_H2;
    QLedIndicator *Led_H3;
    QLedIndicator *Led_H4;
    QLedIndicator *Led_g;
    QLedIndicator *Led_P1;
    QLedIndicator *Led_P2;
    QLedIndicator *Led_P3;
    QLedIndicator *Led_MV1;
    QLedIndicator *Led_MV2;

//private:
    inline void setTimer()
    {
        if(!(ptr_timer->isActive()))
        this->ptr_timer->start(1000);
    }
    inline void stopTimer()
    {
        if(ptr_timer->isActive())
        this->ptr_timer->stop();
    }




};

#endif // ACBCGUI_H
