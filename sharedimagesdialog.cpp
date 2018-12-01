#include "sharedimagesdialog.h"
#include "ui_sharedimagesdialog.h"

SharedImagesDialog::SharedImagesDialog(QWidget *parent, Peer *peer) :
    QDialog(parent), ui(new Ui::SharedImagesDialog), peer(peer) {
    ui->setupUi(this);
    peer->getUsers();

    vector<string> images;

    images = peer->users[peer->username];

    for (int i = 0; i < images.size(); i++) {
      if (i > 2) {

        ui->listWidget->addItem(QString::fromStdString(images[i]));
      }
  }
  }

SharedImagesDialog::~SharedImagesDialog()
{
    delete ui;
}
