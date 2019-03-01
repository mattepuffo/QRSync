#ifndef DIALOGADD_H
#define DIALOGADD_H

#include <QDialog>
#include <QMessageBox>
#include <QLineEdit>
#include <QFileDialog>
#include <QPushButton>
#include "database.h"

#include <QDebug>

namespace Ui {
class DialogAdd;
}

class DialogAdd : public QDialog {
    Q_OBJECT

public:
    explicit DialogAdd(int id = 0, QWidget *parent = nullptr);
    virtual ~DialogAdd();

private slots:
    void addSync();
    void upSync(int id);
    void setDir(QLineEdit *txt);

private:
    QMap<QString, QString> syncMap;
    Ui::DialogAdd *ui;
    QString dir;
    Database db;
};

#endif // DIALOGADD_H
