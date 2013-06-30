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

typedef struct Camera Camera;
typedef struct Wall Wall;
typedef struct Line Line;
//the camera is defined by its center
// ! and not by its upper left corner !
//and an angle
struct Camera{
    int cX;
    int cY;
    int angle;
};

//a simple obstacle structure
//d is the distance from the lowest face of the trapeze to the center of the screen
//h is the thickness of the wall
//line indicates the line that contains this obstacle
//id is self explanatory
//nxt is used by the linked list
struct Wall{
    int d;
    int h;
    int id;
    int line;

    Wall *nxt;
};
#endif
