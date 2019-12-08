#include "notificationdialog.h"
#include "ui_notificationdialog.h"

NotificationDialog::NotificationDialog(QWidget *parent, Peer *peer)
    : QDialog(parent), ui(new Ui::NotificationDialog), peer(peer) {
  ui->setupUi(this);
  ui->line_views->setValidator(new QIntValidator); // only numbers
  ui->lbl_time->setText(
      QString::fromStdString("Last Time Refreshed: " + peer->getCurrentTime()));
  ui->lbl_time->setStyleSheet("QLabel { color : yellow; }");
  ui->line_views->setPlaceholderText("Views");
  ui->lbl_result->setVisible(false);
  int resultUsers = peer->getUsers(); // because approve needs IP & port
  if(resultUsers = 1){
  for (int i = 0; i < peer->requests_buffer.size(); i++) {
    string req;
    if (peer->requests_buffer[i].first == 2002)
      req = " sent a request to view ";
    else if (peer->requests_buffer[i].first == 2004)
      req = " accepted your request to view ";
    else if (peer->requests_buffer[i].first == 2007)
      req = " wants to top up the assigned number of views to ";
    else
      req = " Problem with internet connection ";
    ui->listWidget->addItem(
        QString::fromStdString(peer->requests_buffer[i].second.name + req +
                               peer->requests_buffer[i].second.imagename + " "+to_string(peer->requests_buffer[i].second.views)+ " views"));
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
      ui->lbl_result->setText("Send Failed"); // Getusers send failed!
    }
    else{
      ui->lbl_result->setVisible(true);
      ui->lbl_result->setStyleSheet("QLabel { color : magenta; }");
      ui->lbl_result->setText("Problem with internet connection");
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
        ui->lbl_result->setStyleSheet("QLabel { color : magenta; }");
        ui->lbl_result->setText("Specify Amount of Desired Views");
    }
    else{
        int noViews = ui->line_views->text().toInt();

        if (opcode == 2002){ // req = " sent a request to view ";
            if (noViews <= 0) {
              ui->lbl_result->setVisible(true);
              ui->lbl_result->setText("Invalid Views");
              ui->lbl_result->setStyleSheet("QLabel { color : magenta; }");
            } else {
              cout << "Accepted User " << usname << " image name " << imname << endl;
              std::thread SendImageThread(&Peer::send_image, peer, usname, imname,
                                          noViews);
              SendImageThread.detach();
              ui->lbl_result->setVisible(true);
              ui->lbl_result->setText("Accepted!");
              ui->lbl_result->setStyleSheet("QLabel { color : yellow; }");

            }
        }
        else if (opcode == 2004){ // req = " accepted your request to view ";
            ui->lbl_result->setVisible(true);
            ui->lbl_result->setText("Done");
            ui->lbl_result->setStyleSheet("QLabel { color : magenta; }");
        }
        else if (opcode == 2007){ // req = " wants to top up the assigned number of views to ";
            if (noViews < 0) {
              ui->lbl_result->setVisible(true);
              ui->lbl_result->setText("Invalid Views");
              ui->lbl_result->setStyleSheet("QLabel { color : magenta; }");
            } else {
              cout << "Topping up views of " << usname << " image name " << imname << endl;
              int resultUsers = peer->update_views_by_owner(usname, imname, noViews);
              if(resultUsers == 1){
              ui->lbl_result->setVisible(true);
              ui->lbl_result->setText("Views Topped Up");
              ui->lbl_result->setStyleSheet("QLabel { color : yellow; }");
              }
              else if(resultUsers == 12){
                ui->lbl_result->setVisible(true);
                ui->lbl_result->setStyleSheet("QLabel { color : magenta; }");
                ui->lbl_result->setText("Server Unreachable");
              }
              else if(resultUsers == 10){
                ui->lbl_result->setVisible(true);
                ui->lbl_result->setStyleSheet("QLabel { color : magenta; }");
                ui->lbl_result->setText("Sending Failed"); // Getusers send failed!
              }
              else if(resultUsers == 0){
                ui->lbl_result->setVisible(true);
                ui->lbl_result->setStyleSheet("QLabel { color : magenta; }");
                ui->lbl_result->setText("Failed To Top Up Views"); // update_views_by_owner at viewer failed!
              }
              else{
                ui->lbl_result->setVisible(true);
                ui->lbl_result->setStyleSheet("QLabel { color : magenta; }");
                ui->lbl_result->setText("Problem with Internet Connection");
              }
            }
        }
        else{
            ui->lbl_result->setVisible(true);
            ui->lbl_result->setText("Problem with Internet Connection");
            ui->lbl_result->setStyleSheet("QLabel { color : magenta; }");
        }

        peer->requests_buffer.erase(peer->requests_buffer.begin() +
                                    ui->listWidget->currentRow());

        // refill list
        ui->listWidget->clear();
        for (int i = 0; i < peer->requests_buffer.size(); i++) {
          string req;
          if (peer->requests_buffer[i].first == 2002)
            req = " sent a request to view ";
          else if (peer->requests_buffer[i].first == 2004)
            req = " accepted your request to view";
          else if (peer->requests_buffer[i].first == 2007)
            req = " wants to top up the assigned number of views to ";
          else
            req = " Problem with internet connection ";
          ui->listWidget->addItem(
              QString::fromStdString(peer->requests_buffer[i].second.name + req +
                                     peer->requests_buffer[i].second.imagename + " "+to_string(peer->requests_buffer[i].second.views)+ "views"));

        }

    }
  }
   else {
    ui->lbl_result->setVisible(true);
    ui->lbl_result->setStyleSheet("QLabel { color : magenta; }");
    ui->lbl_result->setText("Choose a Notification");
  }
}

