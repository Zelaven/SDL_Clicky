#include <stdbool.h>
#include "clickable_hierarchy.h"

void Clicky_Clickable_Hierarchy_Render(Clickable_Hierarchy* ch, SDL_Renderer* r) {
  for(int i = 0; i < ch->num_children; i++) {
    Clickable_Hierarchy_Element* elem = (ch->children)+i;
    
    //Render the clickable.
    if(elem->clickable->drawFunc != NULL) {
      elem->clickable->drawFunc(elem->clickable, r);
    }
    if(elem->subtree != NULL) {
      Clicky_Clickable_Hierarchy_Render(elem->subtree, r);
    }
  }
}

//True if a clickable was activated, false otherwise.
bool Clicky_Clickable_Hierarchy_Click(Clickable_Hierarchy* ch, int x, int y) {
  //printf("Call_ Click_Clickable_Hierarchy_Click\n  Params: %p, %d, %d\n", ch, x, y);
  //printf("  #children: %d, #children slots: %d, children: %p\n", ch->num_children, ch->num_children_slots, ch->children);
  
  bool retval = false;
  
  for(int i = 0; i < ch->num_children; i++) {
    Clickable_Hierarchy_Element* elem = (ch->children)+i;
    
    if(elem->subtree != NULL) { //If it is a container, first attempt its children.
      bool innerclick = Clicky_Clickable_Hierarchy_Click(elem->subtree, x, y);
      if(!innerclick) { //Didn't hit anything inside the clickable, propagate to the clickable itself.
        retval = Clicky_ClickClickable((void*)(elem->clickable), x, y);
        if(retval) {break;}
      }
    } else {
      retval = Clicky_ClickClickable((void*)(elem->clickable), x, y);
      if(retval) {break;}
    }
  }
  
  return retval;
}

int Clicky_Clickable_Hierarchy_Add_Clickable(Clickable_Hierarchy* ch, Clickable* cl) {
  //printf("Hierarchy: %p, Clickable: %p\n", ch, cl);
  
  //printf("  #children: %d, #children slots: %d, children: %p\n", ch->num_children, ch->num_children_slots, ch->children);
  if(ch->num_children >= ch->num_children_slots) {
    return 1;
  }
  
  //printf("%p, %p\n", ch->children, ch->children+1);
  
  Clickable_Hierarchy_Element *elem = (ch->children+ch->num_children);
  //printf("Element pointer: %p\n", elem);
  elem->clickable = cl;
  elem->subtree = NULL;
  
  ch->num_children++;
  
  return 0;
}
Clickable_Hierarchy* Clicky_Clickable_Hierarchy_Add_Subtree(Clickable_Hierarchy* ch, Clickable* cl, int num_children) {
  if(ch->num_children >= ch->num_children_slots) {
    return NULL;
  }
  
  Clickable_Hierarchy_Element *elem = (ch->children+ch->num_children);
  //printf("Element pointer: %p\n", elem);
  elem->clickable = cl;
  Clickable_Hierarchy* sh = (Clickable_Hierarchy*) malloc(sizeof(Clickable_Hierarchy));
  sh->num_children = 0;
  sh->num_children_slots = num_children;
  sh->children = (Clickable_Hierarchy_Element*) malloc(sizeof(Clickable_Hierarchy_Element)*num_children);
  elem->subtree = sh;
  
  ch->num_children++;
  
  return sh;
}





