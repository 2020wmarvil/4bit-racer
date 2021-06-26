#ifndef GAME_RENDERER
#define GAME_RENDERER

#include <vector>
#include <SDL2/SDL.h>

#include "Entity.hpp"
#include "Components.hpp"
#include "Utilities.hpp"

class Renderer {
  private:
    std::vector<Entity*> entities;
    SDL_Renderer *ren;
  public:
    Renderer(SDL_Renderer* ren) {
      this->ren=ren;
    }

    void AddEntity(Entity *entity) {
      entities.push_back(entity);
    }

    void Render() {
      SDL_SetRenderDrawColor(ren,0,0,0,255);
      SDL_RenderClear(ren);
      for(int i=0;;i++) { //You better not overflow the integer size
        bool empty = true;
        for(Entity* a : entities) {
          struct Texture::TexData* texdata=(struct Texture::TexData*)a->GetComponent(TEXTURE)->GetData();
          struct Transform::TransformData* transformdata=(struct Transform::TransformData*)a->GetComponent(TRANSFORM)->GetData();
          if(texdata->layer==i) {
            SDL_Rect rect;
            SDL_QueryTexture(texdata->tex,NULL,NULL,&rect.w,&rect.h);
            rect.w*=texdata->scale;
            rect.h*=texdata->scale;
            rect.x=transformdata->posX-rect.w/2;
            rect.y=transformdata->posY-rect.h/2;
            rect.y=SCREEN_HEIGHT-rect.y;
            SDL_RenderCopy(ren,texdata->tex,NULL,&rect);
            empty=false;
          }
        }
        if(empty) {SDL_RenderPresent(ren); return;}
      }
    }
};

#endif
