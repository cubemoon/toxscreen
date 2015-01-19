#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QMenu>
#include <QString>
#include <QTimer>
#include "../qt/QTox.h"
#include "../password_generator.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setStatus(const QString &status);
    void setTox(QTox *tox);

private:
    void clearStatus();
    void initButtons();
    void initMenus();
    void initStatusBar();
    void initStatusClearTimer();
    void onConnectAction(bool checked);
    void onExitAction(bool checked);
    void onPasswordRefreshButtonClicked(bool checked);
    void onToxIdCopyButtonClicked(bool checked);
    Ui::MainWindow *ui;
    QTimer *pStatusClearTimer;
    PasswordGenerator mPasswordGenerator;
    QTox *pTox;
    QMenu *pPrimaryMenu;
    QLabel *pStatusLabel;

    static int clearStatusMilli;
};

#endif // MAINWINDOW_H
