#include "notificationdialog.h"
#include "ui_notificationdialog.h"

NotificationDialog::NotificationDialog(QWidget *parent, Peer *peer)
    : QDialog(parent), ui(new Ui::NotificationDialog), peer(peer) {
  ui->setupUi(this);
  for (int i = 0; i < peer->requests_buffer.size(); i++)

  {
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
  // peer->getUsers();
}

NotificationDialog::~NotificationDialog() { delete ui; }

void NotificationDialog::on_push_approve_clicked() {
  cout << "Approve button clicked" << endl;
  // map<string, vector<string>> users;
  // map<string, vector<string>>::iterator it;
  // users = peer->getUsers();
  int i = 0;
  // vector<string> images;
  string usname =
      peer->requests_buffer[ui->listWidget->currentRow()].second.first;
  string imname =
      peer->requests_buffer[ui->listWidget->currentRow()].second.second;
  // images = users[selectedUser.toUtf8().constData()];
  string path;
  // Parsing the path from the image name
  for (int j = imname.length() - 1; j > 0; j--) {

    if (imname[j] == '/') {

      path = imname.substr(0, j);
      break;
    }
  }

  // const QString &s = ui->listWidget->currentItem()->text();
  cout << "ApprovedUser " << usname << " path " << path << " imagename "
       << imname << endl;
  peer->send_image(usname, imname);
}

void NotificationDialog::on_push_refresh_clicked() {
  // peer->getUsers();
  // refill list
}
