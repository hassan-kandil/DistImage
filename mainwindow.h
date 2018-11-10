#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Peer.h"
#include "seconddialog.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:

  void on_push_login_clicked();

  void on_push_signup_clicked();

private:
  Ui::MainWindow *ui;
  SecondDialog *secdia;
  Peer *peer;
};

#endif // MAINWINDOW_H
