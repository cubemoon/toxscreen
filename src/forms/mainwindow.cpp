#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    pTox(nullptr)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setTox(QTox *tox)
{
    pTox = tox;

    // Set address text field
    QString addressHex(pTox->getAddress().toHex().toUpper());
    ui->toxIdLineEdit->setText(addressHex);
    ui->toxIdLineEdit->setCursorPosition(0);
}
