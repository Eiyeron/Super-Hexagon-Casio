#include "update_states.h"
#include "fixed.h"

void update_title(Game_Data *data)
{
	data->last_time = data->current_time;
	data->current_time = RTC_GetTicks();
	data->chrono_time += (data->current_time - data->last_time)/ 128.;

	if(KeyDown(K_SHIFT)) {
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

	if(data->list != NULL) {
	//if the linked list is not empty
		updateWalls(data->list, min(data->current_time - data->last_time, 2));
		//update the linked list

		//if the player and a wall collide
		if(isColliding(data->list, data->player_angle, data->nb_lines) == true) {
			//death handling
			PrintMini(50, 0, "TOUCHE", MINI_OVER);
		}
	//remove every wall whose distance to the center equals zero
		data->list = removeWall(data->list, 8);
	}
	//level generation
	//TODO: something else than pure randomness
	if(rand() % 40 == 1) {
		data->list = addWall(data->list, 128, 5, 1, rand()%data->nb_lines);
	} else if(rand() % 70 == 1) {
		int emptyRow = rand()%data->nb_lines;
		int i = 0;
		for(i = 0; i < data->nb_lines; i++){
			if(i != emptyRow)
				data->list = addWall(data->list, 128, 5, 1, i);
		}
	}
	if(KeyDown(K_LEFT)){
		data->player_angle-=15;
	}
	if(KeyDown(K_RIGHT)){
		data->player_angle+=15;
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

	if(KeyDown(K_SHIFT)) {
		switch_to_state(GAME, data);
	}
	if(KeyDown(K_ALPHA)) {
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
