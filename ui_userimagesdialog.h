/********************************************************************************
** Form generated from reading UI file 'userimagesdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERIMAGESDIALOG_H
#define UI_USERIMAGESDIALOG_H

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

class Ui_userimagesdialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *lbl_us;
    QSpacerItem *horizontalSpacer;
    QPushButton *push_back;
    QListWidget *listWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *push_request;
    QSpacerItem *horizontalSpacer_3;
    QLineEdit *line_request;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *push_view;
    QSpacerItem *horizontalSpacer_6;
    QLabel *lbl_rem;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout_3;
    QLabel *lbl_request_done;
    QSpacerItem *horizontalSpacer_7;

    void setupUi(QDialog *userimagesdialog)
    {
        if (userimagesdialog->objectName().isEmpty())
            userimagesdialog->setObjectName(QStringLiteral("userimagesdialog"));
        userimagesdialog->resize(500, 500);
        verticalLayout = new QVBoxLayout(userimagesdialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        lbl_us = new QLabel(userimagesdialog);
        lbl_us->setObjectName(QStringLiteral("lbl_us"));

        horizontalLayout_2->addWidget(lbl_us);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        push_back = new QPushButton(userimagesdialog);
        push_back->setObjectName(QStringLiteral("push_back"));

        horizontalLayout_2->addWidget(push_back);


        verticalLayout->addLayout(horizontalLayout_2);

        listWidget = new QListWidget(userimagesdialog);
        listWidget->setObjectName(QStringLiteral("listWidget"));

        verticalLayout->addWidget(listWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        push_request = new QPushButton(userimagesdialog);
        push_request->setObjectName(QStringLiteral("push_request"));

        horizontalLayout->addWidget(push_request);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        line_request = new QLineEdit(userimagesdialog);
        line_request->setObjectName(QStringLiteral("line_request"));

        horizontalLayout->addWidget(line_request);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        push_view = new QPushButton(userimagesdialog);
        push_view->setObjectName(QStringLiteral("push_view"));

        horizontalLayout->addWidget(push_view);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_6);

        lbl_rem = new QLabel(userimagesdialog);
        lbl_rem->setObjectName(QStringLiteral("lbl_rem"));

        horizontalLayout->addWidget(lbl_rem);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        lbl_request_done = new QLabel(userimagesdialog);
        lbl_request_done->setObjectName(QStringLiteral("lbl_request_done"));

        horizontalLayout_3->addWidget(lbl_request_done);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_7);


        verticalLayout->addLayout(horizontalLayout_3);

        QWidget::setTabOrder(listWidget, push_view);
        QWidget::setTabOrder(push_view, push_back);

        retranslateUi(userimagesdialog);
        QObject::connect(push_back, SIGNAL(clicked()), userimagesdialog, SLOT(close()));

        QMetaObject::connectSlotsByName(userimagesdialog);
    } // setupUi

    void retranslateUi(QDialog *userimagesdialog)
    {
        userimagesdialog->setWindowTitle(QApplication::translate("userimagesdialog", "DistImage", nullptr));
        lbl_us->setText(QApplication::translate("userimagesdialog", "User", nullptr));
        push_back->setText(QApplication::translate("userimagesdialog", "Back", nullptr));
        push_request->setText(QApplication::translate("userimagesdialog", "Request", nullptr));
        line_request->setText(QString());
        push_view->setText(QApplication::translate("userimagesdialog", "View", nullptr));
        lbl_rem->setText(QApplication::translate("userimagesdialog", "0", nullptr));
        lbl_request_done->setText(QApplication::translate("userimagesdialog", "Request Done", nullptr));
    } // retranslateUi

};

namespace Ui {
    class userimagesdialog: public Ui_userimagesdialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERIMAGESDIALOG_H
