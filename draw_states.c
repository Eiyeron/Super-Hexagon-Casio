#include "draw_states.h"
#include "fxlib.h"
#include "fixed.h"
#include <stdio.h>

// static functions

static void fillBackground(Game_Data *data);
static void draw_big_num(unsigned char *txt, int x, int y, unsigned char isReversed);

static void drawPlayer(Game_Data *data, int player_angle);
static void drawPolygon(Game_Data *data, int nb_lines, Line_Transition line_transition);
static void drawDiagonals(Game_Data *data, int nb_lines, Line_Transition line_transition);
static void drawHud(Game_Data *data);
static void drawChrono(Game_Data *data);
static int getLevel(Game_Data *data);

static unsigned int length_of_print_string(unsigned char* txt);
static void drawTopLeftCornerTextOffset(unsigned char* txt, unsigned char isReversed, int y);
static void drawTopLeftCornerText(unsigned char* txt, unsigned char isReversed);
static void drawTopRightCornerTextOffset(unsigned char* txt, unsigned char isReversed, int y);
static void drawTopRightCornerText(unsigned char* txt, unsigned char isReversed);
static void drawBottomLeftCornerText(unsigned char* txt, unsigned char isReversed);
static void drawBottomRightCornerText(unsigned char* txt, unsigned char isReversed);

static const unsigned char title_spr[] = {0x07, 0xF6, 0x1B, 0xFD, 0xFE, 0xFE, 0x00, 0x00, 0x0F, 0xF6, 0x1B, 0xFD, 0xFE, 0xFF, 0x00, 0x00, 0x0C, 0x06, 0x1B, 0x0D, 0x80, 0xC3, 0x00, 0x00, 0x0F, 0xF6, 0x1B, 0x0D, 0xFE, 0xC3, 0x00, 0x00, 0x0F, 0xF6, 0x1B, 0xFD, 0xFE, 0xFE, 0x00, 0x00, 0x00, 0x36, 0x1B, 0xF9, 0x80, 0xFF, 0x00, 0x00, 0x0F, 0xF7, 0xFB, 0x01, 0xFE, 0xC3, 0x00, 0x00, 0x0F, 0xE3, 0xFB, 0x00, 0xFE, 0xC3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC3, 0x7F, 0xB0, 0xCF, 0xEF, 0xF3, 0xFB, 0xF8, 0xC3, 0x7F, 0xB0, 0xDF, 0xEF, 0xF7, 0xFB, 0xFC, 0xC3, 0x60, 0x30, 0xD8, 0x6C, 0x06, 0x1B, 0x0C, 0xFF, 0x7F, 0xBF, 0xD8, 0x6C, 0x36, 0x1B, 0x0C, 0xFF, 0x7F, 0x9F, 0x9F, 0xEC, 0x36, 0x1B, 0x0C, 0xC3, 0x60, 0x30, 0xDF, 0xEC, 0x36, 0x1B, 0x0C, 0xC3, 0x7F, 0xB0, 0xD8, 0x6F, 0xF7, 0xFB, 0x0C, 0xC3, 0x3F, 0xB0, 0xD8, 0x6F, 0xE7, 0xF3, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x9F, 0xCF, 0xEF, 0xF3, 0xF8, 0x00, 0x00, 0x7F, 0xBF, 0xDF, 0xEF, 0xF7, 0xF8, 0x00, 0x00, 0x60, 0x30, 0xD8, 0x01, 0x86, 0x18, 0x00, 0x00, 0x60, 0x30, 0xDF, 0xE1, 0x86, 0x18, 0x00, 0x00, 0x60, 0x3F, 0xDF, 0xE1, 0x86, 0x18, 0x00, 0x00, 0x60, 0x3F, 0xC0, 0x61, 0x86, 0x18, 0x00, 0x00, 0x7F, 0xB0, 0xDF, 0xEF, 0xF7, 0xF8, 0x00, 0x00, 0x3F, 0xB0, 0xDF, 0xCF, 0xF7, 0xF0, 0x00};

