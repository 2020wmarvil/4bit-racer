#ifndef GAME_EVENTHANDLER
#define GAME_EVENTHANDLER

#include <SDL2/SDL.h>

struct Params {
  bool W_PRESSED      = false;
  bool A_PRESSED      = false;
  bool S_PRESSED      = false;
  bool D_PRESSED      = false;
  bool ESC_PRESSED    = false;

  bool UP_PRESSED     = false;
  bool LEFT_PRESSED   = false;
  bool DOWN_PRESSED   = false;
  bool RIGHT_PRESSED  = false;

  float ANALOG_Y = 0;
  float ANALOG_X = 0;
};

class EventHandler {
public:
  EventHandler() {}

  bool PollInput(Params* params) {
    SDL_Event event;

    while(SDL_PollEvent(&event)) {
      if(event.type == SDL_QUIT) { SDL_PushEvent(&event); return false;}

      if(event.type == SDL_KEYDOWN || event.type==SDL_KEYUP) {
        switch(event.key.keysym.sym) {
          case SDLK_w:
            params->W_PRESSED=event.type==SDL_KEYDOWN;
            break;
          case SDLK_a:
            params->A_PRESSED=event.type==SDL_KEYDOWN;
            break;
          case SDLK_s:
            params->S_PRESSED=event.type==SDL_KEYDOWN;
            break;
          case SDLK_d:
            params->D_PRESSED=event.type==SDL_KEYDOWN;
            break;
        }
      }
    }

    return true;
  }
};
#endif
