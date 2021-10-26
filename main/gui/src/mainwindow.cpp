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
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionActivateWebSocket;
    QAction *actionDeactivateWebSocket;
    QAction *actionAbout;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *restTab;
    QGridLayout *gridLayout_3;
    QTextEdit *restConsole;
    QVBoxLayout *restVerticalLayout;
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
    QVBoxLayout *restGetVerticalLayout;
    QLabel *restGetLabel;
    QPushButton *getInfoRestBtn;
    QPushButton *getCurrentSongRestBtn;
    QPushButton *getCurrentAlbumArtRestBtn;
    QPushButton *getCurrentArtistRestBtn;
    QPushButton *getIsPlayingRestBtn;
    QPushButton *getRepeatStatusRestBtn;
    QPushButton *getIsCurrentLikedRestBtn;
    QWidget *webSocketTab;
    QGridLayout *webSocketGridLayout;
    QVBoxLayout *webSocketVerticalLayout;
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
    QTextEdit *webSocketConsole;
    QPushButton *activateWebSocketBtn;
    QVBoxLayout *webSocketGetVerticalLayout;
    QLabel *webSocketGetLabel;
    QPushButton *getInfoWebSocketBtn;
    QPushButton *getCurrentSongWebSocketBtn;
    QPushButton *getCurrentAlbumArtWebSocketBtn;
    QPushButton *getCurrentArtistWebSocketBtn;
    QPushButton *getIsPlayingWebSocketBtn;
    QPushButton *getRepeatStatusWebSocketBtn;
    QPushButton *getIsCurrentLikedWebSocketBtn;
    QPushButton *deactivateWebSocketBtn;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(780, 510);
        actionActivateWebSocket = new QAction(MainWindow);
        actionActivateWebSocket->setObjectName(QString::fromUtf8("actionActivateWebSocket"));
        actionDeactivateWebSocket = new QAction(MainWindow);
        actionDeactivateWebSocket->setObjectName(QString::fromUtf8("actionDeactivateWebSocket"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        restTab = new QWidget();
        restTab->setObjectName(QString::fromUtf8("restTab"));
        gridLayout_3 = new QGridLayout(restTab);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        restConsole = new QTextEdit(restTab);
        restConsole->setObjectName(QString::fromUtf8("restConsole"));
        restConsole->setEnabled(false);

        gridLayout_3->addWidget(restConsole, 1, 1, 1, 1);

        restVerticalLayout = new QVBoxLayout();
        restVerticalLayout->setObjectName(QString::fromUtf8("restVerticalLayout"));
        nextRestBtn = new QPushButton(restTab);
        nextRestBtn->setObjectName(QString::fromUtf8("nextRestBtn"));

        restVerticalLayout->addWidget(nextRestBtn);

        playPauseRestBtn = new QPushButton(restTab);
        playPauseRestBtn->setObjectName(QString::fromUtf8("playPauseRestBtn"));

        restVerticalLayout->addWidget(playPauseRestBtn);

        enableRepeatRestBtn = new QPushButton(restTab);
        enableRepeatRestBtn->setObjectName(QString::fromUtf8("enableRepeatRestBtn"));

        restVerticalLayout->addWidget(enableRepeatRestBtn);

        dislikeCurrentRestBtn = new QPushButton(restTab);
        dislikeCurrentRestBtn->setObjectName(QString::fromUtf8("dislikeCurrentRestBtn"));

        restVerticalLayout->addWidget(dislikeCurrentRestBtn);

        playRestBtn = new QPushButton(restTab);
        playRestBtn->setObjectName(QString::fromUtf8("playRestBtn"));

        restVerticalLayout->addWidget(playRestBtn);

        enableRepeatOneRestBtn = new QPushButton(restTab);
        enableRepeatOneRestBtn->setObjectName(QString::fromUtf8("enableRepeatOneRestBtn"));

        restVerticalLayout->addWidget(enableRepeatOneRestBtn);

        toggleLikeRestBtn = new QPushButton(restTab);
        toggleLikeRestBtn->setObjectName(QString::fromUtf8("toggleLikeRestBtn"));

        restVerticalLayout->addWidget(toggleLikeRestBtn);

        pauseRestBtn = new QPushButton(restTab);
        pauseRestBtn->setObjectName(QString::fromUtf8("pauseRestBtn"));

        restVerticalLayout->addWidget(pauseRestBtn);

        likeCurrentRestBtn = new QPushButton(restTab);
        likeCurrentRestBtn->setObjectName(QString::fromUtf8("likeCurrentRestBtn"));

        restVerticalLayout->addWidget(likeCurrentRestBtn);

        previousRestBtn = new QPushButton(restTab);
        previousRestBtn->setObjectName(QString::fromUtf8("previousRestBtn"));

        restVerticalLayout->addWidget(previousRestBtn);

        disableRepeatRestBtn = new QPushButton(restTab);
        disableRepeatRestBtn->setObjectName(QString::fromUtf8("disableRepeatRestBtn"));

        restVerticalLayout->addWidget(disableRepeatRestBtn);

        toggleShuffleRestBtn = new QPushButton(restTab);
        toggleShuffleRestBtn->setObjectName(QString::fromUtf8("toggleShuffleRestBtn"));

        restVerticalLayout->addWidget(toggleShuffleRestBtn);


        gridLayout_3->addLayout(restVerticalLayout, 1, 0, 1, 1);

        restGetVerticalLayout = new QVBoxLayout();
        restGetVerticalLayout->setObjectName(QString::fromUtf8("restGetVerticalLayout"));
        restGetLabel = new QLabel(restTab);
        restGetLabel->setObjectName(QString::fromUtf8("restGetLabel"));
        restGetLabel->setAlignment(Qt::AlignCenter);

        restGetVerticalLayout->addWidget(restGetLabel);

        getInfoRestBtn = new QPushButton(restTab);
        getInfoRestBtn->setObjectName(QString::fromUtf8("getInfoRestBtn"));

        restGetVerticalLayout->addWidget(getInfoRestBtn);

        getCurrentSongRestBtn = new QPushButton(restTab);
        getCurrentSongRestBtn->setObjectName(QString::fromUtf8("getCurrentSongRestBtn"));

        restGetVerticalLayout->addWidget(getCurrentSongRestBtn);

        getCurrentAlbumArtRestBtn = new QPushButton(restTab);
        getCurrentAlbumArtRestBtn->setObjectName(QString::fromUtf8("getCurrentAlbumArtRestBtn"));

        restGetVerticalLayout->addWidget(getCurrentAlbumArtRestBtn);

        getCurrentArtistRestBtn = new QPushButton(restTab);
        getCurrentArtistRestBtn->setObjectName(QString::fromUtf8("getCurrentArtistRestBtn"));

        restGetVerticalLayout->addWidget(getCurrentArtistRestBtn);

        getIsPlayingRestBtn = new QPushButton(restTab);
        getIsPlayingRestBtn->setObjectName(QString::fromUtf8("getIsPlayingRestBtn"));

        restGetVerticalLayout->addWidget(getIsPlayingRestBtn);

        getRepeatStatusRestBtn = new QPushButton(restTab);
        getRepeatStatusRestBtn->setObjectName(QString::fromUtf8("getRepeatStatusRestBtn"));

        restGetVerticalLayout->addWidget(getRepeatStatusRestBtn);

        getIsCurrentLikedRestBtn = new QPushButton(restTab);
        getIsCurrentLikedRestBtn->setObjectName(QString::fromUtf8("getIsCurrentLikedRestBtn"));

        restGetVerticalLayout->addWidget(getIsCurrentLikedRestBtn);


        gridLayout_3->addLayout(restGetVerticalLayout, 1, 7, 1, 1);

        tabWidget->addTab(restTab, QString());
        webSocketTab = new QWidget();
        webSocketTab->setObjectName(QString::fromUtf8("webSocketTab"));
        webSocketGridLayout = new QGridLayout(webSocketTab);
        webSocketGridLayout->setObjectName(QString::fromUtf8("webSocketGridLayout"));
        webSocketVerticalLayout = new QVBoxLayout();
        webSocketVerticalLayout->setObjectName(QString::fromUtf8("webSocketVerticalLayout"));
        nextWebSocketBtn = new QPushButton(webSocketTab);
        nextWebSocketBtn->setObjectName(QString::fromUtf8("nextWebSocketBtn"));
        nextWebSocketBtn->setEnabled(false);

        webSocketVerticalLayout->addWidget(nextWebSocketBtn);

        playPauseWebSocketBtn = new QPushButton(webSocketTab);
        playPauseWebSocketBtn->setObjectName(QString::fromUtf8("playPauseWebSocketBtn"));
        playPauseWebSocketBtn->setEnabled(false);

        webSocketVerticalLayout->addWidget(playPauseWebSocketBtn);

        enableRepeatWebSocketBtn = new QPushButton(webSocketTab);
        enableRepeatWebSocketBtn->setObjectName(QString::fromUtf8("enableRepeatWebSocketBtn"));
        enableRepeatWebSocketBtn->setEnabled(false);

        webSocketVerticalLayout->addWidget(enableRepeatWebSocketBtn);

        dislikeCurrentWebSocketBtn = new QPushButton(webSocketTab);
        dislikeCurrentWebSocketBtn->setObjectName(QString::fromUtf8("dislikeCurrentWebSocketBtn"));
        dislikeCurrentWebSocketBtn->setEnabled(false);

        webSocketVerticalLayout->addWidget(dislikeCurrentWebSocketBtn);

        playWebSocketBtn = new QPushButton(webSocketTab);
        playWebSocketBtn->setObjectName(QString::fromUtf8("playWebSocketBtn"));
        playWebSocketBtn->setEnabled(false);

        webSocketVerticalLayout->addWidget(playWebSocketBtn);

        enableRepeatOneWebSocketBtn = new QPushButton(webSocketTab);
        enableRepeatOneWebSocketBtn->setObjectName(QString::fromUtf8("enableRepeatOneWebSocketBtn"));
        enableRepeatOneWebSocketBtn->setEnabled(false);

        webSocketVerticalLayout->addWidget(enableRepeatOneWebSocketBtn);

        toggleLikeWebSocketBtn = new QPushButton(webSocketTab);
        toggleLikeWebSocketBtn->setObjectName(QString::fromUtf8("toggleLikeWebSocketBtn"));
        toggleLikeWebSocketBtn->setEnabled(false);

        webSocketVerticalLayout->addWidget(toggleLikeWebSocketBtn);

        pauseWebSocketBtn = new QPushButton(webSocketTab);
        pauseWebSocketBtn->setObjectName(QString::fromUtf8("pauseWebSocketBtn"));
        pauseWebSocketBtn->setEnabled(false);

        webSocketVerticalLayout->addWidget(pauseWebSocketBtn);

        likeCurrentWebSocketBtn = new QPushButton(webSocketTab);
        likeCurrentWebSocketBtn->setObjectName(QString::fromUtf8("likeCurrentWebSocketBtn"));
        likeCurrentWebSocketBtn->setEnabled(false);

        webSocketVerticalLayout->addWidget(likeCurrentWebSocketBtn);

        previousWebSocketBtn = new QPushButton(webSocketTab);
        previousWebSocketBtn->setObjectName(QString::fromUtf8("previousWebSocketBtn"));
        previousWebSocketBtn->setEnabled(false);

        webSocketVerticalLayout->addWidget(previousWebSocketBtn);

        disableRepeatWebSocketBtn = new QPushButton(webSocketTab);
        disableRepeatWebSocketBtn->setObjectName(QString::fromUtf8("disableRepeatWebSocketBtn"));
        disableRepeatWebSocketBtn->setEnabled(false);

        webSocketVerticalLayout->addWidget(disableRepeatWebSocketBtn);

        toggleShuffleWebSocketBtn = new QPushButton(webSocketTab);
        toggleShuffleWebSocketBtn->setObjectName(QString::fromUtf8("toggleShuffleWebSocketBtn"));
        toggleShuffleWebSocketBtn->setEnabled(false);

        webSocketVerticalLayout->addWidget(toggleShuffleWebSocketBtn);


        webSocketGridLayout->addLayout(webSocketVerticalLayout, 0, 0, 3, 1);

        webSocketConsole = new QTextEdit(webSocketTab);
        webSocketConsole->setObjectName(QString::fromUtf8("webSocketConsole"));
        webSocketConsole->setEnabled(false);

        webSocketGridLayout->addWidget(webSocketConsole, 1, 1, 2, 2);

        activateWebSocketBtn = new QPushButton(webSocketTab);
        activateWebSocketBtn->setObjectName(QString::fromUtf8("activateWebSocketBtn"));
        activateWebSocketBtn->setEnabled(true);
        activateWebSocketBtn->setAutoDefault(false);
        activateWebSocketBtn->setFlat(false);

        webSocketGridLayout->addWidget(activateWebSocketBtn, 0, 1, 1, 1);

        webSocketGetVerticalLayout = new QVBoxLayout();
        webSocketGetVerticalLayout->setObjectName(QString::fromUtf8("webSocketGetVerticalLayout"));
        webSocketGetLabel = new QLabel(webSocketTab);
        webSocketGetLabel->setObjectName(QString::fromUtf8("webSocketGetLabel"));
        webSocketGetLabel->setAlignment(Qt::AlignCenter);

        webSocketGetVerticalLayout->addWidget(webSocketGetLabel);

        getInfoWebSocketBtn = new QPushButton(webSocketTab);
        getInfoWebSocketBtn->setObjectName(QString::fromUtf8("getInfoWebSocketBtn"));

        webSocketGetVerticalLayout->addWidget(getInfoWebSocketBtn);

        getCurrentSongWebSocketBtn = new QPushButton(webSocketTab);
        getCurrentSongWebSocketBtn->setObjectName(QString::fromUtf8("getCurrentSongWebSocketBtn"));

        webSocketGetVerticalLayout->addWidget(getCurrentSongWebSocketBtn);

        getCurrentAlbumArtWebSocketBtn = new QPushButton(webSocketTab);
        getCurrentAlbumArtWebSocketBtn->setObjectName(QString::fromUtf8("getCurrentAlbumArtWebSocketBtn"));

        webSocketGetVerticalLayout->addWidget(getCurrentAlbumArtWebSocketBtn);

        getCurrentArtistWebSocketBtn = new QPushButton(webSocketTab);
        getCurrentArtistWebSocketBtn->setObjectName(QString::fromUtf8("getCurrentArtistWebSocketBtn"));

        webSocketGetVerticalLayout->addWidget(getCurrentArtistWebSocketBtn);

        getIsPlayingWebSocketBtn = new QPushButton(webSocketTab);
        getIsPlayingWebSocketBtn->setObjectName(QString::fromUtf8("getIsPlayingWebSocketBtn"));

        webSocketGetVerticalLayout->addWidget(getIsPlayingWebSocketBtn);

        getRepeatStatusWebSocketBtn = new QPushButton(webSocketTab);
        getRepeatStatusWebSocketBtn->setObjectName(QString::fromUtf8("getRepeatStatusWebSocketBtn"));

        webSocketGetVerticalLayout->addWidget(getRepeatStatusWebSocketBtn);

        getIsCurrentLikedWebSocketBtn = new QPushButton(webSocketTab);
        getIsCurrentLikedWebSocketBtn->setObjectName(QString::fromUtf8("getIsCurrentLikedWebSocketBtn"));

        webSocketGetVerticalLayout->addWidget(getIsCurrentLikedWebSocketBtn);


        webSocketGridLayout->addLayout(webSocketGetVerticalLayout, 0, 3, 3, 1);

        deactivateWebSocketBtn = new QPushButton(webSocketTab);
        deactivateWebSocketBtn->setObjectName(QString::fromUtf8("deactivateWebSocketBtn"));
        deactivateWebSocketBtn->setEnabled(false);

        webSocketGridLayout->addWidget(deactivateWebSocketBtn, 0, 2, 1, 1);

        tabWidget->addTab(webSocketTab, QString());

        gridLayout->addWidget(tabWidget, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 780, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionActivateWebSocket);
        menuFile->addAction(actionDeactivateWebSocket);
        menuHelp->addAction(actionAbout);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);
        activateWebSocketBtn->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionActivateWebSocket->setText(QCoreApplication::translate("MainWindow", "Activate WebSocket", nullptr));
        actionDeactivateWebSocket->setText(QCoreApplication::translate("MainWindow", "DeactivateWebSocket", nullptr));
        actionAbout->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
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
        restGetLabel->setText(QCoreApplication::translate("MainWindow", "Get", nullptr));
        getInfoRestBtn->setText(QCoreApplication::translate("MainWindow", "Info", nullptr));
        getCurrentSongRestBtn->setText(QCoreApplication::translate("MainWindow", "Current Song", nullptr));
        getCurrentAlbumArtRestBtn->setText(QCoreApplication::translate("MainWindow", "Current Album Art", nullptr));
        getCurrentArtistRestBtn->setText(QCoreApplication::translate("MainWindow", "Current Artist", nullptr));
        getIsPlayingRestBtn->setText(QCoreApplication::translate("MainWindow", "Is Playing", nullptr));
        getRepeatStatusRestBtn->setText(QCoreApplication::translate("MainWindow", "Repeat Status", nullptr));
        getIsCurrentLikedRestBtn->setText(QCoreApplication::translate("MainWindow", "Is Currnet Liked", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(restTab), QCoreApplication::translate("MainWindow", "Rest", nullptr));
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
        activateWebSocketBtn->setText(QCoreApplication::translate("MainWindow", "Activate", nullptr));
        webSocketGetLabel->setText(QCoreApplication::translate("MainWindow", "Get", nullptr));
        getInfoWebSocketBtn->setText(QCoreApplication::translate("MainWindow", "Info", nullptr));
        getCurrentSongWebSocketBtn->setText(QCoreApplication::translate("MainWindow", "Current Song", nullptr));
        getCurrentAlbumArtWebSocketBtn->setText(QCoreApplication::translate("MainWindow", "Current Album Art", nullptr));
        getCurrentArtistWebSocketBtn->setText(QCoreApplication::translate("MainWindow", "Current Artist", nullptr));
        getIsPlayingWebSocketBtn->setText(QCoreApplication::translate("MainWindow", "Is Playing", nullptr));
        getRepeatStatusWebSocketBtn->setText(QCoreApplication::translate("MainWindow", "Repeat Status", nullptr));
        getIsCurrentLikedWebSocketBtn->setText(QCoreApplication::translate("MainWindow", "Is Currnet Liked", nullptr));
        deactivateWebSocketBtn->setText(QCoreApplication::translate("MainWindow", "Deactivate", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(webSocketTab), QCoreApplication::translate("MainWindow", "WebSocket", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("MainWindow", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MAINWINDOW_H
