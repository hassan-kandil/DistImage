#include "editmyimagedialog.h"
#include "ui_editmyimagedialog.h"
#include <QString>
#include <string>
editmyimageDialog::editmyimageDialog(QWidget *parent, Peer *peer,
                                     QString imagename)
    : QDialog(parent), ui(new Ui::editmyimageDialog), peer(peer),
      imagename(imagename) {
  ui->setupUi(this);
  ui->line_views->setPlaceholderText("Views");
  ui->line_views->setValidator(new QIntValidator); // only numbers
  QPixmap pm(imagename);
  ui->lbl_image->setPixmap(
      pm.scaled(200, 200, Qt::IgnoreAspectRatio, Qt::FastTransformation));
  ui->lbl_time->setText(
      QString::fromStdString("Refreshed: " + peer->getCurrentTime()));
  ui->lbl_time->setStyleSheet("QLabel { color : yellow; }");
  ui->lbl_result->setVisible(false);
  vector<pair<string, int>> selectedViewers =
      peer->myimages[imagename.toStdString()];
  for (int i = 0; i < selectedViewers.size(); i++) {
    if(selectedViewers[i].first != "")
      ui->listWidget->addItem(QString::fromStdString(
        "Viewed User: " + selectedViewers[i].first +
        "Number of Views Left: " + std::to_string(selectedViewers[i].second)));
  }
}

editmyimageDialog::~editmyimageDialog() { delete ui; }

void editmyimageDialog::on_push_update_views_clicked() {
    if (ui->listWidget->currentRow() >= 0) {
        if(ui->line_views->text() != ""){

    int noViews = ui->line_views->text().toInt();
    if (noViews < 0) {
      ui->lbl_result->setVisible(true);
      ui->lbl_result->setText("Invalid Views");
      ui->lbl_result->setStyleSheet("QLabel { color : magenta; }");
    } else {
      vector<pair<string, int>> selectedViewers =
          peer->myimages[imagename.toStdString()];
      string viewer = selectedViewers[ui->listWidget->currentRow()].first;
      int resultUsers = peer->update_views_by_owner(viewer, imagename.toStdString(), noViews);
    if(resultUsers == 1){
      ui->lbl_result->setVisible(true);
      ui->lbl_result->setStyleSheet("QLabel { color : green; }");
      ui->lbl_result->setText("Views Topped Up!");
    }
    else if(resultUsers == 12){
      ui->lbl_result->setVisible(true);
      ui->lbl_result->setStyleSheet("QLabel { color : magenta; }");
      ui->lbl_result->setText("Server Unreachable");
    }
    else if(resultUsers == 10){
      ui->lbl_result->setVisible(true);
      ui->lbl_result->setStyleSheet("QLabel { color : magenta; }");
      ui->lbl_result->setText("Sending Failed"); // send failed
    }
    else if(resultUsers == 0){
      ui->lbl_result->setVisible(true);
      ui->lbl_result->setStyleSheet("QLabel { color : magenta; }");
      ui->lbl_result->setText("Failed To Top Up Views"); // update_views_by_owner at viewer failed!
    }
    else{
      ui->lbl_result->setVisible(true);
      ui->lbl_result->setStyleSheet("QLabel { color : magenta; }");
      ui->lbl_result->setText("Problem with internet connection"); // something wrong
    }
    }
        } else{
            ui->lbl_result->setVisible(true);
            ui->lbl_result->setStyleSheet("QLabel { color : magenta; }");
            ui->lbl_result->setText("Specify Amount of Desired Views");
        }

    } else {
      ui->lbl_result->setVisible(true);
      ui->lbl_result->setStyleSheet("QLabel { color : magenta; }");
      ui->lbl_result->setText("Select A Viewer");
    }
}

void editmyimageDialog::on_push_refresh_clicked()
{
    ui->listWidget->clear();
    ui->lbl_time->setText(
        QString::fromStdString("Refreshed at " + peer->getCurrentTime()));
    ui->lbl_time->setStyleSheet("QLabel { color : yellow; }");
    ui->lbl_result->setVisible(false);
    vector<pair<string, int>> selectedViewers =
        peer->myimages[imagename.toStdString()];
    for (int i = 0; i < selectedViewers.size(); i++) {
      ui->listWidget->addItem(QString::fromStdString(
          "Viewed User: " + selectedViewers[i].first +
          "Number of Views Left: " + std::to_string(selectedViewers[i].second)));
    }
}
