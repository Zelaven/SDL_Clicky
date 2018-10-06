#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "../src/SDL_Clicky.h"

void clickedSimpleContainer(void *c_, int x, int y) {
  SimpleContainer *c = c_;
  printf("Clicked inside of SimpleContainer at %p with size: %d x %d\n", c_, c->super.dimensions.w, c->super.dimensions.h);
}

void drawSimpleContainer(void *c_, SDL_Renderer* renderer) {
  SimpleContainer *c = c_;
  SDL_SetRenderDrawColor(renderer, 0x7F, 0x7F, 0, 0xFF);
  SDL_RenderFillRect(renderer, &(c->super.dimensions));
}

bool quit = false;
void clickFunc_QuitButton(void *c_, int x, int y) {
  quit = true;
}

int main() {
  
  if(SDL_Init(SDL_INIT_VIDEO) != 0) {
    fprintf(stderr, "Could not initialize SDL: %s\n", SDL_GetError());
    return 1;
  }
  printf("SDL Initialized\n");
  
  SDL_Window* screen;
  screen = SDL_CreateWindow("My Game Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
  if(!screen) {
    fprintf(stderr, "Could not set video mode: %s\n", SDL_GetError());
    return 1;
  }
  
  SDL_Renderer* renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_PRESENTVSYNC);
  if(!renderer) {
    SDL_DestroyWindow(screen);
    fprintf(stderr, "Could not create renderer: %s", SDL_GetError());
  }
  
  
  
  SimpleContainer sc;
  sc.super.dimensions.x = 0;
  sc.super.dimensions.y = 0;
  sc.super.dimensions.w = 100;
  sc.super.dimensions.h = 100;
  sc.super.isdown = false;
  sc.super.clickFunc = clickedSimpleContainer;
  sc.super.releaseFunc = NULL;
  sc.drawFunc = drawSimpleContainer;
  
  Clickable c2;
  c2.dimensions.x = 590;
  c2.dimensions.y = 0;
  c2.dimensions.w = 50;
  c2.dimensions.h = 50;
  c2.isdown = false;
  c2.clickFunc = clickFunc_QuitButton;
  c2.releaseFunc = NULL;
  
  SDL_Rect screenBounds;
  screenBounds.x = 100;
  screenBounds.y = 0;
  screenBounds.w = 440 - screenBounds.x;
  screenBounds.h = 280 - screenBounds.y;
  
  Dragable d;
   d.super.dimensions.x = 200;
  d.super.dimensions.y = 100;
  d.super.dimensions.w = 50;
  d.super.dimensions.h = 50;
  d.super.isdown = false;
  d.super.clickFunc = Dragable_ClickFunc;
  d.super.releaseFunc = Dragable_ReleaseFunc;
   d.boundaries = &screenBounds;
  d.coordinatesToDrag = &(d.super.dimensions); //Drag itself.
  
  SDL_Event e;
  while(!quit) {
    while(SDL_PollEvent(&e)) {
      switch(e.type) {
        case SDL_QUIT:
          quit = true;
          break;
        case SDL_MOUSEBUTTONDOWN:
          /*if(Clickable_CheckBounds(&c ,e.button.x, e.button.y) == true) {
            //printf("Clicked clickable at addr %p\n", &c);
            c.clickFunc((void*)&c, e.button.x, e.button.y);
          }
          if(Clickable_CheckBounds(&(d.super) ,e.button.x, e.button.y) == true) {
            //printf("Clicked clickable at addr %p\n", &c);
            d.super.clickFunc((void*)&(d.super), e.button.x, e.button.y);
          }*/
          
          Clicky_ClickClickable((void*)&sc, e.button.x, e.button.y);
          Clicky_ClickClickable((void*)&c2, e.button.x, e.button.y);
          Clicky_ClickClickable((void*)&d, e.button.x, e.button.y); //d has a Clickable as supertype.
          
          break;
        case SDL_MOUSEBUTTONUP:
          /*if(Clickable_CheckBounds(&c ,e.button.x, e.button.y) == true) {
            printf("Clicked clickable at addr %p\n", &c);
            c.clickFunc((void*)&c, e.button.x, e.button.y);
          }*/
          /*if(Clickable_CheckBounds(&(d.super) ,e.button.x, e.button.y) == true) {
            //printf("Released clickable at addr %p\n", &c);
            d.super.releaseFunc((void*)&(d.super), e.button.x, e.button.y);
          }*/
          
          //These shouldn't be necessary, but they're there.
          //Clicky_ReleaseClickable((void*)&c, e.button.x, e.button.y);
          //Clicky_ReleaseClickable((void*)&d, e.button.x, e.button.y); //d has a Clickable as supertype.
          
          Clicky_ReleaseHeldClickable(e.button.x, e.button.y);
          
          break;
        case SDL_MOUSEMOTION:
          Clicky_DragUpdate(e.motion.x, e.motion.y);
          break;
      }
    }
    
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  
  //SDL_SetRenderDrawColor(renderer, 0xFF, 0, 0, 0xFF);
  //SDL_RenderFillRect(renderer, &(c.dimensions));
  
  sc.drawFunc(&sc, renderer);
  
  SDL_SetRenderDrawColor(renderer, 0xFF, 0, 0, 0xFF);
  SDL_RenderFillRect(renderer, &(c2.dimensions));
  
  SDL_SetRenderDrawColor(renderer, 0x7F, 0, 0, 0xFF);
  SDL_RenderFillRect(renderer, &(screenBounds));
  
  SDL_SetRenderDrawColor(renderer, 0xFF, 0, 0, 0xFF);
  SDL_RenderFillRect(renderer, &(d.super.dimensions));
  
  SDL_RenderPresent(renderer);
  }
  
  SDL_Quit();
  
  printf("SDL Shutdown\n");
  
  return 0;
}


