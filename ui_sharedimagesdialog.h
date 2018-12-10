/********************************************************************************
** Form generated from reading UI file 'sharedimagesdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHAREDIMAGESDIALOG_H
#define UI_SHAREDIMAGESDIALOG_H

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

class Ui_SharedImagesDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *push_refresh;
    QSpacerItem *horizontalSpacer_4;
    QLabel *lbl_user;
    QSpacerItem *horizontalSpacer;
    QPushButton *push_back;
    QListWidget *listWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *push_request;
    QSpacerItem *horizontalSpacer_5;
    QLineEdit *line_views;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *push_view;
    QSpacerItem *horizontalSpacer_9;
    QHBoxLayout *horizontalLayout_3;
    QLabel *lbl_result;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_7;
    QLabel *lbl_time;
    QSpacerItem *horizontalSpacer_8;

    void setupUi(QDialog *SharedImagesDialog)
    {
        if (SharedImagesDialog->objectName().isEmpty())
            SharedImagesDialog->setObjectName(QStringLiteral("SharedImagesDialog"));
        SharedImagesDialog->resize(500, 500);
        SharedImagesDialog->setStyleSheet(QLatin1String("background-color: rgb(46, 52, 54)\n"
""));
        verticalLayout = new QVBoxLayout(SharedImagesDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        push_refresh = new QPushButton(SharedImagesDialog);
        push_refresh->setObjectName(QStringLiteral("push_refresh"));
        push_refresh->setStyleSheet(QStringLiteral("color: rgb(238, 238, 236)"));

        horizontalLayout_2->addWidget(push_refresh);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        lbl_user = new QLabel(SharedImagesDialog);
        lbl_user->setObjectName(QStringLiteral("lbl_user"));
        lbl_user->setStyleSheet(QStringLiteral("color: rgb(238, 238, 236)"));

        horizontalLayout_2->addWidget(lbl_user);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        push_back = new QPushButton(SharedImagesDialog);
        push_back->setObjectName(QStringLiteral("push_back"));
        push_back->setStyleSheet(QStringLiteral("color: rgb(238, 238, 236)"));

        horizontalLayout_2->addWidget(push_back);


        verticalLayout->addLayout(horizontalLayout_2);

        listWidget = new QListWidget(SharedImagesDialog);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setStyleSheet(QStringLiteral("color: rgb(238, 238, 236)"));

        verticalLayout->addWidget(listWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        push_request = new QPushButton(SharedImagesDialog);
        push_request->setObjectName(QStringLiteral("push_request"));
        push_request->setStyleSheet(QStringLiteral("color: rgb(238, 238, 236)"));

        horizontalLayout->addWidget(push_request);

        horizontalSpacer_5 = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);

        line_views = new QLineEdit(SharedImagesDialog);
        line_views->setObjectName(QStringLiteral("line_views"));
        line_views->setStyleSheet(QStringLiteral("color: rgb(238, 238, 236)"));

        horizontalLayout->addWidget(line_views);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_6);

        push_view = new QPushButton(SharedImagesDialog);
        push_view->setObjectName(QStringLiteral("push_view"));
        push_view->setStyleSheet(QStringLiteral("color: rgb(238, 238, 236)"));

        horizontalLayout->addWidget(push_view);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_9);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        lbl_result = new QLabel(SharedImagesDialog);
        lbl_result->setObjectName(QStringLiteral("lbl_result"));

        horizontalLayout_3->addWidget(lbl_result);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        lbl_time = new QLabel(SharedImagesDialog);
        lbl_time->setObjectName(QStringLiteral("lbl_time"));
        lbl_time->setStyleSheet(QStringLiteral("color: rgb(238, 238, 236)"));

        horizontalLayout_7->addWidget(lbl_time);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_8);


        verticalLayout->addLayout(horizontalLayout_7);

        QWidget::setTabOrder(listWidget, push_request);
        QWidget::setTabOrder(push_request, push_back);

        retranslateUi(SharedImagesDialog);
        QObject::connect(push_back, SIGNAL(clicked()), SharedImagesDialog, SLOT(close()));

        QMetaObject::connectSlotsByName(SharedImagesDialog);
    } // setupUi

    void retranslateUi(QDialog *SharedImagesDialog)
    {
        SharedImagesDialog->setWindowTitle(QApplication::translate("SharedImagesDialog", "DistImage", nullptr));
        push_refresh->setText(QApplication::translate("SharedImagesDialog", "Refresh", nullptr));
        lbl_user->setText(QApplication::translate("SharedImagesDialog", "Shared Images", nullptr));
        push_back->setText(QApplication::translate("SharedImagesDialog", "Back", nullptr));
        push_request->setText(QApplication::translate("SharedImagesDialog", "Request More Views", nullptr));
        push_view->setText(QApplication::translate("SharedImagesDialog", "View", nullptr));
        lbl_result->setText(QApplication::translate("SharedImagesDialog", "Error", nullptr));
        lbl_time->setText(QApplication::translate("SharedImagesDialog", "Time", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SharedImagesDialog: public Ui_SharedImagesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHAREDIMAGESDIALOG_H
