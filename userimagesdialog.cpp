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

void userimagesdialog::on_push_request_clicked()
{

    cout << "Request button clicked" << endl;
    map<string, vector<string>> users;
    map<string, vector<string>>::iterator it;
    users = peer->getUsers();
    int i = 0;
    vector<string> images;

    images = users[selectedUser.toUtf8().constData()];
    string path;
    for (int j = images[3].length() - 1; j > 0; j--) {

        if (images[3][j] == '/') {

             path = images[3].substr(0, j);
            break;
        }
    }

    const QString &s = ui->listWidget->currentItem()->text();
    cout << "selectedUser " << selectedUser.toUtf8().constData() << " parh" << path << endl;
    peer->request_image(selectedUser.toUtf8().constData(), s.toUtf8().constData(), path);

}


void userimagesdialog::temp()
{

}

