#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialognewseriesorig.h"

#include <QDebug>
#include <QDir>
#include <QStandardItemModel>
#include <QSqlError>

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
    querySeriesD = QSqlQuery("SELECT title, id FROM SeriesD ORDER BY complete, title");
    modelSeriesD.setQuery(querySeriesD);
    ui->cbSeriesD->setModel(&modelSeriesD);
}

void MainWindow::fillSeriesOrig()
{
    querySeriesO = QSqlQuery("SELECT title, id FROM SeriesORIG ORDER BY title");
    modelSeriesO.setQuery(querySeriesO);
    ui->cbSeriesOrig->setModel(&modelSeriesO);
    ui->cbSeriesOrig->setCurrentIndex(0);
}

void MainWindow::fillExpectedNextPUB()
{
    QSqlQuery query("SELECT max(id) FROM publication");
    int n = 1;
    if (query.next()) n = query.value(0).toInt()+1;
    QString number = QString("%1").arg(n);
    ui->pubNo->setText(number);
}

void MainWindow::checkPub(){
    qDebug() << "Entered...";
}

void MainWindow::updateTree()
{
    QSqlQuery q("SELECT d.title as serie, p.issue as ausgabe, p.variant, e.title, r.reprintsISSUE, r.reprintsSUBPART FROM publication as p JOIN reprint as r ON r.publication = p.id JOIN SeriesD as d ON p.series = d.id JOIN SeriesORIG as e ON r.reprintsSERIES = e.id ORDER BY serie, ausgabe");
    QStandardItemModel *m = new QStandardItemModel(this);
    QStandardItem *seriesItem;
    QStandardItem *issueItem;
    QString prevSeries;
    QString prevIssue;
    int childrenS = 0, childrenI = 0;
    while(q.next()) {
        QString issue = q.value(1).toString();
        QString series = q.value(0).toString();
        QString reprint = q.value(3).toString() + " " + q.value(4).toString();
        if ((!q.value(5).toString().isEmpty())&&(q.value(5).toInt()>0)) reprint += " Part " + q.value(5).toString();
        if (prevSeries != series) {
            childrenS = 0;
            prevIssue = "";
            seriesItem = new QStandardItem(series);
            m->appendRow(seriesItem);
            prevSeries = series;
        }
        if (prevIssue != issue) {
            childrenI = 0;
            issueItem = new QStandardItem(issue);
            seriesItem->setChild(childrenS, issueItem);
            prevIssue = issue;
            ++childrenS;
        }
        QStandardItem *item = new QStandardItem(reprint);
        issueItem->setChild(childrenI, item);
        ++childrenI;
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
    if (querySeriesO.seek(c.sID))
        c.tID = querySeriesO.value(1).toInt();
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


void MainWindow::on_buttSave_clicked()
{
    //Add publication
    QString cmdlt = "INSERT INTO publication VALUES(";
    cmdlt+=ui->pubNo->text() + ", ";
    if (querySeriesD.seek(ui->cbSeriesD->currentIndex())){
        cmdlt+=querySeriesD.value(1).toString() + ", ";
        cmdlt+=ui->issue->text() + ", 0);";
        qDebug() << "Trying to execute " << cmdlt;
        QSqlQuery q;
        if (!q.exec(cmdlt))
            qDebug() << q.lastError().text();
        else{
            qDebug() << "OKAY";
            contentVector::const_iterator _i = contentList.begin();
            for (;_i!=contentList.end();_i++){
                cmdlt  = "INSERT INTO reprint VALUES(";
                cmdlt +=ui->pubNo->text() + ", ";;
                cmdlt += QString::number(_i->tID) + ", ";
                cmdlt += QString::number(_i->number) + ", ";
                cmdlt += QString::number(_i->part) + ");";
                qDebug() << "Trying to execute " << cmdlt;
                QSqlQuery q;
                if (!q.exec(cmdlt)){
                    qDebug() << q.lastError().text();
                    return;
                }
                else{
                    qDebug() << "OKAY";
                }
            }
            ui->issue->clear();
            fillExpectedNextPUB();
            updateTree();
            contentList.clear();
            updateContent();
        }
    }
}

void MainWindow::on_issue_textChanged(const QString &arg1)
{
    ui->buttSave->setEnabled(!arg1.isEmpty());
}

void MainWindow::on_butAddSeriesEN_clicked()
{
    DialogNewSeriesOrig d;
    d.exec();
    fillSeriesOrig();
}
