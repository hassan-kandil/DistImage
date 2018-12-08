/********************************************************************************
** Form generated from reading UI file 'viewimagedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEWIMAGEDIALOG_H
#define UI_VIEWIMAGEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ViewImageDialog {
public:
  QVBoxLayout *verticalLayout;
  QHBoxLayout *horizontalLayout_2;
  QSpacerItem *horizontalSpacer;
  QPushButton *push_back;
  QLabel *lbl_image;
  QLabel *lbl_error;

  void setupUi(QDialog *ViewImageDialog) {
    if (ViewImageDialog->objectName().isEmpty())
      ViewImageDialog->setObjectName(QStringLiteral("ViewImageDialog"));
    ViewImageDialog->resize(500, 500);
    verticalLayout = new QVBoxLayout(ViewImageDialog);
    verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
    horizontalLayout_2 = new QHBoxLayout();
    horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
    horizontalSpacer =
        new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout_2->addItem(horizontalSpacer);

    push_back = new QPushButton(ViewImageDialog);
    push_back->setObjectName(QStringLiteral("push_back"));

    horizontalLayout_2->addWidget(push_back);

    verticalLayout->addLayout(horizontalLayout_2);

    lbl_image = new QLabel(ViewImageDialog);
    lbl_image->setObjectName(QStringLiteral("lbl_image"));

    verticalLayout->addWidget(lbl_image);

    lbl_error = new QLabel(ViewImageDialog);
    lbl_error->setObjectName(QStringLiteral("lbl_error"));

    verticalLayout->addWidget(lbl_error);

    retranslateUi(ViewImageDialog);
    QObject::connect(push_back, SIGNAL(clicked()), ViewImageDialog,
                     SLOT(close()));

    QMetaObject::connectSlotsByName(ViewImageDialog);
  } // setupUi

  void retranslateUi(QDialog *ViewImageDialog) {
    ViewImageDialog->setWindowTitle(
        QApplication::translate("ViewImageDialog", "DistImage", nullptr));
    push_back->setText(
        QApplication::translate("ViewImageDialog", "Back", nullptr));
    lbl_image->setText(QString());
    lbl_error->setText(
        QApplication::translate("ViewImageDialog", "Image Error!", nullptr));
  } // retranslateUi
};

namespace Ui {
class ViewImageDialog : public Ui_ViewImageDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWIMAGEDIALOG_H
