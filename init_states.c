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

	data->player_angle = 0;

	data->cam.cX = 64;
	data->cam.cY = 32;
	data->cam.angle = 0;
	data->cam.speed = 0.0;

	data->nb_lines = 6;
	data->line_transition.counter = 0;
	data->line_transition.counter_start = 0;
	data->line_transition.delta_nb_lines = 0;
}
void init_title(Game_Data *data)
{


}


void load_difficulty_names(char **str_list)
{
	char c_1[] = "Hard";
	char c_2[] = "Harder";
	char c_3[] = "Hardest";
	char c_4[] = "Hardester";
	char c_5[] = "Hardestest";
	char c_6[] = "Hardestestest";

	for(int i = 0; i < 6; i++)
	{
		str_list[i] = NULL;
		str_list[i] = malloc(sizeof(char) * 24);
		if(str_list[i] == NULL)
			return;
		for(int j = 0; j < 24; str_list[i][j] = 0, j++);
	}
	memcpy(str_list[0], c_1, sizeof(char) * strlen(c_1));
	memcpy(str_list[1], c_2, sizeof(char) * strlen(c_2));
	memcpy(str_list[2], c_3, sizeof(char) * strlen(c_3));
	memcpy(str_list[3], c_4, sizeof(char) * strlen(c_4));
	memcpy(str_list[4], c_5, sizeof(char) * strlen(c_5));
	memcpy(str_list[5], c_6, sizeof(char) * strlen(c_6));
}
void init_menu(Game_Data *data)
{
	data->nb_entries = 6;
	data->current_entry = 1;
	data->current_entry_high_score = 0; //to load from a save file

	data->entry_difficulties = NULL;
	data->entry_difficulties = malloc(sizeof(char*) * 6);
	if(data->entry_difficulties == NULL)
		return;
	load_difficulty_names(data->entry_difficulties);
}
void init_game_over(Game_Data *data)
{

}
