#include "init_states.h"

void init_game(Game_Data *data)
{
	data->level = NULL;
	data->list = NULL;
	data->start_time = RTC_GetTicks(); //1 tick == 1/128 second
	data->last_time = 0;
	data->current_time = RTC_GetTicks();

	data->player_angle = 0;

	data->cam.cX = 64;
	data->cam.cY = 32;
	data->cam.angle = 0;
	data->cam.speed = 0.0;
}
void init_title(Game_Data *data)
{


}
void init_menu(Game_Data *data)
{

}
void init_game_over(Game_Data *data)
{

}