#ifndef DRAW_STATES_H
#define DRAW_STATES_H
#include "math.h"
#include "struct.h"
#include "MonochromeLib.h"

void draw_game(Game_Data *data);
void draw_title(Game_Data *data);
void draw_menu(Game_Data *data);
void draw_game_over(Game_Data *data);

void drawPlayer(Camera *cam, int player_angle, int nb_lines, Line_Transition line_transition);
void drawDiagonals(Camera cam, int nb_lines, Line_Transition line_transition);
#endif
