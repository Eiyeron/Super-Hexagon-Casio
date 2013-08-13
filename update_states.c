#include "update_states.h"

void update_title(Game_Data *data)
{
	if(KeyDown(K_EXE))
		switch_to_state(MENU, data);
}
void update_game(Game_Data *data)
{
	data->last_time = data->current_time;
	data->current_time = RTC_GetTicks();
	if(data->list != NULL){ //if the linked list is not empty
		updateWalls(data->list, data->current_time - data->last_time); //update the linked list

	if(isColliding(data->list, data->player_angle, data->nb_lines) == true){ //if the player and a wall collide
		PrintMini(50, 0, "TOUCHE", MINI_OVER); //death handling
	}
	data->list = removeWall(data->list, 0); //remove every wall whose distance to the center equals zero
	}
	//level generation
	//TODO: something else than pure randomness
	if(rand() % 40 == 1){
		data->list = addWall(data->list, 128, 8, 1, rand()%6);
	}else if(rand() % 70 == 1){
		int emptyRow = rand()%6;
		int i = 0;
		for(i = 0; i < 6; i++)
			if(i != emptyRow)
				data->list = addWall(data->list, 128, 15, 1, i);
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

	if(data->player_angle < 0)
		data->player_angle = 360 + data->player_angle;
		data->player_angle = data->player_angle % 360;

	updateCamera(&(data->cam), data->current_time - data->last_time);
}
void update_menu(Game_Data *data)
{
//TODO
}
void update_game_over(Game_Data *data)
{
//TODO
}

void updateCamera(Camera *cam, unsigned int delta_time){
	cam->speed = 1; //to change
	cam->angle += cam->speed * delta_time / 2.;

	if(cam->angle >= 360)
		cam->angle = cam->angle % 360;
}
