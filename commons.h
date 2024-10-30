
#ifndef COMMONS_H
#define COMMONS_H

const String MENU[] = {"Pad", "Volume", "Equalization", "Fader In/Out (ms)"};

const String NOTES[] = {"A","A#","B","C","C#","D","D#","E","F","F#","G","G#"};
/****
Folder structure

01 - WorshipPadz
02 - ChurchFont Warm MP3
03 - MMQA Worship
04 - MPads Ambient
05 - MPads Hillsong
06 - ChurchFont WAV
*****/
const String PADS[] = {"WorshipPadz", "ChurchFont Warm", "MMQA Worship", "MPads Ambient", "MPads HillSong"};

int currentPad = 5;
int currentNote = 0;
int Fader = 50;
int currentVol = 20;

bool playing = false;


const int NUM_BUTTONS = 3;


#endif
