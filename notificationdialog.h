#ifndef NOTIFICATIONDIALOG_H
#define NOTIFICATIONDIALOG_H
#include "Peer.h"
#include <QDialog>

namespace Ui {
class NotificationDialog;
}

class NotificationDialog : public QDialog {
  Q_OBJECT

public:
  explicit NotificationDialog(QWidget *parent = nullptr, Peer *peer = nullptr);
  ~NotificationDialog();

private slots:
  void on_push_approve_clicked();

  void on_push_refresh_clicked();

private:
  Ui::NotificationDialog *ui;
  Peer *peer;
  QString selectedRequest;
};

#endif // NOTIFICATIONDIALOG_H
