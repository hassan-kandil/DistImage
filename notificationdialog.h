#ifndef NOTIFICATIONDIALOG_H
#define NOTIFICATIONDIALOG_H

#include <QDialog>

namespace Ui {
class NotificationDialog;
}

class NotificationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NotificationDialog(QWidget *parent = nullptr);
    ~NotificationDialog();

private slots:
    void on_push_approve_clicked();

private:
    Ui::NotificationDialog *ui;
};

#endif // NOTIFICATIONDIALOG_H
