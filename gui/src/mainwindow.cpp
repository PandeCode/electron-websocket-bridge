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
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QVBoxLayout *restVerticalLayout;
    QLabel *restLabel;
    QPushButton *nextRestBtn;
    QPushButton *playPauseRestBtn;
    QPushButton *enableRepeatRestBtn;
    QPushButton *dislikeCurrentRestBtn;
    QPushButton *playRestBtn;
    QPushButton *enableRepeatOneRestBtn;
    QPushButton *toggleLikeRestBtn;
    QPushButton *pauseRestBtn;
    QPushButton *likeCurrentRestBtn;
    QPushButton *previousRestBtn;
    QPushButton *disableRepeatRestBtn;
    QPushButton *toggleShuffleRestBtn;
    QVBoxLayout *webSocketVerticalLayout;
    QLabel *webSocketLabel;
    QPushButton *activateWebSocketBtn;
    QPushButton *nextWebSocketBtn;
    QPushButton *playPauseWebSocketBtn;
    QPushButton *enableRepeatWebSocketBtn;
    QPushButton *dislikeCurrentWebSocketBtn;
    QPushButton *playWebSocketBtn;
    QPushButton *enableRepeatOneWebSocketBtn;
    QPushButton *toggleLikeWebSocketBtn;
    QPushButton *pauseWebSocketBtn;
    QPushButton *likeCurrentWebSocketBtn;
    QPushButton *previousWebSocketBtn;
    QPushButton *disableRepeatWebSocketBtn;
    QPushButton *toggleShuffleWebSocketBtn;
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
        restVerticalLayout = new QVBoxLayout();
        restVerticalLayout->setObjectName(QString::fromUtf8("restVerticalLayout"));
        restLabel = new QLabel(centralwidget);
        restLabel->setObjectName(QString::fromUtf8("restLabel"));
        restLabel->setAlignment(Qt::AlignCenter);

        restVerticalLayout->addWidget(restLabel);

        nextRestBtn = new QPushButton(centralwidget);
        nextRestBtn->setObjectName(QString::fromUtf8("nextRestBtn"));

        restVerticalLayout->addWidget(nextRestBtn);

        playPauseRestBtn = new QPushButton(centralwidget);
        playPauseRestBtn->setObjectName(QString::fromUtf8("playPauseRestBtn"));

        restVerticalLayout->addWidget(playPauseRestBtn);

        enableRepeatRestBtn = new QPushButton(centralwidget);
        enableRepeatRestBtn->setObjectName(QString::fromUtf8("enableRepeatRestBtn"));

        restVerticalLayout->addWidget(enableRepeatRestBtn);

        dislikeCurrentRestBtn = new QPushButton(centralwidget);
        dislikeCurrentRestBtn->setObjectName(QString::fromUtf8("dislikeCurrentRestBtn"));

        restVerticalLayout->addWidget(dislikeCurrentRestBtn);

        playRestBtn = new QPushButton(centralwidget);
        playRestBtn->setObjectName(QString::fromUtf8("playRestBtn"));

        restVerticalLayout->addWidget(playRestBtn);

        enableRepeatOneRestBtn = new QPushButton(centralwidget);
        enableRepeatOneRestBtn->setObjectName(QString::fromUtf8("enableRepeatOneRestBtn"));

        restVerticalLayout->addWidget(enableRepeatOneRestBtn);

        toggleLikeRestBtn = new QPushButton(centralwidget);
        toggleLikeRestBtn->setObjectName(QString::fromUtf8("toggleLikeRestBtn"));

        restVerticalLayout->addWidget(toggleLikeRestBtn);

        pauseRestBtn = new QPushButton(centralwidget);
        pauseRestBtn->setObjectName(QString::fromUtf8("pauseRestBtn"));

        restVerticalLayout->addWidget(pauseRestBtn);

        likeCurrentRestBtn = new QPushButton(centralwidget);
        likeCurrentRestBtn->setObjectName(QString::fromUtf8("likeCurrentRestBtn"));

        restVerticalLayout->addWidget(likeCurrentRestBtn);

        previousRestBtn = new QPushButton(centralwidget);
        previousRestBtn->setObjectName(QString::fromUtf8("previousRestBtn"));

        restVerticalLayout->addWidget(previousRestBtn);

        disableRepeatRestBtn = new QPushButton(centralwidget);
        disableRepeatRestBtn->setObjectName(QString::fromUtf8("disableRepeatRestBtn"));

        restVerticalLayout->addWidget(disableRepeatRestBtn);

        toggleShuffleRestBtn = new QPushButton(centralwidget);
        toggleShuffleRestBtn->setObjectName(QString::fromUtf8("toggleShuffleRestBtn"));

        restVerticalLayout->addWidget(toggleShuffleRestBtn);


        gridLayout->addLayout(restVerticalLayout, 0, 0, 1, 1);

        webSocketVerticalLayout = new QVBoxLayout();
        webSocketVerticalLayout->setObjectName(QString::fromUtf8("webSocketVerticalLayout"));
        webSocketLabel = new QLabel(centralwidget);
        webSocketLabel->setObjectName(QString::fromUtf8("webSocketLabel"));
        webSocketLabel->setAlignment(Qt::AlignCenter);

        webSocketVerticalLayout->addWidget(webSocketLabel);

        activateWebSocketBtn = new QPushButton(centralwidget);
        activateWebSocketBtn->setObjectName(QString::fromUtf8("activateWebSocketBtn"));
        activateWebSocketBtn->setEnabled(true);
        activateWebSocketBtn->setAutoDefault(false);
        activateWebSocketBtn->setFlat(false);

        webSocketVerticalLayout->addWidget(activateWebSocketBtn);

        nextWebSocketBtn = new QPushButton(centralwidget);
        nextWebSocketBtn->setObjectName(QString::fromUtf8("nextWebSocketBtn"));
        nextWebSocketBtn->setEnabled(false);

        webSocketVerticalLayout->addWidget(nextWebSocketBtn);

        playPauseWebSocketBtn = new QPushButton(centralwidget);
        playPauseWebSocketBtn->setObjectName(QString::fromUtf8("playPauseWebSocketBtn"));
        playPauseWebSocketBtn->setEnabled(false);

        webSocketVerticalLayout->addWidget(playPauseWebSocketBtn);

        enableRepeatWebSocketBtn = new QPushButton(centralwidget);
        enableRepeatWebSocketBtn->setObjectName(QString::fromUtf8("enableRepeatWebSocketBtn"));
        enableRepeatWebSocketBtn->setEnabled(false);

        webSocketVerticalLayout->addWidget(enableRepeatWebSocketBtn);

        dislikeCurrentWebSocketBtn = new QPushButton(centralwidget);
        dislikeCurrentWebSocketBtn->setObjectName(QString::fromUtf8("dislikeCurrentWebSocketBtn"));
        dislikeCurrentWebSocketBtn->setEnabled(false);

        webSocketVerticalLayout->addWidget(dislikeCurrentWebSocketBtn);

        playWebSocketBtn = new QPushButton(centralwidget);
        playWebSocketBtn->setObjectName(QString::fromUtf8("playWebSocketBtn"));
        playWebSocketBtn->setEnabled(false);

        webSocketVerticalLayout->addWidget(playWebSocketBtn);

        enableRepeatOneWebSocketBtn = new QPushButton(centralwidget);
        enableRepeatOneWebSocketBtn->setObjectName(QString::fromUtf8("enableRepeatOneWebSocketBtn"));
        enableRepeatOneWebSocketBtn->setEnabled(false);

        webSocketVerticalLayout->addWidget(enableRepeatOneWebSocketBtn);

        toggleLikeWebSocketBtn = new QPushButton(centralwidget);
        toggleLikeWebSocketBtn->setObjectName(QString::fromUtf8("toggleLikeWebSocketBtn"));
        toggleLikeWebSocketBtn->setEnabled(false);

        webSocketVerticalLayout->addWidget(toggleLikeWebSocketBtn);

        pauseWebSocketBtn = new QPushButton(centralwidget);
        pauseWebSocketBtn->setObjectName(QString::fromUtf8("pauseWebSocketBtn"));
        pauseWebSocketBtn->setEnabled(false);

        webSocketVerticalLayout->addWidget(pauseWebSocketBtn);

        likeCurrentWebSocketBtn = new QPushButton(centralwidget);
        likeCurrentWebSocketBtn->setObjectName(QString::fromUtf8("likeCurrentWebSocketBtn"));
        likeCurrentWebSocketBtn->setEnabled(false);

        webSocketVerticalLayout->addWidget(likeCurrentWebSocketBtn);

        previousWebSocketBtn = new QPushButton(centralwidget);
        previousWebSocketBtn->setObjectName(QString::fromUtf8("previousWebSocketBtn"));
        previousWebSocketBtn->setEnabled(false);

        webSocketVerticalLayout->addWidget(previousWebSocketBtn);

        disableRepeatWebSocketBtn = new QPushButton(centralwidget);
        disableRepeatWebSocketBtn->setObjectName(QString::fromUtf8("disableRepeatWebSocketBtn"));
        disableRepeatWebSocketBtn->setEnabled(false);

        webSocketVerticalLayout->addWidget(disableRepeatWebSocketBtn);

        toggleShuffleWebSocketBtn = new QPushButton(centralwidget);
        toggleShuffleWebSocketBtn->setObjectName(QString::fromUtf8("toggleShuffleWebSocketBtn"));
        toggleShuffleWebSocketBtn->setEnabled(false);

        webSocketVerticalLayout->addWidget(toggleShuffleWebSocketBtn);


        gridLayout->addLayout(webSocketVerticalLayout, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 640, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        activateWebSocketBtn->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        restLabel->setText(QCoreApplication::translate("MainWindow", "Rest", nullptr));
        nextRestBtn->setText(QCoreApplication::translate("MainWindow", "Next", nullptr));
        playPauseRestBtn->setText(QCoreApplication::translate("MainWindow", "PlayPause", nullptr));
        enableRepeatRestBtn->setText(QCoreApplication::translate("MainWindow", "Enable Repeat", nullptr));
        dislikeCurrentRestBtn->setText(QCoreApplication::translate("MainWindow", "Dislike Current", nullptr));
        playRestBtn->setText(QCoreApplication::translate("MainWindow", "Play", nullptr));
        enableRepeatOneRestBtn->setText(QCoreApplication::translate("MainWindow", "Enable Repeat One", nullptr));
        toggleLikeRestBtn->setText(QCoreApplication::translate("MainWindow", "Toggle Like", nullptr));
        pauseRestBtn->setText(QCoreApplication::translate("MainWindow", "Pause", nullptr));
        likeCurrentRestBtn->setText(QCoreApplication::translate("MainWindow", "Like Current", nullptr));
        previousRestBtn->setText(QCoreApplication::translate("MainWindow", "Previous", nullptr));
        disableRepeatRestBtn->setText(QCoreApplication::translate("MainWindow", "Disable Repeat", nullptr));
        toggleShuffleRestBtn->setText(QCoreApplication::translate("MainWindow", "Toggle Shuffle", nullptr));
        webSocketLabel->setText(QCoreApplication::translate("MainWindow", "WebSocket", nullptr));
        activateWebSocketBtn->setText(QCoreApplication::translate("MainWindow", "Activate", nullptr));
        nextWebSocketBtn->setText(QCoreApplication::translate("MainWindow", "Next", nullptr));
        playPauseWebSocketBtn->setText(QCoreApplication::translate("MainWindow", "PlayPause", nullptr));
        enableRepeatWebSocketBtn->setText(QCoreApplication::translate("MainWindow", "Enable Repeat", nullptr));
        dislikeCurrentWebSocketBtn->setText(QCoreApplication::translate("MainWindow", "Dislike Current", nullptr));
        playWebSocketBtn->setText(QCoreApplication::translate("MainWindow", "Play", nullptr));
        enableRepeatOneWebSocketBtn->setText(QCoreApplication::translate("MainWindow", "Enable Repeat One", nullptr));
        toggleLikeWebSocketBtn->setText(QCoreApplication::translate("MainWindow", "Toggle Like", nullptr));
        pauseWebSocketBtn->setText(QCoreApplication::translate("MainWindow", "Pause", nullptr));
        likeCurrentWebSocketBtn->setText(QCoreApplication::translate("MainWindow", "Like Current", nullptr));
        previousWebSocketBtn->setText(QCoreApplication::translate("MainWindow", "Previous", nullptr));
        disableRepeatWebSocketBtn->setText(QCoreApplication::translate("MainWindow", "Disable Repeat", nullptr));
        toggleShuffleWebSocketBtn->setText(QCoreApplication::translate("MainWindow", "Toggle Shuffle", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MAINWINDOW_H
