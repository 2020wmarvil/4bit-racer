#ifndef GAME_ENTITY
#define GAME_ENTITY

#include <vector>
#include <string>
#include <stdint.h>

#include "Components.hpp"

class Entity {
private:
  static uint16_t GLOBAL_ID_COUNTER;

  uint16_t id;

  std::vector<Component*> components;
public:
  Transform *transform;
  std::string name;

  Entity() {
    id = GLOBAL_ID_COUNTER++;
    transform = new Transform();
    name = "Entity_" + std::to_string(id);
  }

  Entity(std::string name) {
    id = GLOBAL_ID_COUNTER++;
    transform = new Transform();
    this->name = name;
  }

  void AddComponent(Component *component) {
    components.push_back(component);
  }

  int NumComponents() { return components.size(); }
  std::vector<Component*> GetComponents() { return components; }

  bool HasComponent(ComponentType type) {
    for(Component* i : components) {
      if(i->type==type) return true;
    }
    return false;
  }
  Component* GetComponent(ComponentType type) {
    if(type==TRANSFORM) return transform;
    for(Component* i : components) {
      if(i->type==type) return i;
    }
    return NULL;
  }
};
uint16_t Entity::GLOBAL_ID_COUNTER = 0;
#endif
