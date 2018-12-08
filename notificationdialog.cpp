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
    else if (peer->requests_buffer[i].first == 2004)
      req = " approved you to view ";
    else if (peer->requests_buffer[i].first == 2007)
      req = " want to update his number of views to ";
    else
      req = " something wrong here ";
    ui->listWidget->addItem(
        QString::fromStdString(peer->requests_buffer[i].second.name + req +
                               peer->requests_buffer[i].second.imagename + " "+to_string(peer->requests_buffer[i].second.views)+ " times"));
  }
}

NotificationDialog::~NotificationDialog() { delete ui; }

void NotificationDialog::on_push_approve_clicked() {
  if (ui->listWidget->currentRow() >= 0) {
    string usname =
        peer->requests_buffer[ui->listWidget->currentRow()].second.name;
    string imname =
        peer->requests_buffer[ui->listWidget->currentRow()].second.imagename;
    int opcode = peer->requests_buffer[ui->listWidget->currentRow()].first;
    if(ui->line_views->text() == "" && (opcode == 2002 || opcode == 2007)){
        ui->lbl_result->setVisible(true);
        ui->lbl_result->setStyleSheet("QLabel { color : red; }");
        ui->lbl_result->setText("Please, enter number of views!");
    }
    else{
        int noViews = ui->line_views->text().toInt();

        if (opcode == 2002){ // req = " wants to view ";
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


            }
        }
        else if (opcode == 2003){ // req = " approved you to view ";
            ui->push_approve->setText("Ok");
        }
        else if (opcode == 2007){ // req = " want to update his number of views to ";
            if (noViews < 0) {
              ui->lbl_result->setVisible(true);
              ui->lbl_result->setText("Please, add the number of views >= 0");
              ui->lbl_result->setStyleSheet("QLabel { color : red; }");
            } else {
              cout << "Updating views of " << usname << " imagename " << imname << endl;
              peer->update_views_by_owner(usname, imname, noViews);

              ui->lbl_result->setVisible(true);
              ui->lbl_result->setText("Updated!");
              ui->lbl_result->setStyleSheet("QLabel { color : green; }");
            }
        }
        else{ // req = " something wrong here ";
            ui->lbl_result->setVisible(true);
            ui->lbl_result->setText("Something wrong here!");
            ui->lbl_result->setStyleSheet("QLabel { color : red; }");
        }

        peer->requests_buffer.erase(peer->requests_buffer.begin() +
                                    ui->listWidget->currentRow());

        // refill list
        ui->listWidget->clear();
        for (int i = 0; i < peer->requests_buffer.size(); i++) {
          string req;
          if (peer->requests_buffer[i].first == 2002)
            req = " wants to view ";
          else if (peer->requests_buffer[i].first == 2004)
            req = " approved you to view ";
          else if (peer->requests_buffer[i].first == 2007)
            req = " want to update his number of views to ";
          else
            req = " something wrong here ";
          ui->listWidget->addItem(
              QString::fromStdString(peer->requests_buffer[i].second.name + req +
                                     peer->requests_buffer[i].second.imagename + " "+to_string(peer->requests_buffer[i].second.views)+ "times"));

        }

    }
  }
   else {
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
    else if (peer->requests_buffer[i].first == 2007)
      req = " want to update his number of views to ";
    else
      req = " something wrong here ";
    ui->listWidget->addItem(
        QString::fromStdString(peer->requests_buffer[i].second.name + req +
                               peer->requests_buffer[i].second.imagename + " "+to_string(peer->requests_buffer[i].second.views)+ "times"));

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
      else if (peer->requests_buffer[i].first == 2007)
        req = " want to update his number of views to ";
      else
        req = " something wrong here ";
      ui->listWidget->addItem(
          QString::fromStdString(peer->requests_buffer[i].second.name + req +
                                 peer->requests_buffer[i].second.imagename + " "+to_string(peer->requests_buffer[i].second.views)+ "times"));
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
