
#ifndef SDL_CLICKY_CLICKABLE_H_
#define SDL_CLICKY_CLICKABLE_H_

#include <SDL.h>
#include <stdbool.h>

typedef struct {
  SDL_Rect dimensions;
  bool isdown; //When clicked and held.
  void (*clickFunc)(void*, int, int); //The function to call when the clickable is registered as clicked. The arg should be set to be a pointer to the clicked clickable. Makes sense when the clickable is the first member (not as pointer) of an "inheriting" type.
  void (*releaseFunc)(void*, int, int); //Same as above for when the button is released.
} Clickable;

typedef struct {
  Clickable super;
  SDL_Rect *boundaries; //Don't go outside these bounds. May be NULL.
  SDL_Rect *coordinatesToDrag; //The dragable may be inside a container to be moved around.
} Dragable;

bool Clickable_CheckBounds(Clickable *c, int x, int y);
void Clicky_ClickClickable(void *c_, int x, int y);
void Clicky_ReleaseClickable(void *c_, int x, int y);
void Clicky_ReleaseHeldClickable(int x, int y);

void Clicky_DragUpdate(int x, int y); //Updates the dragging.

void Dragable_ClickFunc(void *dragable, int x, int y);
void Dragable_ReleaseFunc(void *dragable, int x, int y);

#endif // SDL_CLICKY_CLICKABLE_H_

