#include "draw_states.h"
void draw_game(Game_Data *data)
{
	//draw the player and the lines
    drawPlayer(&(data->cam), data->player_angle, data->nb_lines);
    drawDiagonal(1, data->cam);
    drawDiagonal(2, data->cam);
    drawDiagonal(3, data->cam);
	//showing the walls
    if(data->list != NULL)
        drawWalls(data->list, &(data->cam));
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
    int x[6];
    int y[6];
    int i = 0;
    int angle = 0;
    for(i = 0; i<6; ++i)
    {
        angle = i * 360 / nb_lines;
        x[i] = (8. + cam->zoom)*cos(PI * (angle + cam->angle)/180.) + cam->cX;
        y[i] = (8. + cam->zoom)*sin(PI * (angle + cam->angle)/180.) + cam->cY;
    }

	//draw the aforementionned circle, depending on the camera's center
    //ML_filled_circle(cam.cX, cam.cY, 6, BLACK);
	ML_polygone(x, y, 6, BLACK);
	//draw the player. At such a low scale, it was impossible to draw a rotating triangle, so its a radius 1 circle instead.
    ML_filled_circle((9. + cam->zoom)*cos( PI*(player_angle + cam->angle)/180) + cam->cX, (9. + cam->zoom)*sin( PI*(player_angle+cam->angle)/180) + cam->cY, 1, BLACK);

}

//draws one of the three rotating lines
void drawDiagonal(int nb, Camera cam, int nb_lines)
{
    int tmp_angle = 0;
    float coeff = 0;
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;

	//defining the angle between the line and the horizontal axis
    if(nb == 1)
        tmp_angle = cam.angle + 60;
    else if(nb == 2)
        tmp_angle = cam.angle;
    else if(nb == 3)
        tmp_angle = 300 + cam.angle;
    if(tmp_angle >= 360)tmp_angle = tmp_angle - 359;

	//defining the slope coefficient
    coeff = sin(PI*tmp_angle / 180)/cos(PI * tmp_angle / 180);

	//ML needs four coordinates in order to draw a line
    x1 = -32/coeff;
    y1 = -32;

    x2 = 32/coeff;
    y2 = 32;

    if(abs(x1) > 64){
        x1 = -64;
        y1 = -64*coeff;

        x2 = 64;
        y2 = 64*coeff;
    }
	//drawing the line
        ML_line(x1 + cam.cX, y1 + cam.cY, x2 + cam.cX, y2 + cam.cY, BLACK);
}