static const unsigned char hex_border_top_left[8] = {0xF0, 0xF0, 0xE0, 0xE0, 0xC0, 0xC0, 0x80, 0x80};
static const unsigned char hex_border_top_right[8] ={0x1F, 0x1F, 0x0F, 0x0F, 0x07, 0x07, 0x03, 0x03};
static const unsigned char hex_border_bottom_left[8] = {0x80, 0x80, 0xC0, 0xC0, 0xE0, 0xE0, 0xF0, 0xF0};
static const unsigned char hex_border_bottom_right[8] ={0x03, 0x03, 0x07, 0x07, 0x0F, 0x0F, 0x1F, 0x1F};

static const unsigned char hex_border_top_left_rev[8] = {0x0F, 0x0F, 0x1F, 0x1F, 0x3F, 0x3F, 0x7F, 0x7F};
static const unsigned char hex_border_top_right_rev[8] ={0xE0, 0xE0, 0xF0, 0xF0, 0xF8, 0xF8, 0xFC, 0xFC};
static const unsigned char hex_border_bottom_left_rev[8] = {0x7F, 0x7F, 0x3F, 0x3F, 0x1F, 0x1F, 0x0F, 0x0F};
static const unsigned char hex_border_bottom_right_rev[8] ={0xFC, 0xFC, 0xF8, 0xF8, 0xF0, 0xF0, 0xE0, 0xE0};

static const unsigned char big_hex_border_left[] = {128,128,192,192,224,224,240,240,248,248};
static const unsigned char big_hex_border_left_rev[] = {248,248,120,120,56,56,24,24,8,8};


// 44*8
static const unsigned char level_spr[] = {192,127,176,223,236,0,192,127,176,223,236,0,192,96,48,216,12,0,192,127,176,223,236,0,192,127,176,223,236,0,192,96,48,216,12,0,255,127,191,223,239,240,127,63,191,143,231,240};
static const unsigned char level_spr_rev[] = {63,128,79,32,19,240,63,128,79,32,19,240,63,159,207,39,243,240,63,128,79,32,19,240,63,128,79,32,19,240,63,159,207,39,243,240,0,128,64,32,16,0,128,192,64,112,24,0};

static const unsigned char num_0[] = {127,255,195,195,195,195,255,254};
static const unsigned char num_1[] = {240,248,24,24,24,24,255,255};
static const unsigned char num_2[] = {255,255,3,127,254,192,255,255};
static const unsigned char num_3[] = {254,255,3,255,255,3,255,254};
static const unsigned char num_4[] = {195,195,195,255,127,3,3,3};
static const unsigned char num_5[] = {255,255,192,254,127,3,255,255};
static const unsigned char num_6[] = {255,255,192,254,255,195,255,255};
static const unsigned char num_7[] = {254,255,3,3,3,3,3,3};
static const unsigned char num_8[] = {127,255,195,255,255,195,255,254};
static const unsigned char num_9[] = {255,255,195,255,127,3,255,255};

static const unsigned char num_0_rev[] = {128,0,60,60,60,60,0,1};
static const unsigned char num_1_rev[] = {15,7,231,231,231,231,0,0};
static const unsigned char num_2_rev[] = {0,0,252,128,1,63,0,0};
static const unsigned char num_3_rev[] = {1,0,252,0,0,252,0,1};
static const unsigned char num_4_rev[] = {60,60,60,0,128,252,252,252};
static const unsigned char num_5_rev[] = {0,0,63,1,128,252,0,0};
static const unsigned char num_6_rev[] = {0,0,63,1,0,60,0,0};
static const unsigned char num_7_rev[] = {1,0,252,252,252,252,252,252};
static const unsigned char num_8_rev[] = {128,0,60,0,0,60,0,1};
static const unsigned char num_9_rev[] = {0,0,60,0,128,252,0,0};


