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
    virtual void* GetData() {} //returns the component data, usually a type of struct
};

class Transform : public Component { //Basic location data for every Entity
public:
  struct TransformData {
    float posX, posY;
    float rotation;
  };
  struct TransformData data;

  Transform() {
    data.posX = 0;
    data.posY = 0;
    data.rotation = 0;
  }

  void* GetData() {return (void*)&data;}

  friend std::ostream& operator<<(std::ostream& os, const Transform& trans) {
    os << "Transform - Pos: (" << trans.data.posX << ", " << trans.data.posY
       << "), Rot: " << trans.data.rotation << std::endl;
    return os;
  }
};

class Texture : public Component { // Basic rendering data
  public:
    struct TexData {
      SDL_Texture *tex; //Texture data
      SDL_Rect *rect; //The rectangle referring to the places in the texture to use
      int layer; // the sorting layer for rendering, higher number means rendered on top
      bool visible; //Don't want random unused stuff visible
      double scale;
    };
    struct TexData data;

    Texture() {
      type=TEXTURE;
      data.tex=nullptr;
      data.rect=nullptr;
      data.layer=0;
      data.visible=true;
    }
    Texture(SDL_Texture *texture, SDL_Rect *rectangle) {
      type=TEXTURE;
      data.tex=texture;
      data.rect=rectangle;
      data.layer=0;
      data.visible=true;
    }
    void SetTexture(SDL_Texture *texture, SDL_Rect *rectangle) {
      data.tex=texture;
      data.rect=rectangle;
    }
    void SetLayer(int layer) {
      data.layer = layer;
    }
    void SetVisible(bool visible) {
      data.visible = visible;
    }
    void SetScale(double scale) {data.scale=scale;}
    void* GetData() {return (void*)&data;}
};

class Rigidbody : public Component { // Basic physics data
  public:
    struct RigidbodyData {

    };
    struct RigidbodyData data;

    Rigidbody() {
      type=RIGIDBODY;
    }

    Rigidbody(SDL_Texture *texture, SDL_Rect *rectangle) {
      type=RIGIDBODY;
    }
    void* GetData() {return (void*)&data;}
};
#endif