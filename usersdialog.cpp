#include "ui_usersdialog.h"
#include "userimagesdialog.h"
#include "usersdialog.h"

string selected;

UsersDialog::UsersDialog(QWidget *parent, Peer *peer)
    : QDialog(parent), ui(new Ui::UsersDialog), peer(peer) {
  ui->setupUi(this);
  ui->lbl_time->setText(
      QString::fromStdString("Refreshed at " + peer->getCurrentTime()));
  //ui->lbl_time->setStyleSheet("QLabel { color : yellow; }");
  ui->lbl_result->setVisible(false);

  int resultUsers = peer->getUsers();
  if(resultUsers == 1){
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
else if(resultUsers == 2){
  ui->lbl_result->setVisible(true);
  ui->lbl_result->setStyleSheet("QLabel { color : magenta; }");
  ui->lbl_result->setText("Server Unreachable");
}
else if(resultUsers == 0){
  ui->lbl_result->setVisible(true);
  ui->lbl_result->setStyleSheet("QLabel { color : magenta; }");
  ui->lbl_result->setText("Sending Failed"); // Getusers send failed!
}
else{
  ui->lbl_result->setVisible(true);
  ui->lbl_result->setStyleSheet("QLabel { color : magenta; }");
  ui->lbl_result->setText("Problem with internet connection!");
}
}

UsersDialog::~UsersDialog() { delete ui; }

void UsersDialog::on_push_view_clicked() {
  if (ui->listWidget->currentRow() >= 0) {
      int resultUsers = peer->getUsers();
      if(resultUsers == 1){
    if (peer->users[ui->listWidget->currentItem()->text().toStdString()][0] == "0") { //  ->textColor() == Qt::magenta
        ui->listWidget->currentItem()->textColor() = Qt::magenta; // set magenta if not already
        ui->lbl_result->setVisible(true);
      ui->lbl_result->setStyleSheet("QLabel { color : magenta; }");
    } else {
      ui->lbl_result->setVisible(false);
      const QString &s = ui->listWidget->currentItem()->text();
      secdia = new userimagesdialog(this, peer, s); // if want to distroy secdia
                                                    // with the main, put (this)
      secdia->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint |
                             Qt::CustomizeWindowHint);
      secdia->show();
    }
      }
      else if(resultUsers == 2){
        ui->lbl_result->setVisible(true);
        ui->lbl_result->setStyleSheet("QLabel { color : magenta; }");
        ui->lbl_result->setText("Server Unreachable");
      }
      else if(resultUsers == 0){
        ui->lbl_result->setVisible(true);
        ui->lbl_result->setStyleSheet("QLabel { color : magenta; }");
        ui->lbl_result->setText("Sending Failed"); // Getusers send failed!
      }
      else{
        ui->lbl_result->setVisible(true);
        ui->lbl_result->setStyleSheet("QLabel { color : magenta; }");
        ui->lbl_result->setText("Problem with internet connection");
      }


  } else {
    ui->lbl_result->setVisible(true);
    ui->lbl_result->setStyleSheet("QLabel { color : magenta; }");
    ui->lbl_result->setText("Choose a user");
  }
}

void UsersDialog::on_push_refresh_clicked() {
  ui->listWidget->clear();
  ui->lbl_result->setVisible(false);
  ui->lbl_time->setText(
      QString::fromStdString("Refreshed at " + peer->getCurrentTime()));
  ui->lbl_time->setStyleSheet("QLabel { color : yellow; }");
  int resultUsers = peer->getUsers();
  if(resultUsers == 1){
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
else if(resultUsers == 2){
  ui->lbl_result->setVisible(true);
  ui->lbl_result->setStyleSheet("QLabel { color : magenta; }");
  ui->lbl_result->setText("Server Unreachable");
}
else if(resultUsers == 0){
  ui->lbl_result->setVisible(true);
  ui->lbl_result->setStyleSheet("QLabel { color : magenta; }");
  ui->lbl_result->setText("Sending Failed"); // Getusers send failed!
}
else{
  ui->lbl_result->setVisible(true);
  ui->lbl_result->setStyleSheet("QLabel { color : magenta; }");
  ui->lbl_result->setText("Problem with internet connection!");
}
}
