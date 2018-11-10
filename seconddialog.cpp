#include "myimagesdialog.h"
#include "seconddialog.h"
#include "ui_seconddialog.h"
#include "usersdialog.h"

SecondDialog::SecondDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::SecondDialog) {
  ui->setupUi(this);
}

SecondDialog::~SecondDialog() { delete ui; }

void SecondDialog::on_push_logout_clicked() { this->close(); }

void SecondDialog::on_push_users_clicked() {
  UsersDialog secd;
  secd.setModal(true);
  secd.exec();
}

void SecondDialog::on_push_images_clicked() {
  MyImagesDialog secd;
  secd.setModal(true);
  secd.exec();
}
