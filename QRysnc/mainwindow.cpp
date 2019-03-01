#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QScreen *screen = QGuiApplication::primaryScreen();
    QSize size = screen->availableGeometry().size() * 0.8;
    setGeometry(
                QStyle::alignedRect(
                    Qt::LeftToRight,
                    Qt::AlignCenter,
                    size,
                    QGuiApplication::primaryScreen()->availableGeometry()
                    )
                );
    this->setWindowTitle("QRsync");
    this->setMinimumWidth(800);
    this->setMinimumHeight(600);

    createActions();
    createMenu();
    createMainLayout();

    //DialogAdd *da = new DialogAdd();
    //da->show();
}

void MainWindow::createActions() {
    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcuts(QKeySequence::Quit);
    connect(exitAction, &QAction::triggered, this, &QWidget::close);

    addSyncAction = new QAction(tr("&Aggiungi sync"), this);
    addSyncAction->setShortcut(Qt::Key_A | Qt::CTRL);
    connect(addSyncAction, &QAction::triggered, this, &MainWindow::addSync);

    refreshAction = new QAction(tr("&Rinfresca sync"), this);
    refreshAction->setShortcut(QKeySequence::Refresh);
    connect(refreshAction, &QAction::triggered, this, &MainWindow::getSync);

    aboutAction = new QAction(tr("&About"), this);
    aboutAction->setShortcut(Qt::Key_Apostrophe | Qt::CTRL);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::about);
}

void MainWindow::createMenu() {
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(addSyncAction);
    fileMenu->addAction(refreshAction);
    fileMenu->addAction(exitAction);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
}

void MainWindow::createMainLayout() {
    QStringList header;
    header << "ID"
           << "NOME"
           << "COMANDO"
           << "SOURCE"
           << "DESTINAZIONE"
           << ""
           << ""
           << "";

    tbl = new QTableWidget();
    tbl->setColumnCount(header.length());
    tbl->horizontalHeader()->show();
    tbl->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tbl->verticalHeader()->setVisible(false);
    tbl->setHorizontalHeaderLabels(header);
    tbl->setContextMenuPolicy(Qt::CustomContextMenu);
    tbl->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tbl->setUpdatesEnabled(true);
    getSync();

    resEdit = new QPlainTextEdit;

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(tbl);
    layout->addWidget(resEdit);

    QWidget *window = new QWidget;
    window->setLayout(layout);
    this->setCentralWidget(window);
}

void MainWindow::getSync() {
    if (list.length() > 0) {
        list.clear();
        tbl->setRowCount(0);
    }

    int rows = 0;
    list = db.getAll();
    QList<Sync>::const_iterator iter;
    for (iter = list.constBegin(); iter != list.constEnd(); ++iter) {
        const Sync &sync = *iter;
        tbl->insertRow(tbl->rowCount());
        tbl->setItem(rows, 0, new QTableWidgetItem(QString::number(sync.getId())));
        tbl->setItem(rows, 1, new QTableWidgetItem(sync.getNome()));
        tbl->setItem(rows, 2, new QTableWidgetItem(sync.getComando()));
        tbl->setItem(rows, 3, new QTableWidgetItem(sync.getSource()));
        tbl->setItem(rows, 4, new QTableWidgetItem(sync.getDestination()));

        QPushButton *btnModifica = new QPushButton("Modifica");
        btnModifica->setStyleSheet("QPushButton {"
                                   "background-color: yellow"
                                   "}");
        QPushButton *btnCancella = new QPushButton("Cancella");
        btnCancella->setStyleSheet("QPushButton {"
                                   "background-color: red"
                                   "}");
        QPushButton *btnEsegui = new QPushButton("Esegui");
        btnEsegui->setStyleSheet("QPushButton {"
                                 "background-color: green"
                                 "}");
        tbl->setIndexWidget(tbl->model()->index(rows, 5), btnModifica);
        tbl->setIndexWidget(tbl->model()->index(rows, 6), btnCancella);
        tbl->setIndexWidget(tbl->model()->index(rows, 7), btnEsegui);
        QString cmdTotal(tbl->item(rows, 2)->text() + " " + " " + tbl->item(rows, 3)->text() + " " + tbl->item(rows, 4)->text());
        connect(btnCancella, &QPushButton::clicked, this, std::bind(&MainWindow::delSync, this, tbl->item(rows, 0)));
        connect(btnModifica, &QPushButton::clicked, this, std::bind(&MainWindow::upSync, this, tbl->item(rows, 0)));
        connect(btnEsegui, &QPushButton::clicked, this, std::bind(&MainWindow::execSync, this, cmdTotal));
        rows++;
    }
}

void MainWindow::execSync(QString cmd) {
    //rsync -av --delete /run/media/matte/MATTE150/Personal/ /home/matte/Personal
    QProcess *process = new QProcess;
    if (process) {
        process->setEnvironment(QProcess::systemEnvironment());
        process->setProcessChannelMode(QProcess::MergedChannels);
        process->start(cmd);
        process->waitForStarted();
        connect(process, &QProcess::readyReadStandardOutput, this, &MainWindow::readOutput);
        connect(process, &QProcess::readyReadStandardError, this, &MainWindow::readError);
    }
}

void MainWindow::readOutput() {
    QProcess *process = dynamic_cast<QProcess *>(sender());
    if (process) {
        resEdit->appendPlainText(process->readAllStandardOutput());
    }
}

void MainWindow::readError() {
    QProcess *process = dynamic_cast<QProcess *>(sender());
    if (process) {
        QPalette p = resEdit->palette();
        p.setColor(QPalette::Text, Qt::red);
        resEdit->setPalette(p);
        resEdit->appendPlainText(process->readAllStandardError());
    }
}

void MainWindow::delSync(QTableWidgetItem *item) {
    db.delSync(item->text().toInt());
    createMainLayout();
}

void MainWindow::upSync(QTableWidgetItem *item) {
    DialogAdd *da = new DialogAdd(item->text().toInt());
    da->show();
}

void MainWindow::addSync() {
    DialogAdd *da = new DialogAdd();
    da->show();
}

void MainWindow::about() {
    QMessageBox::about(
                this,
                tr("About"),
                tr("GUI for rsync")
                );
}

MainWindow::~MainWindow() {
    //delete this;
}
