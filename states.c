#include "states.h"

static void key_latch_update(Game_Data* data) {
	data->shift_latch_value = (KeyDown(K_EXE) || KeyDown(K_SHIFT));
	data->alpha_latch_value = KeyDown(K_ALPHA);
}

State current_state = TITLE;
void switch_to_state(State new_state, Game_Data *data)
{
	switch (new_state)
	{
		case GAME:
		init_game(data);
		break;
		case TITLE:
		init_title(data);
		break;
		case MENU:
		init_menu(data);
		break;
		case GAME_OVER:
		init_game_over(data);
		break;
		case OUT_OF_MEMORY:
		init_oom(data);
		break;
	}
	current_state = new_state;
}
void update(Game_Data *data)
{
	switch(current_state)
	{
		case GAME:
		update_game(data);
		break;
		case TITLE:
		update_title(data);
		break;
		case MENU:
		update_menu(data);
		break;
		case GAME_OVER:
		update_game_over(data);
		break;
		case OUT_OF_MEMORY:
		update_oom(data);
		break;
	}
	key_latch_update(data);
}
void draw(Game_Data *data)
{
	switch(current_state)
	{
		case GAME:
		draw_game(data);
		break;
		case TITLE:
		draw_title(data);
		break;
		case MENU:
		draw_menu(data);
		break;
		case GAME_OVER:
		draw_game_over(data);
		break;
		case OUT_OF_MEMORY:
		draw_oom(data);
		break;
	}
}
