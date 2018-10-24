#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "../src/SDL_Clicky.h"

void clickedClickable(void *c_, int x, int y) {
  Clickable *c = c_;
  printf("Size of clicked clickable at %p: %d x %d\n", c_, c->dimensions.w, c->dimensions.h);
}

void clickable_draw_red(void* c_, SDL_Renderer* r) {
  Clickable *c = c_;
  SDL_SetRenderDrawColor(r, 0xFF, 0, 0, 0xFF);
  SDL_RenderFillRect(r, &(c->dimensions));
}

void clickable_draw_darkred(void* c_, SDL_Renderer* r) {
  Clickable *c = c_;
  SDL_SetRenderDrawColor(r, 0x99, 0, 0, 0xFF);
  SDL_RenderFillRect(r, &(c->dimensions));
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
  
  Clickable_Hierarchy hierarchy = {
  .num_children = 0,
  .num_children_slots = 4,
  .children = malloc(sizeof(Clickable_Hierarchy_Element)*4),
  };
  
  Clickable c;
  c.dimensions.x = 0;
  c.dimensions.y = 0;
  c.dimensions.w = 100;
  c.dimensions.h = 100;
  c.isdown = false;
  c.clickFunc = clickedClickable;
  c.releaseFunc = NULL;
  c.drawFunc = clickable_draw_red;
  Clicky_Clickable_Hierarchy_Add_Clickable(&hierarchy, &c); 
  
  Clickable c2;
  c2.dimensions.x = 590;
  c2.dimensions.y = 0;
  c2.dimensions.w = 50;
  c2.dimensions.h = 50;
  c2.isdown = false;
  c2.clickFunc = clickFunc_QuitButton;
  c2.releaseFunc = NULL;
  c2.drawFunc = clickable_draw_red;
  Clicky_Clickable_Hierarchy_Add_Clickable(&hierarchy, &c2); 
  
  SDL_Rect screenBounds;
  screenBounds.x = 100;
  screenBounds.y = 0;
  screenBounds.w = 340;
  screenBounds.h = 300;
  
  Dragable d;
   d.super.dimensions.x = 200;
  d.super.dimensions.y = 100;
  d.super.dimensions.w = 50;
  d.super.dimensions.h = 50;
  d.super.isdown = false;
  d.super.clickFunc = Dragable_ClickFunc;
  d.super.releaseFunc = Dragable_ReleaseFunc;
  d.super.drawFunc = clickable_draw_red;
   d.boundaries = &screenBounds;
  d.coordinatesToDrag = &(d.super.dimensions); //Drag itself.
  Clicky_Clickable_Hierarchy_Add_Clickable(&hierarchy, &(d.super)); 
  
  //Container thing testing!
  Scrollbar_Container* scrollbar = Scrollbar_Container_Constructor(25, 150, 50, 100, 20);
  scrollbar->super.drawFunc = clickable_draw_darkred;
  scrollbar->bar.super.drawFunc = clickable_draw_red;
  //Clicky_Clickable_Hierarchy_Add_Clickable(&hierarchy, &(scrollbar->bar.super)); 
  Clickable_Hierarchy *sh = Clicky_Clickable_Hierarchy_Add_Subtree(&hierarchy, &(scrollbar->super), 1);
  Clicky_Clickable_Hierarchy_Add_Clickable(sh, &(scrollbar->bar.super));
  
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
          
          //Clicky_ClickClickable((void*)&c, e.button.x, e.button.y);
          //Clicky_ClickClickable((void*)&c2, e.button.x, e.button.y);
          //Clicky_ClickClickable((void*)&d, e.button.x, e.button.y); //d has a Clickable as supertype.
          
          Clicky_Clickable_Hierarchy_Click(&hierarchy, e.button.x, e.button.y);
          
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
  
  //Instead of doing this, the dragable should be put into a container, which should be drawn using the hierarchy.
  // The way it is now, the rendering of the things in the hierarchy will all be laid on top, even if they should logically be drawn below.
  SDL_SetRenderDrawColor(renderer, 0x7F, 0, 0, 0xFF);
  SDL_RenderFillRect(renderer, &(screenBounds));
  
  Clicky_Clickable_Hierarchy_Render(&hierarchy, renderer);
  
  SDL_RenderPresent(renderer);
  
  SDL_Delay(50);
  }
  
  SDL_Quit();
  
  printf("SDL Shutdown\n");
  
  return 0;
}


