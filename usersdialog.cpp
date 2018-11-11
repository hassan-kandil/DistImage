#include "ui_usersdialog.h"
#include "userimagesdialog.h"
#include "usersdialog.h"

string selected;

UsersDialog::UsersDialog(QWidget *parent, Peer *peer)
    : QDialog(parent), ui(new Ui::UsersDialog), peer(peer) {
  ui->setupUi(this);
  map<string, vector<string>> users;
  map<string, vector<string>>::iterator it;
  users = peer->getUsers();
  int i = 0;
  for (it = users.begin(); it != users.end(); it++) {
    if (it->second[0].at((0)) == '1') {
      ui->listWidget->addItem(QString::fromStdString(it->first));
      ui->listWidget->item(i)->setTextColor(Qt::green);
    } else {
      ui->listWidget->addItem(QString::fromStdString(it->first));
      ui->listWidget->item(i)->setTextColor(Qt::red);
    }
    i = i + 1;
  }
  /*
  ui->listWidget->addItem("User 1");
  ui->listWidget->addItem("User 2");
  ui->listWidget->addItem("User 3");
  */
}

UsersDialog::~UsersDialog() { delete ui; }

void UsersDialog::on_push_view_clicked() {
  const QString &s = ui->listWidget->currentItem()->text();
  secdia = new userimagesdialog(this, peer, s); // if want to distroy secdia
                                                // with the main, put (this)
  secdia->show();
}

void UsersDialog::on_push_refresh_clicked() {}