static const unsigned char *num_tab[10] = {
	num_0,
	num_1,
	num_2,
	num_3,
	num_4,
	num_5,
	num_6,
	num_7,
	num_8,
	num_9
};

static const unsigned char *num_tab_rev[10] = {
	num_0_rev,
	num_1_rev,
	num_2_rev,
	num_3_rev,
	num_4_rev,
	num_5_rev,
	num_6_rev,
	num_7_rev,
	num_8_rev,
	num_9_rev
};

static const unsigned char *step_text[6] = {
		"Point",
		"Line",
		"Triangle",
		"Square",
		"Pentagon",
		"Hexagon"
	};


void draw_game(Game_Data *data)
{
	fillBackground(data);
	// draw the player and the lines
	drawPlayer(data, data->player_angle);
	drawPolygon(data, data->nb_lines, data->line_transition);
	drawDiagonals(data, data->nb_lines, data->line_transition);
    	// showing the walls
	if(data->list != NULL)
		drawWalls(data->list, data, data->nb_lines, data->line_transition);
	drawHud(data);
}
void draw_title(Game_Data *data)
{
	fillBackground(data);

	ML_bmp_or(title_spr, 12, (64-26)/2, 62, 26);

	drawPolygon(data, data->nb_lines, data->line_transition);
	drawDiagonals(data, data->nb_lines, data->line_transition);
	drawBottomLeftCornerText("Press Shift", data->are_colors_reversed);
	drawTopRightCornerText("By Eiyeron & Adbook", data->are_colors_reversed);
}
void draw_menu(Game_Data *data)
{
	char highscore_text[50] = {0};
	sprintf(highscore_text, "Best time : %.2f", data->entry_highscores[data->current_entry - 1]);
	fillBackground(data);
	drawPolygon(data, data->nb_lines, data->line_transition);
	drawDiagonals(data, data->nb_lines, data->line_transition);
	drawPlayer(data, (360 - data->cam.angle + 270)%360);
	drawTopRightCornerText(data->entry_difficulties[data->current_entry - 1], data->are_colors_reversed);
	if(data->current_entry > 3) {
		// Hyper Mode
		drawTopLeftCornerText("Hyper Mode", data->are_colors_reversed);
		drawTopLeftCornerTextOffset(highscore_text, data->are_colors_reversed, 8);
		drawTopLeftCornerTextOffset(step_text[getLevel(data)], data->are_colors_reversed, 16);
	} else {
		drawTopRightCornerTextOffset(highscore_text, data->are_colors_reversed, 8);
		drawTopRightCornerTextOffset(step_text[getLevel(data)], data->are_colors_reversed, 16);
	}
}
void draw_game_over(Game_Data *data)
{
	const int time_y_position = 21;
	const int time_border_y_position = time_y_position - 1;
	const int time_bottom_border_y_position = time_border_y_position + 9;


	const int level_y_position = 10;
	const int level_border_y_position = level_y_position - 1;
	const int level_bottom_border_y_position = level_border_y_position + 9;
	const int x_offset = 2;
	const int level_num_x_position = 44+2 + x_offset; // offset from level sprite

	int time_length;
	unsigned char int_time_text[32];
	unsigned char decimal_text[32];
	unsigned char level_text[2] = "0";
	level_text[0] = getLevel(data) + '1';

	sprintf(int_time_text, "%u", (int)data->chrono_time);
	sprintf(decimal_text, ":%02u", (int)(data->chrono_time*100)%100);
	time_length = time_length = 9*strlen(int_time_text);

	fillBackground(data);
	drawPolygon(data, data->nb_lines, data->line_transition);
	drawDiagonals(data, data->nb_lines, data->line_transition);


	if(!data->are_colors_reversed) {

		ML_rectangle(0, level_border_y_position, level_num_x_position + 9, level_bottom_border_y_position, 0, BLACK, BLACK);
		ML_bmp_or(big_hex_border_left, level_num_x_position + 9, level_border_y_position, 5, 10);
		ML_bmp_and(level_spr_rev, x_offset, level_y_position, 44, 8);

		ML_rectangle(0, time_border_y_position, time_length + 3*4, time_bottom_border_y_position, 0, BLACK, BLACK);
		ML_bmp_or(big_hex_border_left, time_length + 3*4, time_border_y_position, 5, 10);
		PrintMini(time_length + x_offset, time_y_position, decimal_text, MINI_REV);
	}
	else {
		ML_rectangle(0, level_border_y_position, level_num_x_position + 9, level_bottom_border_y_position, 0, WHITE, WHITE);
		ML_bmp_and(big_hex_border_left_rev, level_num_x_position + 9 + 1, level_border_y_position, 4, 10);
		ML_bmp_or(level_spr, x_offset, level_y_position, 44, 8);

		ML_rectangle(0, time_border_y_position, time_length + 3*4, time_bottom_border_y_position, 0, WHITE, WHITE);
		ML_bmp_and(big_hex_border_left_rev, time_length + 3*4 + 1, time_border_y_position, 4, 10);
		PrintMini(time_length + x_offset, time_y_position, decimal_text, MINI_OVER);
	}
	draw_big_num(level_text, level_num_x_position, level_y_position, !data->are_colors_reversed);
	draw_big_num(int_time_text, x_offset, time_y_position, !data->are_colors_reversed);
	drawTopLeftCornerText(step_text[getLevel(data)], data->are_colors_reversed);
	if(data->it_s_a_highscore) {
		drawTopRightCornerText("New highscore!", data->are_colors_reversed);
	}


	drawBottomRightCornerText("Shift to retry", data->are_colors_reversed);
}

void draw_oom(Game_Data* data) {
	fillBackground(data);
	drawPolygon(data, data->nb_lines, data->line_transition);
	drawDiagonals(data, data->nb_lines, data->line_transition);
	drawTopRightCornerText("Oops! Out of Memory", data->are_colors_reversed);
	drawTopRightCornerTextOffset("Your progress will be saved.", data->are_colors_reversed, 8);
	drawBottomLeftCornerText("Press EXIT to quit.", data->are_colors_reversed);
}

static void fillBackground(Game_Data *data) {
	if(data->are_colors_reversed) {
		int i, end, *pointer_long, vram;
		char *pointer_byte;
		vram = (int)ML_vram_adress();
		end = 4-vram&3;
		pointer_byte = (char*)vram;
		for(i=0 ; i<end ; i++) pointer_byte[i] = 0xFF;
			pointer_long = (int*) (vram+end);
		for(i=0 ; i<255 ; i++) pointer_long[i] = 0xFFFFFFFF;
			pointer_byte += 1020+end;
		end = vram&3;
		for(i=0 ; i<end ; i++) pointer_byte[i] = 0xFF;
	} else {
		ML_clear_vram();
	}
}

static void drawChrono(Game_Data *data) {
	unsigned char time_text[32] = "";

	sprintf(time_text, "%.2f", data->chrono_time);

	if(data->chrono_time < 60) {
		// Drawing the text with the little progress bar. As I offset the text,
		// I need to remake the whole routine.
		ML_Color drawing_color = data->are_colors_reversed ? WHITE : BLACK;
		unsigned int text_color = data->are_colors_reversed ? MINI_OVER : MINI_REV;
		unsigned short length_of_time, length_of_time_line;
		length_of_time = strlen(time_text);
		length_of_time_line = 4 * length_of_time;
		PrintMini(0, 0, time_text, text_color);
		ML_horizontal_line(6, 0, (data->chrono_time/60.) * (length_of_time_line - 2), drawing_color);
		ML_horizontal_line(7, 0, length_of_time_line - 1, drawing_color);
		if(!data->are_colors_reversed) {
			ML_bmp_8_or(hex_border_top_left, length_of_time_line, 0);
		} else {
			ML_bmp_8_and(hex_border_top_left_rev, length_of_time_line, 0);
		}
	}
	else {
		drawTopLeftCornerText(time_text, data->are_colors_reversed);
	}
}

