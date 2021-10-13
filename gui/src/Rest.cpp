#include "Rest.hpp"

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
// clang-format on
