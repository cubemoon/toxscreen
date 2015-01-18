#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
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
    void setTox(QTox *tox);

private:
    void initButtons();
    void initMenus();
    void onConnectAction(bool checked);
    void onExitAction(bool checked);
    void onPasswordRefreshButtonClicked(bool checked);
    void onToxIdCopyButtonClicked(bool checked);
    Ui::MainWindow *ui;
    PasswordGenerator mPasswordGenerator;
    QTox *pTox;
    QMenu *pPrimaryMenu;

};

#endif // MAINWINDOW_H
