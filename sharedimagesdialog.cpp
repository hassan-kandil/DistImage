#include "sharedimagesdialog.h"
#include "ui_sharedimagesdialog.h"
#include <string>
#include "viewimagedialog.h"

SharedImagesDialog::SharedImagesDialog(QWidget *parent, Peer *peer)
    : QDialog(parent), ui(new Ui::SharedImagesDialog), peer(peer) {
  ui->setupUi(this);

  for (auto const &x : peer->sharedimgs) {
    ui->listWidget->addItem(QString::fromStdString("Owner: " + x.second.ownername + ". Img: " + x.first + ". Views Left: " + std::to_string(x.second.viewsnum)));
  }
}

SharedImagesDialog::~SharedImagesDialog() { delete ui; }

void SharedImagesDialog::on_push_view_clicked()
{
    int i=0;
    string cover, img;
    for (auto const &x : peer->sharedimgs) {
        if(ui->listWidget->currentRow() == i){ img = x.first; cover = x.second.ownername + "_" + x.first; break;}
        else i++;
    }
    ViewImageDialog secd(this, peer, cover, img);
    secd.setWindowFlags(Qt::Dialog | Qt::WindowTitleHint |
                        Qt::CustomizeWindowHint);
    secd.setModal(true);
    secd.exec();
}
