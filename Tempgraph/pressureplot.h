#ifndef PRESSUREPLOT_H
#define PRESSUREPLOT_H

#include <QWidget>

namespace Ui {
    class PressurePlot;
    }

class PressurePlot : public QWidget
{
    Q_OBJECT

public:
    explicit PressurePlot(QWidget *parent = 0);
    ~PressurePlot();

    void PlotGraphs(double P1, bool P1vis, double P2, bool P2vis, double P3, bool P3vis);
private:
    Ui::PressurePlot *ui;
};

#endif // PRESSUREPLOT_H
