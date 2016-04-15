#ifndef ACBCGUI_H
#define ACBCGUI_H

#include <QMainWindow>

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
};

#endif // ACBCGUI_H
