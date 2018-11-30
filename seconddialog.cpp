#include "myimagesdialog.h"
#include "notificationdialog.h"
#include "seconddialog.h"
#include "ui_seconddialog.h"
#include "usersdialog.h"
#include <qfiledialog.h>
#include <thread>

SecondDialog::SecondDialog(QWidget *parent, Peer *peer)
    : QDialog(parent), ui(new Ui::SecondDialog), peer(peer) {
  ui->setupUi(this);
  ui->lbl_upload_successful->setVisible(false);
  cout << "This is user " << peer->username << endl;
  cout << "The thread is starting!! " << endl;
  std::thread listenThread(&Peer::listenPeer, peer);
  listenThread.detach();
}

SecondDialog::~SecondDialog() { delete ui; }

void SecondDialog::on_push_logout_clicked() {
  peer->logout();
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
  MyImagesDialog secd;
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
  // QString imagePath = QFileDialog::getOpenFileName(this,tr("Open Image"),
  // "",tr("JPEG (*.jpg *.jpeg);;PNG (*.png)" ));

  int upload_stat = peer->upload(ui->line_upload_path->text().toStdString(),
                                 ui->line_upload_name->text().toStdString(),
                                 ui->line_upload_default->text().toStdString());
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
    ui->lbl_upload_successful->setText(QString("Fill all info!"));
    ui->lbl_upload_successful->setStyleSheet("QLabel { color : red; }");
  } else {
    ui->lbl_upload_successful->setVisible(true);
    ui->lbl_upload_successful->setText(
        QString("No special Chars! Only 1 dot."));
    ui->lbl_upload_successful->setStyleSheet("QLabel { color : red; }");
  }
}
