#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include "../qt/QTox.h"

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
    void initMenus();
    void onConnectAction(bool checked);
    void onExitAction(bool checked);
    Ui::MainWindow *ui;
    QTox *pTox;
    QMenu *pPrimaryMenu;
};

#endif // MAINWINDOW_H
