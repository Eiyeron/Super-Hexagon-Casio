#include "update_states.h"

void update_title(Game_Data *data)
{
//TODO
}

#define min(a, b) ((a) < (b) ? (a) : (b))

void update_game(Game_Data *data)
{
	data->last_time = data->current_time;
	data->current_time = RTC_GetTicks();
	data->chrono_time += (data->current_time - data->last_time)/ 128.;

	if(data->list != NULL){ //if the linked list is not empty
		updateWalls(data->list, min(data->current_time - data->last_time, 2)); //update the linked list

	if(isColliding(data->list, data->player_angle, data->nb_lines) == true){ //if the player and a wall collide
		PrintMini(50, 0, "TOUCHE", MINI_OVER); //death handling
	}
	data->list = removeWall(data->list, 8); //remove every wall whose distance to the center equals zero
	}
	//level generation
	//TODO: something else than pure randomness
	if(rand() % 40 == 1){
		data->list = addWall(data->list, 128, 5, 1, rand()%data->nb_lines);
	}else if(rand() % 70 == 1){
		int emptyRow = rand()%data->nb_lines;
		int i = 0;
		for(i = 0; i < data->nb_lines; i++)
			if(i != emptyRow)
				data->list = addWall(data->list, 128, 5, 1, i);
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

	while(data->player_angle < 0)
		data->player_angle += 360;
	while(data->player_angle > 360)
		data->player_angle -= 360;
		//data->player_angle = data->player_angle % 360;

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
	if(cam->zoom == 1)
		cam->zoom = 3;
	else
		cam->zoom -= 0.5 * delta_time * FRAME_TIME;
	if(cam->zoom < 1)
		cam->zoom = 1;
}
