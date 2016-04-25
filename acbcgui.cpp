#include "acbcgui.h"
#include "ui_acbcgui.h"
#include <QGridLayout>
#include "Dialogs/dialogaus.h"
#include "Dialogs/dialogprint.h"
//#include <QDialog>;

///C-tor
ACBCGui::ACBCGui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ACBCGui),m_Core(nullptr),ptr_timer(nullptr),m_ptr_Sensordata(nullptr),
    m_ptr_SensordataFast(nullptr),m_Logfile(),m_PID(),m_TotalCO2(0)
{
    ui->setupUi(this);
    this->m_Core = std::make_unique<Core>();
    ///stylesheets
    this->setStyleSheet("QLCDNumber { color: black ;background-color: white }");

    ///Create and add Leds
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
    QObject::connect(ui->pushButton_CO2,&QPushButton::clicked,this,&ACBCGui::CO2,Qt::UniqueConnection);
}

///D-tor
ACBCGui::~ACBCGui()
{
    m_Core->SetCoreState(CoreState_t::EXIT);
    this->stopTimer();
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
    delete ptr_timer;
    delete ui;
}

///Start pB connected Function
void ACBCGui::Start()
{
    if(m_Core->GetState()==CoreState_t::IDLE)
    {
        m_Core->SetCoreState(CoreState_t::CONFIGURE);
        this->setTimer();
        if(!this->m_Logfile.LogFileCreate("../ACBC/LogFiles/"))
        {
            this->ui->textEdit_Status->append(QString("ERROR: Cannot create Logfile"));
        }
    }

    if(m_Core->GetState()==CoreState_t::STOP)
    {
         m_Core->SetCoreState(CoreState_t::START);
    }

    this->m_PID.SetPID(this->ui->doubleSpinBox_Massflow->value(),2,0.1,0.1,2,2);


}

///Stop pB connected Function
void ACBCGui::Stop()
{
    if(m_Core->GetState()==CoreState_t::START)
    {
        m_Core->SetCoreState(CoreState_t::STOP);
        //this->stopTimer();

    }

}

///Reset pB connected Function
void ACBCGui::Reset()
{
    QDialog *dia = new DialogAUS(this,"Are you sure you want to Reset ?");

    if(dia->exec()==QDialog::Rejected)
    {
        delete dia;
        return void();
    }
    delete dia;

    if(m_Core->GetState()==CoreState_t::ERROR||m_Core->GetState()==CoreState_t::STOP)
    {
        m_Core->SetCoreState(CoreState_t::CONFIGURE);
        if(!this->m_Logfile.LogFileCreate("../ACBC/LogFiles/"))
        {
            this->ui->textEdit_Status->append(QString("ERROR: Cannot create Logfile"));
        }
        this->ui->textEdit_Status->clear();
        this->ui->textEdit_TempRec->clear();
        this->ui->frame_Temperature->clearall();
        this->ui->frame_Pressure->clearall();
    }

     this->m_PID.SetPID(this->ui->doubleSpinBox_Massflow->value(),2,0.1,0.1,2,2);

}

///Quit pB connected Function
void ACBCGui::Quit()
{
    QDialog *dia = new DialogAUS(this,"Are you sure you want to Quit ?");

    if(dia->exec()==QDialog::Rejected)
    {
        delete dia;
        return void();
    }
    delete dia;


    //this->stopTimer();
    //m_Core->SetCoreState(CoreState_t::EXIT);

    this->close();

}


///Mute pB connected Function
void ACBCGui::Mute()
{


}

///Info pB connected Function
void ACBCGui::Info()
{
    QDialog *dia = new DialogPrint(this);
    dia->exec();
    delete dia;
}

void ACBCGui::CO2()
{
    QDialog *dia = new DialogAUS(this,"Are you sure you want to Reset CO2 ?");
    if(dia->exec()==QDialog::Rejected)
    {
        delete dia;
        return void();
    }
    delete dia;

    this->m_TotalCO2 = 0;
    this->ui->lcdNumber_CO2->display(m_TotalCO2);

}

