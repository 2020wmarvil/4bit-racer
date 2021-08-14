#ifndef GAME_RENDERER
#define GAME_RENDERER

#ifndef SCREEN_SIZE
#define SCREEN_SIZE 480
#endif

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
            SDL_FRect rect;
            int wid,hei;
            SDL_QueryTexture(texdata->tex,NULL,NULL,&wid,&hei);
            rect.w=wid;rect.h=hei;
            rect.w*=texdata->scale;
            rect.h*=texdata->scale;
            rect.x=SCREEN_SIZE*(transformdata->posX+100)/200-rect.w/2;
            rect.y=SCREEN_SIZE*(transformdata->posY+100)/200+rect.h/2;
            rect.y=SCREEN_SIZE-rect.y;
            //SDL_RenderCopy(ren,texdata->tex,NULL,&rect);
            SDL_RenderCopyExF(ren,texdata->tex,NULL,&rect,transformdata->rotation,NULL,SDL_FLIP_NONE);
            empty=false;
          }
        }
        if(empty) {SDL_RenderPresent(ren); return;}
      }
    }
};

#endif
