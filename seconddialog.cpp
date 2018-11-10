#include "myimagesdialog.h"
#include "seconddialog.h"
#include "ui_seconddialog.h"
#include "usersdialog.h"

SecondDialog::SecondDialog(QWidget *parent, Peer * peer)
    : QDialog(parent), ui(new Ui::SecondDialog), peer(peer) {
  ui->setupUi(this);
  //peer = peer;
}

SecondDialog::~SecondDialog() { delete ui; }

void SecondDialog::on_push_logout_clicked() { this->close(); }

void SecondDialog::on_push_users_clicked() {
  UsersDialog secd(this, peer);
  secd.setModal(true);
  secd.exec();
}

void SecondDialog::on_push_images_clicked() {
  MyImagesDialog secd;
  secd.setModal(true);
  secd.exec();
}
