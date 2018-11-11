#include "notificationdialog.h"
#include "ui_notificationdialog.h"

NotificationDialog::NotificationDialog(QWidget *parent, Peer* peer)
    : QDialog(parent), ui(new Ui::NotificationDialog), peer(peer) {
  ui->setupUi(this);
  for (int i = 0; i < peer->requests_buffer.size(); i++)

  {
        ui->listWidget->addItem(QString::fromStdString(peer->requests_buffer[i]));


  }

}

NotificationDialog::~NotificationDialog() { delete ui; }

void NotificationDialog::on_push_approve_clicked() {}
