
#ifndef SDL_CLICKY_CONTAINERS_H_
#define SDL_CLICKY_CONTAINERS_H_

#include <SDL.h>
#include "../clickable.h"

//This idea has been scrapped. Function argument polymorphism isn't the answer to this problem.
/*
typedef struct ClickyContainerFunctionTable;

typedef struct {
  void *container;
  struct functions;
} ClickyContainer;
*/

//Inheritance is king. Inherit from Clickable and go nuts.
//Dragable containers are a bit of a problem, but not too badly. Having a container be a dragable isn't something I can think of a use for right now, and even then it should be possible to deal with by simply having a dragable inside the container.

//Simple container. It's a clickable that can be drawn.
// The drawing can be one in any way the user wants to, which means that it is sufficient for things like simple button and such. In fact, it's sufficient for a lot of things. Other container types simply provide functionality for the sake of not having to implement it yourself.
// Another thing with this container is that each variant of drawing requires another drawing function, as the drawing function doesn't take any additional arguments.
// In theory, adding a single void* to this container could act as an extension by composition, where the pointer could point to any data that could ever be desired. Perhaps this fact should be given more consideration, though it would have to be handled very well to not be a hassle to use for the user.
typedef struct {
  Clickable super;
} SimpleContainer;
// ^ Might not even have any use. It will stick around for now.


//A container for a scroll bar. It should have related functions but at the time of writing, it is simply used for testing the clickable hierarchy structure.
typedef struct {
  Clickable super;
  Dragable bar;
} Scrollbar_Container;
Scrollbar_Container* Scrollbar_Container_Constructor(int x, int y, int width, int height, int blockheight);

//Add more container types here.

#endif // SDL_CLICKY_CONTAINERS_H_






