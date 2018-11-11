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
  ~userimagesdialog();

private:
  Ui::userimagesdialog *ui;
  Peer *peer;
  QString selectedUser;
};

#endif // USERIMAGESDIALOG_H
