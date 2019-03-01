#include "database.h"

Database::Database() {
    QString fileDb = QDir::currentPath() + "/sync.db";
//    QString fileDb = "/run/media/matte/PUFFA/Project/CPP/QRysnc/sync.db";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(fileDb);
    db.open();
}

void Database::addSync(QString nome, QString comando, QString source, QString destination) {
    QSqlDatabase db = QSqlDatabase::database();
    if (db.isOpen()) {
        QSqlQuery query;
        query.prepare("INSERT OR REPLACE INTO sync (nome, comando, source, destination) "
                      "VALUES (:nome, :comando, :source, :destination)");
        query.bindValue(":nome", nome);
        query.bindValue(":comando", comando);
        query.bindValue(":source", source);
        query.bindValue(":destination", destination);
        query.exec();
        db.close();
    }
}

void Database::upSync(int id, QString nome, QString comando, QString source, QString destination) {
    QSqlDatabase db = QSqlDatabase::database();
    if (db.isOpen()) {
        QSqlQuery query;
        query.prepare("UPDATE sync "
                      "SET nome = :nome, comando = :comando, source = :source, destination = :destination "
                      "WHERE id = :id");
        query.bindValue(":nome", nome);
        query.bindValue(":comando", comando);
        query.bindValue(":source", source);
        query.bindValue(":destination", destination);
        query.bindValue(":id", id);
        query.exec();
        db.close();
    }
}

QList<Sync> Database::getAll() {
    QList<Sync> list;
    QSqlDatabase db = QSqlDatabase::database();
    if (db.isOpen()) {
        QSqlQuery query("SELECT * FROM sync");
        while (query.next()) {
            Sync sync;
            sync.setId(query.value("id").toInt());
            sync.setNome(query.value("nome").toString());
            sync.setComando(query.value("comando").toString());
            sync.setSource(query.value("source").toString());
            sync.setDestination(query.value("destination").toString());
            list.append(sync);
        }
        db.close();
    }

    return list;
}

Sync Database::getById(int id) {
    Sync sync;
    QSqlDatabase db = QSqlDatabase::database();
    if (db.isOpen()) {
        QSqlQuery query;
        query.prepare("SELECT * FROM sync WHERE id = :id");
        query.bindValue(":id", id);
        query.exec();
        while (query.next()) {
            sync.setId(query.value("id").toInt());
            sync.setNome(query.value("nome").toString());
            sync.setComando(query.value("comando").toString());
            sync.setSource(query.value("source").toString());
            sync.setDestination(query.value("destination").toString());
        }
        db.close();
    }

    return sync;
}

void Database::delSync(int id) {
    QSqlDatabase db = QSqlDatabase::database();
    if (db.isOpen()) {
        QSqlQuery query;
        query.prepare("DELETE FROM sync WHERE id = :id");
        query.bindValue(":id", id);
        query.exec();
        db.close();
    }
}

Database::~Database() {
    QSqlDatabase db = QSqlDatabase::database();
    if (db.isOpen()) {
        db.close();
    }
}
