#include "editmyimagedialog.h"
#include "ui_editmyimagedialog.h"
#include <QString>
#include <string>
editmyimageDialog::editmyimageDialog(QWidget *parent, Peer *peer,
                                     QString imagename)
    : QDialog(parent), ui(new Ui::editmyimageDialog), peer(peer),
      imagename(imagename) {
  ui->setupUi(this);
  ui->lbl_time->setText(
      QString::fromStdString("Last Time Refreshed: " + peer->getCurrentTime()));
  ui->lbl_time->setStyleSheet("QLabel { color : blue; }");
  ui->lbl_result->setVisible(false);
  vector<pair<string, int>> selectedViewers =
      peer->myimages[imagename.toStdString()];
  for (int i = 0; i < selectedViewers.size(); i++) {
    ui->listWidget->addItem(QString::fromStdString(
        "Viewer: " + selectedViewers[i].first +
        ". Views Left: " + std::to_string(selectedViewers[i].second)));
  }
}

editmyimageDialog::~editmyimageDialog() { delete ui; }

void editmyimageDialog::on_push_update_views_clicked() {
  if (ui->listWidget->currentRow() >= 0) {
    int noViews = ui->line_reqviews->text().toInt();
    if (noViews < 0) {
      ui->lbl_result->setVisible(true);
      ui->lbl_result->setText("Please, add the number of views >= 0");
      ui->lbl_result->setStyleSheet("QLabel { color : red; }");
    } else {
      vector<pair<string, int>> selectedViewers =
          peer->myimages[imagename.toStdString()];
      string viewer = selectedViewers[ui->listWidget->currentRow()].first;
      cout << imagename.toStdString() << viewer << noViews << endl;
      peer->update_views_by_owner(viewer, imagename.toStdString(), noViews);
    }
  } else {
    ui->lbl_result->setVisible(true);
    ui->lbl_result->setStyleSheet("QLabel { color : red; }");
    ui->lbl_result->setText("Please, select a user!");
  }
}
