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

class Ui_ViewImageDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *push_back;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QLabel *lbl_image;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_2;
    QLabel *lbl_error;

    void setupUi(QDialog *ViewImageDialog)
    {
        if (ViewImageDialog->objectName().isEmpty())
            ViewImageDialog->setObjectName(QStringLiteral("ViewImageDialog"));
        ViewImageDialog->resize(500, 500);
        verticalLayout_2 = new QVBoxLayout(ViewImageDialog);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        push_back = new QPushButton(ViewImageDialog);
        push_back->setObjectName(QStringLiteral("push_back"));

        horizontalLayout_2->addWidget(push_back);


        verticalLayout_2->addLayout(horizontalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        lbl_image = new QLabel(ViewImageDialog);
        lbl_image->setObjectName(QStringLiteral("lbl_image"));

        horizontalLayout->addWidget(lbl_image);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        verticalLayout_2->addLayout(verticalLayout);

        lbl_error = new QLabel(ViewImageDialog);
        lbl_error->setObjectName(QStringLiteral("lbl_error"));

        verticalLayout_2->addWidget(lbl_error);


        retranslateUi(ViewImageDialog);
        QObject::connect(push_back, SIGNAL(clicked()), ViewImageDialog, SLOT(close()));

        QMetaObject::connectSlotsByName(ViewImageDialog);
    } // setupUi

    void retranslateUi(QDialog *ViewImageDialog)
    {
        ViewImageDialog->setWindowTitle(QApplication::translate("ViewImageDialog", "DistImage", nullptr));
        push_back->setText(QApplication::translate("ViewImageDialog", "Back", nullptr));
        lbl_image->setText(QApplication::translate("ViewImageDialog", "Image", nullptr));
        lbl_error->setText(QApplication::translate("ViewImageDialog", "Image Error!", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ViewImageDialog: public Ui_ViewImageDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWIMAGEDIALOG_H
