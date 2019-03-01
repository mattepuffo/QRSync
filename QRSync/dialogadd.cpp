#include "dialogadd.h"
#include "ui_dialogadd.h"

DialogAdd::DialogAdd(int id, QWidget *parent) : QDialog(parent), ui(new Ui::DialogAdd) {
    ui->setupUi(this);

    syncMap.insert("*", "Scegli Sync");
    syncMap.insert("rsync -av --delete", "Sincronizzazione");
    syncMap.insert("rsync -av", "Copia");
    ui->comboBox->addItems(QStringList(syncMap.values()));

    connect(ui->btnSource, &QPushButton::clicked, this, std::bind(&DialogAdd::setDir,this,ui->txtSource));
    connect(ui->btnDestinazione, &QPushButton::clicked, this, std::bind(&DialogAdd::setDir, this, ui->txtDestinazione));

    if (id != 0) {
        Sync sync = db.getById(id);
        ui->txtNome->setText(sync.getNome());
        ui->txtSource->setText(sync.getSource());
        ui->txtDestinazione->setText(sync.getDestination());

        for (auto s : syncMap.keys()) {
            if (s == sync.getComando()) {
                ui->comboBox->setCurrentText(syncMap.value(s));
            }
        }

        connect(ui->btnSalva, &QPushButton::clicked, this, std::bind(&DialogAdd::upSync, this, id));
    } else {
        connect(ui->btnSalva, &QPushButton::clicked, this, &DialogAdd::addSync);
    }
}

void DialogAdd::addSync() {
    QMessageBox msgBox;
    QString nome = ui->txtNome->text();
    QString selValue = ui->comboBox->currentText();
    QString selKey = (syncMap.cbegin() + ui->comboBox->currentIndex()).key();
    QString source = ui->txtSource->text() + "/";
    QString destination = ui->txtDestinazione->text();

    if (!nome.isEmpty() && selKey != '*' && !source.isEmpty() && !destination.isEmpty()) {
        db.addSync(nome.trimmed(), selKey, source, destination);
        msgBox.setText("Sync inserito");
        msgBox.exec();
        this->close();
    } else {
        msgBox.setText("Tutti i campi sono obbligatori!");
        msgBox.exec();
    }
}

void DialogAdd::upSync(int id) {
    QMessageBox msgBox;
    QString nome = ui->txtNome->text();
    QString selValue = ui->comboBox->currentText();
    QString selKey = (syncMap.cbegin() + ui->comboBox->currentIndex()).key();
    QString source = ui->txtSource->text();

    if (source.at(source.length() - 1) != "/") {
        source.append("/");
    }

    QString destination = ui->txtDestinazione->text();

    if (!nome.isEmpty() && selKey != '*' && !source.isEmpty() && !destination.isEmpty()) {
        db.upSync(id, nome.trimmed(), selKey, source, destination);
        msgBox.setText("Sync modificato");
        msgBox.exec();
        this->close();
    } else {
        msgBox.setText("Tutti i campi sono obbligatori!");
        msgBox.exec();
    }
}

void DialogAdd::setDir(QLineEdit *txt) {
    dir = QFileDialog::getExistingDirectory(this, tr("Scegli directory"), QDir::homePath(), QFileDialog::ShowDirsOnly);
    txt->setText(dir);
}

DialogAdd::~DialogAdd() {
    delete ui;
}
