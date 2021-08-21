#ifndef GAME_EVENTHANDLER
#define GAME_EVENTHANDLER

#include <SDL2/SDL.h>
#include <iostream>

struct Params {
  bool W_PRESSED            = false;
  bool A_PRESSED            = false;
  bool S_PRESSED            = false;
  bool D_PRESSED            = false;
  bool ESC_PRESSED          = false;

  bool UP_PRESSED           = false;
  bool LEFT_PRESSED         = false;
  bool DOWN_PRESSED         = false;
  bool RIGHT_PRESSED        = false;

  bool LEFT_MB_PRESSED      = false;
  bool RIGHT_MB_PRESSED     = false;

  bool LEFT_MB_RELEASED     = false;
  bool RIGHT_MB_RELEASED    = false;

  int MOUSE_X = 0;
  int MOUSE_Y = 0;

  float ANALOG_Y = 0;
  float ANALOG_X = 0;
};

class EventHandler {
public:
  EventHandler() {}

  bool PollInput(Params* params) {
    SDL_Event event;

    params->LEFT_MB_PRESSED = false;
    params->LEFT_MB_RELEASED = false;
    params->RIGHT_MB_PRESSED = false;
    params->RIGHT_MB_RELEASED = false;

    while(SDL_PollEvent(&event)) {
      auto type = event.type;

      if(type == SDL_QUIT) { SDL_PushEvent(&event); return false;}

      if(type == SDL_KEYDOWN || type == SDL_KEYUP) {
        switch(event.key.keysym.sym) {
          case SDLK_w:
            params->W_PRESSED = type == SDL_KEYDOWN;
            break;
          case SDLK_a:
            params->A_PRESSED = type == SDL_KEYDOWN;
            break;
          case SDLK_s:
            params->S_PRESSED = type == SDL_KEYDOWN;
            break;
          case SDLK_d:
            params->D_PRESSED = type == SDL_KEYDOWN;
            break;
          case SDLK_ESCAPE:
            params->ESC_PRESSED = type == SDL_KEYDOWN;
            break;
        }
      }

      if (type == SDL_MOUSEMOTION || type == SDL_MOUSEBUTTONDOWN || type == SDL_MOUSEBUTTONUP) {
        params->MOUSE_X = event.button.x;
        params->MOUSE_Y = event.button.y;

        if (event.button.button == SDL_BUTTON_LEFT) {
          params->LEFT_MB_PRESSED = event.type==SDL_MOUSEBUTTONDOWN;
          params->LEFT_MB_RELEASED = event.type==SDL_MOUSEBUTTONUP;
        } else if (event.button.button == SDL_BUTTON_RIGHT) {
          params->RIGHT_MB_PRESSED = event.type==SDL_MOUSEBUTTONDOWN;
          params->RIGHT_MB_RELEASED = event.type==SDL_MOUSEBUTTONUP;
        }
      }
    }

    return true;
  }
};
#endif
