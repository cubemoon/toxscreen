#ifndef TOXSCREEN_FORMS_CONNECT_DIALOG_H
#define TOXSCREEN_FORMS_CONNECT_DIALOG_H

#include <QDialog>

namespace Ui {
class ConnectDialog;
}

class ConnectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectDialog(QWidget *parent = 0);
    ~ConnectDialog();

private:
    Ui::ConnectDialog *ui;
};

#endif // TOXSCREEN_FORMS_CONNECT_DIALOG_H
