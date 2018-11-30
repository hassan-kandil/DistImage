#ifndef SECONDDIALOG_H
#define SECONDDIALOG_H
#include "Peer.h"
#include <QDialog>

namespace Ui {
class SecondDialog;
}

class SecondDialog : public QDialog {
  Q_OBJECT

public:
  explicit SecondDialog(QWidget *parent = nullptr, Peer *peer = nullptr);
  ~SecondDialog();

private slots:
  void on_push_logout_clicked();

  void on_push_users_clicked();

  void on_push_images_clicked();

  void on_push_notifications_clicked();

  void on_push_upload_clicked();

private:
  Ui::SecondDialog *ui;
  Peer *peer;
};

#endif // SECONDDIALOG_H
