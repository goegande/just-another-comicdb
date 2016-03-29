#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QSqlDatabase>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QSqlDatabase m_db;

private slots:
    void checkPub();
    void fillSeriesD();
    void fillSeriesOrig();
    void fillExpectedNextPUB();
    void on_butAddSeriesD_clicked();
};

#endif // MAINWINDOW_H
