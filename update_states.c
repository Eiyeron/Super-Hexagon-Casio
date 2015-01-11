#include "update_states.h"
#include "pattern.h"
#include "fixed.h"

static void game_over(Game_Data *data);


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
	// if the linked list is not empty
		updateWalls(data->list, min(data->current_time - data->last_time, 2));
		// update the linked list

		// if the player and a wall collide
		if(isColliding(data->list, data->player_angle, data->nb_lines) == true) {
			game_over(data);
			return;
		}
	// remove every wall whose distance to the center equals zero
		data->list = removeWall(data->list, 8);
	}
	// level generation
	if(!data->cooldown_timer--) {
		Pattern pattern = data->level->patterns[rand()% data->level->nb_patterns];
		addPattern(data, &pattern, rand()%data->nb_lines, rand()&1);
		data->cooldown_timer = pattern.cooldown;
	}

	if(KeyDown(K_LEFT)){
		float new_player_position = data->player_angle - data->level->player_rotation_speed *  (data->current_time - data->last_time)*FRAME_TIME;
		if(!isCollidingSide(data->list, data->player_angle, data->nb_lines) && isCollidingSide(data->list, new_player_position, data->nb_lines)) {
			new_player_position = data->player_angle;
		}
		data->player_angle = new_player_position;
	}
	if(KeyDown(K_RIGHT)){
		float new_player_position = data->player_angle + data->level->player_rotation_speed *  (data->current_time - data->last_time)*FRAME_TIME;
		if(!isCollidingSide(data->list, data->player_angle, data->nb_lines) && isCollidingSide(data->list, new_player_position, data->nb_lines)) {
			new_player_position = data->player_angle;
		}
		data->player_angle = new_player_position;
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
void update_game_over(Game_Data *data)
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
void update_menu(Game_Data *data)
{
//WARNING: THIS IS JUST PLACEHOLDER TO TEST THE GRAPHICS (too lazy to do some real level handling right now...)
        data->last_time = data->current_time;//updating the time variables
        data->current_time = RTC_GetTicks();

	if(data->keypress_delay == 0) //to make sure that the user isn't scrolling too fast
	{
		if(KeyDown(K_EXE)) //load the selected level
			switch_to_state(GAME, data);//TODO: change some values in data first
		else if(KeyDown(K_LEFT))
		{
			data->current_entry --;//change the selected id
			if(data->current_entry == 0)//check for overflows
				data->current_entry = 6;
			data->keypress_delay = 15;//init the delay
			//TODO: load high score data and stuff, probably not at run time, but in init_states
		}else if(KeyDown(K_RIGHT))
		{
			data->current_entry ++;
			if(data->current_entry == 7)
				data->current_entry = 1;
			data->keypress_delay = 15;
		}
	}else data->keypress_delay --;
	updateCamera(&(data->cam), data->current_time - data->last_time);//update the camera for the background
}

void updateCamera(Camera *cam, unsigned int delta_time){
	cam->angle += cam->speed * delta_time / 2.;

	if(cam->angle >= 360)
		cam->angle = cam->angle % 360;

}


static void game_over(Game_Data *data) {
	// clean up wall
	int i = 128;
	while(data->list != NULL) {
		Wall *next = data->list->nxt;
		free(data->list);
		data->list = next;
	}
	for (i = 0; i < data->level->nb_patterns; ++i)
	{
		freePattern(&data->level->patterns[i]);
	}
	free(data->level);

	switch_to_state(MENU, data);
}