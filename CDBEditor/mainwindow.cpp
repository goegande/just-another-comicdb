#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_sql = new sqliteManager("../GComicsDB.db");
    if (m_sql != NULL)
    {
        //m_sql->getNextPub()
        m_sql->listSeriesD();
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::checkPub(){

}
