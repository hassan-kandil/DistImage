#ifndef MYIMAGESDIALOG_H
#define MYIMAGESDIALOG_H

#include <QDialog>

namespace Ui {
class MyImagesDialog;
}

class MyImagesDialog : public QDialog {
  Q_OBJECT

public:
  explicit MyImagesDialog(QWidget *parent = nullptr);
  ~MyImagesDialog();

private slots:
  void on_push_request_clicked();

private:
  Ui::MyImagesDialog *ui;
};

#endif // MYIMAGESDIALOG_H
