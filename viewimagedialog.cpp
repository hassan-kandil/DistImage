#include "ui_viewimagedialog.h"
#include "viewimagedialog.h"
#include <qpicture.h>

ViewImageDialog::ViewImageDialog(QWidget *parent, Peer *peer)
    : QDialog(parent), ui(new Ui::ViewImageDialog), peer(peer) {
  ui->setupUi(this);
  ui->lbl_error->setVisible(false);
  QPicture picture;
  picture.load("/home/refaay/distributed_pro/rooney.jpeg"); // load picture
  ui->lbl_image->setPicture(picture);
}

ViewImageDialog::~ViewImageDialog() { delete ui; }
