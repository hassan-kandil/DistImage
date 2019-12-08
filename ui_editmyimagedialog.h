/********************************************************************************
** Form generated from reading UI file 'editmyimagedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITMYIMAGEDIALOG_H
#define UI_EDITMYIMAGEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
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
    QLabel *label;
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
        editmyimageDialog->setStyleSheet(QLatin1String("background-color: rgb(0,0,0)\n"
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

        label = new QLabel(editmyimageDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setStyleSheet(QStringLiteral("color: rgb(238, 238, 236)"));

        verticalLayout_2->addWidget(label);

        listWidget = new QListWidget(editmyimageDialog);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setStyleSheet(QStringLiteral("color: rgb(238, 238, 236)"));

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
        editmyimageDialog->setWindowTitle(QApplication::translate("editmyimageDialog", "DistImage", Q_NULLPTR));
        push_refresh->setText(QApplication::translate("editmyimageDialog", "Refresh", Q_NULLPTR));
        lbl_user->setText(QApplication::translate("editmyimageDialog", " My Image Viewers", Q_NULLPTR));
        push_back->setText(QApplication::translate("editmyimageDialog", "Back", Q_NULLPTR));
        lbl_image->setText(QApplication::translate("editmyimageDialog", "Image", Q_NULLPTR));
        label->setText(QApplication::translate("editmyimageDialog", "Viewers:", Q_NULLPTR));
        push_update_views->setText(QApplication::translate("editmyimageDialog", "Top Up Views", Q_NULLPTR));
        lbl_result->setText(QApplication::translate("editmyimageDialog", "Error", Q_NULLPTR));
        lbl_time->setText(QApplication::translate("editmyimageDialog", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class editmyimageDialog: public Ui_editmyimageDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITMYIMAGEDIALOG_H
