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

        float carForceMax = 0.001;
        float carTorqueMax = 0.001;

        float newForce = 0;
        float newTorque = 0;

        if (params->W_PRESSED) newForce += carForceMax;
        if (params->S_PRESSED) newForce -= carForceMax;
        if (params->D_PRESSED) newTorque += carTorqueMax;
        if (params->A_PRESSED) newTorque -= carTorqueMax;

        rb->force = newForce;
        rb->torque = newTorque;

        rb->accelerationX = sin(transform->rotation) * rb->force;
        rb->accelerationY = cos(transform->rotation) * rb->force;

        rb->velocityX += rb->accelerationX;
        rb->velocityY += rb->accelerationY;

        transform->posX += rb->velocityX;
        transform->posY += rb->velocityY; //TODO something is not being initialized properly and is causing the car to start way off the map

        // rb->angularAcceleration = rb->torque;
        // rb->angulaaaaaaaaaaab rVelocity += rb->angularAcceleration;

        //transform->rotation += rb->angularVelocity;
      }
    }
};


#endif
