#include "./mainwindow.cpp"
#include "Log.hpp"
#include "gui/Rest.hpp"
#include "gui/WebSocket.hpp"

#include <qtextedit.h>

#define BIND_BTN(BTN, FUNC) BIND_BTN(BTN, FUNC);

class UIMainWindow : public Ui_MainWindow {
      public:
	WebSocket websocket;

	void init() {

		// clang-format off
 		BIND_BTN(getInfoRestBtn					, [this]() { appendRestConsole(Rest::getInfo()            );  } );
		BIND_BTN(getCurrentSongRestBtn			, [this]() { appendRestConsole(Rest::getCurrentSong()     );  } );
		BIND_BTN(getCurrentAlbumArtRestBtn		, [this]() { appendRestConsole(Rest::getCurrentAlbumArt() );  } );
		BIND_BTN(getCurrentArtistRestBtn		, [this]() { appendRestConsole(Rest::getCurrentArtist()   );  } );
		BIND_BTN(getIsPlayingRestBtn			, [this]() { appendRestConsole(Rest::getIsPlaying()       );  } );
		BIND_BTN(getRepeatStatusRestBtn			, [this]() { appendRestConsole(Rest::getRepeatStatus()    );  } );
		BIND_BTN(getIsCurrentLikedRestBtn		, [this]() { appendRestConsole(Rest::getIsCurrentLiked()  );  } );

		BIND_BTN(toggleShuffleRestBtn			, []() { Rest::toggleShuffle()   ; Log::Info("toggleShuffleRestBtn clicked"  );  } );
		BIND_BTN(playPauseRestBtn				, []() { Rest::playPause()       ; Log::Info("playPauseRestBtn clicked"      );  } );
		BIND_BTN(enableRepeatRestBtn			, []() { Rest::enableRepeat()    ; Log::Info("enableRepeatRestBtn clicked"   );  } );
		BIND_BTN(toggleLikeRestBtn				, []() { Rest::toggleLike()      ; Log::Info("toggleLikeRestBtn clicked"     );  } );
		BIND_BTN(likeCurrentRestBtn				, []() { Rest::likeCurrent()     ; Log::Info("likeCurrentRestBtn clicked"    );  } );
		BIND_BTN(disableRepeatRestBtn			, []() { Rest::disableRepeat()   ; Log::Info("disableRepeatRestBtn clicked"  );  } );
		BIND_BTN(previousRestBtn				, []() { Rest::previous()        ; Log::Info("previousRestBtn clicked"       );  } );
		BIND_BTN(enableRepeatOneRestBtn			, []() { Rest::enableRepeatOne() ; Log::Info("enableRepeatOneRestBtn clicked");  } );
		BIND_BTN(playRestBtn					, []() { Rest::play()            ; Log::Info("playRestBtn clicked"           );  } );
		BIND_BTN(nextRestBtn					, []() { Rest::next()            ; Log::Info("nextRestBtn clicked"           );  } );
		BIND_BTN(pauseRestBtn					, []() { Rest::pause()           ; Log::Info("pauseRestBtn clicked"          );  } );
		BIND_BTN(dislikeCurrentRestBtn			, []() { Rest::dislikeCurrent()  ; Log::Info("dislikeCurrentRestBtn clicked" );  } );

		BIND_BTN(activateWebSocketBtn			, [this]() { activateWebSocket();   Log::Info("activateWebSocketBtn clicked"  );  } );
		BIND_BTN(deactivateWebSocketBtn			, [this]() { deactivateWebSocket(); Log::Info("activateWebSocketBtn clicked"  );  } );

		BIND_BTN(getInfoWebSocketBtn            , [this]() { appendWebSocketConsole(websocket.getInfo()            );  } );
		BIND_BTN(getCurrentSongWebSocketBtn     , [this]() { appendWebSocketConsole(websocket.getCurrentSong()     );  } );
		BIND_BTN(getCurrentAlbumArtWebSocketBtn , [this]() { appendWebSocketConsole(websocket.getCurrentAlbumArt() );  } );
		BIND_BTN(getCurrentArtistWebSocketBtn   , [this]() { appendWebSocketConsole(websocket.getCurrentArtist()   );  } );
		BIND_BTN(getIsPlayingWebSocketBtn       , [this]() { appendWebSocketConsole(websocket.getIsPlaying()       );  } );
		BIND_BTN(getRepeatStatusWebSocketBtn    , [this]() { appendWebSocketConsole(websocket.getRepeatStatus()    );  } );
		BIND_BTN(getIsCurrentLikedWebSocketBtn  , [this]() { appendWebSocketConsole(websocket.getIsCurrentLiked()  );  } );

		BIND_BTN(toggleShuffleWebSocketBtn		, [this]() { websocket.toggleShuffle()   ; Log::Info("toggleShuffleWebSocketBtn clicked"   );  }  );
		BIND_BTN(playPauseWebSocketBtn			, [this]() { websocket.playPause()       ; Log::Info("playPauseWebSocketBtn clicked"       );  }  );
		BIND_BTN(enableRepeatWebSocketBtn		, [this]() { websocket.enableRepeat()    ; Log::Info("enableRepeatWebSocketBtn clicked"    );  }  );
		BIND_BTN(toggleLikeWebSocketBtn			, [this]() { websocket.toggleLike()      ; Log::Info("toggleLikeWebSocketBtn clicked"      );  }  );
		BIND_BTN(likeCurrentWebSocketBtn		, [this]() { websocket.likeCurrent()     ; Log::Info("likeCurrentWebSocketBtn clicked"     );  }  );
		BIND_BTN(disableRepeatWebSocketBtn		, [this]() { websocket.disableRepeat()   ; Log::Info("disableRepeatWebSocketBtn clicked"   );  }  );
		BIND_BTN(previousWebSocketBtn			, [this]() { websocket.previous()        ; Log::Info("previousWebSocketBtn clicked"        );  }  );
		BIND_BTN(enableRepeatOneWebSocketBtn	, [this]() { websocket.enableRepeatOne() ; Log::Info("enableRepeatOneWebSocketBtn clicked" );  }  );
		BIND_BTN(playWebSocketBtn				, [this]() { websocket.play()            ; Log::Info("playWebSocketBtn clicked"            );  }  );
		BIND_BTN(nextWebSocketBtn				, [this]() { websocket.next()            ; Log::Info("nextWebSocketBtn clicked"            );  }  );
		BIND_BTN(pauseWebSocketBtn				, [this]() { websocket.pause()           ; Log::Info("pauseWebSocketBtn clicked"           );  }  );
		BIND_BTN(dislikeCurrentWebSocketBtn  , [this]() { websocket.dislikeCurrent()  ; Log::Info("dislikeCurrentWebSocketBtn clicked"  );  }  );
		// clang-format on
	}

