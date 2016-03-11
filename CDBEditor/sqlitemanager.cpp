#include "sqlitemanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QDebug>

sqliteManager::sqliteManager(const QString& path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if (!m_db.open())
    {
       qDebug() << "Error: connection with database fail";
    }
    else
    {
       qDebug() << "Database: connection ok";
    }
}

sqliteManager::~sqliteManager()
{
    if (m_db.isOpen())
    {
        m_db.close();
    }
}

bool sqliteManager::isOpen() const
{
    return m_db.isOpen();
}

void sqliteManager::listSeriesD()
{
    qDebug() << "Persons in db:";
    QSqlQuery query("SELECT id, title FROM SeriesD ORDER BY title");
    int idName = query.record().indexOf("title");
    while (query.next())
    {
        QString name = query.value(idName).toString();
        qDebug() << "===" << name;
    }
}
