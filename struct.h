#ifndef STRUCT_H
#define STRUCT_H

#define PI 3.14159265
#define SIN_60 0.866025404
#define COS_60 0.5
#define abs(x) x>0 ? x : -x
#define true 1
#define false 0
#define bool unsigned char

typedef struct Camera Camera;
typedef struct Wall Wall;
typedef struct Line Line;

struct Camera{
    int cX;
    int cY;
    int angle;
};

struct Wall{
    int d;
    int h;
    int id;
    int line;

    Wall *nxt;
};

struct Line{
    int id;
    Wall *list;
    int angle;
};
#endif