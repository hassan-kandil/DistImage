#include "mainwindow.h"
#include "seconddialog.h"
#include "ui_mainwindow.h"
#include <QIntValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), peer(new Peer) {
  ui->setupUi(this);
  ui->lbl_login_wrong->setVisible(false);
  ui->lbl_signup_welcome->setVisible(false);
  ui->lbl_dos_error->setVisible(false);
  ui->line_dos_port->setValidator(new QIntValidator); // only numbers

  peer->sc = new UDPSocketClient();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_push_login_clicked() {
  secdia =
      new SecondDialog(); // if want to distroy secdia with the main, put (this)
  secdia->show();
  this->close();
}

void MainWindow::on_push_signup_clicked() {
  // Fill DoS info
  string dos_ip_string = ui->line_dos_ip->text().toStdString();

  peer->dos_ip = new char[dos_ip_string.size() + 1];
  dos_ip_string.copy(peer->dos_ip, dos_ip_string.size() + 1);
  peer->dos_ip[dos_ip_string.size()] = '\0';

  peer->dos_port = 0;
  if (ui->line_dos_port->text().toStdString() != "")
    peer->dos_port = ui->line_dos_port->text().toInt();

  if (dos_ip_string == "" || peer->dos_port == 0) {
    ui->lbl_dos_error->setVisible(true);
  } else {
    ui->lbl_dos_error->setVisible(false);

    string username = ui->line_signup_usr->text().toStdString();
    string password = ui->line_signup_pass->text().toStdString();
    int sign_result = peer->sign_up(username, password);
    if (sign_result == 1){ // Signed up correctly
      ui->lbl_signup_welcome->setVisible(true);
      ui->lbl_signup_welcome->setText(QString("Welcome!"));
      ui->lbl_signup_welcome->setStyleSheet("QLabel { color : green; }");
    }
    else if (sign_result == 3) {
      ui->lbl_signup_welcome->setVisible(true);
      ui->lbl_signup_welcome->setText(QString("No Special Characters!"));
      ui->lbl_signup_welcome->setStyleSheet("QLabel { color : red; }");
    } else if (sign_result == 5){
      ui->lbl_signup_welcome->setVisible(true);
      ui->lbl_signup_welcome->setText(QString("You are already a member!"));
      ui->lbl_signup_welcome->setStyleSheet("QLabel { color : red; }");
    } else{ // Timeout
        ui->lbl_signup_welcome->setVisible(true);
        ui->lbl_signup_welcome->setText(QString("DoS Offline!"));
        ui->lbl_signup_welcome->setStyleSheet("QLabel { color : red; }");
    }
  }
}
