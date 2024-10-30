#ifndef DISPLAY_H
#define DISPLAY_H

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <gfxfont.h>
#include "Adafruit_GC9A01A.h"

#define TFT_DC 9
#define TFT_CS 10
#define TFT_RST 8

//
// create an instance of the library
Adafruit_GC9A01A display (TFT_CS, TFT_DC);

const int center_x = 120;// center x of dial on 240*240 TFT display
const int center_y = 120;// center y of dial on 240*240 TFT display
int x_pos;
int y_pos; 

void drawCentreString(const String &buf, int x, int y)
{
    int16_t x1, y1;
    uint16_t w, h;
   // display.setTextWrap(true,true);
    display.getTextBounds(buf, x, y, &x1, &y1, &w, &h); //calc width of new string
    display.setCursor(x - w / 2, y);
    display.print(buf);
}

void displayRefresh()
{
    display.fillScreen(GC9A01A_BLACK);
    if (currentNotePlaying > -1) { // it's playing
        display.setTextColor(GC9A01A_YELLOW);
        display.setTextSize(10);
        drawCentreString(NOTES[currentNotePlaying], center_x, 30);
    }
    display.setTextColor(GC9A01A_WHITE);
    display.setTextSize(2);
    drawCentreString(PADS[currentPad], center_x + 10, center_y);
    display.setTextColor(GC9A01A_RED);
    display.setTextSize(7);
    drawCentreString(">_" + NOTES[selectedNote] + "_<", center_x, center_y + 30);
}

void displayBoot() {
    display.fillScreen(GC9A01A_BLUE);
    display.setTextColor(GC9A01A_WHITE);
    display.setTextSize(5);
    drawCentreString("Padium", 140, 75);
    drawCentreString("Mini", center_x, 150);
    delay(2000);
    displayRefresh();
}

void displayInit() {
    display.begin();
    display.setRotation(0);
    displayBoot();
}

#endif

