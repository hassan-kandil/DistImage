#ifndef USERIMAGESDIALOG_H
#define USERIMAGESDIALOG_H
#include "Peer.h"
#include <QDialog>

namespace Ui {
class userimagesdialog;
}

class userimagesdialog : public QDialog {
  Q_OBJECT

public:
  explicit userimagesdialog(QWidget *parent = nullptr, Peer *peer = nullptr,
                            QString s = "");
    void temp();
  ~userimagesdialog();

private slots:
    void on_push_request_clicked();

private:
  Ui::userimagesdialog *ui;
  Peer *peer;
  QString selectedUser;
};

#endif // USERIMAGESDIALOG_H
