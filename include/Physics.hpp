#ifndef GAME_PHYSICS
#define GAME_PHYSICS

#include <vector>

#include "Entity.hpp"
#include "Components.hpp"
#include "EventHandler.hpp"
#include "Math.hpp"

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
<<<<<<< HEAD
        
        float dirX = sin(transform->rotation * M_PI / 180);
        float dirY = cos(transform->rotation * M_PI / 180);
=======

        float carForceMax = 0.01;
        float carTorqueMax = 0.01;

        float newForce = 0;
        float newTorque = 0;

        float dirX = sin(DegreesToRadians(transform->rotation));
        float dirY = cos(DegreesToRadians(transform->rotation));
>>>>>>> aa3fbc22a63446289f8bf463338063beeebe3829

        rb->accelerationX = rb->force * dirX;
        rb->accelerationY = rb->force * dirY;
        rb->velocityX += rb->accelerationX;
        rb->velocityY += rb->accelerationY;

        float speed = rb->velocityX * dirX + rb->velocityY * dirY;

        rb->velocityX = speed * dirX;
        rb->velocityY = speed * dirY;
        transform->posX += rb->velocityX;
        transform->posY += rb->velocityY;

        std::cout << "Direction: (" << dirX << ", " << dirY << ")\n";
        std::cout << "Velocity: (" << rb->velocityX << ", " << rb->velocityY << ") - Magnitude: " << sqrt(rb->velocityX * rb->velocityX + rb->velocityY * rb->velocityY) << std::endl;

        //rb->angularAcceleration = rb->torque;
        //rb->angularVelocity += rb->angularAcceleration;
        transform->rotation += rb->angularVelocity;
      }
    }
};


#endif
