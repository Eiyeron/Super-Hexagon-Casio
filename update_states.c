#include "update_states.h"
#include "pattern.h"
#include "fixed.h"

void update_title(Game_Data *data)
{
	data->last_time = data->current_time;
	data->current_time = RTC_GetTicks();
	data->chrono_time += (data->current_time - data->last_time)/ 128.;

	if(KeyDown(K_SHIFT) && data->shift_latch_value == 0) {
		switch_to_state(MENU, data);
	}

	updateCamera(&(data->cam), data->current_time - data->last_time);

}

#define min(a, b) ((a) < (b) ? (a) : (b))

void update_game(Game_Data *data)
{
	data->last_time = data->current_time;
	data->current_time = RTC_GetTicks();
	data->chrono_time += (data->current_time - data->last_time)/ 128.;
	if(data->chrono_time >= 60) {
		data->are_colors_reversed = 1;
	}

	if(data->list != NULL) {
	//if the linked list is not empty
		updateWalls(data->list, min(data->current_time - data->last_time, 2));
		//update the linked list

		//if the player and a wall collide
		if(isColliding(data->list, data->player_angle, data->nb_lines) == true) {
			//death handling
		}
	//remove every wall whose distance to the center equals zero
		data->list = removeWall(data->list, 8);
	}
	//level generation
	if(!data->cooldown_timer--) {
		Pattern pattern = data->level->patterns[rand()% data->level->nb_patterns];
		addPattern(data, &pattern, rand()%data->nb_lines, rand()&1);
		data->cooldown_timer = pattern.cooldown;
	}

	// TODO : stop at wall side.
	if(KeyDown(K_LEFT)){
		data->player_angle-=data->level->player_rotation_speed *  (data->current_time - data->last_time)*FRAME_TIME;
	}
	if(KeyDown(K_RIGHT)){
		data->player_angle+=data->level->player_rotation_speed *  (data->current_time - data->last_time)*FRAME_TIME;
	}

	if(KeyDown(K_ALPHA) && data->alpha_latch_value == 0) {
		switch_to_state(MENU, data);
	}


	if(KeyDown(K_PLUS) && data->line_transition.counter == 0)
	{
		data->line_transition.counter = 10;
		data->line_transition.counter_start = 10;
		data->line_transition.delta_nb_lines = 1;
	}else if(KeyDown(K_MINUS) && data->line_transition.counter == 0){
		data->line_transition.counter = 10;
		data->line_transition.counter_start = 10;
		data->line_transition.delta_nb_lines = -1;
	}
	if(data->line_transition.counter != 0){
		data->line_transition.counter --;
		if(data->line_transition.counter <= 0){
			data->nb_lines += data->line_transition.delta_nb_lines;
			data->line_transition.counter_start = 0;
			data->line_transition.delta_nb_lines = 0;
		}
	}


	data->player_angle = MOD(data->player_angle, 360);

	updateCamera(&(data->cam), data->current_time - data->last_time);
}

void update_menu(Game_Data *data)
{
	data->last_time = data->current_time;
	data->current_time = RTC_GetTicks();
	data->chrono_time += (data->current_time - data->last_time)/ 128.;

	if(KeyDown(K_SHIFT) && data->shift_latch_value == 0) {
		switch_to_state(GAME, data);
	}
	if(KeyDown(K_ALPHA) && data->alpha_latch_value == 0) {
		switch_to_state(TITLE, data);
	}


	updateCamera(&(data->cam), data->current_time - data->last_time);
}
void update_game_over(Game_Data *data)
{
//TODO
}

void updateCamera(Camera *cam, unsigned int delta_time){
	cam->angle += cam->speed * delta_time / 2.;

	if(cam->angle >= 360)
		cam->angle = cam->angle % 360;

}
