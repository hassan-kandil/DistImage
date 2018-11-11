#ifndef VIEWIMAGEDIALOG_H
#define VIEWIMAGEDIALOG_H

#include <QDialog>
#include "Peer.h"

namespace Ui {
class ViewImageDialog;
}

class ViewImageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ViewImageDialog(QWidget *parent = nullptr, Peer *peer = nullptr);
    ~ViewImageDialog();

private:
    Ui::ViewImageDialog *ui;
    Peer *peer;
};

#endif // VIEWIMAGEDIALOG_H
