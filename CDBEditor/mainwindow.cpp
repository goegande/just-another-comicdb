#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDebug>
#include <QDir>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fillSeriesD();
    fillSeriesOrig();
    fillExpectedNextPUB();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fillSeriesD(){
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("GComicsDB.db");
    if (!m_db.open())
    {
       qDebug() << "Error: connection with database fail";
    }
    else
    {
       qDebug() << "Database: connection ok";
    }
    QSqlQuery* query = new QSqlQuery("SELECT title FROM SeriesD ORDER BY title");
    QSqlQueryModel *modelSeriesD = new QSqlQueryModel;
    modelSeriesD->setQuery(*query);
    m_db.close();
    qDebug() << modelSeriesD->rowCount();

    ui->cbSeriesD->setModel(modelSeriesD);
}

void MainWindow::fillSeriesOrig()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("GComicsDB.db");
    if (!m_db.open())
    {
       qDebug() << "Error: connection with database fail";
    }
    else
    {
       qDebug() << "Database: connection ok";
    }
    QSqlQuery* query = new QSqlQuery("SELECT title FROM SeriesORIG ORDER BY title");
    QSqlQueryModel *modelSeries = new QSqlQueryModel;
    modelSeries->setQuery(*query);
    m_db.close();
    ui->cbSeriesOrig->setModel(modelSeries);
}

void MainWindow::fillExpectedNextPUB()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("GComicsDB.db");
    if (!m_db.open())
    {
       qDebug() << "Error: connection with database fail";
    }
    else
    {
       qDebug() << "Database: connection ok";
    }
    QSqlQuery* query = new QSqlQuery("SELECT max(id) FROM publication");
    m_db.close();
    query->first();
    QString number = QString("%1").arg(query->value(0).toInt()+1, 6, 10, QChar('0'));
    number.prepend("PUB");
    ui->pubNo->setText(number);
}

void MainWindow::checkPub(){
    qDebug() << "Entered...";
}

void MainWindow::on_butAddSeriesD_clicked()
{

}
