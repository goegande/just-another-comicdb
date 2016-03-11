#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include "sqlitemanager.h"

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
    sqliteManager *m_sql;

private slots:
    void checkPub();
};

#endif // MAINWINDOW_H
