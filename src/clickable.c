#include "clickable.h"

bool Clickable_CheckBounds(Clickable *c, int x, int y) {
  if(c->dimensions.x < x
   &&c->dimensions.x+c->dimensions.w > x
   &&c->dimensions.y < y
   &&c->dimensions.y+c->dimensions.h > y
    ) {
      return true;
    }
  else {
    return false;
  }
}

Clickable *heldClickable;
//Calls the clickables clickFunc iff the mouse is inside the clickable.
void Clicky_ClickClickable(void *c_, int x, int y) {
  Clickable *c = c_;
  if(Clickable_CheckBounds(c, x, y)) {
    heldClickable = c;
    if(c->clickFunc != NULL) { //Not necessarily true.
      c->clickFunc((void*)c, x, y);
    }
  }
}

//Calls the clickables releaseFunc iff the mouse is inside the clickable.
void Clicky_ReleaseClickable(void *c_, int x, int y) {
  Clickable *c = c_;
  if(Clickable_CheckBounds(c, x, y)) {
    heldClickable = c;
    if(c->releaseFunc != NULL) { //Not necessarily true.
      c->releaseFunc((void*)c, x, y);
    }
  }
}

//Calls the releasefunc of the held clickable, if it isn't NULL.
void Clicky_ReleaseHeldClickable(int x, int y) {
  if(heldClickable == NULL) {
    return; //Nothing to do.
  }
  //Only call the function if it exists.
  if(heldClickable->releaseFunc != NULL) {
    heldClickable->releaseFunc(heldClickable, x, y);
  }
  
  //Always clear this.
  heldClickable = NULL;
}

Dragable *currentDragged = NULL; //This gets dragged on.
SDL_Rect dragOffset; //When a dragable gets dragged, this is the local offset into the container to move.

void Clicky_DragUpdate(int x, int y) {
  if(currentDragged == NULL) {
    return; //Nothing to do here.
  }
  
  Dragable *d = currentDragged;
  
  d->coordinatesToDrag->x = x-dragOffset.x;
  d->coordinatesToDrag->y = y-dragOffset.y;
  
  //Check boundaries.
  if(d->boundaries != NULL) {
    //Left boundary.
    if(d->coordinatesToDrag->x < d->boundaries->x) {
      d->coordinatesToDrag->x = d->boundaries->x;
    }
    //Upper boundary.
    if(d->coordinatesToDrag->y < d->boundaries->y) {
      d->coordinatesToDrag->y = d->boundaries->y;
    }
    //Right boundary.
    if(d->coordinatesToDrag->x > d->boundaries->x + d->boundaries->w - d->coordinatesToDrag->w) {
      d->coordinatesToDrag->x = d->boundaries->x + d->boundaries->w - d->coordinatesToDrag->w;
    }
    //Lower boundary.
    if(d->coordinatesToDrag->y > d->boundaries->y + d->boundaries->h - d->coordinatesToDrag->h) {
      d->coordinatesToDrag->y = d->boundaries->y + d->boundaries->h - d->coordinatesToDrag->h;
    }
    
    //printf("New coords: %d, %d, %d, %d\n", d->coordinatesToDrag->x, d->coordinatesToDrag->y, d->coordinatesToDrag->x+d->coordinatesToDrag->w, d->coordinatesToDrag->y+d->coordinatesToDrag->h);
  }
}

//Sets the global variables for the dragging mechanism. They are used in the function Dragable_DragUpdate.
void Dragable_ClickFunc(void *dragable, int x, int y) {
  currentDragged = dragable;
  dragOffset.x = x - currentDragged->coordinatesToDrag->x;
  dragOffset.y = y - currentDragged->coordinatesToDrag->y;
}

//This function clears the global variables so nothing will be dragged.
//The args are ignored.
void Dragable_ReleaseFunc(void *dragable, int x, int y) {
  currentDragged = NULL;
  dragOffset.x = 0;
  dragOffset.y = 0;
}


