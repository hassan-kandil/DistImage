/********************************************************************************
** Form generated from reading UI file 'myimagesdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYIMAGESDIALOG_H
#define UI_MYIMAGESDIALOG_H

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

class Ui_MyImagesDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *lbl_user;
    QSpacerItem *horizontalSpacer;
    QPushButton *push_back;
    QListWidget *listWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *push_view;
    QSpacerItem *horizontalSpacer_7;
    QHBoxLayout *horizontalLayout_3;
    QLabel *lbl_result;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_7;
    QLabel *lbl_time;
    QSpacerItem *horizontalSpacer_8;

    void setupUi(QDialog *MyImagesDialog)
    {
        if (MyImagesDialog->objectName().isEmpty())
            MyImagesDialog->setObjectName(QStringLiteral("MyImagesDialog"));
        MyImagesDialog->resize(500, 500);
        MyImagesDialog->setStyleSheet(QLatin1String("background-color: rgb(46, 52, 54)\n"
""));
        verticalLayout = new QVBoxLayout(MyImagesDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        lbl_user = new QLabel(MyImagesDialog);
        lbl_user->setObjectName(QStringLiteral("lbl_user"));
        lbl_user->setStyleSheet(QStringLiteral("color: rgb(238, 238, 236)"));

        horizontalLayout_2->addWidget(lbl_user);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        push_back = new QPushButton(MyImagesDialog);
        push_back->setObjectName(QStringLiteral("push_back"));
        push_back->setStyleSheet(QStringLiteral("color: rgb(238, 238, 236)"));

        horizontalLayout_2->addWidget(push_back);


        verticalLayout->addLayout(horizontalLayout_2);

        listWidget = new QListWidget(MyImagesDialog);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setStyleSheet(QStringLiteral("color: rgb(238, 238, 236)"));

        verticalLayout->addWidget(listWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        push_view = new QPushButton(MyImagesDialog);
        push_view->setObjectName(QStringLiteral("push_view"));
        push_view->setStyleSheet(QStringLiteral("color: rgb(238, 238, 236)"));

        horizontalLayout->addWidget(push_view);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_7);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        lbl_result = new QLabel(MyImagesDialog);
        lbl_result->setObjectName(QStringLiteral("lbl_result"));

        horizontalLayout_3->addWidget(lbl_result);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        lbl_time = new QLabel(MyImagesDialog);
        lbl_time->setObjectName(QStringLiteral("lbl_time"));
        lbl_time->setStyleSheet(QStringLiteral("color: rgb(238, 238, 236)"));

        horizontalLayout_7->addWidget(lbl_time);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_8);


        verticalLayout->addLayout(horizontalLayout_7);

        QWidget::setTabOrder(listWidget, push_back);

        retranslateUi(MyImagesDialog);
        QObject::connect(push_back, SIGNAL(clicked()), MyImagesDialog, SLOT(close()));

        QMetaObject::connectSlotsByName(MyImagesDialog);
    } // setupUi

    void retranslateUi(QDialog *MyImagesDialog)
    {
        MyImagesDialog->setWindowTitle(QApplication::translate("MyImagesDialog", "DistImage", nullptr));
        lbl_user->setText(QApplication::translate("MyImagesDialog", "User", nullptr));
        push_back->setText(QApplication::translate("MyImagesDialog", "Back", nullptr));
        push_view->setText(QApplication::translate("MyImagesDialog", "Show Viewers", nullptr));
        lbl_result->setText(QApplication::translate("MyImagesDialog", "TextLabel", nullptr));
        lbl_time->setText(QApplication::translate("MyImagesDialog", "Time", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyImagesDialog: public Ui_MyImagesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYIMAGESDIALOG_H
