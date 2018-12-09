/********************************************************************************
** Form generated from reading UI file 'editmyimagedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITMYIMAGEDIALOG_H
#define UI_EDITMYIMAGEDIALOG_H

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

class Ui_editmyimageDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *push_refresh;
    QSpacerItem *horizontalSpacer_4;
    QLabel *lbl_user;
    QSpacerItem *horizontalSpacer;
    QPushButton *push_back;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_2;
    QLabel *lbl_image;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *verticalSpacer_2;
    QListWidget *listWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *push_update_views;
    QSpacerItem *horizontalSpacer_5;
    QLineEdit *line_views;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout_3;
    QLabel *lbl_result;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *lbl_time;
    QSpacerItem *horizontalSpacer_8;

    void setupUi(QDialog *editmyimageDialog)
    {
        if (editmyimageDialog->objectName().isEmpty())
            editmyimageDialog->setObjectName(QStringLiteral("editmyimageDialog"));
        editmyimageDialog->resize(500, 500);
        editmyimageDialog->setStyleSheet(QLatin1String("background-color: rgb(46, 52, 54)\n"
""));
        verticalLayout_2 = new QVBoxLayout(editmyimageDialog);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        push_refresh = new QPushButton(editmyimageDialog);
        push_refresh->setObjectName(QStringLiteral("push_refresh"));
        push_refresh->setStyleSheet(QStringLiteral("color: rgb(238, 238, 236)"));

        horizontalLayout_2->addWidget(push_refresh);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        lbl_user = new QLabel(editmyimageDialog);
        lbl_user->setObjectName(QStringLiteral("lbl_user"));
        lbl_user->setStyleSheet(QStringLiteral("color: rgb(238, 238, 236)"));

        horizontalLayout_2->addWidget(lbl_user);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        push_back = new QPushButton(editmyimageDialog);
        push_back->setObjectName(QStringLiteral("push_back"));
        push_back->setStyleSheet(QStringLiteral("color: rgb(238, 238, 236)"));

        horizontalLayout_2->addWidget(push_back);


        verticalLayout_2->addLayout(horizontalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);

        lbl_image = new QLabel(editmyimageDialog);
        lbl_image->setObjectName(QStringLiteral("lbl_image"));

        horizontalLayout_5->addWidget(lbl_image);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_7);


        verticalLayout->addLayout(horizontalLayout_5);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        verticalLayout_2->addLayout(verticalLayout);

        listWidget = new QListWidget(editmyimageDialog);
        listWidget->setObjectName(QStringLiteral("listWidget"));

        verticalLayout_2->addWidget(listWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        push_update_views = new QPushButton(editmyimageDialog);
        push_update_views->setObjectName(QStringLiteral("push_update_views"));
        push_update_views->setStyleSheet(QStringLiteral("color: rgb(238, 238, 236)"));

        horizontalLayout->addWidget(push_update_views);

        horizontalSpacer_5 = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);

        line_views = new QLineEdit(editmyimageDialog);
        line_views->setObjectName(QStringLiteral("line_views"));
        line_views->setStyleSheet(QStringLiteral("color: rgb(238, 238, 236)"));

        horizontalLayout->addWidget(line_views);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_6);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        lbl_result = new QLabel(editmyimageDialog);
        lbl_result->setObjectName(QStringLiteral("lbl_result"));

        horizontalLayout_3->addWidget(lbl_result);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        lbl_time = new QLabel(editmyimageDialog);
        lbl_time->setObjectName(QStringLiteral("lbl_time"));
        lbl_time->setStyleSheet(QStringLiteral("color: rgb(238, 238, 236)"));

        horizontalLayout_4->addWidget(lbl_time);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_8);


        verticalLayout_2->addLayout(horizontalLayout_4);

        QWidget::setTabOrder(listWidget, push_update_views);
        QWidget::setTabOrder(push_update_views, push_back);

        retranslateUi(editmyimageDialog);
        QObject::connect(push_back, SIGNAL(clicked()), editmyimageDialog, SLOT(close()));

        QMetaObject::connectSlotsByName(editmyimageDialog);
    } // setupUi

    void retranslateUi(QDialog *editmyimageDialog)
    {
        editmyimageDialog->setWindowTitle(QApplication::translate("editmyimageDialog", "DistImage", nullptr));
        push_refresh->setText(QApplication::translate("editmyimageDialog", "Refresh", nullptr));
        lbl_user->setText(QApplication::translate("editmyimageDialog", " My Image Viewers", nullptr));
        push_back->setText(QApplication::translate("editmyimageDialog", "Back", nullptr));
        lbl_image->setText(QApplication::translate("editmyimageDialog", "Image", nullptr));
        push_update_views->setText(QApplication::translate("editmyimageDialog", "Update Views", nullptr));
        lbl_result->setText(QApplication::translate("editmyimageDialog", "Error", nullptr));
        lbl_time->setText(QApplication::translate("editmyimageDialog", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class editmyimageDialog: public Ui_editmyimageDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITMYIMAGEDIALOG_H
