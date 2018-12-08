#include "ui_usersdialog.h"
#include "userimagesdialog.h"
#include "usersdialog.h"

string selected;

UsersDialog::UsersDialog(QWidget *parent, Peer *peer)
    : QDialog(parent), ui(new Ui::UsersDialog), peer(peer) {
  ui->setupUi(this);
  ui->lbl_offline->setVisible(false);

  peer->getUsers();
  int i = 0;
  for (peer->it = peer->users.begin(); peer->it != peer->users.end();
       peer->it++) {
    if (peer->username != peer->it->first) {
      if (peer->it->second[0].at((0)) == '1') {
        ui->listWidget->addItem(QString::fromStdString(peer->it->first));
        ui->listWidget->item(i)->setTextColor(Qt::green);
      } else {
        ui->listWidget->addItem(QString::fromStdString(peer->it->first));
        ui->listWidget->item(i)->setTextColor(Qt::red);
      }
      i = i + 1;
    }
  }
}

UsersDialog::~UsersDialog() { delete ui; }

void UsersDialog::on_push_view_clicked() {
  if (ui->listWidget->currentItem()->textColor() == Qt::red) {
    ui->lbl_offline->setVisible(true);
    ui->lbl_offline->setStyleSheet("QLabel { color : red; }");
  } else {
    ui->lbl_offline->setVisible(false);
    const QString &s = ui->listWidget->currentItem()->text();
    secdia = new userimagesdialog(this, peer, s); // if want to distroy secdia
                                                  // with the main, put (this)
    secdia->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint |
                           Qt::CustomizeWindowHint);
    secdia->show();
  }
}

void UsersDialog::on_push_refresh_clicked() {
  ui->listWidget->clear();

  peer->getUsers();
  int i = 0;
  for (peer->it = peer->users.begin(); peer->it != peer->users.end();
       peer->it++) {
    if (peer->username != peer->it->first) {
      if (peer->it->second[0].at((0)) == '1') {
        ui->listWidget->addItem(QString::fromStdString(peer->it->first));
        ui->listWidget->item(i)->setTextColor(Qt::green);
      } else {
        ui->listWidget->addItem(QString::fromStdString(peer->it->first));
        ui->listWidget->item(i)->setTextColor(Qt::red);
      }
      i = i + 1;
    }
  }
}
