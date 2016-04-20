#include "dialogaus.h"
#include "ui_dialogaus.h"


DialogAUS::DialogAUS(QWidget *parent, const QString info) :
    QDialog(parent),
    ui(new Ui::DialogAUS)
{
    ui->setupUi(this);
    //QPixmap *pic = new QPixmap("../ACBC/Dialogs/exmark2.jpeg");
    QPixmap pic("../ACBC/Dialogs/exmark2.jpeg");
    this->ui->label_pic->setPixmap(pic);

    this->ui->label_info->setText(info);
}

DialogAUS::~DialogAUS()
{
    delete ui;
}
