#include "draw_states.h"
#include "fxlib.h"
#include "fixed.h"
#include <stdio.h>
// static functions
static void drawPlayer(Camera *cam, int player_angle, int nb_lines, Line_Transition line_transition);
static void drawDiagonals(Camera cam, int nb_lines, Line_Transition line_transition);
static void drawHud(Game_Data *data);
static void drawChrono(Game_Data *data);
static void drawStep(Game_Data *data);

void draw_game(Game_Data *data)
{
	//draw the player and the lines
	drawPlayer(&(data->cam), data->player_angle, data->nb_lines, data->line_transition);
	drawDiagonals(data->cam, data->nb_lines, data->line_transition);
	drawHud(data);
    	//showing the walls
	if(data->list != NULL)
		drawWalls(data->list, &(data->cam), data->nb_lines, data->line_transition);
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

static void drawChrono(Game_Data *data) {
	unsigned char time_text[8] = "";
	static const unsigned char time_hud_border[8] = {0xF0, 0xF0, 0xE0, 0xE0, 0xC0, 0xC0, 0x80, 0x80};
	unsigned short length_of_time, length_of_time_line;

	sprintf(time_text, "%.2f", data->chrono_time);
	length_of_time = strlen(time_text);
	length_of_time_line = 4 * length_of_time;


	if(data->chrono_time < 60) {
		PrintMini(0, 0, time_text, MINI_REV);
		ML_horizontal_line(6, 0, (data->chrono_time/60.) * (length_of_time_line - 2), BLACK);
		ML_horizontal_line(7, 0, length_of_time_line - 1, BLACK);
	}
	else {
		PrintMini(0, 1, time_text, MINI_REV);
		ML_horizontal_line(6, 0, length_of_time_line - 1, BLACK);
		ML_horizontal_line(7, 0, length_of_time_line - 1, BLACK);
	}
	ML_bmp_8_or(time_hud_border, length_of_time_line, 0);
}

static void drawStep(Game_Data *data) {
	unsigned char *step_text[6] = {
		"Point",
		"Line",
		"Triangle",
		"Square",
		"Pentagon",
		"Hexagon"
	};
	unsigned short step_time[5] = {
		10,
		20,
		30,
		45,
		60
	};

	unsigned char step_hud_border[8] ={0x1F, 0x1F, 0x0F, 0x0F, 0x07, 0x07, 0x01, 0x01};
	unsigned short length_of_step, current_step, i;
	current_step = 5;
	for(i = 0; i < 5; i++) {
		if(data->chrono_time < step_time[i]) {
			current_step = i;
			break;
		}
	}


	length_of_step = 4 * strlen(step_text[current_step]) + 1;

	// Little patch because the font is not fixed width and 'n' chars are annoying me.
	ML_vertical_line(125,0,5, BLACK);
	ML_vertical_line(126,0,5, BLACK);
	ML_vertical_line(127,0,5, BLACK);

	PrintMini(127 - length_of_step, 1, step_text[current_step], MINI_REV);
	ML_bmp_8_or(step_hud_border, 127 - length_of_step - 8, 0);
	ML_horizontal_line(6, 127 - length_of_step - 2, 127, BLACK);
	ML_horizontal_line(7, 127 - length_of_step - 2, 127, BLACK);
}

static void drawHud(Game_Data *data) {
	drawChrono(data);
	drawStep(data);

}

//draws the player
//at first, was supposed to draw an hexagon in the center, plus a triangle to show the player,
//but the hexagon was not visible, and it was a pixel mess, so we're showing a circle instead.
//there is still for code to calculate the vertices of the hexagon, in case we want to change that again
static void drawPlayer(Camera *cam, int player_angle, int nb_lines, Line_Transition line_transition)
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
		// TODO : use fixed for only two trig calls?
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
	// TODO : Replace it for a quick sprite blit, or unwrapped ML_pixel procedure.
	ML_filled_circle((9. + cam->zoom)*cos( PI*(player_angle + cam->angle)/180) + cam->cX, (9. + cam->zoom)*sin( PI*(player_angle+cam->angle)/180) + cam->cY, 1, BLACK);

}

//draws one of the three rotating lines
static void drawDiagonals(Camera cam, int nb_lines, Line_Transition line_transition)
{
	fix tmp_angle = FIX(cam.angle);
	int i = 0;

	fix x1 = 0, y1 = 0, x2 = 0, y2 = 0;

	fix delta_angle = 0;

	fix coeff = 0;
	fix transition_angle = 0;
	
	delta_angle = fdiv(FIX(360), FIX(nb_lines));

	if(line_transition.delta_nb_lines == 1)
		nb_lines ++;

	if(line_transition.counter_start != 0)
		coeff = fdiv(FIX(line_transition.counter), FIX(line_transition.counter_start));
	transition_angle = fmul(delta_angle, coeff);

	do{
		x1 = fmul(FIX(9) + ftofix(cam.zoom), fcos(tmp_angle));
		y1 = fmul(FIX(9) + ftofix(cam.zoom), fsin(tmp_angle));
		x2 = fmul(fcos(tmp_angle), FIX(64));
		y2 = fmul(fsin(tmp_angle), FIX(64));
		ML_line(UNFIX(x1) + cam.cX, UNFIX(y1) + cam.cY, UNFIX(x2) + cam.cX, UNFIX(y2) + cam.cY, BLACK);

		i++;

		switch(line_transition.delta_nb_lines){
			case 0:
			tmp_angle += fdiv(FIX(360), FIX(nb_lines));
			break;

			case 1:
			if(i < nb_lines - 1)
			{
				tmp_angle += fdiv(FIX(360) - (delta_angle - transition_angle), FIX(nb_lines - 1));
			}else{
				tmp_angle += delta_angle - transition_angle;
			}
			break;

			case -1:
			if(i < nb_lines - 1)
			{
				tmp_angle += fdiv(FIX(360) - transition_angle, FIX(nb_lines - 1));
			}else{
				tmp_angle += transition_angle;
			}
			break;
		}
		if(tmp_angle >= FIX(360)) tmp_angle = tmp_angle - FIX(359);
	}while(i < nb_lines);
}
