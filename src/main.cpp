#include <iostream>

#include <SDL2/SDL.h>

#define SCREEN_SIZE 480

#include "../include/Utilities.hpp"
#include "../include/Entity.hpp"
#include "../include/Components.hpp"
#include "../include/EventHandler.hpp"
#include "../include/World.hpp"
#include "../include/Physics.hpp"
#include "../include/Renderer.hpp"
#include "../include/UI_Elements.hpp"

const int SCREEN_FPS = 30;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    Uint32 rmask = 0xff000000;
    Uint32 gmask = 0x00ff0000;
    Uint32 bmask = 0x0000ff00;
    Uint32 amask = 0x000000ff;
#else
    Uint32 rmask = 0x000000ff;
    Uint32 gmask = 0x0000ff00;
    Uint32 bmask = 0x00ff0000;
    Uint32 amask = 0xff000000;
#endif

void titlescreen(SDL_Renderer *ren);
void game(SDL_Renderer *ren);

const char cartemplate[][4]={
                      {1,2,2,1},
                      {2,2,2,2},
                      {0,0,0,0},
                      {0,2,2,0},
                      {2,2,2,2},
                      {0,0,0,0},
                      {2,2,2,2},
                      {2,2,2,2}
                    };

struct Params *params = new struct Params;

int main(/*int argc, char** argv*/) {
  Uint32 windowFlags = 0;

  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window *win = SDL_CreateWindow("4Bit Racer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_SIZE, SCREEN_SIZE, windowFlags);
  SDL_Renderer *ren = SDL_GetRenderer(win);
	if(!ren) ren = SDL_CreateRenderer(win, -1, 0);

  titlescreen(ren);

  SDL_Quit();
  return 0;
}

void game(SDL_Renderer *ren) {
  EventHandler *inputHandler = new EventHandler() ;
  World *world = new World();
  PhysicsSim *sim = new PhysicsSim();
  Renderer *renderer = new Renderer(ren);

  // begin entity creation
  Entity *car = new Entity("PlayerCar");
  Texture *carTexture = new Texture(
    SDL_CreateTextureFromSurface(ren, SDL_LoadBMP("../assets/Car.bmp")),
    createRect(316, 232, 8, 16)
  );
  carTexture->SetLayer(1);
  carTexture->SetScale(2.5);
  car->AddComponent(carTexture);
  renderer->AddEntity(car);
  Rigidbody *carRB = new Rigidbody();
  car->AddComponent(carRB);
  world->AddEntity(car);
  sim->AddEntity(car);

  car->transform->data.rotation = 45;

  Entity *map = new Entity();
  Texture *mapTexture = new Texture(
    SDL_CreateTextureFromSurface(ren, SDL_LoadBMP("../assets/map.bmp")),
    createRect(0, 0, SCREEN_SIZE, SCREEN_SIZE)
  );
  mapTexture->SetScale(30);
  map->AddComponent(mapTexture);
  renderer->AddEntity(map);
  // end entity creation

  int previousTicks = SDL_GetTicks();

  while(true) {
    if (!inputHandler->PollInput(params)) return;
    if (!world->Update(params))return;
    sim->Update(params);
    renderer->Render();

    // limit framerate
    int frameTicks = SDL_GetTicks() - previousTicks;
    if(frameTicks < SCREEN_TICKS_PER_FRAME) SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
    previousTicks = SDL_GetTicks();
    std::cout<< *(Transform*)((*car).GetComponent(TRANSFORM)) <<std::endl;
  }
}
void titlescreen(SDL_Renderer *ren) {
  EventHandler *inputHandler = new EventHandler() ;
  World *world = new World();
  Renderer *renderer = new Renderer(ren);

  // begin element creation
  SDL_Rect button;button.x=220;button.y=230;button.w=40;button.h=20;
  Button start(&button);
  std::function<void()> call=[ren](){ game(ren);};
  std::function<void()> enter=[](){ std::cout << "on enter" << std::endl; };
  std::function<void()> exit=[](){ std::cout << "on exit" << std::endl; };
  std::function<void()> release=[](){ std::cout << "on release" << std::endl; };
  start.SetOnMouseDown(call);
  start.SetOnMouseEnter(enter);
  start.SetOnMouseExit(exit);
  start.SetOnMouseUp(release);
  world->AddButton(&start);
  // end element creation

  // begin entity creation
  Entity *ui = new Entity("TitlescreenCanvas");
  Canvas *canvas = new Canvas();
  canvas->AddElement(&start);
  ui->AddComponent(canvas);
  renderer->AddCanvas(canvas);
  // end entity creation

  int previousTicks = SDL_GetTicks();

  while(true) {
    if (!inputHandler->PollInput(params)) return;
    world->Update(params);
    renderer->Render();

    // limit framerate
    int frameTicks = SDL_GetTicks() - previousTicks;
    if(frameTicks < SCREEN_TICKS_PER_FRAME) SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
    previousTicks = SDL_GetTicks();
  }

  delete(params);
  delete(inputHandler);
  delete(world);
  delete(renderer);

  game(ren);
}
