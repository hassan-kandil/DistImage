#ifndef EDITMYIMAGEDIALOG_H
#define EDITMYIMAGEDIALOG_H

#include <QDialog>
#include "Peer.h"

namespace Ui {
class editmyimageDialog;
}

class editmyimageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit editmyimageDialog(QWidget *parent = nullptr, Peer *peer = nullptr, QString imagename = "");
    ~editmyimageDialog();

private slots:
    void on_push_update_views_clicked();

private:
    Ui::editmyimageDialog *ui;
    Peer *peer;
    QString imagename;
};

#endif // EDITMYIMAGEDIALOG_H
