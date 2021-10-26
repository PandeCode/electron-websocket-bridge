#include "gui/UIMainWindow.hpp"

#include "Log.hpp"
#include "gui/Rest.hpp"

#include <qtextedit.h>

#define BIND_BTN_PRESS(BTN, FUNC) QObject::connect(BTN, &QPushButton::pressed, FUNC);

void UIMainWindow::init() {

	// clang-format off

 	BIND_BTN_PRESS(getInfoRestBtn,                 [this]() { appendRestConsole(Rest::getInfo()            );  } );
	BIND_BTN_PRESS(getCurrentSongRestBtn,          [this]() { appendRestConsole(Rest::getCurrentSong()     );  } );
	BIND_BTN_PRESS(getCurrentAlbumArtRestBtn,      [this]() { appendRestConsole(Rest::getCurrentAlbumArt() );  } );
	BIND_BTN_PRESS(getCurrentArtistRestBtn,        [this]() { appendRestConsole(Rest::getCurrentArtist()   );  } );
	BIND_BTN_PRESS(getIsPlayingRestBtn,            [this]() { appendRestConsole(Rest::getIsPlaying()       );  } );
	BIND_BTN_PRESS(getRepeatStatusRestBtn,         [this]() { appendRestConsole(Rest::getRepeatStatus()    );  } );
	BIND_BTN_PRESS(getIsCurrentLikedRestBtn,       [this]() { appendRestConsole(Rest::getIsCurrentLiked()  );  } );

	BIND_BTN_PRESS(toggleShuffleRestBtn,           []() { Rest::toggleShuffle()   ; Log::Info("toggleShuffleRestBtn clicked"  );  } );
	BIND_BTN_PRESS(playPauseRestBtn,               []() { Rest::playPause()       ; Log::Info("playPauseRestBtn clicked"      );  } );
	BIND_BTN_PRESS(enableRepeatRestBtn,            []() { Rest::enableRepeat()    ; Log::Info("enableRepeatRestBtn clicked"   );  } );
	BIND_BTN_PRESS(toggleLikeRestBtn,              []() { Rest::toggleLike()      ; Log::Info("toggleLikeRestBtn clicked"     );  } );
	BIND_BTN_PRESS(likeCurrentRestBtn,             []() { Rest::likeCurrent()     ; Log::Info("likeCurrentRestBtn clicked"    );  } );
	BIND_BTN_PRESS(disableRepeatRestBtn,           []() { Rest::disableRepeat()   ; Log::Info("disableRepeatRestBtn clicked"  );  } );
	BIND_BTN_PRESS(previousRestBtn,                []() { Rest::previous()        ; Log::Info("previousRestBtn clicked"       );  } );
	BIND_BTN_PRESS(enableRepeatOneRestBtn,         []() { Rest::enableRepeatOne() ; Log::Info("enableRepeatOneRestBtn clicked");  } );
	BIND_BTN_PRESS(playRestBtn,                    []() { Rest::play()            ; Log::Info("playRestBtn clicked"           );  } );
	BIND_BTN_PRESS(nextRestBtn,                    []() { Rest::next()            ; Log::Info("nextRestBtn clicked"           );  } );
	BIND_BTN_PRESS(pauseRestBtn,                   []() { Rest::pause()           ; Log::Info("pauseRestBtn clicked"          );  } );
	BIND_BTN_PRESS(dislikeCurrentRestBtn,          []() { Rest::dislikeCurrent()  ; Log::Info("dislikeCurrentRestBtn clicked" );  } );

	BIND_BTN_PRESS(activateWebSocketBtn,           [this]() { activateWebSocket();   Log::Info("activateWebSocketBtn clicked"  );  } );
	BIND_BTN_PRESS(deactivateWebSocketBtn,         [this]() { deactivateWebSocket(); Log::Info("activateWebSocketBtn clicked"  );  } );

	BIND_BTN_PRESS(getInfoWebSocketBtn,            [this]() { appendWebSocketConsole(websocket.getInfo()            );  } );
	BIND_BTN_PRESS(getCurrentSongWebSocketBtn,     [this]() { appendWebSocketConsole(websocket.getCurrentSong()     );  } );
	BIND_BTN_PRESS(getCurrentAlbumArtWebSocketBtn, [this]() { appendWebSocketConsole(websocket.getCurrentAlbumArt() );  } );
	BIND_BTN_PRESS(getCurrentArtistWebSocketBtn,   [this]() { appendWebSocketConsole(websocket.getCurrentArtist()   );  } );
	BIND_BTN_PRESS(getIsPlayingWebSocketBtn,       [this]() { appendWebSocketConsole(websocket.getIsPlaying()       );  } );
	BIND_BTN_PRESS(getRepeatStatusWebSocketBtn,    [this]() { appendWebSocketConsole(websocket.getRepeatStatus()    );  } );
	BIND_BTN_PRESS(getIsCurrentLikedWebSocketBtn,  [this]() { appendWebSocketConsole(websocket.getIsCurrentLiked()  );  } );

	BIND_BTN_PRESS(toggleShuffleWebSocketBtn,      [this]() { websocket.toggleShuffle()   ; Log::Info("toggleShuffleWebSocketBtn clicked"   );  }  );
	BIND_BTN_PRESS(playPauseWebSocketBtn,          [this]() { websocket.playPause()       ; Log::Info("playPauseWebSocketBtn clicked"       );  }  );
	BIND_BTN_PRESS(enableRepeatWebSocketBtn,       [this]() { websocket.enableRepeat()    ; Log::Info("enableRepeatWebSocketBtn clicked"    );  }  );
	BIND_BTN_PRESS(toggleLikeWebSocketBtn,         [this]() { websocket.toggleLike()      ; Log::Info("toggleLikeWebSocketBtn clicked"      );  }  );
	BIND_BTN_PRESS(likeCurrentWebSocketBtn,        [this]() { websocket.likeCurrent()     ; Log::Info("likeCurrentWebSocketBtn clicked"     );  }  );
	BIND_BTN_PRESS(disableRepeatWebSocketBtn,      [this]() { websocket.disableRepeat()   ; Log::Info("disableRepeatWebSocketBtn clicked"   );  }  );
	BIND_BTN_PRESS(previousWebSocketBtn,           [this]() { websocket.previous()        ; Log::Info("previousWebSocketBtn clicked"        );  }  );
	BIND_BTN_PRESS(enableRepeatOneWebSocketBtn,    [this]() { websocket.enableRepeatOne() ; Log::Info("enableRepeatOneWebSocketBtn clicked" );  }  );
	BIND_BTN_PRESS(playWebSocketBtn,               [this]() { websocket.play()            ; Log::Info("playWebSocketBtn clicked"            );  }  );
	BIND_BTN_PRESS(nextWebSocketBtn,               [this]() { websocket.next()            ; Log::Info("nextWebSocketBtn clicked"            );  }  );
	BIND_BTN_PRESS(pauseWebSocketBtn,              [this]() { websocket.pause()           ; Log::Info("pauseWebSocketBtn clicked"           );  }  );
	BIND_BTN_PRESS(dislikeCurrentWebSocketBtn,     [this]() { websocket.dislikeCurrent()  ; Log::Info("dislikeCurrentWebSocketBtn clicked"  );  }  );

	// clang-format on
}

// clang-format off
	 void UIMainWindow::appendRestConsole(const char* message)             { restConsole->append(message);              }
	 void UIMainWindow::appendWebSocketConsole(const char* message)        { webSocketConsole->append(message);         }
	 void UIMainWindow::appendRestConsole(const std::string& message)      { restConsole->append(message.c_str());      }
	 void UIMainWindow::appendWebSocketConsole(const std::string& message) { webSocketConsole->append(message.c_str()); }
// clang-format on

void UIMainWindow::deactivateWebSocket() {
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

void UIMainWindow::activateWebSocket() {
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

UIMainWindow::~UIMainWindow() {
	websocket.close();
}
