#ifndef DIALOGAUS_H
#define DIALOGAUS_H

#include <QDialog>
#include<QString>

namespace Ui {
    class DialogAUS;
    }

class DialogAUS : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAUS(QWidget *parent = 0, const QString info="");
    ~DialogAUS();

private:
    Ui::DialogAUS *ui;
};

#endif // DIALOGAUS_H
