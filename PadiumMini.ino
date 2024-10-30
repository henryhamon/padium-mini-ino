
#include <ezButton.h>

#include "commons.h"
#include "display.h"
#include "audio.h"

#define DEBOUNCE_TIME 50
#define PITCH_UP 7
#define PITCH_DOWN 5
#define ACTION 6

ezButton buttons[] = {PITCH_DOWN, ACTION, PITCH_UP};
const int BTN_DOWN = 0;
const int BTN_PLAY = 1;
const int BTN_UP = 2;


void onButtonPressed(int idxBtn)
{
    if (idxBtn == BTN_PLAY)
    {
        if (currentNotePlaying > -1) { // it's playing
            if (currentNotePlaying == selectedNote) {
                // stop
                Serial.println("stop");
                currentNotePlaying = -1;
                stopAudio();
            } else {
                // play
                Serial.println("play");
                currentNotePlaying = selectedNote;
                playAudio(currentPad + 1, currentNotePlaying + 1);
            }
        } else {
            // play
            Serial.println("play");
            currentNotePlaying = selectedNote;
            playAudio(currentPad + 1, currentNotePlaying + 1);
        }
        displayRefresh();
    } 

    if (idxBtn == BTN_DOWN) {
        if (selectedNote > 0) {
            selectedNote -= 1;
        } else {
            selectedNote = 11;
        }
        selectedNote = selectedNote % 12;
        Serial.print(NOTES[selectedNote]);
        Serial.println(" is Current Note ");
        Serial.print(selectedNote);
        Serial.println("");
        displayRefresh();
    }

    if (idxBtn == BTN_UP) {
        selectedNote += 1;
        selectedNote = selectedNote % 12;
        Serial.print(NOTES[selectedNote]);
        Serial.println(" is Current Note ");
        Serial.print(selectedNote);
        Serial.println("");
        displayRefresh();
    }
}

void footSetup()
{

    for (int i = 0; i < NUM_BUTTONS; i++)
    {
        buttons[i].setDebounceTime(DEBOUNCE_TIME);
    }
}

void footEvent()
{
    for (int i = 0; i < NUM_BUTTONS; i++)
    {
        buttons[i].loop();

        if (buttons[i].isPressed())
        {
            Serial.print(i);
            Serial.println(" Btn is pressed");
            onButtonPressed(i);
        }
    }
}


void setup() {
    Serial.begin(115200);
    Serial.println(F("Booting.."));
    displayInit();
    footSetup();
    audioInit();
}

void loop() {
    footEvent();
}
