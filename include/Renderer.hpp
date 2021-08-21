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
    std::vector<Canvas*> canvases;

    SDL_Renderer *ren;
    int maxLayers = 32;
  public:
    Renderer(SDL_Renderer* ren) {
      this->ren=ren;
    }

    void AddEntity(Entity *entity) {
      entities.push_back(entity);
    }

    void AddCanvas(Canvas *canvas) {
      canvases.push_back(canvas);
    }

    void Render() {
      SDL_SetRenderDrawColor(ren,0,0,0,255);
      SDL_RenderClear(ren);

      // render entities
      for(int layer=0; layer<maxLayers; layer++) {
        for(Entity* a : entities) {
          struct Texture::TexData* texdata=(struct Texture::TexData*)a->GetComponent(TEXTURE)->GetData();
          struct Transform::TransformData* transformdata=(struct Transform::TransformData*)a->GetComponent(TRANSFORM)->GetData();
          if(texdata->layer==layer) {
            SDL_FRect rect;
            int wid,hei;
            SDL_QueryTexture(texdata->tex,NULL,NULL,&wid,&hei);
            rect.w=wid;rect.h=hei;
            rect.w*=texdata->scale;
            rect.h*=texdata->scale;
            rect.x=SCREEN_SIZE*(transformdata->posX+100)/200-rect.w/2;
            rect.y=SCREEN_SIZE*(transformdata->posY+100)/200+rect.h/2;
            rect.y=SCREEN_SIZE-rect.y;
            SDL_RenderCopyExF(ren,texdata->tex,NULL,&rect,transformdata->rotation,NULL,SDL_FLIP_NONE);
          }
        }
      }

      // render UI

      for(int layer=0; layer<maxLayers; layer++) {
        for(Canvas* c : canvases) {
          if (c->IsEnabled()) {
            std::vector<UI_Element*> elements = c->GetElements();
            for(int i=0; i<elements.size(); i++) {
              if (!elements[i]->visible) continue;

              if(elements[i]->layer == layer) {
                RenderUI_Element(elements[i]);
              }
            }
          }
        }
      }

      SDL_RenderPresent(ren);
    }

    void RenderUI_Element(UI_Element* element) {

      if (element->type == TEXT) {
        // draw true type font
      } else if (element->type == BUTTON) {
        SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
        SDL_RenderFillRect(ren, element->rect);
      } else if (element->type == IMAGE) {
        struct Image::ImageData* imgdata=(struct Image::ImageData*)element->GetData();
        SDL_RenderCopy(ren, imgdata->tex, NULL, element->rect);
      }
    }
};

#endif
