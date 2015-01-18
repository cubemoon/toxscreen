#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    pTox(nullptr),
    pPrimaryMenu(nullptr)
{
    ui->setupUi(this);

    initMenus();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete pPrimaryMenu;
}

void MainWindow::initMenus()
{
    pPrimaryMenu = new QMenu("ToxScreen");
    QAction *connectAction = pPrimaryMenu->addAction("&Connect");
    pPrimaryMenu->addSeparator();
    QAction *exitAction = pPrimaryMenu->addAction("&Exit");

    QObject::connect(connectAction, &QAction::triggered, this, &MainWindow::onConnectAction);
    QObject::connect(exitAction, &QAction::triggered, this, &MainWindow::onExitAction);

    ui->toxScreenMenuPushButton->setMenu(pPrimaryMenu);
}

void MainWindow::setTox(QTox *tox)
{
    pTox = tox;

    // Set address text field
    QString addressHex(pTox->getAddress().toHex().toUpper());
    ui->toxIdLineEdit->setPlaceholderText(addressHex);
    ui->toxIdLineEdit->setCursorPosition(0);
}

void MainWindow::onConnectAction(bool checked)
{
    qDebug("Connect action triggered");
}

void MainWindow::onExitAction(bool checked)
{
	close();
}
