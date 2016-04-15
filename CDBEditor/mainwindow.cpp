#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QDir>
#include <QStandardItemModel>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    selectedLineInOrig = -1;
    ui->setupUi(this);

    //connect to DB
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("GComicsDB.db");
    if (!m_db.open())
    {
       qDebug() << "Error: connection with database fail";
       return;
    }
    fillSeriesD();
    fillSeriesOrig();
    fillExpectedNextPUB();
    updateTree();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fillSeriesD(){
    querySeriesD = QSqlQuery("SELECT title FROM SeriesD ORDER BY title");
    modelSeriesD.setQuery(querySeriesD);
    ui->cbSeriesD->setModel(&modelSeriesD);
}

void MainWindow::fillSeriesOrig()
{
    querySeriesO = QSqlQuery("SELECT title FROM SeriesORIG ORDER BY title");
    modelSeriesO.setQuery(querySeriesO);
    ui->cbSeriesOrig->setModel(&modelSeriesO);
}

void MainWindow::fillExpectedNextPUB()
{
    QSqlQuery query("SELECT max(id) FROM publication");
    query.first();
    QString number = QString("%1").arg(query.value(0).toInt()+1, 6, 10, QChar('0'));
    number.prepend("PUB");
    ui->pubNo->setText(number);
}

void MainWindow::checkPub(){
    qDebug() << "Entered...";
}

void MainWindow::updateTree()
{
    QSqlQuery q("SELECT d.title as serie, p.issue as ausgabe, p.variant, e.title, r.reprintsISSUE, r.reprintsSUBPART FROM publication as p JOIN reprint as r ON r.publication = p.id JOIN SeriesD as d ON p.series = d.id JOIN SeriesORIG as e ON r.reprintsSERIES = e.id ORDER BY serie, ausgabe");
    QStandardItemModel *m = new QStandardItemModel(this);
    QStandardItem *parent;
    QString prevClass;
    QString prevIssue;
    int children = 0;
    while(q.next()) {
        QString issue = q.value(1).toString();
        QString className = q.value(0).toString();
        int id = q.value(1).toInt();
        if (prevClass != className) {
            children = 0;
            parent = new QStandardItem(className);
            m->appendRow(parent);
            prevClass = className;
        }
        QStandardItem *item = new QStandardItem(issue);
        parent->setChild(children, item);
        ++children;
    }
    ui->treeViewDB->setModel(m);
}

void MainWindow::on_butAddSeriesD_clicked()
{

}

void MainWindow::updateContent()
{
    ui->listWidget->clear();
    contentVector::const_iterator _i = contentList.begin();
    for (;_i!=contentList.end();_i++){
        QString tmp;
        tmp = _i->title + " Issue " + QString::number(_i->number);
        if (_i->part>0){
            tmp += " Part " + QString::number(_i->part);
        }
        new QListWidgetItem(tmp,ui->listWidget);
    }
    ui->butRemoveLine->setEnabled(false);
    selectedLineInOrig = -1;
    ui->issueEN->clear();
    ui->isuuePart->clear();
    ui->cbSeriesOrig->setFocus();
}

void MainWindow::on_butAddReprint_clicked()
{
    content c;
    QString tmp;
    c.sID = ui->cbSeriesOrig->currentIndex();
    c.title = ui->cbSeriesOrig->currentText();
    c.number = ui->issueEN->text().toInt();
    tmp = c.title + " Issue " + ui->issueEN->text();
    QString buf = ui->isuuePart->text();
    c.part = 0;
    if (buf.length()>0){
        c.part = buf.toInt();
        tmp += " Part " + buf;
    }
    if (selectedLineInOrig>=0)
        contentList[selectedLineInOrig]=c;
    else
        contentList.append(c);
    listContent.append(tmp);
    updateContent();
}

void MainWindow::on_listWidget_clicked(const QModelIndex &index)
{
    ui->butRemoveLine->setEnabled(true);
    selectedLineInOrig = index.row();
    ui->cbSeriesOrig->setCurrentIndex(contentList[selectedLineInOrig].sID);
    ui->issueEN->setText(QString::number(contentList[selectedLineInOrig].number));
    if (contentList[selectedLineInOrig].part>0)
        ui->isuuePart->setText(QString::number(contentList[selectedLineInOrig].part));
    else
        ui->isuuePart->clear();

}

void MainWindow::on_butRemoveLine_clicked()
{
    contentList.removeAt(selectedLineInOrig);
    updateContent();
}

void MainWindow::on_tabWidget_tabBarClicked(int index)
{

}
