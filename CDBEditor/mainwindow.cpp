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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::checkPub(){

}

void MainWindow::on_butAddSeriesD_clicked()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("GComicsDB.db");
    QDir *dir = new QDir();
    qDebug() << dir->absolutePath();
    if (!m_db.open())
    {
       qDebug() << "Error: connection with database fail";
    }
    else
    {
       qDebug() << "Database: connection ok";
    }
    QSqlQuery* query = new QSqlQuery(m_db);
    query->prepare("SELECT * FROM SeriesD ORDER BY title");
    query->exec();
    QSqlQueryModel *modelSeriesD = new QSqlQueryModel;
    modelSeriesD->setQuery(*query);
    m_db.close();
    qDebug() << modelSeriesD->rowCount();

    ui->tableView->setModel(modelSeriesD);

}
