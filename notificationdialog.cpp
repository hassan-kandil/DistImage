#include "notificationdialog.h"
#include "ui_notificationdialog.h"

NotificationDialog::NotificationDialog(QWidget *parent, Peer *peer)
    : QDialog(parent), ui(new Ui::NotificationDialog), peer(peer) {
  ui->setupUi(this);
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
  cout << "Approve button clicked" << endl;

  string usname =
      peer->requests_buffer[ui->listWidget->currentRow()].second.first;
  string imname =
      peer->requests_buffer[ui->listWidget->currentRow()].second.second;

  cout << "ApprovedUser " << usname << " imagename " << imname << endl;
  peer->send_image(usname, imname);
}

void NotificationDialog::on_push_refresh_clicked() {

  // refill list
}
