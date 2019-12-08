#include "ui_userimagesdialog.h"
#include "userimagesdialog.h"
#include "viewimagedialog.h"
#include <QString>
userimagesdialog::userimagesdialog(QWidget *parent, Peer *peer, QString s)
    : QDialog(parent), ui(new Ui::userimagesdialog), peer(peer),
      selectedUser(s) {
  ui->setupUi(this);
  ui->line_views->setPlaceholderText("Views");
  ui->lbl_time->setText(
      QString::fromStdString("Refreshed at " + peer->getCurrentTime()));
  ui->lbl_time->setStyleSheet("QLabel { color : yellow; }");
  ui->line_views->setPlaceholderText("Views");
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
                ui->lbl_result->setStyleSheet("QLabel { color : yellow; }");
                ui->lbl_result->setText(QString("Request sent"));
                ui->lbl_result->setVisible(true);
              } else if (result == 3) {
                ui->lbl_result->setStyleSheet("QLabel { color : magenta; }");
                ui->lbl_result->setText(QString("Request Sending Failed")); // Request send failed!
                ui->lbl_result->setVisible(true);
              } else if (result == 0) {
                ui->lbl_result->setStyleSheet("QLabel { color : magenta; }");
                ui->lbl_result->setText(
                    QString("Request already Sent,  Wait for user reply .. "));
                ui->lbl_result->setVisible(true);
              } else if (result == 2) {
                ui->lbl_result->setStyleSheet("QLabel { color : magenta; }");
                ui->lbl_result->setText(
                    QString("Problem with internet connection!"));
                ui->lbl_result->setVisible(true);
              } else {
                ui->lbl_result->setStyleSheet("QLabel { color : magenta; }");
                ui->lbl_result->setText(QString("Problem with internet connection!"));
                ui->lbl_result->setVisible(true);
              }
          }
          else{
              ui->lbl_result->setVisible(true);
              ui->lbl_result->setStyleSheet("QLabel { color : magenta; }");
              ui->lbl_result->setText("Image already shared with you, request to top up your views.");
          }
      } else{
          ui->lbl_result->setVisible(true);
          ui->lbl_result->setStyleSheet("QLabel { color : magenta; }");
          ui->lbl_result->setText("Specify Amount of Desired Views");
      }
  } else {
    ui->lbl_result->setVisible(true);
    ui->lbl_result->setStyleSheet("QLabel { color : magenta; }");
    ui->lbl_result->setText("Choose an image!");
  }
}

void userimagesdialog::temp() {}

void userimagesdialog::on_push_view_clicked() { // view from shared

}
