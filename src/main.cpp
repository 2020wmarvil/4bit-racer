#include <iostream>

#include <SDL2/SDL.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#include "../include/Utilities.hpp"
#include "../include/Entity.hpp"
#include "../include/Components.hpp"
#include "../include/EventHandler.hpp"
#include "../include/Physics.hpp"
#include "../include/Renderer.hpp"

const int SCREEN_FPS = 30;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    Uint32 rmask = 0xff000000;
    Uint32 gmask = 0x00ff0000;
    Uint32 bmask = 0x0000ff00;
    Uint32 amask = 0x000000ff;
#else
    Uint32 rmask = 0x000000ff;
    Uint32 gmask = 0x0000ff00;
    Uint32 bmask = 0x00ff0000;
    Uint32 amask = 0xff000000;
#endif

void titlescreen(SDL_Renderer *ren);
void game(SDL_Renderer *ren);

const char cartemplate[][4]={
                      {1,2,2,1},
                      {2,2,2,2},
                      {0,0,0,0},
                      {0,2,2,0},
                      {2,2,2,2},
                      {0,0,0,0},
                      {2,2,2,2},
                      {2,2,2,2}
                    };

int main(/*int argc, char** argv*/) {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window *win = SDL_CreateWindow("4Bit Racer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
  SDL_Renderer *ren = SDL_GetRenderer(win);
	if(!ren) ren = SDL_CreateRenderer(win, -1, 0);

  titlescreen(ren);

  SDL_Quit();
  return 0;
}

void game(SDL_Renderer *ren) {
  struct Params *params = new struct Params;

  PhysicsSim *sim = new PhysicsSim();
  Renderer *renderer = new Renderer(ren);

  // begin entity creation
  Entity *car = new Entity();
  Texture *carTexture = new Texture(
    SDL_CreateTextureFromSurface(ren, SDL_LoadBMP("../assets/Car.bmp")),
    createRect(316, 232, 8, 16)
  );
  carTexture->SetLayer(1);
  carTexture->SetScale(10);
  car->AddComponent(carTexture);
  renderer->AddEntity(car);
  Rigidbody *carRB = new Rigidbody();
  car->AddComponent(carRB);
  sim->AddEntity(car);

  Entity *map = new Entity();
  Texture *mapTexture = new Texture(
    SDL_CreateTextureFromSurface(ren, SDL_LoadBMP("../assets/map.bmp")),
    createRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)
  );
  mapTexture->SetScale(10);
  map->AddComponent(mapTexture);
  renderer->AddEntity(map);
  // end entity creation

  int previousTicks = SDL_GetTicks();

  while(true) {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
      if(event.type==SDL_QUIT) {SDL_PushEvent(&event);return;}
      if(event.type==SDL_KEYDOWN||event.type==SDL_KEYUP) {
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
          default:
            return;
        }
      }
    }

    sim->Update(params);

    renderer->Render();

    // limit framerate
    int frameTicks = SDL_GetTicks() - previousTicks;
    if(frameTicks < SCREEN_TICKS_PER_FRAME) SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
    previousTicks = SDL_GetTicks();
  }
}
void titlescreen(SDL_Renderer *ren) {
  SDL_Rect button;button.x=300;button.y=230;button.w=40;button.h=20;
  while(true) {
    SDL_Event event;
    if(SDL_PollEvent(&event)) {//event handling todo: clean it up a bit
      if(event.type==SDL_QUIT) {SDL_PushEvent(&event);return;}
      if(event.type==SDL_MOUSEBUTTONDOWN&&event.button.button==SDL_BUTTON_LEFT&&withinRect(event.button.x,event.button.y,button)) game(ren);
    }
    SDL_SetRenderDrawColor(ren,0,0,0,255);
    SDL_RenderClear(ren);
    SDL_SetRenderDrawColor(ren,255,255,255,255);
    SDL_RenderFillRect(ren, &button);
    SDL_RenderPresent(ren);
  }
}
