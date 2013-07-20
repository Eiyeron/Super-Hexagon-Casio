#include "draw_states.h"
void draw_game(Game_Data *data)
{
	//draw the player and the lines
    drawPlayer(&(data->cam), data->player_angle, data->nb_lines);
    drawDiagonals(data->cam, data->nb_lines);
    	//showing the walls
    if(data->list != NULL)
        drawWalls(data->list, &(data->cam), data->nb_lines);
}
void draw_title(Game_Data *data)
{

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
void drawPlayer(Camera *cam, int player_angle, int nb_lines)
{
    int x[32];
    int y[32];
    int i = 0;
    int angle = 0;
    for(i = 0; i < nb_lines; ++i)
    {
        angle = i * 360 / nb_lines;
        x[i] = (8. + cam->zoom)*cos(PI * (angle + cam->angle)/180.) + cam->cX;
        y[i] = (8. + cam->zoom)*sin(PI * (angle + cam->angle)/180.) + cam->cY;
    }

	//draw the aforementionned circle, depending on the camera's center
    //ML_filled_circle(cam.cX, cam.cY, 6, BLACK);
	ML_polygone(x, y, nb_lines, BLACK);
	//draw the player. At such a low scale, it was impossible to draw a rotating triangle, so its a radius 1 circle instead.
    ML_filled_circle((9. + cam->zoom)*cos( PI*(player_angle + cam->angle)/180) + cam->cX, (9. + cam->zoom)*sin( PI*(player_angle+cam->angle)/180) + cam->cY, 1, BLACK);

}

//draws one of the three rotating lines
void drawDiagonals(Camera cam, int nb_lines)
{
	int tmp_angle = cam.angle;
	float tmp_angle_rad = 0.0f;
	int i = 0;
	
	float x1 = 0.0f, y1 = 0.0f, x2 = 0.0f, y2 = 0.0f;

	do{	
		tmp_angle_rad = tmp_angle * PI / 180.0f;
		x1 = 9.0f * cos(tmp_angle_rad);
		y1 = 9.0f * sin(tmp_angle_rad);
		x2 = 64.0f * cos(tmp_angle_rad);
		y2 = 64.0f * sin(tmp_angle_rad);
		ML_line(x1 + cam.cX, y1 + cam.cY, x2 + cam.cX, y2 + cam.cY, BLACK);

		tmp_angle += (360 / nb_lines);
		if(tmp_angle >= 360)tmp_angle = tmp_angle - 359;
		i++;
	}while(i < nb_lines);
}