	// clang-format off
	inline void appendRestConsole(const char* message)             { restConsole->append(message);              }
	inline void appendWebSocketConsole(const char* message)        { webSocketConsole->append(message);         }
	inline void appendRestConsole(const std::string& message)      { restConsole->append(message.c_str());      }
	inline void appendWebSocketConsole(const std::string& message) { webSocketConsole->append(message.c_str()); }
	// clang-format on

	inline void deactivateWebSocket() {
		websocket.close();

		activateWebSocketBtn->setEnabled(true);
		deactivateWebSocketBtn->setEnabled(false);

		toggleShuffleWebSocketBtn->setEnabled(false);
		playPauseWebSocketBtn->setEnabled(false);
		enableRepeatWebSocketBtn->setEnabled(false);
		toggleLikeWebSocketBtn->setEnabled(false);
		likeCurrentWebSocketBtn->setEnabled(false);
		disableRepeatWebSocketBtn->setEnabled(false);
		previousWebSocketBtn->setEnabled(false);
		enableRepeatOneWebSocketBtn->setEnabled(false);
		playWebSocketBtn->setEnabled(false);
		nextWebSocketBtn->setEnabled(false);
		pauseWebSocketBtn->setEnabled(false);
		dislikeCurrentWebSocketBtn->setEnabled(false);
	}

	inline void activateWebSocket() {
		websocket.activate();

		activateWebSocketBtn->setEnabled(false);
		deactivateWebSocketBtn->setEnabled(true);

		toggleShuffleWebSocketBtn->setEnabled(true);
		playPauseWebSocketBtn->setEnabled(true);
		enableRepeatWebSocketBtn->setEnabled(true);
		toggleLikeWebSocketBtn->setEnabled(true);
		likeCurrentWebSocketBtn->setEnabled(true);
		disableRepeatWebSocketBtn->setEnabled(true);
		previousWebSocketBtn->setEnabled(true);
		enableRepeatOneWebSocketBtn->setEnabled(true);
		playWebSocketBtn->setEnabled(true);
		nextWebSocketBtn->setEnabled(true);
		pauseWebSocketBtn->setEnabled(true);
		dislikeCurrentWebSocketBtn->setEnabled(true);
	}

	~UIMainWindow() { websocket.close(); }
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
