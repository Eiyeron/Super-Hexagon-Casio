#include "fxlib.h"
#include "MonochromeLib.h"
#include "math.h"
#include "ECode.h"
#include "struct.h"
#include "wall.h"
#include "syscall.h"
#include "states.h"

static const FONTCHARACTER filename[] = {'\\', '\\', 'f', 'l', 's', '0', '\\', 'S', 'H', 'C', '.', 's', 'a', 'v', 0};
static const unsigned int filesize = sizeof(SaveData);

void load_difficulty_names(char **str_list)
{
    char c_1[] = "Hard";
    char c_2[] = "Harder";
    char c_3[] = "Hardest";
    char c_4[] = "Hardester";
    char c_5[] = "Hardestest";
    char c_6[] = "Hardestestest";
    int i = 0;
    int j = 0;
    for(i = 0; i < 6; i++)
    {
        str_list[i] = NULL;
        str_list[i] = malloc(sizeof(char) * 24);
        if(str_list[i] == NULL)
            return;
        for(j = 0; j < 24; str_list[i][j] = 0, j++) {

        }
    }
    memcpy(str_list[0], c_1, sizeof(char) * strlen(c_1));
    memcpy(str_list[1], c_2, sizeof(char) * strlen(c_2));
    memcpy(str_list[2], c_3, sizeof(char) * strlen(c_3));
    memcpy(str_list[3], c_4, sizeof(char) * strlen(c_4));
    memcpy(str_list[4], c_5, sizeof(char) * strlen(c_5));
    memcpy(str_list[5], c_6, sizeof(char) * strlen(c_6));
}



void loadDataFromSave(Game_Data* data) {
    int i, hasLoadedSave;
    SaveData dataLoaded;
    hasLoadedSave = 0;
    data->fileHandle = Bfile_OpenFile(filename, _OPENMODE_READ);
    if(data->fileHandle>= 0) {
        hasLoadedSave = 1;
        //(char*)data->entry_highscores
        if(Bfile_ReadFile(data->fileHandle, &dataLoaded, sizeof(dataLoaded), -1) < sizeof(dataLoaded))
            hasLoadedSave = 0;
        else {
            Bfile_CloseFile(data->fileHandle);
            Bfile_DeleteFile(filename);
        }
    }

    if(!hasLoadedSave) {
        for(i = 0; i < 6; i++) {
            data->entry_highscores[i] = 0.0f;
        }
    } else {
        for(i = 0; i < 6; i++) {
            data->entry_highscores[i] = dataLoaded.highscores[i];
        }
    }

}

int AddIn_main(int isAppli, unsigned short OptionNum)
{
    SaveData dataToSave;
    int i;
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

    data.entry_highscores = NULL;
    data.entry_highscores = malloc(sizeof(float) * 6);
    if(data.entry_highscores == NULL)
        switch_to_state(OUT_OF_MEMORY, &data);


    data.entry_difficulties = NULL;
    data.entry_difficulties = malloc(sizeof(char*) * 6);
    if(data.entry_difficulties == NULL)
        switch_to_state(OUT_OF_MEMORY, &data);
    load_difficulty_names(data.entry_difficulties);


    loadDataFromSave(&data);
    switch_to_state(TITLE, &data);

    {
        char machin[] = "0";
        machin[0] = GetMPU() + '0';
        locate(1,1);
        Print(machin);
        GetKey(&i);

    }

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

    for(i = 0; i < 6; ++i)
        dataToSave.highscores[i] = data.entry_highscores[i];
    Bfile_CreateFile(filename, filesize);
    data.fileHandle = Bfile_OpenFile(filename, _OPENMODE_WRITE);
    if(data.fileHandle >= 0) {
        Bfile_WriteFile(data.fileHandle, &dataToSave, filesize);
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

