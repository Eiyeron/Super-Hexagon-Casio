#include "fxlib.h"
#include "MonochromeLib.h"
#include "math.h"
#include "ECode.h"
#include "struct.h"
#include "wall.h"
#include "syscall.h"
#include "states.h"

int AddIn_main(int isAppli, unsigned short OptionNum)
{
    Game_Data data;
	// variables for fps calculation
    unsigned int fps = 0, frame = 0, tempsOrigine = RTC_GetTicks();
	// char string to display the fps
    unsigned char fps_text[8] = {0};
	// rand initialisation
    srand(RTC_GetTicks());

    // Key init
    data.shift_latch_value = 0;
    data.alpha_latch_value = 0;
    data.are_entries_loaded = 0;

    switch_to_state(TITLE, &data);


    while(KeyUp(K_EXIT)){ // main loop
        // fps
        if(RTC_GetTicks() - tempsOrigine >= 32 )// if 1/4 seconds elapsed
        {
            fps = frame*4;
            frame = 0;
            tempsOrigine = RTC_GetTicks();
        }
        frame++;


        update(&data);
        draw(&data);

	// printing debug information

	// updating the screen
        ML_display_vram();
        ML_clear_vram();

        Sleep(1/0.06);
    }

    return 1;
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

