#include "fxlib.h"
#include "MonochromeLib.h"
#include "math.h"
#include "ECode.h"
#include "stdlib.h"
#include "struct.h"
#include "wall.h"
#include "syscall.h"

#define FPS 60
//duration of a frame
#define FRAME_TIME 1/FPS

//oriented angle between the player and the horizontal axis
int player_angle=0;

Camera cam = {64, 32, 0, 0, 0};

//linked list of obstacles
//at the moment, there is only a list, but at term, we should be using the lists from the Line struct. (And thus remove the "line" member from the Wall struct
Wall *list = NULL;

//delta angle: defines the 'speed' of the camera

//function prototypes
//draws the player
void drawPlayer();
//draws one of the lines (from 0 to 2)
void drawDiagonal(int nb);

void updateCamera(Camera *cam, unsigned int delta_time);

int AddIn_main(int isAppli, unsigned short OptionNum)
{
    unsigned int start_time = RTC_GetTicks(); //1 tick == 1/128 second
    unsigned int last_time = 0;
    unsigned int current_time = RTC_GetTicks();
	//variables for fps calculation
    unsigned int fps = 0, frame = 0, tempsOrigine = RTC_GetTicks();
	//char string to display the fps
    unsigned char fps_text[8] = {0};
	//rand initialisation
    srand(RTC_GetTicks());

    //list = addWall(list, 128, 8, 1, 1);

    while(KeyUp(K_EXIT)){ //main loop
    	last_time = current_time;
	current_time = RTC_GetTicks();
        //fps
        if(RTC_GetTicks() - tempsOrigine >= 32 )//if 1/4 seconds elapsed
        {
            fps = frame*4;
            frame = 0;
            tempsOrigine = RTC_GetTicks();
        }
        frame++;
	
        if(list != NULL){ //if the linked list is not empty
            update(list, current_time - last_time); //update the linked list

        if(isColliding(list, player_angle) == true) //if the player and a wall collide
     	{
            PrintMini(50, 0, "TOUCHE", MINI_OVER); //death handling
        }
            list = removeWall(list, 0); //remove every wall whose distance to the center equals zero

        }
	//level generation
	//TODO: something else than pure randomness
        if(rand() % 40 == 1)//
        {
            list = addWall(list, 128, 8, 1, rand()%6);
        }else if(rand() % 70 == 1)
        {
            int emptyRow = rand()%6;
            int i = 0;
            for(i = 0; i < 6; i++)
                if(i != emptyRow)
                    list = addWall(list, 128, 15, 1, i);
        }
	//draw the player and the lines
        drawPlayer();
        drawDiagonal(1);
        drawDiagonal(2);
        drawDiagonal(3);

	//printing debug information
        intToStr(fps_text, fps);
        PrintMini(0, 0, fps_text, MINI_OVER);
        intToStr(fps_text, player_angle);
        PrintMini(116, 0, fps_text, MINI_OVER);

	//showing the walls
        if(list != NULL)
            show(list, &cam);
    	
	//updating the screen
        ML_display_vram();
        ML_clear_vram();

	//player input
	//TODO: no magic values
        if(KeyDown(K_LEFT))
        {
            player_angle-=15;
        }
        if(KeyDown(K_RIGHT))
        {
            player_angle+=15;
        }

	updateCamera(&cam, current_time - last_time);
	//manually change the rotation speed
	//TODO: automatize this
/*        if(KeyDown(K_PLUS))
        {
            dAngle += 0.2;
        }
        if(KeyDown(K_MINUS))
        {
            dAngle -= 0.2;
        }
*/
	//the angle must not be greater than 360
        if(player_angle < 0)
            player_angle = 360 + player_angle;
        player_angle = player_angle % 360;

        if(player_angle > 360)
        {
            while(KeyUp(K_EXE))
            {}
        }
        //while
	//pause
        Sleep(1/0.06);
    }

    return 1;
}

void updateCamera(Camera *cam, unsigned int delta_time){
	cam->acceleration += 0.25 / 2 - rand() / 4; //between -0.25 and 0.25, perfect.
	if(cam->acceleration > 0.5)
		cam->acceleration = 0.5;
	else if(cam->acceleration < -0.5)
		cam->acceleration = -0.5;
	cam->speed += 0.5 * cam->acceleration * delta_time / 2;
	cam->angle += cam->speed;

	if(cam->angle >= 360)
		cam->angle -= 359;


}
//draws the player
//at first, was supposed to draw an hexagon in the center, plus a triangle to show the player,
//but the hexagon was not visible, and it was a pixel mess, so we're showing a circle instead.
//there is still for code to calculate the vertices of the hexagon, in case we want to change that again
void drawPlayer()
{
/*    int x[6];
    int y[6];
    int i = 0;

    for(i = 0; i++; i != 6)
    {
        int angle = i *60;
        x[i] = 16*cos(PI*angle/180) + cam.cX;
        y[i] = 16*sin(PI*angle/180) + cam.cY;
    }
*/
	//draw the aforementionned circle, depending on the camera's center
    ML_filled_circle(cam.cX, cam.cY, 6, BLACK);
	//draw the player. At such a low scale, it was impossible to draw a rotating triangle, so its a radius 1 circle instead.
    ML_filled_circle(9*cos( PI*(player_angle + cam.angle)/180) + cam.cX, 9*sin( PI*(player_angle+cam.angle)/180) + cam.cY, 1, BLACK);
    
}

//draws one of the three rotating lines
void drawDiagonal(int nb)
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

#pragma section _BR_Size
unsigned long BR_Size;
#pragma section
#pragma section _TOP
int InitializeSystem(int isAppli, unsigned short OptionNum)
{
    return INIT_ADDIN_APPLICATION(isAppli, OptionNum);
}
#pragma section