///Timer Triggerd Gui Updating Funtkion
void ACBCGui::UpdateData()
{
    ///TimeStamp
    std::stringstream ss2;
    char buffer [40];
    time_t rawtime;
    time (&rawtime);
    struct tm *timeinfo;
    timeinfo = localtime (&rawtime);
    strftime (buffer,40,"%H:%M:%S",timeinfo);


    ///Get current State form Core and Diplay
    switch (m_Core->GetState()) {
        case CoreState_t::ERROR:
            ss2 << buffer << " ERROR : No connection to alix";
            this->ui->textEdit_Status->append(QString::fromStdString(ss2.str()));
            this->ui->pushButton_Start->setEnabled(false);
            this->ui->pushButton_Stop->setEnabled(false);
            this->ui->pushButton_Mute->setEnabled(false);
            this->ui->pushButton_Reset->setEnabled(true);
            this->ui->pushButton_CO2->setEnabled(false);
            return void();
            break;
        case CoreState_t::START:
            ss2 << buffer << " Running";
            this->ui->textEdit_Status->append(QString::fromStdString(ss2.str()));
            this->ui->pushButton_Start->setEnabled(false);
            this->ui->pushButton_Stop->setEnabled(true);
            this->ui->pushButton_Mute->setEnabled(false);
            this->ui->pushButton_Reset->setEnabled(false);
            this->ui->pushButton_CO2->setEnabled(false);
            this->ui->doubleSpinBox_Massflow->setEnabled(false);
            break;
        case CoreState_t::STOP:
            ss2 << buffer << " Stop";
            this->ui->textEdit_Status->append(QString::fromStdString(ss2.str()));
            this->ui->pushButton_Start->setEnabled(true);
            this->ui->pushButton_Stop->setEnabled(false);
            this->ui->pushButton_Mute->setEnabled(false);
            this->ui->pushButton_Reset->setEnabled(true);
            this->ui->pushButton_CO2->setEnabled(true);
            this->ui->doubleSpinBox_Massflow->setEnabled(true);
            return void();
            break;
        case CoreState_t::EXIT:
            ss2 << buffer << " Exit";
            this->ui->textEdit_Status->append(QString::fromStdString(ss2.str()));
            return void();
            break;
        default:
            break;
    }
    /// Get Data pointer from Core
    this->m_ptr_Sensordata = m_Core->GetData();
    this->m_ptr_SensordataFast = m_Core->GetDataFast();

    /// Diplay Temp T1-T4
    this->ui->lcdNumber_T1->display(m_ptr_Sensordata->ThermoValue[0]);
    this->ui->lcdNumber_T2->display(m_ptr_Sensordata->ThermoValue[1]);
    this->ui->lcdNumber_T3->display(m_ptr_Sensordata->ThermoValue[2]);
    this->ui->lcdNumber_T4->display(m_ptr_Sensordata->ThermoValue[3]);

    /// Display Heater Value and set Led
    this->ui->lcdNumber_T5->display(m_ptr_Sensordata->ThermoValue[4]);
    (m_ptr_Sensordata->ThermoValue[4] < 20 || m_ptr_Sensordata->ThermoValue[4] >60) ? this->Led_T5->setChecked(true) : this->Led_T5->setChecked(false);

    /// Display H1 Value and set Led
    this->ui->lcdNumber_H1->display(m_ptr_Sensordata->DP0);
    m_ptr_Sensordata->DP0-5 > m_ptr_Sensordata->ThermoValue[1] ? this->Led_H1->setChecked(true) : this->Led_H1->setChecked(false);

    /// Display H2 Value and set Led
    this->ui->lcdNumber_H2->display(m_ptr_Sensordata->DP1);
    m_ptr_Sensordata->DP1-5 > m_ptr_Sensordata->ThermoValue[0] ? this->Led_H2->setChecked(true) : this->Led_H2->setChecked(false);

    /// Display H1 Value and set Led
    this->ui->lcdNumber_H3->display(m_ptr_Sensordata->DP2);
    m_ptr_Sensordata->DP2-5 > m_ptr_Sensordata->ThermoValue[3] ? this->Led_H3->setChecked(true) : this->Led_H3->setChecked(false);

    /// Display H1 Value and set Led
    this->ui->lcdNumber_H4->display(m_ptr_Sensordata->DP3);
    m_ptr_Sensordata->DP3-5 > m_ptr_Sensordata->ThermoValue[2] ? this->Led_H4->setChecked(true) : this->Led_H4->setChecked(false);

    /// Display H1 Value and set Led
    this->ui->lcdNumber_g->display(m_ptr_Sensordata->VolValue);
    (m_ptr_Sensordata->VolValue < 50 || m_ptr_Sensordata->VolValue >150) ? this->Led_g->setChecked(true) : this->Led_g->setChecked(false);

    ///T1-T4 to TempRec
    std::stringstream ss;
    ss <<buffer<<"\t"<< m_ptr_Sensordata->ThermoValue[0]<<"\t"<< m_ptr_Sensordata->ThermoValue[1]
           <<"\t"<< m_ptr_Sensordata->ThermoValue[2] <<"\t"<< m_ptr_Sensordata->ThermoValue[3]
           <<"\t"<< m_ptr_Sensordata->ThermoValue[4];
    this->ui->textEdit_TempRec->append(QString::fromStdString(ss.str()));

    /// Display P1 Value and set Led
    this->ui->lcdNumber_P1->display(m_ptr_SensordataFast->P1Value);
    m_ptr_SensordataFast->P1Value < 25 ? this->Led_P1->setChecked(false) : this->Led_P1->setChecked(true);

    /// Display P2 Value and set Led
    this->ui->lcdNumber_P2->display(m_ptr_SensordataFast->P2Value);
    m_ptr_SensordataFast->P2Value < 15 ? this->Led_P2->setChecked(false) : this->Led_P2->setChecked(true);

    /// Display P3 Value and set Led
    this->ui->lcdNumber_P3->display(m_ptr_SensordataFast->P3Value);
    m_ptr_SensordataFast->P3Value < 15 ? this->Led_P3->setChecked(false) : this->Led_P3->setChecked(true);

    /// Display MV1-MV2 Value and set Leds
//    float toleranzmax;
//    toleranzmax = this->ui->doubleSpinBox_v1->value()*1.2;
//    float toleranzmin;
//    toleranzmin = this->ui->doubleSpinBox_v2->value()*0.8;
    this->ui->lcdNumber_v1->display(m_ptr_SensordataFast->MV1Value);
    ((  this->ui->doubleSpinBox_v1->value()-1 <= m_ptr_SensordataFast->MV1Value )&&(this->ui->doubleSpinBox_v1->value()+1 >m_ptr_SensordataFast->MV1Value ))?
                this->Led_MV1->setChecked(false):this->Led_MV1->setChecked(true);
    this->ui->lcdNumber_v2->display(m_ptr_SensordataFast->MV2Value);
    (( this->ui->doubleSpinBox_v2->value()-1 <= m_ptr_SensordataFast->MV2Value) && (this->ui->doubleSpinBox_v2->value()+1 >m_ptr_SensordataFast->MV2Value ))?
                this->Led_MV2->setChecked(false):this->Led_MV2->setChecked(true);

    /// Display MassFlow Value
    this->ui->lcdNumber_massflow->display(m_ptr_SensordataFast->MassValue);

    ///Sum TotalCo2 and Display
    m_TotalCO2 += m_ptr_SensordataFast->MassValue*1/1000;
    this->ui->lcdNumber_CO2->display(m_TotalCO2);

    ///Plot Tempreature
    this->ui->frame_Temperature->PlotGraphs(m_ptr_Sensordata->ThermoValue[0],ui->checkBox_T1->isChecked(),
                                            m_ptr_Sensordata->ThermoValue[1],ui->checkBox_T2->isChecked(),
                                            m_ptr_Sensordata->ThermoValue[2],ui->checkBox_T3->isChecked(),
                                            m_ptr_Sensordata->ThermoValue[3],ui->checkBox_T4->isChecked());
    ///Plot Pressure
    this->ui->frame_Pressure->PlotGraphs(m_ptr_SensordataFast->P1Value,ui->checkBox_P1->isChecked()
                                         ,m_ptr_SensordataFast->P2Value,ui->checkBox_P2->isChecked()
                                         ,m_ptr_SensordataFast->P3Value,ui->checkBox_P3->isChecked()
                                         ,m_ptr_SensordataFast->MassValue,ui->checkBox_Massf->isChecked());

    if(this->ui->checkBox_Mv->isChecked())
    {
        this->ui->doubleSpinBox_v1->setEnabled(true);
        this->ui->doubleSpinBox_v2->setEnabled(true);
        this->ui->doubleSpinBox_Massflow->setEnabled(false);
        m_ptr_SensordataFast->MV1Out = static_cast<float>(this->ui->doubleSpinBox_v1->value());
        m_ptr_SensordataFast->MV2Out = static_cast<float>(this->ui->doubleSpinBox_v2->value());
    }else
    {
        this->ui->doubleSpinBox_v1->setEnabled(false);
        this->ui->doubleSpinBox_v2->setEnabled(false);
        //this->ui->doubleSpinBox_Massflow->setEnabled(true);
        this->m_PID.UpdatePID(m_ptr_SensordataFast->MassValue);
        m_ptr_SensordataFast->MV1Out = this->m_PID.GetOut();
        this->ui->doubleSpinBox_v1->setValue(this->m_PID.GetOut());

    }

    if(this->m_Logfile.CheckLogFile())
        this->m_Logfile.LogFileWrite(m_ptr_Sensordata,m_ptr_SensordataFast,buffer);


}








