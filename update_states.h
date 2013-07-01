#ifndef UPDATE_STATES_H
#define UPDATE_STATES_H
#include "fxlib.h"
#include "ECode.h"
#include "struct.h"
#include "wall.h"

void update_game(Game_Data *data);
void update_title(Game_Data *data);
void update_menu(Game_Data *data);
void update_game_over(Game_Data *data);
void updateCamera(Camera *cam, unsigned int delta_time);

#endif