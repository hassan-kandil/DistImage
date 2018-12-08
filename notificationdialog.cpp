#include "notificationdialog.h"
#include "ui_notificationdialog.h"

NotificationDialog::NotificationDialog(QWidget *parent, Peer *peer)
    : QDialog(parent), ui(new Ui::NotificationDialog), peer(peer) {
  ui->setupUi(this);
  ui->lbl_time->setText(
      QString::fromStdString("Last Time Refreshed: " + peer->getCurrentTime()));
  ui->lbl_time->setStyleSheet("QLabel { color : blue; }");
  ui->line_views->setPlaceholderText("No. of Views");
  ui->lbl_result->setVisible(false);
  peer->getUsers(); // because approve needs IP & port
  for (int i = 0; i < peer->requests_buffer.size(); i++) {
    string req;
    if (peer->requests_buffer[i].first == 2002)
      req = " wants to view ";
    else if (peer->requests_buffer[i].first == 2003)
      req = " approved you to view ";
    else
      req = " something wrong here ";
    ui->listWidget->addItem(
        QString::fromStdString(peer->requests_buffer[i].second.first + req +
                               peer->requests_buffer[i].second.second));
  }
}

NotificationDialog::~NotificationDialog() { delete ui; }

void NotificationDialog::on_push_approve_clicked() {
  if (ui->listWidget->currentRow() >= 0) {
    string usname =
        peer->requests_buffer[ui->listWidget->currentRow()].second.first;
    string imname =
        peer->requests_buffer[ui->listWidget->currentRow()].second.second;
    int noViews = ui->line_views->text().toInt();
    if (noViews <= 0) {
      ui->lbl_result->setVisible(true);
      ui->lbl_result->setText("Please, add the number of views > 0");
      ui->lbl_result->setStyleSheet("QLabel { color : red; }");
    } else {
      cout << "ApprovedUser " << usname << " imagename " << imname << endl;
      std::thread SendImageThread(&Peer::send_image, peer, usname, imname,
                                  noViews);
      SendImageThread.detach();
      //  peer->send_image(usname, imname, noViews);
      ui->lbl_result->setVisible(true);
      ui->lbl_result->setText("Approved!");
      ui->lbl_result->setStyleSheet("QLabel { color : green; }");

      peer->requests_buffer.erase(peer->requests_buffer.begin() +
                                  ui->listWidget->currentRow());

      // refill list
      ui->listWidget->clear();
      for (int i = 0; i < peer->requests_buffer.size(); i++) {
        string req;
        if (peer->requests_buffer[i].first == 2002)
          req = " wants to view ";
        else if (peer->requests_buffer[i].first == 2003)
          req = " approved you to view ";
        else
          req = " something wrong here ";
        ui->listWidget->addItem(
            QString::fromStdString(peer->requests_buffer[i].second.first + req +
                                   peer->requests_buffer[i].second.second));
      }
    }
  } else {
    ui->lbl_result->setVisible(true);
    ui->lbl_result->setStyleSheet("QLabel { color : red; }");
    ui->lbl_result->setText("Please, select a notification!");
  }
}

void NotificationDialog::on_push_refresh_clicked() { // refill list
  ui->lbl_result->setVisible(false);
  ui->lbl_time->setText(
      QString::fromStdString("Last Time Refreshed: " + peer->getCurrentTime()));
  ui->lbl_time->setStyleSheet("QLabel { color : blue; }");
  ui->listWidget->clear();
  peer->getUsers(); // because approve needs IP & port

  for (int i = 0; i < peer->requests_buffer.size(); i++) {
    string req;
    if (peer->requests_buffer[i].first == 2002)
      req = " wants to view ";
    else if (peer->requests_buffer[i].first == 2003)
      req = " approved you to view ";
    else
      req = " something wrong here ";
    ui->listWidget->addItem(
        QString::fromStdString(peer->requests_buffer[i].second.first + req +
                               peer->requests_buffer[i].second.second));
  }
}

void NotificationDialog::on_push_disapprove_clicked() {
  if (ui->listWidget->currentRow() >= 0) {
    // Refaay: should reply with request disapproved

    peer->requests_buffer.erase(peer->requests_buffer.begin() +
                                ui->listWidget->currentRow());

    ui->listWidget->clear();
    for (int i = 0; i < peer->requests_buffer.size(); i++) {
      string req;
      if (peer->requests_buffer[i].first == 2002)
        req = " wants to view ";
      else if (peer->requests_buffer[i].first == 2003)
        req = " approved you to view ";
      else
        req = " something wrong here ";
      ui->listWidget->addItem(
          QString::fromStdString(peer->requests_buffer[i].second.first + req +
                                 peer->requests_buffer[i].second.second));
    }
    ui->lbl_result->setVisible(true);
    ui->lbl_result->setStyleSheet("QLabel { color : green; }");
    ui->lbl_result->setText("Notification deleted!");
  } else {
    ui->lbl_result->setVisible(true);
    ui->lbl_result->setStyleSheet("QLabel { color : red; }");
    ui->lbl_result->setText("Please, select a notification!");
  }
}
