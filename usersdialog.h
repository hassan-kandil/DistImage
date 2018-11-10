#ifndef USERSDIALOG_H
#define USERSDIALOG_H
#include "Peer.h"
#include "userimagesdialog.h"
#include <QDialog>

namespace Ui {
class UsersDialog;
}

class UsersDialog : public QDialog {
  Q_OBJECT

public:
  explicit UsersDialog(QWidget *parent = nullptr, Peer * peer = nullptr);
  ~UsersDialog();

private slots:
  void on_push_view_clicked();

  void on_push_refresh_clicked();

private:
  Ui::UsersDialog *ui;
  userimagesdialog *secdia;

  Peer *peer;

};

#endif // USERSDIALOG_H
