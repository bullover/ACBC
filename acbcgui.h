#ifndef ACBCGUI_H
#define ACBCGUI_H

#include <QMainWindow>
#include <LED/qledindicator.h>

namespace Ui {
    class ACBCGui;
    }

class ACBCGui : public QMainWindow
{
    Q_OBJECT

public:
    explicit ACBCGui(QWidget *parent = 0);
    ~ACBCGui();

private:
    Ui::ACBCGui *ui;
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

};

#endif // ACBCGUI_H
