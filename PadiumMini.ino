
#include <ezButton.h>

#include "commons.h"
#include "display.h"

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
        if (playing) {
            // stop
            Serial.println("stop");
        } else {
            // play
            Serial.println("play");
        }
        playing = !playing;
    } 

    if (idxBtn == BTN_DOWN) {
        if (currentNote > 0) {
            currentNote -= 1;
        } else {
            currentNote = 11;
        }
        currentNote = currentNote % 12;
        Serial.print(NOTES[currentNote]);
        Serial.println(" is Current Note ");
        Serial.print(currentNote);
        Serial.println("");
        displayRefresh();
    }

    if (idxBtn == BTN_UP) {
        currentNote += 1;
        currentNote = currentNote % 12;
        Serial.print(NOTES[currentNote]);
        Serial.println(" is Current Note ");
        Serial.print(currentNote);
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
}

void loop() {
    footEvent();
}
