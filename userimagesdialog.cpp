#include "ui_userimagesdialog.h"
#include "userimagesdialog.h"
#include "viewimagedialog.h"

userimagesdialog::userimagesdialog(QWidget *parent, Peer *peer, QString s)
    : QDialog(parent), ui(new Ui::userimagesdialog), peer(peer),
      selectedUser(s) {
  ui->setupUi(this);
  ui->line_request->setPlaceholderText("No. of Views");
  ui->lbl_request_done->setVisible(false);
  ui->lbl_us->setText(selectedUser);
  vector<string> images;

  images = peer->users[selectedUser.toUtf8().constData()];

  for (int i = 0; i < images.size(); i++) {
    if (i > 2) {

      ui->listWidget->addItem(QString::fromStdString(images[i]));
    }
  }
}

userimagesdialog::~userimagesdialog() { delete ui; }

void userimagesdialog::on_push_request_clicked() {

  cout << "Request button clicked" << endl;

  const QString &s = ui->listWidget->currentItem()->text();

  int result = peer->request_image(selectedUser.toUtf8().constData(),
                                   s.toUtf8().constData());
  if (result == 1) {
    ui->lbl_request_done->setStyleSheet("QLabel { color : green; }");
    ui->lbl_request_done->setText(QString("Request sent!"));
    ui->lbl_request_done->setVisible(true);
  } else if (result == 3) {
    ui->lbl_request_done->setStyleSheet("QLabel { color : red; }");
    ui->lbl_request_done->setText(QString("Request send failed!"));
    ui->lbl_request_done->setVisible(true);
  } else if (result == 0) {
    ui->lbl_request_done->setStyleSheet("QLabel { color : red; }");
    ui->lbl_request_done->setText(
        QString("Request sent before! Wait for owner response!"));
    ui->lbl_request_done->setVisible(true);
  } else if (result == 2) {
    ui->lbl_request_done->setStyleSheet("QLabel { color : red; }");
    ui->lbl_request_done->setText(
        QString("Something went wrong at peer->request_image!"));
    ui->lbl_request_done->setVisible(true);
  } else {
    ui->lbl_request_done->setStyleSheet("QLabel { color : red; }");
    ui->lbl_request_done->setText(QString("Something went wrong here!"));
    ui->lbl_request_done->setVisible(true);
  }
}

void userimagesdialog::temp() {}

void userimagesdialog::on_push_view_clicked() {
  ViewImageDialog secd(this, peer);
  secd.setWindowFlags(Qt::Dialog | Qt::WindowTitleHint |
                      Qt::CustomizeWindowHint);
  secd.setModal(true);
  secd.exec();
}
