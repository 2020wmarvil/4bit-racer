#ifndef GAME_WORLD
#define GAME_WORLD

#include <SDL2/SDL.h>

#include <vector>

#include "EventHandler.hpp"
#include "Entity.hpp"
#include "UI_Elements.hpp"

class World {
  private:
    std::vector<Entity*> entities;
    std::vector<Button*> buttons;
  public:
    World() { }

    void AddEntity(Entity *entity) {
      entities.push_back(entity);
    }
    void AddButton(Button *button) {
      buttons.push_back(button);
    }

    bool Update(struct Params *params) {
      if (params->ESC_PRESSED) {
        return false;
      }

      for(Entity* entity : entities) {
        if (entity->name == "PlayerCar") {
          ProcessPlayerInput(params, entity);
        }
      }

      // if button is not working, check if it is scaled, because that is not supported
      for(Button* button : buttons) {
        if (!button->data.interactable) continue;

        int x = params->MOUSE_X;
        int y = params->MOUSE_Y;

        SDL_Rect *rect = button->rect;

        if (x > rect->x && y > rect->y && x < rect->x + rect->w && y < rect->y + rect->h) {
          if (!button->data.hovered) {
            button->data.hovered = true;
            if (button->data.OnMouseEnter != nullptr) button->data.OnMouseEnter();
          } else {
            if (params->LEFT_MB_PRESSED) {
              if (button->data.OnMouseDown != nullptr) button->data.OnMouseDown();
            } else if (params->LEFT_MB_RELEASED) {
              if (button->data.OnMouseUp != nullptr) button->data.OnMouseUp();
            }
          }
        } else {
          if (button->data.hovered) {
            button->data.hovered = false;
            if (button->data.OnMouseExit != nullptr) button->data.OnMouseExit();
          }
        }
      }

      return true;
    }

    void ProcessPlayerInput(struct Params *params, Entity *player) {
        struct Rigidbody::RigidbodyData* rb=(struct Rigidbody::RigidbodyData*)player->GetComponent(RIGIDBODY)->GetData();

        float carForceMax = 0.01;
        //float carTorqueMax = 0.01;
        float newForce = 0;
        //float newTorque = 0;

        if (params->W_PRESSED) newForce += carForceMax;
        if (params->S_PRESSED) newForce -= carForceMax;
        //if (params->D_PRESSED) newTorque += carTorqueMax;
        //if (params->A_PRESSED) newTorque -= carTorqueMax;
        if (params->D_PRESSED) rb->angularVelocity = 1;
        if (params->A_PRESSED) rb->angularVelocity = -1;
        if (!params->D_PRESSED && !params->A_PRESSED) {
          rb->angularVelocity = 0;
        }

        rb->force = newForce;
        //rb->torque = newTorque;
    }
};

#endif
