#ifndef STRUCT_H
#define STRUCT_H

//constants
#define PI 3.14159265
#define SIN_60 0.866025404
#define COS_60 0.5
#define true 1
#define false 0
#define bool unsigned char

//macros
#define abs(x) x>0 ? x : -x
typedef enum {PATTERN} Pattern_Enum;
typedef struct Camera Camera;
typedef struct Wall Wall;
typedef struct Line Line;
typedef struct Level Level;

struct Level{
	//for the level generation
	Pattern_Enum available_patterns[32][32];
	int nb_patterns;

	//for the camera rotation
	int change_interval; //5 seconds most of the time, but who knows...
	int change_precision; //to add a bit of randomness to the intervals
	float change_probability; //sometimes, there can be no change at all
	
	float max_speed;
	float min_speed;

	float fast_spin_probability; //very low, sometimes there is a slightly faster spin for one second, then a normal spin. This is the number that allow us to generate it
};

//the camera is defined by its center
// ! and not by its upper left corner !
//and an angle
struct Camera{
    int cX;
    int cY;
    int angle;

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
    int h;
    int id;
    int line;

    Wall *nxt;
};
#endif
