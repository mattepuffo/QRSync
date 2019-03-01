#ifndef SYNC_H
#define SYNC_H

#include <QObject>

class Sync {

public:
    Sync();
    Sync(const Sync &other) = default;
    Sync &operator = (const Sync &other) = default;
    virtual ~Sync();

    int getId() const;
    void setId(const int &value);
    QString getNome() const;
    void setNome(const QString &value);
    QString getComando() const;
    void setComando(const QString &value);
    QString getSource() const;
    void setSource(const QString &value);
    QString getDestination() const;
    void setDestination(const QString &value);

private:
    int id;
    QString nome;
    QString comando;
    QString source;
    QString destination;
};

#endif // SYNC_H
