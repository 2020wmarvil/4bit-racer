#ifndef GAME_WORLD
#define GAME_WORLD

#include <SDL2/SDL.h>

#include <vector>

#include "EventHandler.hpp"
#include "Entity.hpp"

class World {
  private:
    std::vector<Entity*> entities;
  public:
    World() { }

    void AddEntity(Entity *entity) {
      entities.push_back(entity);
    }

    void Update(struct Params *params) {
      for(Entity* entity : entities) {
        if (entity->name == "PlayerCar") {
          ProcessPlayerInput(params, entity);
        }
      }
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
