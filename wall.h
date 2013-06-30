#ifndef WALL_H
#define WALL_H

#include "stdlib.h"
#include "struct.h"
#include "MonochromeLib.h"
#include "math.h"
//adds a wall to the linked list specified in the parameter "list"
Wall *addWall(Wall *list, int d, int h, int id, int line);//returns a new pointer to the first element
//removes every wall from "list" whose d member is smaller than the "d" passed as argument
Wall *removeWall(Wall *list, int d); //returns a new pointer to the first element

//show the ll "list"
void show(Wall *list, Camera *cam);
//updates the ll "list"
void update(Wall *list);
//simple collision test. Returns true if a Wall from the list collides with the player
bool isColliding(Wall *list, int player_angle);
#endif
