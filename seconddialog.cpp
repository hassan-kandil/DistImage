#include "myimagesdialog.h"
#include "notificationdialog.h"
#include "seconddialog.h"
#include "sharedimagesdialog.h"
#include "ui_seconddialog.h"
#include "usersdialog.h"
#include <QWindow>
#include <qfiledialog.h>
#include <thread>
SecondDialog::SecondDialog(QWidget *parent, Peer *peer)
    : QDialog(parent), ui(new Ui::SecondDialog), peer(peer) {
  ui->setupUi(this);
  ui->lbl_time->setText(
      QString::fromStdString("Login Time: " + peer->getCurrentTime()));
  ui->lbl_time->setStyleSheet("QLabel { color : white; }");
  connect(this, SIGNAL(destroyed()), this->parent(),
          SLOT(close())); // to close all after logout
  ui->lbl_user->setText(QString::fromStdString(peer->username));
  peer->readfile();
  ui->lbl_upload_successful->setVisible(false);
  cout << "This is user " << peer->username << endl;
  cout << "The thread is starting!! " << endl;
  std::thread listenThread(&Peer::listenPeer, peer);
  listenThread.detach();
}

SecondDialog::~SecondDialog() { delete ui; }

void SecondDialog::on_push_logout_clicked() {
  peer->logout();
  peer->updatefile();
  peer->update_my_images_file();
  this->close();
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
  peer->read_my_images_file();
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
    ui->lbl_upload_successful->setText(QString("Uploaded Successfully!"));
    ui->lbl_upload_successful->setStyleSheet("QLabel { color : green; }");
  } else if (upload_stat == 0) {
    ui->lbl_upload_successful->setVisible(true);
    ui->lbl_upload_successful->setText(QString("Username not found!"));
    ui->lbl_upload_successful->setStyleSheet("QLabel { color : red; }");
  } else if (upload_stat == 6) {
    ui->lbl_upload_successful->setVisible(true);
    ui->lbl_upload_successful->setText(QString("Please, choose a file!"));
    ui->lbl_upload_successful->setStyleSheet("QLabel { color : red; }");
  } else if (upload_stat == 3) {
    ui->lbl_upload_successful->setVisible(true);
    ui->lbl_upload_successful->setText(
        QString("No special Chars allowed in image name! Only 1 dot."));
    ui->lbl_upload_successful->setStyleSheet("QLabel { color : red; }");
  } else if (upload_stat == 9) {
    ui->lbl_upload_successful->setVisible(true);
    ui->lbl_upload_successful->setText(QString("Image uploaded before!"));
    ui->lbl_upload_successful->setStyleSheet("QLabel { color : red; }");
  } else {
    ui->lbl_upload_successful->setVisible(true);
    ui->lbl_upload_successful->setText(QString("Something Wrong here!"));
    ui->lbl_upload_successful->setStyleSheet("QLabel { color : red; }");
  }
}

void SecondDialog::on_push_shared_clicked() {
  SharedImagesDialog secd(this, peer);
  secd.setWindowFlags(Qt::Dialog | Qt::WindowTitleHint |
                      Qt::CustomizeWindowHint);
  secd.setModal(true);
  secd.exec();
}
