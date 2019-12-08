#include "myimagesdialog.h"
#include "notificationdialog.h"
#include "seconddialog.h"
#include "sharedimagesdialog.h"
#include "ui_seconddialog.h"
#include "usersdialog.h"
#include <QWindow>
#include <qfiledialog.h>
#include <thread>
#include <unistd.h>
SecondDialog::SecondDialog(QWidget *parent, Peer *peer)
    : QDialog(parent), ui(new Ui::SecondDialog), peer(peer) {
  ui->setupUi(this);
  ui->lbl_time->setText(
      QString::fromStdString("Logged in at " + peer->getCurrentTime()));
  ui->lbl_time->setStyleSheet("QLabel { color : yellow; }");
  connect(this, SIGNAL(destroyed()), this->parent(),
          SLOT(close())); // to close all after logout
  ui->lbl_user->setText(QString::fromStdString(peer->username));
  peer->readfile();
  peer->read_my_images_file();
  ui->lbl_upload_successful->setVisible(false);
  cout << "Username: " << peer->username << " Logged in " << endl;
  cout << "Thread Started" << endl;
  std::thread listenThread(&Peer::listenPeer, peer);
  listenThread.detach();
}

SecondDialog::~SecondDialog() { delete ui; }

void SecondDialog::on_push_logout_clicked() {
  int result = peer->logout();
  if (result == 1) { // Logged out success
      ui->lbl_upload_successful->setVisible(true);
      ui->lbl_upload_successful->setText(QString("Logged Out"));
      ui->lbl_upload_successful->setStyleSheet("QLabel { color : yellow; }");
      usleep(2000);
  peer->updatefile();
  peer->update_my_images_file();
  this->close();
  } else if (result == 6 || result == 0) {
    ui->lbl_upload_successful->setVisible(true);
    ui->lbl_upload_successful->setText(QString("Problem with Internet Connection")); // Signup Send Failed!
    ui->lbl_upload_successful->setStyleSheet("QLabel { color : magenta; }");
  } else { // Timeout
    ui->lbl_upload_successful->setVisible(true);
    ui->lbl_upload_successful->setText(QString("Server Unreachable"));
    ui->lbl_upload_successful->setStyleSheet("QLabel { color : magenta; }");
  }
}

void SecondDialog::on_push_users_clicked() {
  UsersDialog secd(this, peer);
  secd.setWindowFlags(Qt::Dialog | Qt::WindowTitleHint |
                      Qt::CustomizeWindowHint);
  secd.setModal(true);
  secd.exec();
}

void SecondDialog::on_push_images_clicked() {
  MyImagesDialog secd(this, peer);
  secd.setWindowFlags(Qt::Dialog | Qt::WindowTitleHint |
                      Qt::CustomizeWindowHint);
  secd.setModal(true);
  secd.exec();
}

void SecondDialog::on_push_notifications_clicked() {
  NotificationDialog secd(this, peer);
  secd.setWindowFlags(Qt::Dialog | Qt::WindowTitleHint |
                      Qt::CustomizeWindowHint);
  secd.setModal(true);
  secd.exec();
}

void SecondDialog::on_push_upload_clicked() {
  QString imagePath = QFileDialog::getOpenFileName(
      this, tr("Open Image"), "", tr("JPEG (*.jpg *.jpeg);;PNG (*.png)"));

  int upload_stat = peer->upload(imagePath.toStdString());

  if (upload_stat == 1) { // Successful
    ui->lbl_upload_successful->setVisible(true);
    ui->lbl_upload_successful->setText(QString("Image Uploaded"));
    ui->lbl_upload_successful->setStyleSheet("QLabel { color : yellow; }");
  } else if (upload_stat == 0) {
    ui->lbl_upload_successful->setVisible(true);
    ui->lbl_upload_successful->setText(QString("Incorrect Username"));
    ui->lbl_upload_successful->setStyleSheet("QLabel { color : magenta; }");
  } else if (upload_stat == 6) {
    ui->lbl_upload_successful->setVisible(true);
    ui->lbl_upload_successful->setText(QString("Please, choose a file!"));
    ui->lbl_upload_successful->setStyleSheet("QLabel { color : magenta; }");
  } else if (upload_stat == 3) {
    ui->lbl_upload_successful->setVisible(true);
    ui->lbl_upload_successful->setText(
        QString("Special Characters Prohibited in Image Name"));
    ui->lbl_upload_successful->setStyleSheet("QLabel { color : magenta; }");
  } else if (upload_stat == 9) {
    ui->lbl_upload_successful->setVisible(true);
    ui->lbl_upload_successful->setText(QString("Image already Uploaded"));
    ui->lbl_upload_successful->setStyleSheet("QLabel { color : magenta; }");
  } else if (upload_stat == 2) {
    ui->lbl_upload_successful->setVisible(true);
    ui->lbl_upload_successful->setText(QString("Server Unreachable"));
    ui->lbl_upload_successful->setStyleSheet("QLabel { color : magenta; }");
  } else if (upload_stat == 30) {
    ui->lbl_upload_successful->setVisible(true);
    ui->lbl_upload_successful->setText(QString("Sending Failed")); // Send to failed!
    ui->lbl_upload_successful->setStyleSheet("QLabel { color : magenta; }");
  } else {
    ui->lbl_upload_successful->setVisible(true);
    ui->lbl_upload_successful->setText(QString("Problem with internet connection!"));
    ui->lbl_upload_successful->setStyleSheet("QLabel { color : magenta; }");
  }
}

void SecondDialog::on_push_shared_clicked() {
  SharedImagesDialog secd(this, peer);
  secd.setWindowFlags(Qt::Dialog | Qt::WindowTitleHint |
                      Qt::CustomizeWindowHint);
  secd.setModal(true);
  secd.exec();
}
