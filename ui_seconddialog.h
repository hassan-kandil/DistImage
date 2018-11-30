/********************************************************************************
** Form generated from reading UI file 'seconddialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SECONDDIALOG_H
#define UI_SECONDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SecondDialog
{
public:
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QPushButton *push_users;
    QSpacerItem *verticalSpacer_2;
    QPushButton *push_images;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *push_notifications;
    QSpacerItem *verticalSpacer_4;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *push_logout;
    QSpacerItem *verticalSpacer_5;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *lbl_upload_path;
    QLineEdit *line_upload_path;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_6;
    QVBoxLayout *verticalLayout_3;
    QLabel *lbl_upload_imagename;
    QLineEdit *line_upload_name;
    QSpacerItem *horizontalSpacer_10;
    QVBoxLayout *verticalLayout_4;
    QLabel *lbl_upload_defaultimage;
    QLineEdit *line_upload_default;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *push_upload;
    QSpacerItem *horizontalSpacer_8;
    QHBoxLayout *horizontalLayout_6;
    QLabel *lbl_upload_successful;
    QSpacerItem *horizontalSpacer_9;

    void setupUi(QDialog *SecondDialog)
    {
        if (SecondDialog->objectName().isEmpty())
            SecondDialog->setObjectName(QStringLiteral("SecondDialog"));
        SecondDialog->resize(500, 500);
        verticalLayout_5 = new QVBoxLayout(SecondDialog);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(154, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        push_users = new QPushButton(SecondDialog);
        push_users->setObjectName(QStringLiteral("push_users"));

        verticalLayout->addWidget(push_users);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        push_images = new QPushButton(SecondDialog);
        push_images->setObjectName(QStringLiteral("push_images"));

        verticalLayout->addWidget(push_images);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        horizontalLayout_2->addItem(verticalSpacer_3);

        horizontalSpacer_5 = new QSpacerItem(58, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);


        verticalLayout->addLayout(horizontalLayout_2);

        push_notifications = new QPushButton(SecondDialog);
        push_notifications->setObjectName(QStringLiteral("push_notifications"));

        verticalLayout->addWidget(push_notifications);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);


        horizontalLayout_3->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        push_logout = new QPushButton(SecondDialog);
        push_logout->setObjectName(QStringLiteral("push_logout"));

        horizontalLayout->addWidget(push_logout);


        verticalLayout_2->addLayout(horizontalLayout);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_5);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout_2->addItem(horizontalSpacer_2);


        horizontalLayout_3->addLayout(verticalLayout_2);


        verticalLayout_5->addLayout(horizontalLayout_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        lbl_upload_path = new QLabel(SecondDialog);
        lbl_upload_path->setObjectName(QStringLiteral("lbl_upload_path"));

        horizontalLayout_5->addWidget(lbl_upload_path);

        line_upload_path = new QLineEdit(SecondDialog);
        line_upload_path->setObjectName(QStringLiteral("line_upload_path"));

        horizontalLayout_5->addWidget(line_upload_path);


        verticalLayout_5->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer_6 = new QSpacerItem(13, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        lbl_upload_imagename = new QLabel(SecondDialog);
        lbl_upload_imagename->setObjectName(QStringLiteral("lbl_upload_imagename"));

        verticalLayout_3->addWidget(lbl_upload_imagename);

        line_upload_name = new QLineEdit(SecondDialog);
        line_upload_name->setObjectName(QStringLiteral("line_upload_name"));

        verticalLayout_3->addWidget(line_upload_name);


        horizontalLayout_4->addLayout(verticalLayout_3);

        horizontalSpacer_10 = new QSpacerItem(17, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_10);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        lbl_upload_defaultimage = new QLabel(SecondDialog);
        lbl_upload_defaultimage->setObjectName(QStringLiteral("lbl_upload_defaultimage"));

        verticalLayout_4->addWidget(lbl_upload_defaultimage);

        line_upload_default = new QLineEdit(SecondDialog);
        line_upload_default->setObjectName(QStringLiteral("line_upload_default"));

        verticalLayout_4->addWidget(line_upload_default);


        horizontalLayout_4->addLayout(verticalLayout_4);

        horizontalSpacer_7 = new QSpacerItem(17, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_7);

        push_upload = new QPushButton(SecondDialog);
        push_upload->setObjectName(QStringLiteral("push_upload"));

        horizontalLayout_4->addWidget(push_upload);

        horizontalSpacer_8 = new QSpacerItem(13, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_8);


        verticalLayout_5->addLayout(horizontalLayout_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        lbl_upload_successful = new QLabel(SecondDialog);
        lbl_upload_successful->setObjectName(QStringLiteral("lbl_upload_successful"));

        horizontalLayout_6->addWidget(lbl_upload_successful);

        horizontalSpacer_9 = new QSpacerItem(154, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_9);


        verticalLayout_5->addLayout(horizontalLayout_6);

        QWidget::setTabOrder(push_users, push_images);
        QWidget::setTabOrder(push_images, push_notifications);
        QWidget::setTabOrder(push_notifications, line_upload_path);
        QWidget::setTabOrder(line_upload_path, line_upload_name);
        QWidget::setTabOrder(line_upload_name, line_upload_default);
        QWidget::setTabOrder(line_upload_default, push_upload);
        QWidget::setTabOrder(push_upload, push_logout);

        retranslateUi(SecondDialog);
        QObject::connect(line_upload_name, SIGNAL(returnPressed()), push_upload, SLOT(click()));
        QObject::connect(line_upload_default, SIGNAL(returnPressed()), push_upload, SLOT(click()));

        QMetaObject::connectSlotsByName(SecondDialog);
    } // setupUi

    void retranslateUi(QDialog *SecondDialog)
    {
        SecondDialog->setWindowTitle(QApplication::translate("SecondDialog", "DistImage", nullptr));
        push_users->setText(QApplication::translate("SecondDialog", "All Users", nullptr));
        push_images->setText(QApplication::translate("SecondDialog", "My Images", nullptr));
        push_notifications->setText(QApplication::translate("SecondDialog", "Notifications", nullptr));
        push_logout->setText(QApplication::translate("SecondDialog", "Logout", nullptr));
        lbl_upload_path->setText(QApplication::translate("SecondDialog", "Upload Images Path:", nullptr));
        lbl_upload_imagename->setText(QApplication::translate("SecondDialog", "Upload Image Name", nullptr));
        lbl_upload_defaultimage->setText(QApplication::translate("SecondDialog", "Default Image Name", nullptr));
        push_upload->setText(QApplication::translate("SecondDialog", "Upload", nullptr));
        lbl_upload_successful->setText(QApplication::translate("SecondDialog", "Uploaded Successfully!", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SecondDialog: public Ui_SecondDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SECONDDIALOG_H
