#include "myimagesdialog.h"
#include "ui_myimagesdialog.h"

MyImagesDialog::MyImagesDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::MyImagesDialog) {
  ui->setupUi(this);
  ui->listWidget->addItem("Image 1");
  ui->listWidget->addItem("Image 2");
  ui->listWidget->addItem("Image 3");
}

MyImagesDialog::~MyImagesDialog() { delete ui; }

void MyImagesDialog::on_push_request_clicked() {}
