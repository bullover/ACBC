#include "tempplot.h"
#include "ui_tempplot.h"


#include <QDebug>
#include <QDesktopWidget>
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>

tempplot::tempplot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tempplot)//,m_KeyT1(0)
{

    ui->setupUi(this);
    ///Add Graph T1
    this->ui->QC_Templot->addGraph(); // blue line
    this->ui->QC_Templot->graph(0)->setPen(QPen(Qt::blue));
//    this->ui->QC_Templot->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));
//    this->ui->QC_Templot->graph(0)->setAntialiasedFill(false);
    //this->ui->QC_Templot->graph(0)->
    this->ui->QC_Templot->addGraph(); // blue dot
    this->ui->QC_Templot->graph(1)->setPen(QPen(Qt::blue));
    this->ui->QC_Templot->graph(1)->setLineStyle(QCPGraph::lsNone);
    this->ui->QC_Templot->graph(1)->setScatterStyle(QCPScatterStyle::ssDisc);
    ///Add Graph T2
    this->ui->QC_Templot->addGraph(); // red line
    this->ui->QC_Templot->graph(2)->setPen(QPen(Qt::red));
    //this->ui->QC_Templot->graph(2)->setBrush(QBrush(QColor(240, 255, 200)));
    //this->ui->QC_Templot->graph(2)->setAntialiasedFill(false);
    this->ui->QC_Templot->addGraph(); // red dot
    this->ui->QC_Templot->graph(3)->setPen(QPen(Qt::red));
    this->ui->QC_Templot->graph(3)->setLineStyle(QCPGraph::lsNone);
    this->ui->QC_Templot->graph(3)->setScatterStyle(QCPScatterStyle::ssDisc);
    ///Add Graph T3
    this->ui->QC_Templot->addGraph(); // green line
    this->ui->QC_Templot->graph(4)->setPen(QPen(Qt::green));
    //this->ui->QC_Templot->graph(4)->setBrush(QBrush(QColor(240, 255, 200)));
    //this->ui->QC_Templot->graph(4)->setAntialiasedFill(false);
    this->ui->QC_Templot->addGraph(); // green dot
    this->ui->QC_Templot->graph(5)->setPen(QPen(Qt::green));
    this->ui->QC_Templot->graph(5)->setLineStyle(QCPGraph::lsNone);
    this->ui->QC_Templot->graph(5)->setScatterStyle(QCPScatterStyle::ssDisc);
    ///Add Graph T4
    this->ui->QC_Templot->addGraph(); // black line
    this->ui->QC_Templot->graph(6)->setPen(QPen(Qt::black));
    //this->ui->QC_Templot->graph(6)->setBrush(QBrush(QColor(240, 255, 200)));
    //this->ui->QC_Templot->graph(6)->setAntialiasedFill(false);
    this->ui->QC_Templot->addGraph(); // black dot
    this->ui->QC_Templot->graph(7)->setPen(QPen(Qt::black));
    this->ui->QC_Templot->graph(7)->setLineStyle(QCPGraph::lsLine);
    this->ui->QC_Templot->graph(7)->setScatterStyle(QCPScatterStyle::ssDisc);


    this->ui->QC_Templot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    this->ui->QC_Templot->xAxis->setDateTimeFormat("hh:mm:ss");
    this->ui->QC_Templot->xAxis->setAutoTickStep(false);
    this->ui->QC_Templot->xAxis->setTickStep(10);
    this->ui->QC_Templot->axisRect()->setupFullAxesBox();

    // make left and bottom axes transfer their ranges to right and top axes:
    connect(this->ui->QC_Templot->xAxis, SIGNAL(rangeChanged(QCPRange)), this->ui->QC_Templot->xAxis2, SLOT(setRange(QCPRange)));
    connect(this->ui->QC_Templot->yAxis, SIGNAL(rangeChanged(QCPRange)), this->ui->QC_Templot->yAxis2, SLOT(setRange(QCPRange)));
}

tempplot::~tempplot()
{
    delete ui;
}

void tempplot::PlotGraphs(double T1, bool T1vis,double T2, bool T2vis,double T3, bool T3vis, double T4, bool T4vis )
{
    double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;

    ///Plot Graph T1
    this->ui->QC_Templot->graph(0)->setVisible(T1vis);
    this->ui->QC_Templot->graph(0)->addData(key,T1);
    this->ui->QC_Templot->graph(1)->clearData();
    this->ui->QC_Templot->graph(1)->addData(key, T1);
    this->ui->QC_Templot->graph(0)->removeDataBefore(key-60);


        //m_KeyT1 = key;
    ///Plot Graph T2
    this->ui->QC_Templot->graph(2)->setVisible(T2vis);
    this->ui->QC_Templot->graph(2)->addData(key,T2);
    this->ui->QC_Templot->graph(3)->clearData();
    this->ui->QC_Templot->graph(3)->addData(key, T2);
    this->ui->QC_Templot->graph(2)->removeDataBefore(key-60);

    ///Plot Graph T3
    this->ui->QC_Templot->graph(4)->setVisible(T3vis);
    this->ui->QC_Templot->graph(4)->addData(key,T3);
    this->ui->QC_Templot->graph(5)->clearData();
    this->ui->QC_Templot->graph(5)->addData(key, T3);
    this->ui->QC_Templot->graph(4)->removeDataBefore(key-60);

    ///Plot Graph T4
    this->ui->QC_Templot->graph(6)->setVisible(T4vis);
    this->ui->QC_Templot->graph(6)->addData(key,T4);
    this->ui->QC_Templot->graph(7)->clearData();
    this->ui->QC_Templot->graph(7)->addData(key, T4);
    this->ui->QC_Templot->graph(6)->removeDataBefore(key-60);

    ///XY Axis ranges


//    this->ui->QC_Templot->graph(0)->rescaleValueAxis();
    this->ui->QC_Templot->rescaleAxes();
    //this->ui->QC_Templot->yAxis->setRange(-20,100,Qt::AlignCenter);
    this->ui->QC_Templot->xAxis->setRange(key+0.25, 60, Qt::AlignRight);
    this->ui->QC_Templot->replot();


}

void tempplot::clearall()
{
    this->ui->QC_Templot->graph(0)->clearData();
    this->ui->QC_Templot->graph(1)->clearData();
    this->ui->QC_Templot->graph(2)->clearData();
    this->ui->QC_Templot->graph(3)->clearData();
    this->ui->QC_Templot->graph(4)->clearData();
    this->ui->QC_Templot->graph(5)->clearData();
    this->ui->QC_Templot->graph(6)->clearData();
    this->ui->QC_Templot->graph(7)->clearData();
    this->ui->QC_Templot->replot();
}

