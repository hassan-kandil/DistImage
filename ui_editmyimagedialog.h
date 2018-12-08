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
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *push_refresh;
    QSpacerItem *horizontalSpacer_4;
    QLabel *lbl_user;
    QSpacerItem *horizontalSpacer;
    QPushButton *push_back;
    QListWidget *listWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *push_update_views;
    QSpacerItem *horizontalSpacer_5;
    QLineEdit *line_reqviews;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *push_view;
    QSpacerItem *horizontalSpacer_7;
    QLabel *lbl_rem;
    QSpacerItem *horizontalSpacer_9;
    QHBoxLayout *horizontalLayout_3;
    QLabel *lbl_result;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QDialog *editmyimageDialog)
    {
        if (editmyimageDialog->objectName().isEmpty())
            editmyimageDialog->setObjectName(QStringLiteral("editmyimageDialog"));
        editmyimageDialog->resize(500, 500);
        verticalLayout = new QVBoxLayout(editmyimageDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        push_refresh = new QPushButton(editmyimageDialog);
        push_refresh->setObjectName(QStringLiteral("push_refresh"));

        horizontalLayout_2->addWidget(push_refresh);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        lbl_user = new QLabel(editmyimageDialog);
        lbl_user->setObjectName(QStringLiteral("lbl_user"));

        horizontalLayout_2->addWidget(lbl_user);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        push_back = new QPushButton(editmyimageDialog);
        push_back->setObjectName(QStringLiteral("push_back"));

        horizontalLayout_2->addWidget(push_back);


        verticalLayout->addLayout(horizontalLayout_2);

        listWidget = new QListWidget(editmyimageDialog);
        listWidget->setObjectName(QStringLiteral("listWidget"));

        verticalLayout->addWidget(listWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        push_update_views = new QPushButton(editmyimageDialog);
        push_update_views->setObjectName(QStringLiteral("push_update_views"));

        horizontalLayout->addWidget(push_update_views);

        horizontalSpacer_5 = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);

        line_reqviews = new QLineEdit(editmyimageDialog);
        line_reqviews->setObjectName(QStringLiteral("line_reqviews"));

        horizontalLayout->addWidget(line_reqviews);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_6);

        push_view = new QPushButton(editmyimageDialog);
        push_view->setObjectName(QStringLiteral("push_view"));

        horizontalLayout->addWidget(push_view);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_7);

        lbl_rem = new QLabel(editmyimageDialog);
        lbl_rem->setObjectName(QStringLiteral("lbl_rem"));

        horizontalLayout->addWidget(lbl_rem);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_9);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        lbl_result = new QLabel(editmyimageDialog);
        lbl_result->setObjectName(QStringLiteral("lbl_result"));

        horizontalLayout_3->addWidget(lbl_result);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout_3);

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
        push_update_views->setText(QApplication::translate("editmyimageDialog", "Update Views", nullptr));
        push_view->setText(QApplication::translate("editmyimageDialog", "View", nullptr));
        lbl_rem->setText(QApplication::translate("editmyimageDialog", "0", nullptr));
        lbl_result->setText(QApplication::translate("editmyimageDialog", "Error", nullptr));
    } // retranslateUi

};

namespace Ui {
    class editmyimageDialog: public Ui_editmyimageDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITMYIMAGEDIALOG_H
