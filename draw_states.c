#include "draw_states.h"
#include "fxlib.h"
#include "fixed.h"
#include <stdio.h>
// static functions
static void drawPlayer(Camera *cam, int player_angle);
static void drawPolygon(Camera *cam, int nb_lines, Line_Transition line_transition);
static void drawDiagonals(Camera cam, int nb_lines, Line_Transition line_transition);
static void drawHud(Game_Data *data);
static void drawChrono(Game_Data *data);
static void drawStep(Game_Data *data);

static unsigned int length_of_print_string(unsigned char* txt);
static void drawTopLeftCornerText(unsigned char* txt);
static void drawTopRightCornerText(unsigned char* txt);
static void drawBottomLeftCornerText(unsigned char* txt);
static void drawBottomRightCornerText(unsigned char* txt);

static const unsigned char title_spr[] = {0x07, 0xF6, 0x1B, 0xFD, 0xFE, 0xFE, 0x00, 0x00, 0x0F, 0xF6, 0x1B, 0xFD, 0xFE, 0xFF, 0x00, 0x00, 0x0C, 0x06, 0x1B, 0x0D, 0x80, 0xC3, 0x00, 0x00, 0x0F, 0xF6, 0x1B, 0x0D, 0xFE, 0xC3, 0x00, 0x00, 0x0F, 0xF6, 0x1B, 0xFD, 0xFE, 0xFE, 0x00, 0x00, 0x00, 0x36, 0x1B, 0xF9, 0x80, 0xFF, 0x00, 0x00, 0x0F, 0xF7, 0xFB, 0x01, 0xFE, 0xC3, 0x00, 0x00, 0x0F, 0xE3, 0xFB, 0x00, 0xFE, 0xC3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC3, 0x7F, 0xB0, 0xCF, 0xEF, 0xF3, 0xFB, 0xF8, 0xC3, 0x7F, 0xB0, 0xDF, 0xEF, 0xF7, 0xFB, 0xFC, 0xC3, 0x60, 0x30, 0xD8, 0x6C, 0x06, 0x1B, 0x0C, 0xFF, 0x7F, 0xBF, 0xD8, 0x6C, 0x36, 0x1B, 0x0C, 0xFF, 0x7F, 0x9F, 0x9F, 0xEC, 0x36, 0x1B, 0x0C, 0xC3, 0x60, 0x30, 0xDF, 0xEC, 0x36, 0x1B, 0x0C, 0xC3, 0x7F, 0xB0, 0xD8, 0x6F, 0xF7, 0xFB, 0x0C, 0xC3, 0x3F, 0xB0, 0xD8, 0x6F, 0xE7, 0xF3, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x9F, 0xCF, 0xEF, 0xF3, 0xF8, 0x00, 0x00, 0x7F, 0xBF, 0xDF, 0xEF, 0xF7, 0xF8, 0x00, 0x00, 0x60, 0x30, 0xD8, 0x01, 0x86, 0x18, 0x00, 0x00, 0x60, 0x30, 0xDF, 0xE1, 0x86, 0x18, 0x00, 0x00, 0x60, 0x3F, 0xDF, 0xE1, 0x86, 0x18, 0x00, 0x00, 0x60, 0x3F, 0xC0, 0x61, 0x86, 0x18, 0x00, 0x00, 0x7F, 0xB0, 0xDF, 0xEF, 0xF7, 0xF8, 0x00, 0x00, 0x3F, 0xB0, 0xDF, 0xCF, 0xF7, 0xF0, 0x00};
static const unsigned char hex_border_top_left[8] = {0xF0, 0xF0, 0xE0, 0xE0, 0xC0, 0xC0, 0x80, 0x80};
static const unsigned char hex_border_top_right[8] ={0x1F, 0x1F, 0x0F, 0x0F, 0x07, 0x07, 0x03, 0x03};
static const unsigned char hex_border_bottom_left[8] = {0x80, 0x80, 0xC0, 0xC0, 0xE0, 0xE0, 0xF0, 0xF0};
static const unsigned char hex_border_bottom_right[8] ={0x03, 0x03, 0x07, 0x07, 0x0F, 0x0F, 0x1F, 0x1F};


void draw_game(Game_Data *data)
{
	//draw the player and the lines
	drawPlayer(&(data->cam), data->player_angle);
	drawPolygon(&(data->cam), data->nb_lines, data->line_transition);
	drawDiagonals(data->cam, data->nb_lines, data->line_transition);
	drawHud(data);
    	//showing the walls
	if(data->list != NULL)
		drawWalls(data->list, &(data->cam), data->nb_lines, data->line_transition);
}
void draw_title(Game_Data *data)
{

	ML_bmp_or(title_spr, 12, (64-26)/2, 62, 26);

	drawBottomLeftCornerText("Press Shift");	
	drawBottomRightCornerText("By Eiyeron");	


	drawPolygon(&(data->cam), data->nb_lines, data->line_transition);
	drawDiagonals(data->cam, data->nb_lines, data->line_transition);

}
void draw_menu(Game_Data *data)
{
	drawTopRightCornerText("WIP Menu. Forget that.  ");
	drawPolygon(&(data->cam), data->nb_lines, data->line_transition);
	drawDiagonals(data->cam, data->nb_lines, data->line_transition);

}
void draw_game_over(Game_Data *data)
{

}

static void drawChrono(Game_Data *data) {
	unsigned char time_text[8] = "";
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
	ML_bmp_8_or(hex_border_top_left
	, length_of_time_line, 0);
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

	unsigned short current_step, i;
	current_step = 5;
	for(i = 0; i < 5; i++) {
		if(data->chrono_time < step_time[i]) {
			current_step = i;
			break;
		}
	}

	// Little patch because the font is not fixed width and 'n' chars are annoying me.
	// ML_vertical_line(125,0,5, BLACK);
	// ML_vertical_line(126,0,5, BLACK);
	// ML_vertical_line(127,0,5, BLACK);

	// PrintMini(127 - length_of_step, 1, step_text[current_step], MINI_REV);
	// ML_bmp_8_or(hex_border_top_right, 127 - length_of_step - 8, 0);
	// ML_horizontal_line(6, 127 - length_of_step - 2, 127, BLACK);
	// ML_horizontal_line(7, 127 - length_of_step - 2, 127, BLACK);
	drawTopRightCornerText(step_text[current_step]);
}

static void drawHud(Game_Data *data) {
	drawChrono(data);
	drawStep(data);

}

static void drawPolygon(Camera *cam, int nb_lines, Line_Transition line_transition) {
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
}

//draws the player
//at first, was supposed to draw an hexagon in the center, plus a triangle to show the player,
//but the hexagon was not visible, and it was a pixel mess, so we're showing a circle instead.
//there is still for code to calculate the vertices of the hexagon, in case we want to change that again
static void drawPlayer(Camera *cam, int player_angle)
{
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
		x2 = fmul(fcos(tmp_angle), FIX(128));
		y2 = fmul(fsin(tmp_angle), FIX(128));
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

static unsigned int length_of_print_string(unsigned char* txt) {
	// TODO : define
	return strlen(txt) * 4;
}

static void drawTopLeftCornerText(unsigned char* txt) {
	unsigned int text_length = length_of_print_string(txt);
	PrintMini(0, 1, txt, MINI_REV);
	ML_bmp_8_or(hex_border_top_left, text_length, 0);
	ML_horizontal_line(7, 0, text_length, BLACK);
}

static void drawTopRightCornerText(unsigned char* txt) {
	int text_length = length_of_print_string(txt);
	int xPosition = 128 - text_length;
	PrintMini(xPosition, 1, txt, MINI_REV);
	ML_bmp_8_or(hex_border_top_right, xPosition - 8, 0);
	ML_horizontal_line(7, xPosition, 127, BLACK);
}

static void drawBottomLeftCornerText(unsigned char* txt) {
	unsigned int text_length = length_of_print_string(txt);
	PrintMini(0, 57, txt, MINI_REV);
	ML_bmp_8_or(hex_border_bottom_left, text_length - 1, 56);
	ML_horizontal_line(63, 0, text_length, BLACK);
}

static void drawBottomRightCornerText(unsigned char* txt) {
	int text_length = length_of_print_string(txt);
	int xPosition = 128 - text_length;
	PrintMini(xPosition, 57, txt, MINI_REV);
	ML_bmp_8_or(hex_border_bottom_right, xPosition - 8, 56);
	ML_horizontal_line(63, xPosition, 127, BLACK);
}
