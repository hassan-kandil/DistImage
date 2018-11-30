/********************************************************************************
** Form generated from reading UI file 'usersdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERSDIALOG_H
#define UI_USERSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_UsersDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *push_refresh;
    QSpacerItem *horizontalSpacer;
    QPushButton *push_back;
    QListWidget *listWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *push_view;
    QSpacerItem *horizontalSpacer_5;
    QLabel *lbl_offline;

    void setupUi(QDialog *UsersDialog)
    {
        if (UsersDialog->objectName().isEmpty())
            UsersDialog->setObjectName(QStringLiteral("UsersDialog"));
        UsersDialog->resize(500, 500);
        verticalLayout = new QVBoxLayout(UsersDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        push_refresh = new QPushButton(UsersDialog);
        push_refresh->setObjectName(QStringLiteral("push_refresh"));

        horizontalLayout_2->addWidget(push_refresh);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        push_back = new QPushButton(UsersDialog);
        push_back->setObjectName(QStringLiteral("push_back"));

        horizontalLayout_2->addWidget(push_back);


        verticalLayout->addLayout(horizontalLayout_2);

        listWidget = new QListWidget(UsersDialog);
        listWidget->setObjectName(QStringLiteral("listWidget"));

        verticalLayout->addWidget(listWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        push_view = new QPushButton(UsersDialog);
        push_view->setObjectName(QStringLiteral("push_view"));

        horizontalLayout->addWidget(push_view);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);


        verticalLayout->addLayout(horizontalLayout);

        lbl_offline = new QLabel(UsersDialog);
        lbl_offline->setObjectName(QStringLiteral("lbl_offline"));

        verticalLayout->addWidget(lbl_offline);

        QWidget::setTabOrder(listWidget, push_view);
        QWidget::setTabOrder(push_view, push_refresh);
        QWidget::setTabOrder(push_refresh, push_back);

        retranslateUi(UsersDialog);
        QObject::connect(push_back, SIGNAL(clicked()), UsersDialog, SLOT(close()));

        QMetaObject::connectSlotsByName(UsersDialog);
    } // setupUi

    void retranslateUi(QDialog *UsersDialog)
    {
        UsersDialog->setWindowTitle(QApplication::translate("UsersDialog", "DistImage", nullptr));
        push_refresh->setText(QApplication::translate("UsersDialog", "Refresh", nullptr));
        push_back->setText(QApplication::translate("UsersDialog", "Back", nullptr));
        push_view->setText(QApplication::translate("UsersDialog", "View Selected User Images", nullptr));
        lbl_offline->setText(QApplication::translate("UsersDialog", "Selected User is Offline!", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UsersDialog: public Ui_UsersDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERSDIALOG_H
