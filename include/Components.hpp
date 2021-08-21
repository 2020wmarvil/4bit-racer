#ifndef GAME_COMPONENTS
#define GAME_COMPONENTS

#include <SDL2/SDL.h>

#include <iostream>

enum ComponentType { TRANSFORM, RIGIDBODY, TEXTURE, CAMERA, AUDIO };

/* Parent class of all Components
 * Holds a type to refer to the subclass type
 * returns the component data, usually a type of struct
*/
class Component {
  public:
    ComponentType type;
    virtual void* GetData() {return nullptr;} //returns the component data, usually a type of struct
};

class Transform : public Component { //Basic location data for every Entity
public:
  struct TransformData {
    float posX, posY;
    float rotation; //degrees
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
      float velocityX;
      float velocityY;
      float accelerationX;
      float accelerationY;
      float force;

      float angularVelocity;
      float angularAcceleration;
      float torque;

      float horsePower;

      float drag;
      float angularDrag;
      float mass;
    };
    struct RigidbodyData data;

    Rigidbody() {
      type=RIGIDBODY;
      data.velocityX=0;
      data.velocityY=0;
      data.accelerationX=0;
      data.accelerationY=0;
      data.force=0;
      data.angularVelocity=0;
      data.angularAcceleration=0;
      data.torque=0;
      data.horsePower=0;
      data.drag=0;
      data.angularDrag=0;
      data.mass=1;
    }

    Rigidbody(SDL_Texture *texture, SDL_Rect *rectangle) {
      type=RIGIDBODY;
      data.velocityX=0;
      data.velocityY=0;
      data.accelerationX=0;
      data.accelerationY=0;
      data.force=0;
      data.angularVelocity=0;
      data.angularAcceleration=0;
      data.torque=0;
      data.horsePower=0;
      data.drag=0;
      data.angularDrag=0;
      data.mass=1;
    }
    void* GetData() {return (void*)&data;}
};

class Camera : public Component { // Camera component
  public:
    struct CameraData {
      void *followTarget; //Entity to follow, Renderer will copy transform data from this entity to the camera's transform
      // viewport width and height + x and y defined in percentage of SCREEN_WIDTH and SCREEN_HEIGHT
      float viewportWidth;
      float viewportHeight;
      float viewportX;
      float viewportY;
      // lens width and height defined in world units
      float lensWidth;
      float lensHeight;
    };
    struct CameraData data;

    Camera() {
      type=CAMERA;
      data.followTarget=nullptr;
      data.viewportWidth=1;
      data.viewportHeight=1;
      data.viewportX=0;
      data.viewportY=0;
      data.lensWidth=200;
      data.lensHeight=200;
    }
    void* GetData() {return (void*)&data;}
};
/*
class Audio : public Component { // Audio source component
  public:
    struct AudioData {
      Channel *channel; // holds frequency and waveform data
      bool spatial; //whether or not the audio decays over distance
      DecayCharacteristics *decay;
    };
    struct AudioData data;

    Audio() {
      type=AUDIO;
    }
    void* GetData() {return (void*)&data;}
};
*/
#endif
