#include "dialognewseriesorig.h"
#include "ui_dialognewseriesorig.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QAbstractButton>

DialogNewSeriesOrig::DialogNewSeriesOrig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNewSeriesOrig)
{
    ui->setupUi(this);
    QSqlQuery q("SELECT title FROM SeriesORIG ORDER BY title");
    q.first();
    while(q.next()) list.append(q.value(0).toString());
    on_lineEdit_textChanged(ui->lineEdit->text());
    ui->lineEdit->setFocus();
}

DialogNewSeriesOrig::~DialogNewSeriesOrig()
{
    delete ui;
}

void DialogNewSeriesOrig::on_lineEdit_textChanged(const QString &arg1)
{
    QStringList tmp(list);
    tmp.append(arg1);
    tmp.sort();
    int index = tmp.indexOf(arg1);
    if (index>0) ui->m1->setText(tmp[index-1]); else ui->m1->clear();
    if (index>1) ui->m2->setText(tmp[index-2]); else ui->m2->clear();
    if (index>2) ui->m3->setText(tmp[index-3]); else ui->m3->clear();
    if (index>3) ui->m4->setText(tmp[index-4]); else ui->m4->clear();
    if (index+1 < tmp.length()) ui->p1->setText(tmp[index+1]); else ui->p1->clear();
    if (index+2 < tmp.length()) ui->p2->setText(tmp[index+2]); else ui->p2->clear();
    if (index+3 < tmp.length()) ui->p3->setText(tmp[index+3]); else ui->p3->clear();
    if (index+4 < tmp.length()) ui->p4->setText(tmp[index+4]); else ui->p4->clear();
}

void DialogNewSeriesOrig::on_buttonBox_accepted()
{

}

void DialogNewSeriesOrig::on_buttonBox_clicked(QAbstractButton *button)
{
    if (button->text()=="OK")
    {
        QString c = "INSERT INTO SeriesORIG VALUES(null,\"";
        c+=ui->lineEdit->text() + "\");";
        qDebug() << "Trying to execute " << c;
        QSqlQuery q;
        if (!q.exec(c)){
            qDebug() << q.lastError().text();
            return;
        }
        else{
            qDebug() << "OKAY";
            emit accept();
        }
    }
    else
        emit reject();
}
