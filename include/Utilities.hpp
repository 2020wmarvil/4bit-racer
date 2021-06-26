#ifndef GAME_UTILITIES
#define GAME_UTILITIES

#include <SDL2/SDL.h>

bool withinRect(int x, int y, SDL_Rect rect) {
  return (x>rect.x&&x<(rect.x+rect.w))&&(y>rect.y&&y<(rect.y+rect.h));
}
SDL_Rect* createRect(int x, int y, int w, int h) {
  SDL_Rect *rect=new SDL_Rect;
  rect->x=x;rect->y=y;rect->w=w;rect->h=h;
  return rect;
}
#endif
