#ifndef TEMPPLOT_H
#define TEMPPLOT_H

#include <QWidget>
#include "../qcustomplot/qcustomplot.h"

namespace Ui {
    class tempplot;
    }

class tempplot : public QWidget
{
    Q_OBJECT

public:
    explicit tempplot(QWidget *parent = 0);
    ~tempplot();

    void PlotGraphs(double T1, bool T1vis, double T2, bool T2vis, double T3, bool T3vis, double T4, bool T4vis);
    void clearall();
private:
    Ui::tempplot *ui;

    //double m_KeyT1;
};

#endif // TEMPPLOT_H
