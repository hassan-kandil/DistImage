#include "myimagesdialog.h"
#include "notificationdialog.h"
#include "seconddialog.h"
#include "ui_seconddialog.h"
#include "usersdialog.h"

SecondDialog::SecondDialog(QWidget *parent, Peer *peer)
    : QDialog(parent), ui(new Ui::SecondDialog), peer(peer) {
  ui->setupUi(this);
  ui->lbl_upload_successful->setVisible(false);
  // peer = peer;
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
  NotificationDialog secd;
  secd.setWindowFlags(Qt::Dialog | Qt::WindowTitleHint |
                      Qt::CustomizeWindowHint);
  secd.setModal(true);
  secd.exec();
}

void SecondDialog::on_push_upload_clicked() {
  int upload_stat = peer->upload(ui->line_upload_path->text().toStdString(),ui->line_upload_name->text().toStdString(), ui->line_upload_default->text().toStdString());
  if (upload_stat == 1) { // Successful
    ui->lbl_upload_successful->setVisible(true);
    ui->lbl_upload_successful->setText(QString("Uploaded Successfully!"));
    ui->lbl_upload_successful->setStyleSheet("QLabel { color : green; }");
  } else if (upload_stat == 0) {
    ui->lbl_upload_successful->setVisible(true);
    ui->lbl_upload_successful->setText(QString("Username not found!"));
    ui->lbl_upload_successful->setStyleSheet("QLabel { color : red; }");
  } else {
    ui->lbl_upload_successful->setVisible(true);
    ui->lbl_upload_successful->setText(
        QString("No special Chars! Only 1 dot."));
    ui->lbl_upload_successful->setStyleSheet("QLabel { color : red; }");
  }
}
