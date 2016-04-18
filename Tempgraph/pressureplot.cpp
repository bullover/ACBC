#include "pressureplot.h"
#include "ui_pressureplot.h"


#include <QDebug>
#include <QDesktopWidget>
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>

PressurePlot::PressurePlot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PressurePlot)
{
    ui->setupUi(this);

    ///Add Graph P1
    this->ui->QC_PressurePlot->addGraph(); // blue line
    this->ui->QC_PressurePlot->graph(0)->setPen(QPen(Qt::blue));
//    this->ui->QC_PressurePlot->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));
//    this->ui->QC_PressurePlot->graph(0)->setAntialiasedFill(false);
    //this->ui->QC_PressurePlot->graph(0)->
    this->ui->QC_PressurePlot->addGraph(); // blue dot
    this->ui->QC_PressurePlot->graph(1)->setPen(QPen(Qt::blue));
    this->ui->QC_PressurePlot->graph(1)->setLineStyle(QCPGraph::lsNone);
    this->ui->QC_PressurePlot->graph(1)->setScatterStyle(QCPScatterStyle::ssDisc);
    ///Add Graph P2
    this->ui->QC_PressurePlot->addGraph(); // red line
    this->ui->QC_PressurePlot->graph(2)->setPen(QPen(Qt::red));
    //this->ui->QC_PressurePlot->graph(2)->setBrush(QBrush(QColor(240, 255, 200)));
    //this->ui->QC_PressurePlot->graph(2)->setAntialiasedFill(false);
    this->ui->QC_PressurePlot->addGraph(); // red dot
    this->ui->QC_PressurePlot->graph(3)->setPen(QPen(Qt::red));
    this->ui->QC_PressurePlot->graph(3)->setLineStyle(QCPGraph::lsNone);
    this->ui->QC_PressurePlot->graph(3)->setScatterStyle(QCPScatterStyle::ssDisc);
    ///Add Graph P3
    this->ui->QC_PressurePlot->addGraph(); // green line
    this->ui->QC_PressurePlot->graph(4)->setPen(QPen(Qt::green));
    //this->ui->QC_PressurePlot->graph(4)->setBrush(QBrush(QColor(240, 255, 200)));
    //this->ui->QC_PressurePlot->graph(4)->setAntialiasedFill(false);
    this->ui->QC_PressurePlot->addGraph(); // green dot
    this->ui->QC_PressurePlot->graph(5)->setPen(QPen(Qt::green));
    this->ui->QC_PressurePlot->graph(5)->setLineStyle(QCPGraph::lsNone);
    this->ui->QC_PressurePlot->graph(5)->setScatterStyle(QCPScatterStyle::ssDisc);

    this->ui->QC_PressurePlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    this->ui->QC_PressurePlot->xAxis->setDateTimeFormat("hh:mm:ss");
    this->ui->QC_PressurePlot->xAxis->setAutoTickStep(false);
    this->ui->QC_PressurePlot->xAxis->setTickStep(10);
    this->ui->QC_PressurePlot->axisRect()->setupFullAxesBox();

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(this->ui->QC_PressurePlot->xAxis, SIGNAL(rangeChanged(QCPRange)), this->ui->QC_PressurePlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(this->ui->QC_PressurePlot->yAxis, SIGNAL(rangeChanged(QCPRange)), this->ui->QC_PressurePlot->yAxis2, SLOT(setRange(QCPRange)));

}

PressurePlot::~PressurePlot()
{
    delete ui;
}

void PressurePlot::PlotGraphs(double P1, bool P1vis,double P2, bool P2vis,double P3, bool P3vis)
{
    double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;

    ///Plot Graph P1
    this->ui->QC_PressurePlot->graph(0)->setVisible(P1vis);
    this->ui->QC_PressurePlot->graph(0)->addData(key,P1);
    this->ui->QC_PressurePlot->graph(1)->clearData();
    this->ui->QC_PressurePlot->graph(1)->addData(key, P1);
    this->ui->QC_PressurePlot->graph(0)->removeDataBefore(key-60);


        //m_KeyT1 = key;
    ///Plot Graph P2
    this->ui->QC_PressurePlot->graph(2)->setVisible(P2vis);
    this->ui->QC_PressurePlot->graph(2)->addData(key,P2);
    this->ui->QC_PressurePlot->graph(3)->clearData();
    this->ui->QC_PressurePlot->graph(3)->addData(key, P2);
    this->ui->QC_PressurePlot->graph(2)->removeDataBefore(key-60);

    ///Plot Graph P3
    this->ui->QC_PressurePlot->graph(4)->setVisible(P3vis);
    this->ui->QC_PressurePlot->graph(4)->addData(key,P3);
    this->ui->QC_PressurePlot->graph(5)->clearData();
    this->ui->QC_PressurePlot->graph(5)->addData(key, P3);
    this->ui->QC_PressurePlot->graph(4)->removeDataBefore(key-60);

    ///XY Axis ranges


//    this->ui->QC_PressurePlot->graph(0)->rescaleValueAxis();
    this->ui->QC_PressurePlot->rescaleAxes();
    //this->ui->QC_PressurePlot->yAxis->setRange(-20,100,Qt::AlignCenter);
    this->ui->QC_PressurePlot->xAxis->setRange(key+0.25, 60, Qt::AlignRight);
    this->ui->QC_PressurePlot->replot();

}
