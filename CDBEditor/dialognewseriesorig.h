#ifndef DIALOGNEWSERIESORIG_H
#define DIALOGNEWSERIESORIG_H

#include <QDialog>
#include <QStringList>
#include <QAbstractButton>

namespace Ui {
class DialogNewSeriesOrig;
}

class DialogNewSeriesOrig : public QDialog
{
    Q_OBJECT

public:
    explicit DialogNewSeriesOrig(QWidget *parent = 0);
    ~DialogNewSeriesOrig();

private slots:
    void on_lineEdit_textChanged(const QString &arg1);

    void on_buttonBox_accepted();

    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::DialogNewSeriesOrig *ui;
    QStringList list;
};

#endif // DIALOGNEWSERIESORIG_H
