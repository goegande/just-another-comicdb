#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QStringListModel>

namespace Ui {
class MainWindow;
}

typedef struct sConent{
    int sID;
    QString title;
    int number;
    int part;
} content;

typedef QVector<content> contentVector;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QSqlDatabase m_db;
    QSqlQuery querySeriesD;
    QSqlQuery querySeriesO;
    QStringList listContent;
    QSqlQueryModel modelSeriesD;
    QSqlQueryModel modelSeriesO;
    QStringListModel modelContent;
    contentVector contentList;

    int selectedLineInOrig;

private slots:
    void checkPub();
    void updateTree();
    void fillSeriesD();
    void fillSeriesOrig();
    void fillExpectedNextPUB();
    void on_butAddSeriesD_clicked();
    void updateContent();
    void on_butAddReprint_clicked();
    void on_listWidget_clicked(const QModelIndex &index);
    void on_butRemoveLine_clicked();
    void on_tabWidget_tabBarClicked(int index);
};

#endif // MAINWINDOW_H
