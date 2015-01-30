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
    const FONTCHARACTER filename[] = {'\\', '\\', 'f', 'l', 's', '0', '\\', 'S', 'H', 'C', '.', 's', 'a', 'v', 0};
    const filesize = sizeof(float) * 6;
    Game_Data data;
    int i;
    float buffer[6] = {0};
	// variables for fps calculation
    unsigned int fps = 0, frame = 0, tempsOrigine = RTC_GetTicks();
	// char string to display the fps
    unsigned char fps_text[8] = {0};
	// rand initialisation
    srand(RTC_GetTicks());

    // Key init
    data.shift_latch_value = 0;
    data.alpha_latch_value = 0;

    data.entry_highscores = NULL;
    data.entry_highscores = malloc(sizeof(float) * 6);
    if(data.entry_highscores == NULL)
        return 1;


    data.is_save_feature_enabled = 1;
    data.fileHandle = Bfile_OpenFile(filename, _OPENMODE_READ);
    if(data.fileHandle == IML_FILEERR_ENTRYNOTFOUND) {
        void;
    } else if(data.fileHandle>= 0) {
        if(Bfile_ReadFile(data.fileHandle, (char*)data.entry_highscores, filesize, -1) < 0)
            data.is_save_feature_enabled = 0;
        Bfile_CloseFile(data.fileHandle);
        Bfile_DeleteFile(filename);
    } else
    data.is_save_feature_enabled = 0;


    if(!data.is_save_feature_enabled){
        for(i = 0; i < 6; i++) {
            data.entry_highscores[i] = 0.0f;
        }
    }

    data.entry_difficulties = NULL;
    data.entry_difficulties = malloc(sizeof(char*) * 6);
    if(data.entry_difficulties == NULL)
        return 1;
    load_difficulty_names(data.entry_difficulties);


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

    if(data.is_save_feature_enabled) {
        Bfile_CreateFile(filename, filesize);
        data.fileHandle = Bfile_OpenFile(filename, _OPENMODE_WRITE);
        if(Bfile_WriteFile(data.fileHandle, (char*)data.entry_highscores, filesize) < 0) {
            int why;
            locate(1,1);
            Print("POURQUOI");
            GetKey(&why);
        }
        Bfile_CloseFile(data.fileHandle);
   }

    free(data.entry_highscores);

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

