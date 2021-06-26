#ifndef GAME_PHYSICS
#define GAME_PHYSICS

#include <vector>

#include "Entity.hpp"
#include "Components.hpp"
#include "EventHandler.hpp"

class PhysicsSim {
  private:
    std::vector<Entity*> entities;
  public:
    PhysicsSim() { }

    void AddEntity(Entity *entity) {
      entities.push_back(entity);
    }

    void Update(struct Params *params) {
      for(Entity* a : entities) {
        struct Rigidbody::RigidbodyData* rb=(struct Rigidbody::RigidbodyData*)a->GetComponent(RIGIDBODY)->GetData();
        struct Transform::TransformData* transform=(struct Transform::TransformData*)a->GetComponent(TRANSFORM)->GetData();

        if (params->W_PRESSED) transform->posY += 1;
        if (params->S_PRESSED) transform->posY -= 1;
        if (params->D_PRESSED) transform->posX += 1;
        if (params->A_PRESSED) transform->posX -= 1;
      }
    }
};


#endif
