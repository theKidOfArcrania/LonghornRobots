#include "pitches.h"
#include "Mirobot.h"
void boomBox(int *notes, double *noteLength)
{
	int control = 1;
	int index = 0;
	
	while(control)
	{
		if(notes[index] != 0)
		{
			tone(SPEAKER_PIN, notes[index], 1000*noteLength[index]);
		}
		
		delay(1000*noteLength[index]);
	}
}

void play_DeepInTheHeart(){
	/*
    2/4 F major
    Deep In The Heart
    C .5 -----F 1 F 1 ----- A 1.5 C .5 ----- F 1 F 1 ----- A .5 Rest 1.5
    ----- Rest .5 C5 .5 c5 .5 c5 .5 ----- C 1.5 D .5 ----- A .5 G 1.5+ -----
    G +1.5 C3 .5 ~~Melody Next~~
    */

    /*
    tone(pin, freq, duration)
    Need to wait after????
    */

    int notes[16] = {NOTE_C4,
       NOTE_F4, NOTE_F4,
        NOTE_A4, NOTE_C4,
        NOTE_F4, NOTE_F4,
        NOTE_A4, 0,
        NOTE_C5, NOTE_C5, 
        NOTE_C5,
        NOTE_C4, NOTE_D4,
        NOTE_A4, NOTE_G4};
    double length[16] = {.5,
        1, 1,
        1.5, .5,
        1, 1,
        .5, 2.5,
        .5, .5,
        .5, 1.5,
        .5, .5,
        3};



    boomBox(notes, length);
}

void play_ZombieNation(){
	/*
    4/4 C major
    Zombie Nation
    */

    int notes[18] = {0, NOTE_A4,
        NOTE_C5, NOTE_D5, 
        NOTE_E5, NOTE_A4,
        0, NOTE_A4,
        NOTE_C5, NOTE_D5, 
        NOTE_E5, NOTE_F5,
        NOTE_E5, NOTE_C5,
        NOTE_D5, NOTE_C5,
        NOTE_E5, NOTE_A4};
    double length[18] = {.5,
       .5, .5,
        .5, .5,
        1.5, .5,
        .5, .5,
        .5, .5,
        .5, .5,
        .5, 2,
        1, .5,
        4.5};

    boomBox(notes, length);
}
