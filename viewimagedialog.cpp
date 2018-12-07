#include "ui_viewimagedialog.h"
#include "viewimagedialog.h"
#include <qpicture.h>

ViewImageDialog::ViewImageDialog(QWidget *parent, Peer *peer, string cover, string img)
    : QDialog(parent), ui(new Ui::ViewImageDialog), peer(peer) {
  ui->setupUi(this);
  ui->lbl_error->setVisible(false);


  string extract_command;

  extract_command = "steghide extract -sf " + cover +
                    " -p hk"; // + " -xf " + newViewsName

  QProcess::execute(QString::fromStdString(extract_command));
  QPixmap pm(QString::fromStdString(img));
  ui->lbl_image->setPixmap(pm);

  // deleting the extracted image from the receiver's folder after
  // extracting the number of views
  string deletecommand = "rm " + img;

  QProcess::execute(QString::fromStdString(deletecommand));
}

ViewImageDialog::~ViewImageDialog() { delete ui; }
