#include "acbcgui.h"
#include "ui_acbcgui.h"

ACBCGui::ACBCGui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ACBCGui)
{
    ui->setupUi(this);
}

ACBCGui::~ACBCGui()
{
    delete ui;
}
