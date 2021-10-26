#include "gui/Rest.hpp"

#include "Log.hpp"

httplib::Client Rest::cli("http://localhost:8080");

// clang-format off

void Rest::toggleShuffle()   { cli.Get("/command/toggleShuffle");   }
void Rest::playPause()       { cli.Get("/command/playPause");       }
void Rest::enableRepeat()    { cli.Get("/command/enableRepeat");    }
void Rest::toggleLike()      { cli.Get("/command/toggleLike");      }
void Rest::likeCurrent()     { cli.Get("/command/likeCurrent");     }
void Rest::disableRepeat()   { cli.Get("/command/disableRepeat");   }
void Rest::previous()        { cli.Get("/command/previous");        }
void Rest::enableRepeatOne() { cli.Get("/command/enableRepeatOne"); }
void Rest::play()            { cli.Get("/command/play");            }
void Rest::next()            { cli.Get("/command/next");            }
void Rest::pause()           { cli.Get("/command/pause");           }
void Rest::dislikeCurrent()  { cli.Get("/command/dislikeCurrent");  }

std::string Rest::getCurrentSong()     { if(auto res = cli.Get("/command/getCurrentSong"))     { Log::Debug("getCurrentSong", res->body);return res->body ;     } return "Error Making request" ; }
std::string Rest::getCurrentAlbumArt() { if(auto res = cli.Get("/command/getCurrentAlbumArt")) { Log::Debug("getCurrentAlbumArt", res->body);return res->body ; } return "Error Making request" ; }
std::string Rest::getCurrentArtist()   { if(auto res = cli.Get("/command/getCurrentArtist"))   { Log::Debug("getCurrentArtist", res->body);return res->body ;   } return "Error Making request" ; }
std::string Rest::getIsPlaying()       { if(auto res = cli.Get("/command/getIsPlaying"))       { Log::Debug("getIsPlaying", res->body);return res->body ;       } return "Error Making request" ; }
std::string Rest::getRepeatStatus()    { if(auto res = cli.Get("/command/getRepeatStatus"))    { Log::Debug("getRepeatStatus", res->body);return res->body ;    } return "Error Making request" ; }
std::string Rest::getIsCurrentLiked()  { if(auto res = cli.Get("/command/getIsCurrentLiked"))  { Log::Debug("getIsCurrentLiked", res->body);return res->body ;  } return "Error Making request" ; }

// clang-format on

std::string Rest::getInfo() {
	if(auto res = cli.Get("/command/getInfo")) {
		Log::Debug("getInfo ", res->status, res->body);
		return res->body;
	}
	return "Error Making request";
}
