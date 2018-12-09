#include "sharedimagesdialog.h"
#include "ui_sharedimagesdialog.h"
#include "viewimagedialog.h"
#include <string>

SharedImagesDialog::SharedImagesDialog(QWidget *parent, Peer *peer)
    : QDialog(parent), ui(new Ui::SharedImagesDialog), peer(peer) {
  ui->setupUi(this);
  ui->lbl_time->setText(
      QString::fromStdString("Last Time Refreshed: " + peer->getCurrentTime()));
  ui->lbl_time->setStyleSheet("QLabel { color : white; }");
  ui->lbl_result->setVisible(false);
  string imagename, ownername, fullname;
  for (auto const &x : peer->sharedimgs) {
    fullname = x.first;
    for (int j = fullname.length() - 1; j > 0; j--) {
      if (fullname[j] == '_') {
        ownername = fullname.substr(0, j);
        imagename = fullname.substr(j + 1, fullname.length() - 1);
        break;
      }
    }
    ui->listWidget->addItem(
        QString::fromStdString("Owner: " + ownername + ". Img: " + imagename +
                               ". Views Left: " + std::to_string(x.second)));
  }
}

SharedImagesDialog::~SharedImagesDialog() { delete ui; }

void SharedImagesDialog::on_push_view_clicked() {
  if (ui->listWidget->currentRow() >= 0) {
    int i = 0;
    int views = 0;
    string imagename, ownername, fullname, img, cover;
    for (auto const &x : peer->sharedimgs) {
      fullname = x.first;
      for (int j = fullname.length() - 1; j > 0; j--) {
        if (fullname[j] == '_') {
          ownername = fullname.substr(0, j);
          imagename = fullname.substr(j + 1, fullname.length() - 1);
          break;
        }
      }
      if (ui->listWidget->currentRow() == i) {
        img = imagename;
        cover = fullname;
        views = x.second;
        break;
      } else
        i++;
    }
    if (views > 0) {
      ui->lbl_result->setVisible(false);
      peer->sharedimgs[cover]--;
      cout << ownername << " " << imagename << " " << peer->sharedimgs[cover]
           << endl;
      int resultUsers = peer->notify_views_by_viewer(ownername, imagename,
                                   peer->sharedimgs[cover]);
      if(resultUsers == 1){
      ViewImageDialog secd(this, peer, cover, img);
      secd.setWindowFlags(Qt::Dialog | Qt::WindowTitleHint |
                          Qt::CustomizeWindowHint);
      secd.setModal(true);
      secd.exec();
      }
      else if(resultUsers == 12){
        ui->lbl_result->setVisible(true);
        ui->lbl_result->setStyleSheet("QLabel { color : red; }");
        ui->lbl_result->setText("DoS Offline!");
      }
      else if(resultUsers == 10){
        ui->lbl_result->setVisible(true);
        ui->lbl_result->setStyleSheet("QLabel { color : red; }");
        ui->lbl_result->setText("Getusers send failed!");
      }
      else if(resultUsers == 0){
        ui->lbl_result->setVisible(true);
        ui->lbl_result->setStyleSheet("QLabel { color : red; }");
        ui->lbl_result->setText("notify_views_by_viewer at viewer failed!");
      }
      else{
        ui->lbl_result->setVisible(true);
        ui->lbl_result->setStyleSheet("QLabel { color : red; }");
        ui->lbl_result->setText("Something wrong getusers!");
      }
    } else {
      ui->lbl_result->setVisible(true);
      ui->lbl_result->setText(QString("You don't have enough views!"));
      ui->lbl_result->setStyleSheet("QLabel { color : red; }");

      // get any updates before displaying image
      ui->listWidget->clear();
      ui->lbl_time->setText(QString::fromStdString("Last Time Refreshed: " +
                                                   peer->getCurrentTime()));
      ui->lbl_time->setStyleSheet("QLabel { color : white; }");
      for (auto const &x : peer->sharedimgs) {
        fullname = x.first;
        for (int j = fullname.length() - 1; j > 0; j--) {
          if (fullname[j] == '_') {
            ownername = fullname.substr(0, j);
            imagename = fullname.substr(j + 1, fullname.length() - 1);
            break;
          }
        }
        ui->listWidget->addItem(QString::fromStdString(
            "Owner: " + ownername + ". Img: " + imagename +
            ". Views Left: " + std::to_string(x.second)));
      }
    }
  } else {
    ui->lbl_result->setVisible(true);
    ui->lbl_result->setStyleSheet("QLabel { color : red; }");
    ui->lbl_result->setText("Please, select an image!");
  }
}

void SharedImagesDialog::on_push_refresh_clicked() {
  // get any updates
    ui->lbl_result->setVisible(false);
  ui->listWidget->clear();
  ui->lbl_time->setText(
      QString::fromStdString("Last Time Refreshed: " + peer->getCurrentTime()));
  ui->lbl_time->setStyleSheet("QLabel { color : white; }");
  string fullname, imagename, ownername;
  for (auto const &x : peer->sharedimgs) {
    fullname = x.first;
    for (int j = fullname.length() - 1; j > 0; j--) {
      if (fullname[j] == '_') {
        ownername = fullname.substr(0, j);
        imagename = fullname.substr(j + 1, fullname.length() - 1);
        break;
      }
    }
    ui->listWidget->addItem(
        QString::fromStdString("Owner: " + ownername + ". Img: " + imagename +
                               ". Views Left: " + std::to_string(x.second)));
  }
}

void SharedImagesDialog::on_push_request_clicked()
{
    if (ui->listWidget->currentRow() >= 0) {
        if(ui->line_views->text() != ""){
        int i = 0;
        string imagename, ownername, fullname;
        int noViews = ui->line_views->text().toInt();
        for (auto const &x : peer->sharedimgs) {
            if(i == ui->listWidget->currentRow()){
                fullname = x.first;
                for (int j = fullname.length() - 1; j > 0; j--) {
                  if (fullname[j] == '_') {
                    ownername = fullname.substr(0, j);
                    imagename = fullname.substr(j + 1, fullname.length() - 1);
                    break;
                  }
                }

            }
          i++;
        }
        int result = peer->update_views_request_by_viewer(ownername, imagename, noViews);
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
        }
        else if(result == 12){
          ui->lbl_result->setVisible(true);
          ui->lbl_result->setStyleSheet("QLabel { color : red; }");
          ui->lbl_result->setText("DoS Offline!");
        }
        else if(result == 10){
          ui->lbl_result->setVisible(true);
          ui->lbl_result->setStyleSheet("QLabel { color : red; }");
          ui->lbl_result->setText("Getusers send failed!");
        }
        else {
          ui->lbl_result->setStyleSheet("QLabel { color : red; }");
          ui->lbl_result->setText(QString("Something went wrong here!"));
          ui->lbl_result->setVisible(true);
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
