#include "userimagesdialog.h"
#include "ui_userimagesdialog.h"

userimagesdialog::userimagesdialog(QWidget *parent, Peer* peer, QString s) :
    QDialog(parent), ui(new Ui::userimagesdialog), peer(peer), selectedUser(s)
{
    ui->setupUi(this);

    map <string, vector<string>> users;
    map<string, vector<string>>::iterator it;
    users = peer->getUsers();
      int i = 0;
      vector <string> images;

      images = users[selectedUser.toUtf8().constData()];


      for (int i = 0; i<images.size();i++){

          ui->listWidget->addItem(QString::fromStdString(images[i]));


      }

}

userimagesdialog::~userimagesdialog()
{
    delete ui;
}
