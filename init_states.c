#include "init_states.h"
#include "pattern.h"

const unsigned char patternTest1[] = {
	0x0F,    0x00, 0x60,
	0x01,    0x00, 0x00,    0x00, 0x05,
	0x02,    0x00, 0x00,    0x00, 0x05,
	0x03,    0x00, 0x00,    0x00, 0x05,
	0x04,    0x00, 0x00,    0x00, 0x05,
	0x05,    0x00, 0x00,    0x00, 0x05,

	0x04,    0x00, 0x20,    0x00, 0x05,
	0x05,    0x00, 0x20,    0x00, 0x05,
	0x00,    0x00, 0x20,    0x00, 0x05,
	0x01,    0x00, 0x20,    0x00, 0x05,
	0x02,    0x00, 0x20,    0x00, 0x05,


	0x01,    0x00, 0x40,    0x00, 0x05,
	0x02,    0x00, 0x40,    0x00, 0x05,
	0x03,    0x00, 0x40,    0x00, 0x05,
	0x04,    0x00, 0x40,    0x00, 0x05,
	0x05,    0x00, 0x40,    0x00, 0x05,
};

const unsigned char patternTest2[] = {
	0x0F,    0x00, 0x30,
	0x00,    0x00, 0x00,    0x00, 0x03,
	0x02,    0x00, 0x00,    0x00, 0x03,
	0x04,    0x00, 0x00,    0x00, 0x03,

	0x00,    0x00, 0x08,    0x00, 0x03,
	0x02,    0x00, 0x08,    0x00, 0x03,
	0x04,    0x00, 0x08,    0x00, 0x03,

	0x00,    0x00, 0x10,    0x00, 0x03,
	0x02,    0x00, 0x10,    0x00, 0x03,
	0x04,    0x00, 0x10,    0x00, 0x03,

	0x00,    0x00, 0x18,    0x00, 0x03,
	0x02,    0x00, 0x18,    0x00, 0x03,
	0x04,    0x00, 0x18,    0x00, 0x03,

	0x00,    0x00, 0x20,    0x00, 0x03,
	0x02,    0x00, 0x20,    0x00, 0x03,
	0x04,    0x00, 0x20,    0x00, 0x03,
};

const unsigned char patternTest3[] = {
	0x09,   0x00, 0x60,
	0x00,   0x00, 0x00,    0x00, 0x04,
	0x01,   0x00, 0x00,    0x00, 0x04,
	0x02,   0x00, 0x00,    0x00, 0x04,

	0x02,   0x00, 0x20,    0x00, 0x04,
	0x03,   0x00, 0x20,    0x00, 0x04,
	0x04,   0x00, 0x20,    0x00, 0x04,

	0x04,   0x00, 0x40,    0x00, 0x04,
	0x05,   0x00, 0x40,    0x00, 0x04,
	0x00,   0x00, 0x40,    0x00, 0x04,
};

const unsigned char patternTest4[] = {
	0x0E,  0x00, 0x80,
	0x00,  0x00, 0x00,    0x00, 0x65,
	0x03,  0x00, 0x00,    0x00, 0x65,

	0x01,  0x00, 0x10,    0x00, 0x02,
	0x04,  0x00, 0x10,    0x00, 0x02,
	0x02,  0x00, 0x20,    0x00, 0x02,
	0x05,  0x00, 0x20,    0x00, 0x02,

	0x01,  0x00, 0x30,    0x00, 0x02,
	0x04,  0x00, 0x30,    0x00, 0x02,
	0x02,  0x00, 0x40,    0x00, 0x02,
	0x05,  0x00, 0x40,    0x00, 0x02,

	0x01,  0x00, 0x50,    0x00, 0x02,
	0x04,  0x00, 0x50,    0x00, 0x02,
	0x02,  0x00, 0x60,    0x00, 0x05,
	0x05,  0x00, 0x60,    0x00, 0x05

};

const unsigned char patternTest5[] = {
	0x04,    0x00, 0x20,
	0x01,    0x00, 0x00,    0x00, 0x05,
	0x02,    0x00, 0x00,    0x00, 0x05,
	0x03,    0x00, 0x00,    0x00, 0x05,
	0x05,    0x00, 0x00,    0x00, 0x05
};

const unsigned char patternTest6[] = {
	0x09,    0x00, 0x40,

	0x00,    0x00, 0x10,    0x00, 0x03,
	0x02,    0x00, 0x10,    0x00, 0x03,
	0x04,    0x00, 0x10,    0x00, 0x03,

	0x01,    0x00, 0x20,    0x00, 0x03,
	0x03,    0x00, 0x20,    0x00, 0x03,
	0x05,    0x00, 0x20,    0x00, 0x03,

	0x00,    0x00, 0x30,    0x00, 0x03,
	0x02,    0x00, 0x30,    0x00, 0x03,
	0x04,    0x00, 0x30,    0x00, 0x03
};

const unsigned char patternTest7[] = {
	0x0C,    0x00, 0x70,

	0x01,    0x00, 0x00,    0x00, 0x11,
	0x02,    0x00, 0x10,    0x00, 0x11,
	0x03,    0x00, 0x20,    0x00, 0x11,
	0x04,    0x00, 0x30,    0x00, 0x11,
	0x05,    0x00, 0x45,    0x00, 0x11,
	0x00,    0x00, 0x50,    0x00, 0x11,

	0x04,    0x00, 0x00,    0x00, 0x11,
	0x05,    0x00, 0x10,    0x00, 0x11,
	0x00,    0x00, 0x20,    0x00, 0x11,
	0x01,    0x00, 0x30,    0x00, 0x11,
	0x02,    0x00, 0x40,    0x00, 0x11,
	0x03,    0x00, 0x50,    0x00, 0x11,
};

void init_game(Game_Data *data)
{
	data->level = NULL;
	data->level = malloc(sizeof(Level));
	if(data->level == NULL)
		return;

	data->level->id = 1;

	data->level->patterns = malloc(7*sizeof(Pattern));
	readPattern(&data->level->patterns[0], patternTest1);
	readPattern(&data->level->patterns[1], patternTest2);
	readPattern(&data->level->patterns[2], patternTest3);
	readPattern(&data->level->patterns[3], patternTest4);
	readPattern(&data->level->patterns[4], patternTest5);
	readPattern(&data->level->patterns[5], patternTest6);
	readPattern(&data->level->patterns[6], patternTest7);
	data->level->nb_patterns = 7;

	data->level->player_rotation_speed = 60;

	data->level->cam_change_interval = 5;
	data->level->cam_change_precision = 1;
	data->level->cam_change_probability = 0.75;
	data->level->cam_max_speed = 5;
	data->level->cam_min_speed = 1;
	data->level->fast_spin_probability = 0.1;

	data->level->lc_min_score = 20;
	data->level->lc_probability = 0.05;
	data->level->lc_duration = 15;

	data->are_colors_reversed = 0;


	data->list = NULL;
	data->start_time = RTC_GetTicks(); // 1 tick == 1/128 second
	data->last_time = 0;
	data->current_time = RTC_GetTicks();
	data->chrono_time = 0;

	data->player_angle = 0;

	data->cam.cX = 64;
	data->cam.cY = 32;
	data->cam.angle = 0;
	data->cam.speed = 1.5;
	data->cam.zoom = 0.0;


	data->nb_lines = 6;
	data->line_transition.counter = 0;
	data->line_transition.counter_start = 0;
	data->line_transition.delta_nb_lines = 0;
	data->cooldown_timer = 16;
}
void init_title(Game_Data *data)
{
	data->start_time = RTC_GetTicks(); // 1 tick == 1/128 second
	data->last_time = 0;
	data->current_time = RTC_GetTicks();
	data->chrono_time = 0;

	data->are_colors_reversed = 0;


	data->cam.cX = 96;
	data->cam.cY = 32;
	data->cam.angle = 0;
	data->cam.speed = 1;
	data->cam.zoom = 24;

	data->nb_lines = 6;
	data->line_transition.counter = 0;
	data->line_transition.counter_start = 0;
	data->line_transition.delta_nb_lines = 0;

}
void init_menu(Game_Data *data)
{
	data->start_time = RTC_GetTicks(); // 1 tick == 1/128 second
	data->last_time = 0;
	data->current_time = RTC_GetTicks();
	data->chrono_time = 0;

	data->are_colors_reversed = 0;


	data->cam.cX = 64;
	data->cam.cY = 64;
	data->cam.angle = 0;
	data->cam.speed = 0;
	data->cam.zoom = 48;

	data->nb_lines = 6;
	data->line_transition.counter = 0;
	data->line_transition.counter_start = 0;
	data->line_transition.delta_nb_lines = 0;
}
void init_game_over(Game_Data *data)
{

}
