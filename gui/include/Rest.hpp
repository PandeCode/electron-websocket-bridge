#pragma once
#include "httplib.h"

class Rest {
	static httplib::Client cli;

      public:
	Rest()             = delete;
	~Rest()            = delete;
	Rest(const Rest&)  = delete;
	Rest(const Rest&&) = delete;

	static void toggleShuffle();
	static void playPause();
	static void enableRepeat();
	static void toggleLike();
	static void likeCurrent();
	static void disableRepeat();
	static void previous();
	static void enableRepeatOne();
	static void play();
	static void next();
	static void pause();
	static void dislikeCurrent();
};
