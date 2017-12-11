/********************************************************************************
** Form generated from reading UI file 'lorakit.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LORAKIT_H
#define UI_LORAKIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoraKit
{
public:
    QWidget *centralWidget;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_3;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *LoraKit)
    {
        if (LoraKit->objectName().isEmpty())
            LoraKit->setObjectName(QStringLiteral("LoraKit"));
        LoraKit->resize(261, 315);
        centralWidget = new QWidget(LoraKit);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        lineEdit_2 = new QLineEdit(centralWidget);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(30, 60, 151, 20));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(110, 20, 75, 23));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(30, 100, 151, 23));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(30, 20, 61, 21));
        lineEdit_3 = new QLineEdit(centralWidget);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(30, 140, 171, 91));
        LoraKit->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(LoraKit);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 261, 21));
        LoraKit->setMenuBar(menuBar);
        mainToolBar = new QToolBar(LoraKit);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        LoraKit->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(LoraKit);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        LoraKit->setStatusBar(statusBar);

        retranslateUi(LoraKit);

        QMetaObject::connectSlotsByName(LoraKit);
    } // setupUi

    void retranslateUi(QMainWindow *LoraKit)
    {
        LoraKit->setWindowTitle(QApplication::translate("LoraKit", "LoraKit", 0));
        pushButton->setText(QApplication::translate("LoraKit", "ouvrir", 0));
        pushButton_2->setText(QApplication::translate("LoraKit", "PushButton", 0));
        lineEdit->setText(QApplication::translate("LoraKit", "COM", 0));
    } // retranslateUi

};

namespace Ui {
    class LoraKit: public Ui_LoraKit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LORAKIT_H
