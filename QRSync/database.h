#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QDir>
#include <QSqlQuery>
#include "sync.h"

#include <QDebug>

class Database {

public:
    Database();
    virtual ~Database();
    void addSync(QString nome, QString comando, QString source, QString destination);
    void upSync(int id, QString nome, QString comando, QString source, QString destination);
    void delSync(int id);
    QList<Sync> getAll();
    Sync getById(int id);
};

#endif // DATABASE_H
