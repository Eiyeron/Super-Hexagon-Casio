#ifndef WALL_H
#define WALL_H

#include "struct.h"
#include "MonochromeLib.h"
#include "math.h"
// adds a wall to the linked list specified in the parameter "list"
Wall *addWall(Wall *list, int d, int h, int id, int line);// returns a new pointer to the first element
// removes every wall from "list" whose d member is smaller than the "d" passed as argument
Wall *removeWall(Wall *list, int d); // returns a new pointer to the first element

// show the ll "list"
void drawWalls(Wall *list, Game_Data *data, int nb_lines, Line_Transition line_transition);
// updates the ll "list"
void updateWalls(Wall *list, unsigned int delta_time);
// simple collision test. Returns true if a Wall from the list collides with the player
bool isColliding(Wall *list, int player_angle, int nb_lines);
#endif
