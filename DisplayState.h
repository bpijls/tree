#ifndef _DISPLAYSTATE_H
#define _DISPLAYSTATE_H

#define NPIXELS 140

#include "rgb_util.h"

class DisplayState {
  public:

    static uint32_t frameCount;
    static uint32_t *pixelArray;
    static Adafruit_NeoPixel strip;
    static uint8_t brightness;
    
    DisplayState() {
    }

    virtual void update(float dt) {}

    void showPixelArray() {
      DisplayState::strip.setBrightness(brightness);
      for (uint16_t iPixel = 0; iPixel < NPIXELS; iPixel++) {
        uint8_t red = getRed(pixelArray[iPixel]),
                green = getGreen(pixelArray[iPixel]),
                blue = getBlue(pixelArray[iPixel]);

        //        strip.setPixelColor(iPixel,
        //                            pgm_read_byte(&gamma8[red]),
        //                            pgm_read_byte(&gamma8[green]),
        //                            pgm_read_byte(&gamma8[blue]));
        strip.setPixelColor(iPixel, pixelArray[iPixel]);

      }

      strip.show();
      frameCount++;
    }

};

uint32_t DisplayState :: frameCount = 0;
uint32_t * DisplayState :: pixelArray = new uint32_t[NPIXELS];
Adafruit_NeoPixel DisplayState :: strip  = Adafruit_NeoPixel(NPIXELS, D1, NEO_GRB + NEO_KHZ800);
uint8_t DisplayState :: brightness = 100;
#endif