void NotificationDialog::on_push_refresh_clicked() { // refill list
  ui->lbl_result->setVisible(false);
  ui->lbl_time->setText(
      QString::fromStdString("Refreshed at " + peer->getCurrentTime()));
  ui->lbl_time->setStyleSheet("QLabel { color : yellow; }");
  ui->listWidget->clear();
  int resultUsers = peer->getUsers(); // because approve needs IP & port
  if(resultUsers == 1){
  for (int i = 0; i < peer->requests_buffer.size(); i++) {
    string req;
    if (peer->requests_buffer[i].first == 2002)
      req = " sent a request to view ";
    else if (peer->requests_buffer[i].first == 2003)
      req = " accepted your request to view ";
    else if (peer->requests_buffer[i].first == 2007)
      req = " wants to top up the assigned number of views to ";
    else
      req = " Problem with internet connection ";
    ui->listWidget->addItem(
        QString::fromStdString(peer->requests_buffer[i].second.name + req +
                               peer->requests_buffer[i].second.imagename + " "+to_string(peer->requests_buffer[i].second.views)+ " Views"));

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
    ui->lbl_result->setText("Sending Failed");
  }
  else{
    ui->lbl_result->setVisible(true);
    ui->lbl_result->setStyleSheet("QLabel { color : magenta; }");
    ui->lbl_result->setText("Problem with internet connection");
  }
}

void NotificationDialog::on_push_disapprove_clicked() {
  if (ui->listWidget->currentRow() >= 0) {
    // should reply with request disapproved

    peer->requests_buffer.erase(peer->requests_buffer.begin() +
                                ui->listWidget->currentRow());

    ui->listWidget->clear();
    for (int i = 0; i < peer->requests_buffer.size(); i++) {
      string req;
      if (peer->requests_buffer[i].first == 2002)
        req = " sent a request to view ";
      else if (peer->requests_buffer[i].first == 2003)
        req = " accepted your request to view ";
      else if (peer->requests_buffer[i].first == 2007)
        req = " wants to top up the assigned number of views to ";
      else
        req = " Problem with internet connection ";
      ui->listWidget->addItem(
          QString::fromStdString(peer->requests_buffer[i].second.name + req +
                                 peer->requests_buffer[i].second.imagename + " "+to_string(peer->requests_buffer[i].second.views)+ " views "));
    }
    ui->lbl_result->setVisible(true);
    ui->lbl_result->setStyleSheet("QLabel { color : yellow; }");
    ui->lbl_result->setText("Notification Removed");
  } else {
    ui->lbl_result->setVisible(true);
    ui->lbl_result->setStyleSheet("QLabel { color : magenta; }");
    ui->lbl_result->setText("Choose a notification");
  }
}
