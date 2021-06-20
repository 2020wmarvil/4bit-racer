#ifndef GAME_COMPONENTS
#define GAME_COMPONENTS

#include <SDL2/SDL.h>

#include <iostream>

enum ComponentType { TRANSFORM, RIGIDBODY, TEXTURE };

/* Parent class of all Components
 * Holds a type to refer to the subclass type
 * returns the component data, usually a type of struct
*/
class Component {
  public:
    ComponentType type;
    virtual void* GetData(); //returns the component data, usually a type of struct
};

class Transform : public Component { //Basic location data for every Entity
public:
  float posX, posY;
  float rotation;

  Transform() : posX(0), posY(0), rotation(0) {}

  friend std::ostream& operator<<(std::ostream& os, const Transform& trans) {
    os << "Transform - Pos: (" << trans.posX << ", " << trans.posY
       << "), Rot: " << trans.rotation << std::endl;
    return os;
  }
};

class Texture : public Component { // Basic rendering data
  public:
    struct TexData {
      SDL_Texture *tex; //Texture data
      SDL_Rect *rect; //The rectangle referring to the places in the texture to use
    };
    struct TexData data;

    Texture() {
      type=TEXTURE;
      data.tex=nullptr;
      data.rect=nullptr;
    }
    Texture(SDL_Texture *texture, SDL_Rect *rectangle) {
      type=TEXTURE;
      data.tex=texture;
      data.rect=rectangle;
    }
    void SetData(SDL_Texture *texture, SDL_Rect *rectangle) {
      data.tex=texture;
      data.rect=rectangle;
    }
    void* GetData() {return (void*)&data;}
};
#endif
