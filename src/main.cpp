#include <iostream>

#include <SDL2/SDL.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
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
int main(int argc, char** argv) {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window *win = SDL_CreateWindow("4Bit Racer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
  SDL_Renderer *ren = SDL_GetRenderer(win);
	if(!ren) ren = SDL_CreateRenderer(win, -1, 0);

  SDL_Surface* car = SDL_CreateRGBSurface(0,4,8,32,rmask,gmask,bmask,amask);


  bool quit = false;
  while(!quit) {
    SDL_Event event;
    if(SDL_PollEvent(&event)) {
      quit=event.type==SDL_QUIT;
    }
  }

  SDL_Quit();
  return 0;
}
