#include "acbcgui.h"
#include "ui_acbcgui.h"
#include <QGridLayout>

ACBCGui::ACBCGui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ACBCGui)
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
}
    ///Add Leds














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
