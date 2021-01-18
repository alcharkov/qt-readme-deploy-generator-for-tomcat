#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "element.h"
#include <QList>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
\

void MainWindow::on_makeButton_clicked()
{

    this->genText = new GenerateText();
    Element *elApp = new Element("app", ui->appListWidget->selectedItems(), ui->appSpinBox->value());
    Element *elApi = new Element("api", ui->apiListWidget->selectedItems(), ui->apiSpinBox->value());
    Element *elSvc = new Element("svc", ui->svcListWidget->selectedItems(), ui->svcSpinBox->value());


    ui->generatedTextEdit->setPlainText(this->genText->build({elApp, elApi, elSvc}, ui->dbUpdateCheckBox->isChecked(), ui->dbRollbackCheckbox->isChecked(), ui->webCheckBox->isChecked()));
}
