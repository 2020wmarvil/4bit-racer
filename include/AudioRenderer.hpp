#ifndef GAME_AUDIORENDERER
#define GAME_AUDIORENDERER

#include <vector>
#include <SDL2/SDL.h>

#include "Entity.hpp"
#include "Components.hpp"
#include "Utilities.hpp"

class AudioRenderer {
  private:
    std::vector<Entity*> entities;
  public:
    AudioRenderer() { }

    void AddEntity(Entity *entity) {
      entities.push_back(entity);
    }

    void Render() {
     for(Entity* a : entities) {
       //struct Audio::AudioData* data=(struct Audio::AudioData*)a->GetComponent(AUDIO)->GetData();
       struct Transform::TransformData* transform=(struct Transform::TransformData*)a->GetComponent(TRANSFORM)->GetData();
     }
    }
};

#endif
