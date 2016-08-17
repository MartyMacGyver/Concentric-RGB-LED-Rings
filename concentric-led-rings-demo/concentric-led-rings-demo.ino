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

#define RING_DATA_PIN   D0
#define RING_PIXEL_TYPE WS2812B

const int MAX_INTENSITY = 8;
const int pixelCnt = 93;
const int rings[6][2] =
    {{ 0,  1},
     { 1,  8},
     { 9, 12},
     {21, 16},
     {37, 24},
     {61, 32}};

Adafruit_NeoPixel * full_ring;

void setup()
{
    full_ring = new Adafruit_NeoPixel(pixelCnt, RING_DATA_PIN, RING_PIXEL_TYPE);
    full_ring->begin();
    full_ring->show();
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
    for (int j = 0; j < reps; j++)
    {
        for (int i = 0; i < 32; i++)
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
}

void spiral1(int delayMS, int reps)
{
    for (int j = 0; j < reps; j++)
    {
        for (int i = 0; i < (pixelCnt*2-1)*3; i++)
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
}

void random1(int delayMS, int reps) {
    for (int j = 0; j < reps; j++)
    {
        for (int i = 0; i  < pixelCnt; i++)
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
}

void all_same(int delayMS, int col_R, int col_G, int col_B)
{
    for (int i = 0; i < pixelCnt; i++)
    {
        full_ring->setPixelColor(i, col_R, col_G, col_B, 0);
    }
    full_ring->show();
    delay(delayMS);
}
