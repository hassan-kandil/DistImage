#ifndef MYIMAGESDIALOG_H
#define MYIMAGESDIALOG_H
#include "Peer.h"
#include <QDialog>

namespace Ui {
class MyImagesDialog;
}

class MyImagesDialog : public QDialog {
  Q_OBJECT

public:
  explicit MyImagesDialog(QWidget *parent = nullptr, Peer *peer = nullptr);
  ~MyImagesDialog();

private slots:
  //void on_push_request_clicked();

  void on_push_view_clicked();

private:
  Ui::MyImagesDialog *ui;
  Peer *peer;
};

#endif // MYIMAGESDIALOG_H
