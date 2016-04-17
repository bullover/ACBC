#include "acbcgui.h"
#include "ui_acbcgui.h"
#include <QGridLayout>

ACBCGui::ACBCGui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ACBCGui),m_Core(),ptr_timer(nullptr),m_ptr_Sensordata(nullptr),
    m_ptr_SensordataFast(nullptr),m_TotalCO2(0)
{
    ui->setupUi(this);
    ///Create Leds
    Led_T5 = new QLedIndicator(this->ui->centralWidget);
    this->ui->gridLayout_2->addWidget(Led_T5,4,3,Qt::AlignLeft);
    Led_H1 = new QLedIndicator(this->ui->centralWidget);
    this->ui->gridLayout_2->addWidget(Led_H1,0,7,Qt::AlignLeft);
    Led_H2 = new QLedIndicator(this->ui->centralWidget);
    this->ui->gridLayout_2->addWidget(Led_H2,1,7,Qt::AlignLeft);
    Led_H3 = new QLedIndicator(this->ui->centralWidget);
    this->ui->gridLayout_2->addWidget(Led_H3,2,7,Qt::AlignLeft);
    Led_H4 = new QLedIndicator(this->ui->centralWidget);
    this->ui->gridLayout_2->addWidget(Led_H4,3,7,Qt::AlignLeft);
    Led_g = new QLedIndicator(this->ui->centralWidget);
    this->ui->gridLayout_2->addWidget(Led_g,4,7,Qt::AlignLeft);
    Led_P1 = new QLedIndicator(this->ui->centralWidget);
    this->ui->gridLayout_6->addWidget(Led_P1,0,3,Qt::AlignLeft);
    Led_P2 = new QLedIndicator(this->ui->centralWidget);
    this->ui->gridLayout_6->addWidget(Led_P2,1,3,Qt::AlignLeft);
    Led_P3 = new QLedIndicator(this->ui->centralWidget);
    this->ui->gridLayout_6->addWidget(Led_P3,2,3,Qt::AlignLeft);
    Led_MV1 = new QLedIndicator(this->ui->centralWidget);
    this->ui->gridLayout_7->addWidget(Led_MV1,1,10,Qt::AlignCenter);
    Led_MV2 = new QLedIndicator(this->ui->centralWidget);
    this->ui->gridLayout_7->addWidget(Led_MV2,2,10,Qt::AlignCenter);
    ///connect Timer
    this->ptr_timer=new QTimer(this);
    QObject::connect(ptr_timer, &QTimer::timeout, this,&ACBCGui::UpdateData,Qt::UniqueConnection);
    ///connect Buttons
    QObject::connect(ui->pushButton_Start,&QPushButton::clicked,this,&ACBCGui::Start,Qt::UniqueConnection);
    QObject::connect(ui->pushButton_Stop,&QPushButton::clicked,this,&ACBCGui::Stop,Qt::UniqueConnection);
    QObject::connect(ui->pushButton_Reset,&QPushButton::clicked,this,&ACBCGui::Reset,Qt::UniqueConnection);
    QObject::connect(ui->pushButton_Quit,&QPushButton::clicked,this,&ACBCGui::Quit,Qt::UniqueConnection);
    QObject::connect(ui->pushButton_Mute,&QPushButton::clicked,this,&ACBCGui::Mute,Qt::UniqueConnection);
    QObject::connect(ui->pushButton_Info,&QPushButton::clicked,this,&ACBCGui::Info,Qt::UniqueConnection);

}

ACBCGui::~ACBCGui()
{
    delete Led_T5;
    delete Led_H1;
    delete Led_H2;
    delete Led_H3;
    delete Led_H4;
    delete Led_g;
    delete Led_P1;
    delete Led_P2;
    delete Led_P3;
    delete Led_MV1;
    delete Led_MV2;
    delete ui;
}

void ACBCGui::Start()
{
    if(m_Core.GetState()==CoreState_t::IDLE)
    {
        m_Core.SetCoreState(CoreState_t::CONFIGURE);
        this->setTimer();
        //
    }

    if(m_Core.GetState()==CoreState_t::STOP)
    {
        this->setTimer();
    }

}

