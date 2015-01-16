#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
    Ui::MainWindow *ui;
    QTox *pTox;
};

#endif // MAINWINDOW_H
