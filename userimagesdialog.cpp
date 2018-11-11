#include "ui_userimagesdialog.h"
#include "userimagesdialog.h"

userimagesdialog::userimagesdialog(QWidget *parent, Peer *peer, QString s)
    : QDialog(parent), ui(new Ui::userimagesdialog), peer(peer),
      selectedUser(s) {
  ui->setupUi(this);
    ui->line_request->setPlaceholderText("No. of Views");
  map<string, vector<string>> users;
  map<string, vector<string>>::iterator it;
  users = peer->getUsers();
  int i = 0;
  vector<string> images;

  images = users[selectedUser.toUtf8().constData()];

  for (int i = 0; i < images.size(); i++) {
    string imageonly;
    if(i > 2){
      for (int j = images[i].length() - 1; j > 0; j--) {

        if (images[i][j] == '/') {

          imageonly = images[i].substr(j+1, images[i].length() - 1);
          break;
        }
      }

    ui->listWidget->addItem(QString::fromStdString(imageonly));
    }
  }
}

userimagesdialog::~userimagesdialog() { delete ui; }
