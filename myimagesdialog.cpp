#include "myimagesdialog.h"
#include "ui_myimagesdialog.h"

MyImagesDialog::MyImagesDialog(QWidget *parent, Peer *peer)
    : QDialog(parent), ui(new Ui::MyImagesDialog), peer(peer) {
  ui->setupUi(this);
  ui->lbl_user->setText(QString::fromStdString(peer->username));
  peer->getUsers();

  vector<string> images;

  images = peer->users[peer->username];

  for (int i = 0; i < images.size(); i++) {
    if (i > 2) {

      ui->listWidget->addItem(QString::fromStdString(images[i]));
    }
}
}
MyImagesDialog::~MyImagesDialog() { delete ui; }

void MyImagesDialog::on_push_request_clicked() {}
