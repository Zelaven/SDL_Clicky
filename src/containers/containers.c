
#include "containers.h"

Scrollbar_Container* Scrollbar_Container_Constructor(int x, int y, int width, int height, int blockheight) {
  Scrollbar_Container* sb = malloc(sizeof(Scrollbar_Container));
  sb->super.dimensions.x = x;
  sb->super.dimensions.y = y;
  sb->super.dimensions.w = width;
  sb->super.dimensions.h = height;
  sb->super.isdown = false;
  sb->super.clickFunc = NULL;
  sb->super.releaseFunc = NULL;
  sb->super.drawFunc = NULL;

  sb->bar.super.dimensions.x = x;
  sb->bar.super.dimensions.y = y;
  sb->bar.super.dimensions.w = width;
  sb->bar.super.dimensions.h = blockheight;
  sb->bar.super.isdown = false;
  sb->bar.super.clickFunc = Dragable_ClickFunc;
  sb->bar.super.releaseFunc = Dragable_ReleaseFunc;
  sb->bar.super.drawFunc = NULL;
  sb->bar.boundaries = &(sb->super.dimensions);
  sb->bar.coordinatesToDrag = &(sb->bar.super.dimensions);

  return sb;
}

