#ifndef SQLITEMANAGER_H
#define SQLITEMANAGER_H

#include <QSqlDatabase>

class sqliteManager
{
public:
    sqliteManager(const QString& path);
    ~sqliteManager();

    bool isOpen() const;
    void listSeriesD();

private:
    QSqlDatabase m_db;
};

#endif // SQLITEMANAGER_H
