#include "draw_states.h"
#include "fxlib.h"

void draw_game(Game_Data *data)
{
	//draw the player and the lines
    drawPlayer(&(data->cam), data->player_angle);
    drawDiagonal(1, data->cam);
    drawDiagonal(2, data->cam);
    drawDiagonal(3, data->cam);
	//showing the walls
    if(data->list != NULL)
        drawWalls(data->list, &(data->cam));
	//showing the HUD
	drawGameHUD(data);
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

int numDigits(unsigned int number)
{
    int digits = 0;
    if (number <= 0) digits = 1; // remove this line if '-' counts as a digit
    while (number) {
        number /= 10;
        digits++;
    }
    return digits;
}


//draws HUD
//Shows the time elapsed and the current level
void drawGameHUD(Game_Data *data) {
	unsigned char timeBuffer[11] =""; 					//9 digits + . + \0
	unsigned long int delta = RTC_GetTIcks() - data->start_time;
	unsigned int centis = ((delta%128)/128.) *100; 		//calculate 1/100e second deciaml part
	unsigned int seconds = delta /128;					//calculatr seconds
	
	unsigned char offset = 0;							//offset touse to merge strings in the same array
	uintToStr(timeBuffer + offset, seconds);
	offset += numDigits(seconds);
	timeBuffer[offset++] ='.';
	uintToStr(timeBuffer + offset, centis);
	PrintMini(0, 8, timeBuffer, MINI_OVER);
}

//draws the player
//at first, was supposed to draw an hexagon in the center, plus a triangle to show the player,
//but the hexagon was not visible, and it was a pixel mess, so we're showing a circle instead.
//there is still for code to calculate the vertices of the hexagon, in case we want to change that again
void drawPlayer(Camera *cam, int player_angle)
{
    int x[6];
    int y[6];
    int i = 0;
    int angle = 0;
    for(i = 0; i<6; ++i)
    {
        angle = i *60;
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
void drawDiagonal(int nb, Camera cam)
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