/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.0.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *itemList;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *sourcePathSelectBtn;
    QLineEdit *sourcePahtLineEdit;
    QPushButton *targetPathSelectBtn;
    QLineEdit *targetPathLineEdit;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *resultItemList;
    QTextEdit *logTextEdit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(600, 800);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(80, 100, 451, 311));
        itemList = new QVBoxLayout(verticalLayoutWidget);
        itemList->setObjectName(QString::fromUtf8("itemList"));
        itemList->setContentsMargins(0, 0, 0, 0);
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(80, 10, 451, 80));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        sourcePathSelectBtn = new QPushButton(gridLayoutWidget);
        sourcePathSelectBtn->setObjectName(QString::fromUtf8("sourcePathSelectBtn"));
        sourcePathSelectBtn->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(sourcePathSelectBtn, 0, 0, 1, 1);

        sourcePahtLineEdit = new QLineEdit(gridLayoutWidget);
        sourcePahtLineEdit->setObjectName(QString::fromUtf8("sourcePahtLineEdit"));

        gridLayout->addWidget(sourcePahtLineEdit, 0, 1, 1, 1);

        targetPathSelectBtn = new QPushButton(gridLayoutWidget);
        targetPathSelectBtn->setObjectName(QString::fromUtf8("targetPathSelectBtn"));
        targetPathSelectBtn->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(targetPathSelectBtn, 1, 0, 1, 1);

        targetPathLineEdit = new QLineEdit(gridLayoutWidget);
        targetPathLineEdit->setObjectName(QString::fromUtf8("targetPathLineEdit"));

        gridLayout->addWidget(targetPathLineEdit, 1, 1, 1, 1);

        verticalLayoutWidget_2 = new QWidget(centralwidget);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(80, 430, 451, 271));
        resultItemList = new QVBoxLayout(verticalLayoutWidget_2);
        resultItemList->setObjectName(QString::fromUtf8("resultItemList"));
        resultItemList->setContentsMargins(0, 0, 0, 0);
        logTextEdit = new QTextEdit(verticalLayoutWidget_2);
        logTextEdit->setObjectName(QString::fromUtf8("logTextEdit"));
        logTextEdit->setReadOnly(true);

        resultItemList->addWidget(logTextEdit);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 600, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        sourcePathSelectBtn->setText(QCoreApplication::translate("MainWindow", "\346\272\220\350\267\257\345\276\204", nullptr));
        targetPathSelectBtn->setText(QCoreApplication::translate("MainWindow", "\347\233\256\346\240\207\350\267\257\345\276\204", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