void ACBCGui::Stop()
{
    if(m_Core.GetState()==CoreState_t::START)
    {
        m_Core.SetCoreState(CoreState_t::STOP);
        this->stopTimer();

    }

}

void ACBCGui::Reset()
{
    if(m_Core.GetState()==CoreState_t::ERROR)
    {
        m_Core.SetCoreState(CoreState_t::CONFIGURE);
    }

}

void ACBCGui::Quit()
{
    m_Core.SetCoreState(CoreState_t::EXIT);
}

void ACBCGui::Mute()
{


}

void ACBCGui::Info()
{

}

void ACBCGui::UpdateData()
{
    std::stringstream ss;
    std::stringstream ss2;
    char buffer [40];
    time_t rawtime;
    time (&rawtime);
    struct tm * timeinfo;
    timeinfo = localtime (&rawtime);

    strftime (buffer,40,"%H:%M:%S",timeinfo);



    switch (m_Core.GetState()) {
        case CoreState_t::ERROR:
            ss2 << buffer << " ERROR";
            this->ui->textEdit_Status->append(QString::fromStdString(ss2.str()));
            break;
        case CoreState_t::START:
        ss2 << buffer << " Start";
        this->ui->textEdit_Status->append(QString::fromStdString(ss2.str()));
            break;
        case CoreState_t::STOP:
        ss2 << buffer << " Stop";
        this->ui->textEdit_Status->append(QString::fromStdString(ss2.str()));
            break;
        case CoreState_t::EXIT:
        ss2 << buffer << " Exit";
        this->ui->textEdit_Status->append(QString::fromStdString(ss2.str()));
            break;
        default:
            break;
    }

    this->m_ptr_Sensordata = m_Core.GetData();
    this->m_ptr_SensordataFast = m_Core.GetDataFast();

    this-> ui->lcdNumber_H1->display(m_ptr_Sensordata->H0TempValue);
    this->ui->lcdNumber_H2->display(m_ptr_Sensordata->H1TempValue);
    this->ui->lcdNumber_H3->display(m_ptr_Sensordata->H2TempValue);
    this->ui->lcdNumber_H4->display(m_ptr_Sensordata->H3TempValue);
    this->ui->lcdNumber_g->display(m_ptr_Sensordata->VolValue);
    this->ui->lcdNumber_T1->display(m_ptr_Sensordata->ThermoValue[0]);
    this->ui->lcdNumber_T2->display(m_ptr_Sensordata->ThermoValue[1]);
    this->ui->lcdNumber_T3->display(m_ptr_Sensordata->ThermoValue[2]);
    this->ui->lcdNumber_T4->display(m_ptr_Sensordata->ThermoValue[3]);
    this->ui->lcdNumber_T5->display(m_ptr_Sensordata->ThermoValue[4]);

    ss <<buffer<<" "<< m_ptr_Sensordata->ThermoValue[0]<<" "<< m_ptr_Sensordata->ThermoValue[1]
           <<" "<< m_ptr_Sensordata->ThermoValue[2] <<" "<< m_ptr_Sensordata->ThermoValue[3] <<" "<< m_ptr_Sensordata->ThermoValue[4]
       ;

    this->ui->textEdit_TempRec->append(QString::fromStdString(ss.str()));


    this->ui->lcdNumber_P1->display(m_ptr_SensordataFast->P1Value);
    this->ui->lcdNumber_P2->display(m_ptr_SensordataFast->P2Value);
    this->ui->lcdNumber_P3->display(m_ptr_SensordataFast->P3Value);
    this->ui->lcdNumber_v1->display(m_ptr_SensordataFast->MV1Value);
    this->ui->lcdNumber_v2->display(m_ptr_SensordataFast->MV2Value);
    this->ui->lcdNumber_massflow->display(m_ptr_SensordataFast->MassValue);

    m_TotalCO2 += m_ptr_SensordataFast->MassValue*0.5;
    this->ui->lcdNumber_CO2->display(m_TotalCO2);



}
