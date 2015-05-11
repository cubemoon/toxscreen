#ifndef TOXSCREEN_FORMS_MAIN_WINDOW_H
#define TOXSCREEN_FORMS_MAIN_WINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QMenu>
#include <QString>
#include <QTimer>
#include <QTox.h>
#include "connect_dialog.h"
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
    ConnectDialog mConnectDialog;
    PasswordGenerator mPasswordGenerator;
    Ui::MainWindow *ui;
    QTox *pTox;
    QTimer *pStatusClearTimer;
    QMenu *pPrimaryMenu;
    QLabel *pStatusLabel;

    static int clearStatusMilli;
};

#endif // TOXSCREEN_FORMS_MAIN_WINDOW_H
