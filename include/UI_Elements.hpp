#ifndef GAME_UI_ELEMENTS
#define GAME_UI_ELEMENTS

#include <string>
#include <functional>
#include <SDL2/SDL.h>

enum UI_ElementType { TEXT, BUTTON, IMAGE };

/* Parent class of all UI_Elements
 * Holds a type to refer to the subclass type
 * returns the ui element data, usually a type of struct
*/
class UI_Element {
  public:
    UI_ElementType type;
    SDL_Rect *rect; // holds position and size data for ui elements
    int layer = 0;      // the sorting layer for rendering, higher number means rendered on top
    bool visible = true;   // sets whether or not to render the element
    float scale;

    virtual void* GetData() {return nullptr;} //returns the component data, usually a type of struct
};

class Text : public UI_Element { // holds text
  public:
    struct TextData {
      std::string text;
      /* font, fontSize */
    };
    struct TextData data;

    Text(SDL_Rect *rectangle) {
      type=TEXT;
      rect = rectangle;
    }
    void* GetData() {return (void*)&data;}
};

class Button : public UI_Element { // interactable button
  public:
    struct ButtonData {
      std::function<void()> OnMouseDown;
      std::function<void()> OnMouseUp;
      std::function<void()> OnMouseEnter;
      std::function<void()> OnMouseExit;

      bool interactable;
      bool hovered;
    };
    struct ButtonData data;

    Button(SDL_Rect *rectangle) {
      type=BUTTON;
      rect = rectangle;
      data.OnMouseDown = nullptr;
      data.OnMouseUp = nullptr;
      data.OnMouseEnter = nullptr;
      data.OnMouseExit = nullptr;
      data.interactable = true;
      data.hovered = false;
    }

    void SetOnMouseDown(std::function<void()> func) { data.OnMouseDown = func; }
    void SetOnMouseUp(std::function<void()> func) { data.OnMouseUp = func; }
    void SetOnMouseEnter(std::function<void()> func) { data.OnMouseEnter = func; }
    void SetOnMouseExit(std::function<void()> func) { data.OnMouseExit = func; }
    void SetInteractable(bool enabled) { data.interactable = enabled; }

    void* GetData() {return (void*)&data;}
};

class Image : public UI_Element { // holds a texture
  public:
    struct ImageData {
      SDL_Texture *tex; //Texture data
    };
    struct ImageData data;

    Image(SDL_Rect *rectangle) {
      type=IMAGE;
      rect = rectangle;
      data.tex=nullptr;
    }
    Image(SDL_Texture *texture, SDL_Rect *rectangle) {
      type=IMAGE;
      data.tex=texture;
      rect = rectangle;
    }
    void SetTexture(SDL_Texture *texture, SDL_Rect *rectangle) {
      data.tex=texture;
      rect=rectangle;
    }
    void* GetData() {return (void*)&data;}
};

#endif