static int getLevel(Game_Data *data) {
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
	return current_step;
}


static void drawHud(Game_Data *data) {
	drawChrono(data);
	drawTopRightCornerText(step_text[getLevel(data)], data->are_colors_reversed);

}

static void drawPolygon(Game_Data *data, int nb_lines, Line_Transition line_transition) {
	int x[32];
	int y[32];
	int i = 0;
	int angle = 0;

	Camera* cam= &data->cam;
	ML_Color drawing_color = data->are_colors_reversed ? WHITE : BLACK;

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

	// draw the aforementionned circle, depending on the camera's center
	// ML_filled_circle(cam.cX, cam.cY, 6, BLACK);
	ML_polygone(x, y, nb_lines, drawing_color);
	// draw the player. At such a low scale, it was impossible to draw a rotating triangle, so its a radius 1 circle instead.
	// TODO : Replace it for a quick sprite blit, or unwrapped ML_pixel procedure.
}

// draws the player
// at first, was supposed to draw an hexagon in the center, plus a triangle to show the player,
// but the hexagon was not visible, and it was a pixel mess, so we're showing a circle instead.
// there is still for code to calculate the vertices of the hexagon, in case we want to change that again
static void drawPlayer(Game_Data *data, int player_angle)
{
	ML_Color drawing_color = data->are_colors_reversed ? WHITE : BLACK;

	ML_point((9. + data->cam.zoom)*cos( PI*(player_angle + data->cam.angle)/180) + data->cam.cX, (9. + data->cam.zoom)*sin( PI*(player_angle+data->cam.angle)/180) + data->cam.cY, 3, drawing_color);

}

