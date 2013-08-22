#ifndef STRUCT_H
#define STRUCT_H

#include "stdlib.h"

//constants
#define FPS 20
#define FRAME_TIME 1/FPS
#define PI 3.14159265
#define SIN_60 0.866025404
#define COS_60 0.5
#define true 1
#define false 0
#define bool unsigned char

//macros

#define abs(x) x>0 ? x : -x

typedef enum {PATTERN1, PATTERN2, PATTERN3, END_PATTERNS} Pattern_Enum;
typedef struct Camera Camera;
typedef struct Wall Wall;
typedef struct Line Line;
typedef struct Level Level;
typedef struct Line_Transition Line_Transition;
typedef struct Game_Data Game_Data;
typedef struct Pattern_Stage Pattern_Stage;
typedef enum {GAME, MENU, TITLE, GAME_OVER} State;
typedef struct Pattern Pattern;

struct Pattern_Stage{
	bool walls[6];
};
struct Pattern{
	Pattern_Stage *stages;
	int num_stages;
	int nb_lines; //so that we don't load a 5-lines pattern when we have 6 lines to fill
	float prob; //some patterns are more common than some others
};

struct Level{

	int id; //1 to 6

	//for the level generation
	Pattern_Enum available_patterns[32];

	int nb_patterns;

	//for the camera rotation
	int cam_change_interval; //5 seconds most of the time, but who knows...
	int cam_change_precision; //to add a bit of randomness to the intervals
	float cam_change_probability; //sometimes, there can be no change at all
	//camera speed
	float cam_max_speed;
	float cam_min_speed;

	float fast_spin_probability; //very low, there sometimes is a slightly faster spin for one second, then a normal spin. This is the number that allow us to generate it
	
	//for the line number changes (lc prefix):
	int lc_min_score; //minimum score in seconds to reach before any line number change occurs
	float lc_probability;
	int lc_duration;
};

//the camera is defined by its center
// ! and not by its upper left corner !
//and an angle
struct Camera{
    int cX;
    int cY;
    unsigned int angle;
    float zoom;

    float speed;
};

//a simple obstacle structure
//d is the distance from the lowest face of the trapeze to the center of the screen
//h is the thickness of the wall
//line indicates the line that contains this obstacle
//id is self explanatory
//nxt is used by the linked list
struct Wall{
    float d;
    unsigned int h;
    unsigned int id;
    unsigned int line;

    Wall *nxt;
};

struct Line_Transition{
	unsigned int counter;
	unsigned int counter_start;
	int delta_nb_lines;
};

struct Game_Data{
//Main game data
	unsigned int start_time;
	unsigned int last_time;
	unsigned int current_time;
	unsigned int player_angle;

	unsigned int nb_lines;
	Line_Transition line_transition;

	Wall *list;

	Level *level;

	Camera cam;

//Start menu data
	unsigned int nb_entries;
	unsigned int current_entry; //from 1 to 6
	unsigned int current_entry_high_score;
	char **entry_difficulties; //a table of null-terminated strings
	unsigned int keypress_delay;

	Pattern patterns[END_PATTERNS];
};

#endif
