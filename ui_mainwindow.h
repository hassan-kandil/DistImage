/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QLabel *lbl_dos_info;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout_5;
    QLabel *lbl_dos_ip;
    QSpacerItem *horizontalSpacer_4;
    QLineEdit *line_dos_ip;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_6;
    QLabel *lbl_dos_port;
    QSpacerItem *horizontalSpacer_5;
    QLineEdit *line_dos_port;
    QSpacerItem *verticalSpacer_7;
    QLabel *lbl_dos_error;
    QSpacerItem *verticalSpacer_6;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout;
    QLabel *lbl_login_already;
    QHBoxLayout *horizontalLayout;
    QLabel *lbl_login_usr;
    QSpacerItem *horizontalSpacer;
    QLineEdit *line_login_usr;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *lbl_login_pass;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *line_login_pass;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *push_login;
    QLabel *lbl_login_wrong;
    QVBoxLayout *verticalLayout_2;
    QLabel *lbl_login_not_on_our_system;
    QHBoxLayout *horizontalLayout_9;
    QLabel *lbl_signup_usr;
    QSpacerItem *horizontalSpacer_7;
    QLineEdit *line_signup_usr;
    QSpacerItem *verticalSpacer_9;
    QHBoxLayout *horizontalLayout_10;
    QLabel *lbl_signup_pass;
    QSpacerItem *horizontalSpacer_8;
    QLineEdit *line_signup_pass;
    QSpacerItem *verticalSpacer_8;
    QHBoxLayout *horizontalLayout_11;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *push_signup;
    QLabel *lbl_signup_welcome;
    QHBoxLayout *horizontalLayout_7;
    QLabel *lbl_time;
    QSpacerItem *horizontalSpacer_6;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(587, 500);
        MainWindow->setStyleSheet(QLatin1String("background-color: rgb(0,0,50)\n"
""));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_4 = new QVBoxLayout(centralWidget);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setScaledContents(false);
        label->setAlignment(Qt::AlignCenter);
        label->setWordWrap(true);

        verticalLayout_3->addWidget(label);

        lbl_dos_info = new QLabel(centralWidget);
        lbl_dos_info->setObjectName(QStringLiteral("lbl_dos_info"));
        lbl_dos_info->setStyleSheet(QStringLiteral("color: rgb(238, 238, 236)"));

        verticalLayout_3->addWidget(lbl_dos_info);

        verticalSpacer_5 = new QSpacerItem(17, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_5);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        lbl_dos_ip = new QLabel(centralWidget);
        lbl_dos_ip->setObjectName(QStringLiteral("lbl_dos_ip"));
        lbl_dos_ip->setStyleSheet(QStringLiteral("color: rgb(238, 238, 236)"));

        horizontalLayout_5->addWidget(lbl_dos_ip);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);


        verticalLayout_3->addLayout(horizontalLayout_5);

        line_dos_ip = new QLineEdit(centralWidget);
        line_dos_ip->setObjectName(QStringLiteral("line_dos_ip"));
        line_dos_ip->setStyleSheet(QStringLiteral("color: rgb(238, 238, 236)"));

        verticalLayout_3->addWidget(line_dos_ip);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        lbl_dos_port = new QLabel(centralWidget);
        lbl_dos_port->setObjectName(QStringLiteral("lbl_dos_port"));
        lbl_dos_port->setStyleSheet(QStringLiteral("color: rgb(238, 238, 236)"));

        horizontalLayout_6->addWidget(lbl_dos_port);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_5);


        verticalLayout_3->addLayout(horizontalLayout_6);

        line_dos_port = new QLineEdit(centralWidget);
        line_dos_port->setObjectName(QStringLiteral("line_dos_port"));
        line_dos_port->setStyleSheet(QStringLiteral("color: rgb(238, 238, 236)"));

        verticalLayout_3->addWidget(line_dos_port);

        verticalSpacer_7 = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_7);

        lbl_dos_error = new QLabel(centralWidget);
        lbl_dos_error->setObjectName(QStringLiteral("lbl_dos_error"));

        verticalLayout_3->addWidget(lbl_dos_error);


        verticalLayout_4->addLayout(verticalLayout_3);

        verticalSpacer_6 = new QSpacerItem(20, 28, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_6);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        lbl_login_already = new QLabel(centralWidget);
        lbl_login_already->setObjectName(QStringLiteral("lbl_login_already"));
        lbl_login_already->setStyleSheet(QStringLiteral("color: rgb(114, 159, 207)"));

        verticalLayout->addWidget(lbl_login_already);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        lbl_login_usr = new QLabel(centralWidget);
        lbl_login_usr->setObjectName(QStringLiteral("lbl_login_usr"));
        lbl_login_usr->setStyleSheet(QStringLiteral("color: rgb(238, 238, 236)"));

        horizontalLayout->addWidget(lbl_login_usr);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        line_login_usr = new QLineEdit(centralWidget);
        line_login_usr->setObjectName(QStringLiteral("line_login_usr"));
        line_login_usr->setStyleSheet(QStringLiteral("color: rgb(238, 238, 236)"));

        verticalLayout->addWidget(line_login_usr);

        verticalSpacer_2 = new QSpacerItem(334, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        lbl_login_pass = new QLabel(centralWidget);
        lbl_login_pass->setObjectName(QStringLiteral("lbl_login_pass"));
        lbl_login_pass->setStyleSheet(QStringLiteral("color: rgb(238, 238, 236)"));

        horizontalLayout_2->addWidget(lbl_login_pass);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);

        line_login_pass = new QLineEdit(centralWidget);
        line_login_pass->setObjectName(QStringLiteral("line_login_pass"));
        line_login_pass->setStyleSheet(QStringLiteral("color: rgb(238, 238, 236)"));
        line_login_pass->setEchoMode(QLineEdit::Password);

        verticalLayout->addWidget(line_login_pass);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        push_login = new QPushButton(centralWidget);
        push_login->setObjectName(QStringLiteral("push_login"));
        push_login->setStyleSheet(QStringLiteral("color: rgb(238, 238, 236)"));

        horizontalLayout_3->addWidget(push_login);


        verticalLayout->addLayout(horizontalLayout_3);

        lbl_login_wrong = new QLabel(centralWidget);
        lbl_login_wrong->setObjectName(QStringLiteral("lbl_login_wrong"));

        verticalLayout->addWidget(lbl_login_wrong);


        horizontalLayout_4->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        lbl_login_not_on_our_system = new QLabel(centralWidget);
        lbl_login_not_on_our_system->setObjectName(QStringLiteral("lbl_login_not_on_our_system"));
        lbl_login_not_on_our_system->setStyleSheet(QStringLiteral("color: rgb(114, 159, 207)"));
        lbl_login_not_on_our_system->setWordWrap(false);

        verticalLayout_2->addWidget(lbl_login_not_on_our_system);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        lbl_signup_usr = new QLabel(centralWidget);
        lbl_signup_usr->setObjectName(QStringLiteral("lbl_signup_usr"));
        lbl_signup_usr->setStyleSheet(QStringLiteral("color: rgb(238, 238, 236)"));

        horizontalLayout_9->addWidget(lbl_signup_usr);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_7);


        verticalLayout_2->addLayout(horizontalLayout_9);

        line_signup_usr = new QLineEdit(centralWidget);
        line_signup_usr->setObjectName(QStringLiteral("line_signup_usr"));
        line_signup_usr->setStyleSheet(QStringLiteral("color: rgb(238, 238, 236)"));

        verticalLayout_2->addWidget(line_signup_usr);

        verticalSpacer_9 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_9);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        lbl_signup_pass = new QLabel(centralWidget);
        lbl_signup_pass->setObjectName(QStringLiteral("lbl_signup_pass"));
        lbl_signup_pass->setStyleSheet(QStringLiteral("color: rgb(238, 238, 236)"));

        horizontalLayout_10->addWidget(lbl_signup_pass);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_8);


        verticalLayout_2->addLayout(horizontalLayout_10);

        line_signup_pass = new QLineEdit(centralWidget);
        line_signup_pass->setObjectName(QStringLiteral("line_signup_pass"));
        line_signup_pass->setStyleSheet(QStringLiteral("color: rgb(238, 238, 236)"));
        line_signup_pass->setEchoMode(QLineEdit::Password);

        verticalLayout_2->addWidget(line_signup_pass);

        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_8);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_9);

        push_signup = new QPushButton(centralWidget);
        push_signup->setObjectName(QStringLiteral("push_signup"));
        push_signup->setStyleSheet(QStringLiteral("color: rgb(238, 238, 236)"));

        horizontalLayout_11->addWidget(push_signup);


        verticalLayout_2->addLayout(horizontalLayout_11);

        lbl_signup_welcome = new QLabel(centralWidget);
        lbl_signup_welcome->setObjectName(QStringLiteral("lbl_signup_welcome"));

        verticalLayout_2->addWidget(lbl_signup_welcome);


        horizontalLayout_4->addLayout(verticalLayout_2);


        verticalLayout_4->addLayout(horizontalLayout_4);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        lbl_time = new QLabel(centralWidget);
        lbl_time->setObjectName(QStringLiteral("lbl_time"));
        lbl_time->setStyleSheet(QStringLiteral("color: rgb(114, 159, 207)"));

        horizontalLayout_7->addWidget(lbl_time);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_6);


        verticalLayout_4->addLayout(horizontalLayout_7);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);
        QObject::connect(line_login_pass, SIGNAL(returnPressed()), push_login, SLOT(click()));
        QObject::connect(line_signup_pass, SIGNAL(returnPressed()), push_signup, SLOT(click()));

        push_login->setDefault(true);
        push_signup->setDefault(true);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "DistImage", Q_NULLPTR));
        label->setText(QString());
        lbl_dos_info->setText(QApplication::translate("MainWindow", "Directory of Service Connection Info", Q_NULLPTR));
        lbl_dos_ip->setText(QApplication::translate("MainWindow", "IP Address", Q_NULLPTR));
        lbl_dos_port->setText(QApplication::translate("MainWindow", "Port Number", Q_NULLPTR));
        lbl_dos_error->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#ef2929;\">Please, fill in all info!</span></p></body></html>", Q_NULLPTR));
        lbl_login_already->setText(QApplication::translate("MainWindow", "Already a Member? Log In!", Q_NULLPTR));
        lbl_login_usr->setText(QApplication::translate("MainWindow", "UserName", Q_NULLPTR));
        lbl_login_pass->setText(QApplication::translate("MainWindow", "Password", Q_NULLPTR));
        push_login->setText(QApplication::translate("MainWindow", "Login", Q_NULLPTR));
        lbl_login_wrong->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#ef2929;\">Wrong Username or Password!</span></p></body></html>", Q_NULLPTR));
        lbl_login_not_on_our_system->setText(QApplication::translate("MainWindow", "Not On Our System Yet? Sign Up!", Q_NULLPTR));
        lbl_signup_usr->setText(QApplication::translate("MainWindow", "UserName", Q_NULLPTR));
        lbl_signup_pass->setText(QApplication::translate("MainWindow", "Password", Q_NULLPTR));
        push_signup->setText(QApplication::translate("MainWindow", "Sign Up", Q_NULLPTR));
        lbl_signup_welcome->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#4e9a06;\">Signed Up. Welcome!</span></p></body></html>", Q_NULLPTR));
        lbl_time->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
