#include "draw_states.h"
void draw_game(Game_Data *data)
{
	//draw the player and the lines
    drawPlayer(&(data->cam), data->player_angle, data->nb_lines, data->line_transition);
    drawDiagonals(data->cam, data->nb_lines, data->line_transition);
    	//showing the walls
    if(data->list != NULL)
	drawWalls(data->list, &(data->cam), data->nb_lines);
}
void draw_title(Game_Data *data)
{
	PrintMini(20, 28, "Press EXE to begin");
	drawDiagonals(data->cam, 6, data->line_transition);
}
void draw_menu(Game_Data *data)
{

}
void draw_game_over(Game_Data *data)
{

}

//draws the player
//at first, was supposed to draw an hexagon in the center, plus a triangle to show the player,
//but the hexagon was not visible, and it was a pixel mess, so we're showing a circle instead.
//there is still for code to calculate the vertices of the hexagon, in case we want to change that again
void drawPlayer(Camera *cam, int player_angle, int nb_lines, Line_Transition line_transition)
{
	int x[32];
	int y[32];
	int i = 0;
	int angle = 0;

	float tmp_angle = 0.0;
	float transition_angle = 0.0;
	float delta_angle = 0.0;

	if(line_transition.delta_nb_lines == 1)
		nb_lines ++;
	if(line_transition.counter_start != 0)
		transition_angle = (360.0 / (float)nb_lines) * ((float)line_transition.counter / (float)line_transition.counter_start);
	delta_angle = 360.0/nb_lines;

	do
	{
		x[i] = (8. + cam->zoom)*cos(PI * (tmp_angle + cam->angle)/180.) + cam->cX;
		y[i] = (8. + cam->zoom)*sin(PI * (tmp_angle + cam->angle)/180.) + cam->cY;

		i++;

		switch(line_transition.delta_nb_lines)
		{
			case 0:
				tmp_angle += delta_angle;
				break;
			case 1:
				if(i < nb_lines)
					tmp_angle += (360 - (delta_angle - transition_angle)) / (nb_lines - 1);
				else
					tmp_angle += delta_angle - transition_angle;
				break;
			case -1:
				if(i < nb_lines)
					tmp_angle += (360 - transition_angle) / (nb_lines - 1);
				else
					tmp_angle = transition_angle;
				break;
		}
	}while(i <= nb_lines);

	//draw the aforementionned circle, depending on the camera's center
	//ML_filled_circle(cam.cX, cam.cY, 6, BLACK);
	ML_polygone(x, y, nb_lines, BLACK);
	//draw the player. At such a low scale, it was impossible to draw a rotating triangle, so its a radius 1 circle instead.
	ML_filled_circle((9. + cam->zoom)*cos( PI*(player_angle + cam->angle)/180) + cam->cX, (9. + cam->zoom)*sin( PI*(player_angle+cam->angle)/180) + cam->cY, 1, BLACK);
}

//draws one of the three rotating lines
void drawDiagonals(Camera cam, int nb_lines, Line_Transition line_transition)
{
	int tmp_angle = cam.angle;
	float tmp_angle_rad = 0.0f;
	int i = 0;

	float x1 = 0.0f, y1 = 0.0f, x2 = 0.0f, y2 = 0.0f;

	float delta_angle = 0.0;

	float coeff = 0.0;
	float transition_angle = 0.0;
	
	delta_angle = 360.0 / nb_lines;

	if(line_transition.delta_nb_lines == 1)
		nb_lines ++;

	if(line_transition.counter_start != 0)
		coeff = (float)line_transition.counter / (float)line_transition.counter_start;
	transition_angle = delta_angle * coeff;

	do{
		tmp_angle_rad = tmp_angle * PI / 180.0f;
		x1 = 9.0f * cos(tmp_angle_rad);
		y1 = 9.0f * sin(tmp_angle_rad);
		x2 = 128.0f * cos(tmp_angle_rad);
		y2 = 128.0f * sin(tmp_angle_rad);
		ML_line(x1 + cam.cX, y1 + cam.cY, x2 + cam.cX, y2 + cam.cY, BLACK);

		i++;

		switch(line_transition.delta_nb_lines){
		case 0:
			tmp_angle += 360/nb_lines;
			break;

		case 1:
			if(i < nb_lines - 1)
			{
				tmp_angle += (360 - (delta_angle - transition_angle)) / (nb_lines - 1);
			}else{
				tmp_angle += delta_angle - transition_angle;
			}
			break;

		case -1:
			if(i < nb_lines - 1)
			{
				tmp_angle += (360 - transition_angle) / (nb_lines - 1);
			}else{
				tmp_angle += transition_angle;
			}
			break;
		}
		if(tmp_angle >= 360)tmp_angle = tmp_angle - 359;
	}while(i < nb_lines);
}
