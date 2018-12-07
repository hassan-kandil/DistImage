#include "sharedimagesdialog.h"
#include "ui_sharedimagesdialog.h"
#include <string>
#include "viewimagedialog.h"

SharedImagesDialog::SharedImagesDialog(QWidget *parent, Peer *peer)
    : QDialog(parent), ui(new Ui::SharedImagesDialog), peer(peer) {
  ui->setupUi(this);
  ui->lbl_result->setVisible(false);
  for (auto const &x : peer->sharedimgs) {
    ui->listWidget->addItem(QString::fromStdString("Owner: " + x.second.ownername + ". Img: " + x.first + ". Views Left: " + std::to_string(x.second.viewsnum)));
  }
}

SharedImagesDialog::~SharedImagesDialog() { delete ui; }

void SharedImagesDialog::on_push_view_clicked()
{
    int i=0;
    string cover, img;
    int views = 0;
    for (auto const &x : peer->sharedimgs) {
        if(ui->listWidget->currentRow() == i){ img = x.first; cover = x.second.ownername + "_" + x.first; views = x.second.viewsnum; break;}
        else i++;
    }
    if(views > 0){
        ui->lbl_result->setVisible(false);
        peer->sharedimgs[img].viewsnum--;
        ViewImageDialog secd(this, peer, cover, img);
        secd.setWindowFlags(Qt::Dialog | Qt::WindowTitleHint |
                            Qt::CustomizeWindowHint);
        secd.setModal(true);
        secd.exec();
    }
    else{
        ui->lbl_result->setVisible(true);
        ui->lbl_result->setText(QString("You don't have enough views!"));
        ui->lbl_result->setStyleSheet("QLabel { color : red; }");

        // get any updates before displaying image
        ui->listWidget->clear();
        for (auto const &x : peer->sharedimgs) {
          ui->listWidget->addItem(QString::fromStdString("Owner: " + x.second.ownername + ". Img: " + x.first + ". Views Left: " + std::to_string(x.second.viewsnum)));
        }
    }
}

void SharedImagesDialog::on_push_refresh_clicked()
{
    // get any updates
    ui->listWidget->clear();
    for (auto const &x : peer->sharedimgs) {
      ui->listWidget->addItem(QString::fromStdString("Owner: " + x.second.ownername + ". Img: " + x.first + ". Views Left: " + std::to_string(x.second.viewsnum)));
    }
}
