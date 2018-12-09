#include "ui_userimagesdialog.h"
#include "userimagesdialog.h"
#include "viewimagedialog.h"
#include <QString>
userimagesdialog::userimagesdialog(QWidget *parent, Peer *peer, QString s)
    : QDialog(parent), ui(new Ui::userimagesdialog), peer(peer),
      selectedUser(s) {
  ui->setupUi(this);
  ui->lbl_time->setText(
      QString::fromStdString("Last Time Refreshed: " + peer->getCurrentTime()));
  ui->lbl_time->setStyleSheet("QLabel { color : white; }");
  ui->line_views->setPlaceholderText("No. of Views");
  ui->lbl_result->setVisible(false);
  ui->lbl_us->setText(selectedUser);
  vector<string> images;

  images = peer->users[selectedUser.toUtf8().constData()];

  for (int i = 0; i < images.size(); i++) {
    if (i > 2) {
      ui->listWidget->addItem(QString::fromStdString(images[i]));
    }
  }
  ui->line_views->setValidator(new QIntValidator); // only numbers
}

userimagesdialog::~userimagesdialog() { delete ui; }

void userimagesdialog::on_push_request_clicked() {
  if (ui->listWidget->currentRow() >= 0) {
      if(ui->line_views->text() != ""){
          cout << "Request button clicked" << endl;

          QString s = ui->listWidget->currentItem()->text();

          QString fullImageName = selectedUser + "_" + s;
          // Is it already on my pc?
          if(peer->sharedimgs.count(fullImageName.toUtf8().constData()) == 0){
              int result = peer->request_image(selectedUser.toUtf8().constData(),
                                               s.toUtf8().constData(), ui->line_views->text().toInt());
              if (result == 1) {
                ui->lbl_result->setStyleSheet("QLabel { color : green; }");
                ui->lbl_result->setText(QString("Request sent!"));
                ui->lbl_result->setVisible(true);
              } else if (result == 3) {
                ui->lbl_result->setStyleSheet("QLabel { color : red; }");
                ui->lbl_result->setText(QString("Request send failed!"));
                ui->lbl_result->setVisible(true);
              } else if (result == 0) {
                ui->lbl_result->setStyleSheet("QLabel { color : red; }");
                ui->lbl_result->setText(
                    QString("Request sent before! Wait for owner response!"));
                ui->lbl_result->setVisible(true);
              } else if (result == 2) {
                ui->lbl_result->setStyleSheet("QLabel { color : red; }");
                ui->lbl_result->setText(
                    QString("Something went wrong at peer->request_image!"));
                ui->lbl_result->setVisible(true);
              } else {
                ui->lbl_result->setStyleSheet("QLabel { color : red; }");
                ui->lbl_result->setText(QString("Something went wrong here!"));
                ui->lbl_result->setVisible(true);
              }
          }
          else{
              ui->lbl_result->setVisible(true);
              ui->lbl_result->setStyleSheet("QLabel { color : red; }");
              ui->lbl_result->setText("Image shared with you before! Request more views from Shared Images!");
          }
      } else{
          ui->lbl_result->setVisible(true);
          ui->lbl_result->setStyleSheet("QLabel { color : red; }");
          ui->lbl_result->setText("Please, enter the amount of views you want!");
      }
  } else {
    ui->lbl_result->setVisible(true);
    ui->lbl_result->setStyleSheet("QLabel { color : red; }");
    ui->lbl_result->setText("Please, select an image!");
  }
}

void userimagesdialog::temp() {}

void userimagesdialog::on_push_view_clicked() { // view from shared

}
