#ifndef STATES_H
#define STATES_H

#include "update_states.h"
#include "init_states.h"
#include "draw_states.h"
#include "struct.h"

void switch_to_state(State new_state, Game_Data *data);
void update(Game_Data *data);
void draw(Game_Data *data);

#endif