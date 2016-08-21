//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// Concentric RGB LED rings demo
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
/*
    Copyright (c) 2016 Martin F. Falatic
    
    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at
    
        http://www.apache.org/licenses/LICENSE-2.0
    
    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#include "application.h"

#include "neopixel/neopixel.h"  // LGPL

const uint16_t RING_PIXEL_TYPE = WS2812B;
const uint8_t pixelRingDataPin = D6;
const uint8_t button1Pin = A1;
const uint16_t pixelCnt = 93;
const int MAX_INTENSITY = 8;

const int rings[6][2] =
    {{ 0,  1},
     { 1,  8},
     { 9, 12},
     {21, 16},
     {37, 24},
     {61, 32}};

Adafruit_NeoPixel * full_ring;
volatile bool button1Pressed = false;
int debounceWindow = 100;
int ignoreWindow = 1000;

void INT_button1()
{
    volatile static unsigned long tIgnorePrev = 0;
    unsigned long tIgnoreCurr = millis();
    volatile static unsigned long tDebouncePrev = 0;
    unsigned long tDebounceCurr = millis();
    if (tIgnoreCurr - tIgnorePrev > ignoreWindow) {
        if (tDebounceCurr - tDebouncePrev > debounceWindow) {
            button1Pressed = true;
            tIgnorePrev = tIgnoreCurr;
        }
    }
    tDebouncePrev = tDebounceCurr;
}

void setup()
{
    full_ring = new Adafruit_NeoPixel(pixelCnt, pixelRingDataPin, RING_PIXEL_TYPE);
    full_ring->begin();
    full_ring->show();

    pinMode(button1Pin, INPUT_PULLUP);
    attachInterrupt(button1Pin, INT_button1, FALLING);
}


void loop()
{
    clockwork1(15, 10);
    spiral1(15, 10);
    random1(100, 64);
    all_same(1000, 0, 0, 0);
}


void clockwork1(int delayMS, int reps)
{
    for (int j = 0; j < reps && !button1Pressed; j++)
    {
        for (int i = 0; i < 32 && !button1Pressed; i++)
        {
            full_ring->clear();
            for (int k = 0; k < 6; k++)
            {
                full_ring->setPixelColor(
                    rings[k][0]+i*rings[k][1]/32,
                    random(MAX_INTENSITY),
                    random(MAX_INTENSITY),
                    random(MAX_INTENSITY),
                    random(0));
            }
            full_ring->show();
            delay(delayMS);
        }
    }
    if (button1Pressed) { delay(200); button1Pressed = false; }
}


void spiral1(int delayMS, int reps)
{
    for (int j = 0; j < reps && !button1Pressed; j++)
    {
        for (int i = 0; i < (pixelCnt*2-1)*3 && !button1Pressed; i++)
        {
            full_ring->clear();
            full_ring->setPixelColor(
                abs(((i + (pixelCnt-1)) % ((pixelCnt-1)*2)) - (pixelCnt-1)),
                random(MAX_INTENSITY),
                random(MAX_INTENSITY),
                random(MAX_INTENSITY),
                random(0));
            full_ring->show();
            delay(delayMS);
        }
    }
    if (button1Pressed) { delay(200); button1Pressed = false; }
}


void random1(int delayMS, int reps) {
    for (int j = 0; j < reps && !button1Pressed; j++)
    {
        for (int i = 0; i < pixelCnt && !button1Pressed; i++)
        {
            full_ring->setPixelColor(
                i,
                random(MAX_INTENSITY),
                random(MAX_INTENSITY),
                random(MAX_INTENSITY),
                random(0));
        }
        full_ring->show();
        delay(delayMS);
    }
    if (button1Pressed) { delay(200); button1Pressed = false; }
}


void all_same(int delayMS, int col_R, int col_G, int col_B)
{
    for (int i = 0; i < pixelCnt; i++)
    {
        full_ring->setPixelColor(i, col_R, col_G, col_B, 0);
    }
    full_ring->show();
    delay(delayMS);
    if (button1Pressed) { delay(200); button1Pressed = false; }
}
