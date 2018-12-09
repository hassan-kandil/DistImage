/********************************************************************************
** Form generated from reading UI file 'notificationdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOTIFICATIONDIALOG_H
#define UI_NOTIFICATIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_NotificationDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *push_refresh;
    QSpacerItem *horizontalSpacer;
    QPushButton *push_back;
    QListWidget *listWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *push_approve;
    QSpacerItem *horizontalSpacer_6;
    QLineEdit *line_views;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *push_disapprove;
    QSpacerItem *horizontalSpacer_7;
    QHBoxLayout *horizontalLayout_3;
    QLabel *lbl_result;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_7;
    QLabel *lbl_time;
    QSpacerItem *horizontalSpacer_8;

    void setupUi(QDialog *NotificationDialog)
    {
        if (NotificationDialog->objectName().isEmpty())
            NotificationDialog->setObjectName(QStringLiteral("NotificationDialog"));
        NotificationDialog->resize(500, 500);
        NotificationDialog->setStyleSheet(QLatin1String("background-color: rgb(46, 52, 54)\n"
""));
        verticalLayout = new QVBoxLayout(NotificationDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        push_refresh = new QPushButton(NotificationDialog);
        push_refresh->setObjectName(QStringLiteral("push_refresh"));
        push_refresh->setStyleSheet(QStringLiteral("color: rgb(238, 238, 236)"));

        horizontalLayout_2->addWidget(push_refresh);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        push_back = new QPushButton(NotificationDialog);
        push_back->setObjectName(QStringLiteral("push_back"));
        push_back->setStyleSheet(QStringLiteral("color: rgb(238, 238, 236)"));

        horizontalLayout_2->addWidget(push_back);


        verticalLayout->addLayout(horizontalLayout_2);

        listWidget = new QListWidget(NotificationDialog);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setAutoFillBackground(false);
        listWidget->setStyleSheet(QStringLiteral("color: rgb(238, 238, 236)"));

        verticalLayout->addWidget(listWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        push_approve = new QPushButton(NotificationDialog);
        push_approve->setObjectName(QStringLiteral("push_approve"));
        push_approve->setStyleSheet(QStringLiteral("color: rgb(238, 238, 236)"));

        horizontalLayout->addWidget(push_approve);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_6);

        line_views = new QLineEdit(NotificationDialog);
        line_views->setObjectName(QStringLiteral("line_views"));
        line_views->setStyleSheet(QStringLiteral("color: rgb(238, 238, 236)"));

        horizontalLayout->addWidget(line_views);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);

        push_disapprove = new QPushButton(NotificationDialog);
        push_disapprove->setObjectName(QStringLiteral("push_disapprove"));
        push_disapprove->setStyleSheet(QStringLiteral("color: rgb(238, 238, 236)"));

        horizontalLayout->addWidget(push_disapprove);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_7);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        lbl_result = new QLabel(NotificationDialog);
        lbl_result->setObjectName(QStringLiteral("lbl_result"));

        horizontalLayout_3->addWidget(lbl_result);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        lbl_time = new QLabel(NotificationDialog);
        lbl_time->setObjectName(QStringLiteral("lbl_time"));
        lbl_time->setStyleSheet(QStringLiteral("color: rgb(238, 238, 236)"));

        horizontalLayout_7->addWidget(lbl_time);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_8);


        verticalLayout->addLayout(horizontalLayout_7);

        QWidget::setTabOrder(listWidget, push_approve);
        QWidget::setTabOrder(push_approve, push_refresh);
        QWidget::setTabOrder(push_refresh, push_back);

        retranslateUi(NotificationDialog);
        QObject::connect(push_back, SIGNAL(clicked()), NotificationDialog, SLOT(close()));

        QMetaObject::connectSlotsByName(NotificationDialog);
    } // setupUi

    void retranslateUi(QDialog *NotificationDialog)
    {
        NotificationDialog->setWindowTitle(QApplication::translate("NotificationDialog", "DistImage", nullptr));
        push_refresh->setText(QApplication::translate("NotificationDialog", "Refresh", nullptr));
        push_back->setText(QApplication::translate("NotificationDialog", "Back", nullptr));
        push_approve->setText(QApplication::translate("NotificationDialog", "Approve", nullptr));
        line_views->setText(QString());
        push_disapprove->setText(QApplication::translate("NotificationDialog", "Delete", nullptr));
        lbl_result->setText(QApplication::translate("NotificationDialog", "Approved", nullptr));
        lbl_time->setText(QApplication::translate("NotificationDialog", "Time", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NotificationDialog: public Ui_NotificationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOTIFICATIONDIALOG_H
