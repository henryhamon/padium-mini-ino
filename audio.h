#ifndef AUDIO_H
#define AUDIO_H

#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>
#include "duration.h"

#define AUDIO_RX 3
#define AUDIO_TX 4
//

SoftwareSerial softwareSerial(AUDIO_RX, AUDIO_TX); // RX, TX
DFRobotDFPlayerMini audioPlayer;


void audioInit() {
    softwareSerial.begin(9600);
    Serial.println();
    Serial.println(F("Audio player initialize..."));
    if (!audioPlayer.begin(softwareSerial))
    {
        Serial.println(F("Problems to initialize the audio module:"));
        Serial.println(F("- Is Module connected?"));
        Serial.println(F("- Has a SD card?"));
        while (true);
    }

    audioPlayer.setTimeOut(500); //  Timeout serial 500ms
    audioPlayer.volume(20);      //  Volume (de 0 até 30)
    audioPlayer.EQ(0);           //  Equalização normal
    
    Serial.println();
    Serial.println(F("Audio module works fine!"));
    //----Read imformation----
    Serial.println(F("MP3 state"));
    Serial.println(audioPlayer.readState()); //read mp3 state
    Serial.println(F("Current Volume"));
    Serial.println(audioPlayer.readVolume()); //read current volume
    Serial.println(F("Equalization"));
    Serial.println(audioPlayer.readEQ()); //read EQ setting
    Serial.println(F("Read all file counts in SD card"));
    Serial.println(audioPlayer.readFileCounts(DFPLAYER_DEVICE_SD)); //read all file counts in SD card
}

void playAudio(int folder, int file) {
    audioPlayer.playFolder( folder, file);
    audioPlayer.start();
    audioPlayer.volume(0);

    Timer fadeTimer = initTimer(Fader);
    int step = currentVol / (Fader/10); // Calcula o incremento por passo
    if (step == 0) step = 1;
    int wait = Fader / step;
    int volume = 0;
    while(timeNotExpired(fadeTimer) && volume < currentVol) {
        audioPlayer.volume(volume);
        volume += step;
        delay(wait);
    }
    audioPlayer.volume(currentVol); // Garante que chegue no volume final
}

void stopAudio() {
    audioPlayer.volume(currentVol);
    Timer fadeTimer = initTimer(Fader);
    int step = currentVol / (Fader/10); // Calcula o incremento por passo
    if (step == 0) step = 1;
    int wait = (Fader / step) + 10;
    int volume = currentVol;
    while(timeNotExpired(fadeTimer) && volume > 0) {
        audioPlayer.volume(volume);
        volume -= step;
        delay(wait);
    }
    audioPlayer.volume(0); // Garante que chegue no volume final
    audioPlayer.stop();
}

#endif

