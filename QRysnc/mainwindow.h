#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QScreen>
#include <QGuiApplication>
#include <QStyle>
#include <QAction>
#include <QPushButton>
#include <QSplitter>
#include <QTableWidget>
#include <QMessageBox>
#include <QHeaderView>
#include <QProcess>
#include <QVBoxLayout>
#include <QPlainTextEdit>
#include "database.h"
#include "dialogadd.h"
#include "sync.h"

#include <QDebug>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();

private slots:
    void about();
    void addSync();
    void upSync(QTableWidgetItem *item);
    void delSync(QTableWidgetItem *item);
    void execSync(QString cmd);
    void getSync();
    void readOutput();
    void readError();

private:
    // METODI
    void createMenu();
    void createActions();
    void createMainLayout();
    // VARIABILI
    QMenu *fileMenu;
    QMenu *helpMenu;
    QAction *addSyncAction;
    QAction *refreshAction;
    QAction *exitAction;
    QAction *aboutAction;
    QTableWidget *tbl;
    Database db;
    QPlainTextEdit *resEdit;
    QList<Sync> list;
};

#endif // MAINWINDOW_H
