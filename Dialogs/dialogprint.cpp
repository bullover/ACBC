#include "dialogprint.h"
#include "ui_dialogprint.h"

DialogPrint::DialogPrint(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogPrint)
{
    ui->setupUi(this);
    QPixmap pic("../ACBC/Dialogs/blueprint.png");
    this->ui->label_print->setPixmap(pic);

}

DialogPrint::~DialogPrint()
{
    delete ui;
}
