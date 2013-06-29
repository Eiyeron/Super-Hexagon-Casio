#ifndef WALL_H
#define WALL_H

#include "stdlib.h"
#include "struct.h"
#include "MonochromeLib.h"
#include "math.h"
Wall *addWall(Wall *list, int d, int h, int id, int line);//returns a new pointer to the first element
Wall *removeWall(Wall *list, int id); //returns a new pointer to the first element
void show(Wall *list, Camera *cam);
void update(Wall *list);
bool isColliding(Wall *list, int player_angle);
#endif