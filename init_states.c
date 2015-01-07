#include "init_states.h"

void init_game(Game_Data *data)
{
	data->level = NULL;
	data->level = malloc(sizeof(Level));
	if(data->level == NULL)
		return;

	data->level->id = 1;
	data->level->nb_patterns = 0;

	data->level->cam_change_interval = 5;
	data->level->cam_change_precision = 1;
	data->level->cam_change_probability = 0.75;
	data->level->cam_max_speed = 5;
	data->level->cam_min_speed = 1;
	data->level->fast_spin_probability = 0.1;

	data->level->lc_min_score = 20;
	data->level->lc_probability = 0.05;
	data->level->lc_duration = 15;


	data->list = NULL;
	data->start_time = RTC_GetTicks(); //1 tick == 1/128 second
	data->last_time = 0;
	data->current_time = RTC_GetTicks();
	data->chrono_time = 0;

	data->player_angle = 0;

	data->cam.cX = 64;
	data->cam.cY = 32;
	data->cam.angle = 0;
	data->cam.speed = 1.5;
	data->cam.zoom = 0.0;

	data->nb_lines = 6;
	data->line_transition.counter = 0;
	data->line_transition.counter_start = 0;
	data->line_transition.delta_nb_lines = 0;
}
void init_title(Game_Data *data)
{
	data->start_time = RTC_GetTicks(); //1 tick == 1/128 second
	data->last_time = 0;
	data->current_time = RTC_GetTicks();
	data->chrono_time = 0;

	data->cam.cX = 96;
	data->cam.cY = 32;
	data->cam.angle = 0;
	data->cam.speed = 1;
	data->cam.zoom = 24;

	data->nb_lines = 6;
	data->line_transition.counter = 0;
	data->line_transition.counter_start = 0;
	data->line_transition.delta_nb_lines = 0;

}
void init_menu(Game_Data *data)
{
	data->start_time = RTC_GetTicks(); //1 tick == 1/128 second
	data->last_time = 0;
	data->current_time = RTC_GetTicks();
	data->chrono_time = 0;

	data->cam.cX = 64;
	data->cam.cY = 64;
	data->cam.angle = 0;
	data->cam.speed = 0;
	data->cam.zoom = 48;

	data->nb_lines = 6;
	data->line_transition.counter = 0;
	data->line_transition.counter_start = 0;
	data->line_transition.delta_nb_lines = 0;
}
void init_game_over(Game_Data *data)
{

}