// draws one of the three rotating lines
static void drawDiagonals(Game_Data *data, int nb_lines, Line_Transition line_transition)
{
	fix tmp_angle = FIX(data->cam.angle);
	int i = 0;

	fix x1 = 0, y1 = 0, x2 = 0, y2 = 0;

	fix delta_angle = 0;

	fix coeff = 0;
	fix transition_angle = 0;

	ML_Color drawing_color = data->are_colors_reversed ? WHITE : BLACK;

	delta_angle = fdiv(FIX(360), FIX(nb_lines));

	if(line_transition.delta_nb_lines == 1)
		nb_lines ++;

	if(line_transition.counter_start != 0)
		coeff = fdiv(FIX(line_transition.counter), FIX(line_transition.counter_start));
	transition_angle = fmul(delta_angle, coeff);

	do{
		x1 = fmul(FIX(9) + ftofix(data->cam.zoom), fcos(tmp_angle));
		y1 = fmul(FIX(9) + ftofix(data->cam.zoom), fsin(tmp_angle));
		x2 = fmul(fcos(tmp_angle), FIX(128));
		y2 = fmul(fsin(tmp_angle), FIX(128));
		ML_line(UNFIX(x1) + data->cam.cX, UNFIX(y1) + data->cam.cY, UNFIX(x2) + data->cam.cX, UNFIX(y2) + data->cam.cY, drawing_color);
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
	unsigned int text_length = 0;
	unsigned int i;
	unsigned int current_char_length = 0;

	for(i = 0; i < strlen(txt); i++) {
		switch(txt[i]) {
			// upper case
			case  'K':
			case  'M':
			case  'N':
			case  'Q':
			case  'W':
			current_char_length = 6;
			break;

			// lower case
			case 'i':
			current_char_length = 2;
			break;

			case 'n':
			case 'r':
			current_char_length = 5;
			break;

			case 'm':
			case 'w':
			current_char_length = 6;
			break;

			case '!':
			current_char_length = 2;
			break;

			case '&':
			current_char_length = 5;
			break;

			case '[':
			case ']':
			/*case '.':*/
			case '\'':
			current_char_length = 3;
			break;


			default:
			current_char_length = 4;
			break;
		}
		text_length += current_char_length;
	}
	return text_length;
}

static void drawTopLeftCornerTextOffset(unsigned char* txt, unsigned char isReversed, int y) {
	ML_Color drawing_color = isReversed ? WHITE : BLACK;
	unsigned int text_color = isReversed ? MINI_OVER : MINI_REV;
	unsigned int text_length = length_of_print_string(txt);
	if(!isReversed) {
		ML_bmp_8_or(hex_border_top_left, text_length, y);
	} else {
		ML_bmp_8_and(hex_border_top_left_rev, text_length, y);
	}
	PrintMini(0, y + 1, txt, text_color);

	ML_horizontal_line(7 + y, 0, text_length, drawing_color);

}

static void drawTopLeftCornerText(unsigned char* txt, unsigned char isReversed) {
	drawTopLeftCornerTextOffset(txt, isReversed, 0);
}

static void drawTopRightCornerTextOffset(unsigned char* txt, unsigned char isReversed, int y) {
	ML_Color drawing_color = isReversed ? WHITE : BLACK;
	unsigned int text_color = isReversed ? MINI_OVER : MINI_REV;
	int text_length = length_of_print_string(txt);
	int xPosition = 128 - text_length;
	if(!isReversed) {
		ML_bmp_8_or(hex_border_top_right, xPosition - 8, y);
	} else {
		ML_bmp_8_and(hex_border_top_right_rev, xPosition - 8, y);

	}
	PrintMini(xPosition, y + 1, txt, text_color);

	ML_horizontal_line(7 + y, xPosition, 127, drawing_color);
}


static void drawTopRightCornerText(unsigned char* txt, unsigned char isReversed) {
	drawTopRightCornerTextOffset(txt, isReversed, 0);
}

static void drawBottomLeftCornerText(unsigned char* txt, unsigned char isReversed) {
	ML_Color drawing_color = isReversed ? WHITE : BLACK;
	unsigned int text_length = length_of_print_string(txt);
	unsigned int text_color = isReversed ? MINI_OVER : MINI_REV;
	if(!isReversed) {
		ML_bmp_8_or(hex_border_bottom_left, text_length - 1, 56);
	} else {
		ML_bmp_8_and(hex_border_bottom_left_rev, text_length - 1, 56);
	}
	PrintMini(0, 57, txt, text_color);

	ML_horizontal_line(63, 0, text_length, drawing_color);
}

static void drawBottomRightCornerText(unsigned char* txt, unsigned char isReversed) {
	ML_Color drawing_color = isReversed ? WHITE : BLACK;
	unsigned int text_color = isReversed ? MINI_OVER : MINI_REV;
	int text_length = length_of_print_string(txt);
	int xPosition = 128 - text_length;
	if(!isReversed) {
		ML_bmp_8_or(hex_border_bottom_right, xPosition - 8, 56);
	} else {
		ML_bmp_8_and(hex_border_bottom_right_rev, xPosition - 8, 56);
	}
	ML_horizontal_line(63, xPosition, 127, drawing_color);
	PrintMini(xPosition, 57, txt, text_color);
}

static void draw_big_num(unsigned char *txt, int x, int y, unsigned char isReversed) {
	int i;
	for(i = 0; i < strlen(txt); i++) {
		if(txt[i] >= '0' && txt[i] <= '9')
			if(isReversed)
				ML_bmp_8_and(num_tab_rev[txt[i] - '0'], x + 9*i, y);
			else
				ML_bmp_8_or(num_tab[txt[i] - '0'], x + 9*i, y);
		}
	}