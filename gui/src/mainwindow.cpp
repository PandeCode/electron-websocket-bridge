/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QPushButton *nextBtn;
    QPushButton *pauseBtn;
    QPushButton *previousBtn;
    QPushButton *playPauseBtn;
    QPushButton *playBtn;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(640, 480);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        nextBtn = new QPushButton(centralwidget);
        nextBtn->setObjectName(QString::fromUtf8("nextBtn"));

        gridLayout->addWidget(nextBtn, 2, 0, 1, 1);

        pauseBtn = new QPushButton(centralwidget);
        pauseBtn->setObjectName(QString::fromUtf8("pauseBtn"));

        gridLayout->addWidget(pauseBtn, 1, 0, 1, 1);

        previousBtn = new QPushButton(centralwidget);
        previousBtn->setObjectName(QString::fromUtf8("previousBtn"));

        gridLayout->addWidget(previousBtn, 4, 0, 1, 1);

        playPauseBtn = new QPushButton(centralwidget);
        playPauseBtn->setObjectName(QString::fromUtf8("playPauseBtn"));

        gridLayout->addWidget(playPauseBtn, 3, 0, 1, 1);

        playBtn = new QPushButton(centralwidget);
        playBtn->setObjectName(QString::fromUtf8("playBtn"));

        gridLayout->addWidget(playBtn, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 640, 21));
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
        nextBtn->setText(QCoreApplication::translate("MainWindow", "Next", nullptr));
        pauseBtn->setText(QCoreApplication::translate("MainWindow", "Pause", nullptr));
        previousBtn->setText(QCoreApplication::translate("MainWindow", "Previous", nullptr));
        playPauseBtn->setText(QCoreApplication::translate("MainWindow", "PlayPause", nullptr));
        playBtn->setText(QCoreApplication::translate("MainWindow", "Play", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MAINWINDOW_H
