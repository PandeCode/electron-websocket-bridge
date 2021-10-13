#include "./mainwindow.cpp"
#include "Log.hpp"
#include "WebSocket.hpp"
#include "Rest.hpp"

class UIMainWindow : public Ui_MainWindow {
      public:
	WebSocket websocket;

	void init() {

		// clang-format off
		QObject::connect(toggleShuffleRestBtn,        &QPushButton::clicked, []()          { Rest::toggleShuffle()       ; Log::Info("toggleShuffleRestBtn clicked"  )      ;  } ) ;
		QObject::connect(playPauseRestBtn,            &QPushButton::clicked, []()          { Rest::playPause()           ; Log::Info("playPauseRestBtn clicked"      )      ;  } ) ;
		QObject::connect(enableRepeatRestBtn,         &QPushButton::clicked, []()          { Rest::enableRepeat()        ; Log::Info("enableRepeatRestBtn clicked"   )      ;  } ) ;
		QObject::connect(toggleLikeRestBtn,           &QPushButton::clicked, []()          { Rest::toggleLike()          ; Log::Info("toggleLikeRestBtn clicked"     )      ;  } ) ;
		QObject::connect(likeCurrentRestBtn,          &QPushButton::clicked, []()          { Rest::likeCurrent()         ; Log::Info("likeCurrentRestBtn clicked"    )      ;  } ) ;
		QObject::connect(disableRepeatRestBtn,        &QPushButton::clicked, []()          { Rest::disableRepeat()       ; Log::Info("disableRepeatRestBtn clicked"  )      ;  } ) ;
		QObject::connect(previousRestBtn,             &QPushButton::clicked, []()          { Rest::previous()            ; Log::Info("previousRestBtn clicked"       )      ;  } ) ;
		QObject::connect(enableRepeatOneRestBtn,      &QPushButton::clicked, []()          { Rest::enableRepeatOne()     ; Log::Info("enableRepeatOneRestBtn clicked")      ;  } ) ;
		QObject::connect(playRestBtn,                 &QPushButton::clicked, []()          { Rest::play()                ; Log::Info("playRestBtn clicked"           )      ;  } ) ;
		QObject::connect(nextRestBtn,                 &QPushButton::clicked, []()          { Rest::next()                ; Log::Info("nextRestBtn clicked"           )      ;  } ) ;
		QObject::connect(pauseRestBtn,                &QPushButton::clicked, []()          { Rest::pause()               ; Log::Info("pauseRestBtn clicked"          )      ;  } ) ;
		QObject::connect(dislikeCurrentRestBtn,       &QPushButton::clicked, []()          { Rest::dislikeCurrent()      ; Log::Info("dislikeCurrentRestBtn clicked" )      ;  } ) ;
		// clang-format on

		// clang-format off
		QObject::connect(activateWebSocketBtn,        &QPushButton::clicked, [this]() { websocket.activate()        ; Log::Info("activateWebSocketBtn clicked"  )      ;  } ) ;
		QObject::connect(toggleShuffleWebSocketBtn,   &QPushButton::clicked, [this]() { websocket.toggleShuffle()   ; Log::Info("toggleShuffleWebSocketBtn clicked"  ) ;  } ) ;
		QObject::connect(playPauseWebSocketBtn,       &QPushButton::clicked, [this]() { websocket.playPause()       ; Log::Info("playPauseWebSocketBtn clicked"      ) ;  } ) ;
		QObject::connect(enableRepeatWebSocketBtn,    &QPushButton::clicked, [this]() { websocket.enableRepeat()    ; Log::Info("enableRepeatWebSocketBtn clicked"   ) ;  } ) ;
		QObject::connect(toggleLikeWebSocketBtn,      &QPushButton::clicked, [this]() { websocket.toggleLike()      ; Log::Info("toggleLikeWebSocketBtn clicked"     ) ;  } ) ;
		QObject::connect(likeCurrentWebSocketBtn,     &QPushButton::clicked, [this]() { websocket.likeCurrent()     ; Log::Info("likeCurrentWebSocketBtn clicked"    ) ;  } ) ;
		QObject::connect(disableRepeatWebSocketBtn,   &QPushButton::clicked, [this]() { websocket.disableRepeat()   ; Log::Info("disableRepeatWebSocketBtn clicked"  ) ;  } ) ;
		QObject::connect(previousWebSocketBtn,        &QPushButton::clicked, [this]() { websocket.previous()        ; Log::Info("previousWebSocketBtn clicked"       ) ;  } ) ;
		QObject::connect(enableRepeatOneWebSocketBtn, &QPushButton::clicked, [this]() { websocket.enableRepeatOne() ; Log::Info("enableRepeatOneWebSocketBtn clicked") ;  } ) ;
		QObject::connect(playWebSocketBtn,            &QPushButton::clicked, [this]() { websocket.play()            ; Log::Info("playWebSocketBtn clicked"           ) ;  } ) ;
		QObject::connect(nextWebSocketBtn,            &QPushButton::clicked, [this]() { websocket.next()            ; Log::Info("nextWebSocketBtn clicked"           ) ;  } ) ;
		QObject::connect(pauseWebSocketBtn,           &QPushButton::clicked, [this]() { websocket.pause()           ; Log::Info("pauseWebSocketBtn clicked"          ) ;  } ) ;
		QObject::connect(dislikeCurrentWebSocketBtn,  &QPushButton::clicked, [this]() { websocket.dislikeCurrent()  ; Log::Info("dislikeCurrentWebSocketBtn clicked" ) ;  } ) ;
		// clang-format on

	}
};

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);

	auto MainWindow = QMainWindow();

	auto ui         = UIMainWindow();
	ui.setupUi(&MainWindow);
	ui.init();

	MainWindow.show();

	app.exec();

	return 0;
}
