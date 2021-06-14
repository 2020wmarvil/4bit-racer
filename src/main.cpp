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

void titlescreen(SDL_Renderer *ren);
bool withinRect(int x, int y, SDL_Rect rect);
void game(SDL_Renderer *ren);

int main(int argc, char** argv) {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window *win = SDL_CreateWindow("4Bit Racer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
  SDL_Renderer *ren = SDL_GetRenderer(win);
	if(!ren) ren = SDL_CreateRenderer(win, -1, 0);

  titlescreen(ren);

  SDL_Quit();
  return 0;
}
void game(SDL_Renderer *ren) {
  SDL_Surface* car = SDL_CreateRGBSurface(0,4,8,32,rmask,gmask,bmask,amask); //todo actually load in and render the car
  while(true) {
    SDL_Event event;
    if(SDL_PollEvent(&event)) {
      if(event.type==SDL_QUIT) {SDL_PushEvent(&event);return;}
      if(event.type==SDL_KEYDOWN) return;
    }
    SDL_SetRenderDrawColor(ren,255,0,0,255);
    SDL_RenderClear(ren);
    SDL_RenderPresent(ren);
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
bool withinRect(int x, int y, SDL_Rect rect) {
  return (x>rect.x&&x<(rect.x+rect.w))&&(y>rect.y&&y<(rect.y+rect.h));
}
