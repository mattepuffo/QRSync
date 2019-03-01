#include "sync.h"

Sync::Sync() {}

Sync::~Sync() {
}

int Sync::getId() const {
    return id;
}

void Sync::setId(const int &value) {
    id = value;
}

QString Sync::getNome() const {
    return nome;
}

void Sync::setNome(const QString &value) {
    nome = value;
}

QString Sync::getComando() const {
    return comando;
}

void Sync::setComando(const QString &value) {
    comando = value;
}

QString Sync::getSource() const {
    return source;
}

void Sync::setSource(const QString &value) {
    source = value;
}

QString Sync::getDestination() const {
    return destination;
}

void Sync::setDestination(const QString &value) {
    destination = value;
}
