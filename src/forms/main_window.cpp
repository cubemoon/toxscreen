#include <QClipboard>
#include "main_window.h"
#include "ui_main_window.h"

// Wait 3 seconds before clearing status
int MainWindow::clearStatusMilli = 3000;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    mConnectDialog(this),
    ui(new Ui::MainWindow),
    pTox(nullptr),
    pStatusClearTimer(new QTimer(this)),
    pPrimaryMenu(nullptr),
    pStatusLabel(nullptr)
{
    ui->setupUi(this);

    initButtons();
    initMenus();
    initStatusBar();
    initStatusClearTimer();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete pPrimaryMenu;
    delete pStatusLabel;
    delete pStatusClearTimer;
}

/**
 * Initialize QPushButton menus.
 */
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

/**
 * Initialize button connections.
 */
void MainWindow::initButtons()
{
    QObject::connect(ui->passwordRefreshPushButton, &QPushButton::clicked, this, &MainWindow::onPasswordRefreshButtonClicked);
    QObject::connect(ui->toxIdCopyPushButton, &QPushButton::clicked, this, &MainWindow::onToxIdCopyButtonClicked);
}

/**
 * Initialize the status bar. This is necessary as QtCreator doesn't allow
 * for any children to be added to a QStatusBar.
 */
void MainWindow::initStatusBar()
{
    pStatusLabel = new QLabel("");
    pStatusLabel->setObjectName("statusLabel");
    //pStatusLabel->setAlignment(Qt::AlignRight);
    ui->statusBar->addWidget(pStatusLabel);
}

/**
 * Initialize the status clear QTimer.
 */
void MainWindow::initStatusClearTimer()
{
    pStatusClearTimer->setInterval(MainWindow::clearStatusMilli);
    QObject::connect(pStatusClearTimer, &QTimer::timeout, this, &MainWindow::clearStatus);
}

/**
 * Clear the status label.
 */
void MainWindow::clearStatus()
{
    setStatus("");
}

/**
 * Set the status label text.
 * @param status Status label text
 */
void MainWindow::setStatus(const QString &status)
{
    pStatusLabel->setText(status);
    pStatusClearTimer->start();
}

/**
 * Set the associated QTox instance.
 * @param tox Pointer to QTox
 */
void MainWindow::setTox(QTox *tox)
{
    pTox = tox;

    // Set address text field
    QString addressHex(pTox->getAddress().toHex().toUpper());
    ui->toxIdLineEdit->setPlaceholderText(addressHex);
    ui->toxIdLineEdit->setCursorPosition(0);
}

/**
 * Called when the Connect menu action is triggered.
 * @param checked Checked, unused
 */
void MainWindow::onConnectAction(bool checked)
{
    qDebug("Connect action triggered");
    mConnectDialog.show();
    mConnectDialog.raise();
    mConnectDialog.activateWindow();
}

/**
 * Called when the Exit menu action is triggered. Will close
 * this window.
 * @param checked Checked, unused
 */
void MainWindow::onExitAction(bool checked)
{
    close();
}

/**
 * Called when the password refresh button is clicked. Will
 * regenerate a new password.
 * @param checked Checked, unused
 */
void MainWindow::onPasswordRefreshButtonClicked(bool checked)
{
    QString newPass = mPasswordGenerator.generate();
    ui->passwordLineEdit->setText(newPass);
    setStatus("Refreshed password");
}

/**
 * Called when the Tox Id copy button is clicked. Will copy the
 * Tox Id into the clipboard.
 * @param checked Checked, unused
 */
void MainWindow::onToxIdCopyButtonClicked(bool checked)
{
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(pTox->getAddress().toHex().toUpper());
    setStatus("Copied Tox Id to clipboard");
}
