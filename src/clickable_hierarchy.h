//This is the central structure that is supposed to make this library be useful.
//It is essentially a rose-tree structure that is traversed in a depth-first-esque manner.
//When rendering, the tree is traversed in "left to right" fashion, rendering everything things as it goes.
//When clicking, the tree is traversed in "right to left" fashion and stops at the first eligible object.

//Possible todo: add usage of nifty means to figure out at runtime when updates are made to structure, 
// which objects don't need to be rendered at all and keep track of that by managing the tree structure more closely.
//That might require some trickery, depending on how the management of this structure pans out.

#ifndef SDL_CLICKY_CLICKABLE_HIERARCHY_H_
#define SDL_CLICKY_CLICKABLE_HIERARCHY_H_

#include "clickable.h"

struct Clickable_Hierarchy_Element;

//Simply a list of subtress that may be leaves.
typedef struct {
  int num_children;
  int num_children_slots;
  struct Clickable_Hierarchy_Element* children;
} Clickable_Hierarchy;

//This one requires explanation.
//The clickable should be self-explanatory, this is the clickable that this element represents.
//The subtree, though, determines if this is a leaf (NULL) or not (!NULL). If !NULL, then the clickable is a container object.
//How to use this, from a clickable and container perspective?
// Clickable: Just add it and the subtree will be NULL.
// Container: If your container only renders itself then it should add all of its subelements to the tree.
//  If it recursively renders all of its own subelements, then it should not add those to the tree because the tree would render them too.
//  That means, if you handle the rendering of subelements, just pretend to only be a clickable.
//  If you have a mix for some reason, register as a container but only add the subelements you don't handle yourself.
typedef struct Clickable_Hierarchy_Element {
  Clickable* clickable;
  Clickable_Hierarchy* subtree;
} Clickable_Hierarchy_Element;

void Clicky_Clickable_Hierarchy_Render(Clickable_Hierarchy* ch, SDL_Renderer* r);
bool Clicky_Clickable_Hierarchy_Click(Clickable_Hierarchy* ch, int x, int y);

int Clicky_Clickable_Hierarchy_Add_Clickable(Clickable_Hierarchy* ch, Clickable* cl);
Clickable_Hierarchy* Clicky_Clickable_Hierarchy_Add_Subtree(Clickable_Hierarchy* ch, Clickable* cl, int numchildren);

#endif // SDL_CLICKY_CLICKABLE_HIERARCHY_H_

