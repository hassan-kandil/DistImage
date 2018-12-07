#ifndef VIEWIMAGEDIALOG_H
#define VIEWIMAGEDIALOG_H

#include "Peer.h"
#include <QDialog>

namespace Ui {
class ViewImageDialog;
}

class ViewImageDialog : public QDialog {
  Q_OBJECT

public:
  explicit ViewImageDialog(QWidget *parent = nullptr, Peer *peer = nullptr, string cover = "",string img = "");
  ~ViewImageDialog();

private:
  Ui::ViewImageDialog *ui;
  Peer *peer;
};

#endif // VIEWIMAGEDIALOG_H
