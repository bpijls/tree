#ifndef _RGB_UTIL_H
#define _RGB_UTIL_H

#include "DisplayState.h"
#include "gamma.h"

#define getRed(a) ((a & 0x00FF0000) >> 16)
#define getGreen(a) ((a & 0x0000FF00) >> 8)
#define getBlue(a) (a & 0x000000FF)
#define color(r, g, b) (((int)r << 16) | ((int)g << 8) | ((int)b << 0))

void arrayClearColor(uint32_t *pixelArray, uint32_t pixelColor) {
  for (uint16_t iPixel = 0; iPixel < NPIXELS; iPixel++)
    pixelArray[iPixel] = pixelColor;
}

uint32_t wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

uint32_t lerpColor(float t, uint32_t sourceColor, uint32_t targetColor) {
  int16_t sr = getRed(sourceColor),
          sg = getGreen(sourceColor),
          sb = getBlue(sourceColor),
          tr = getRed(targetColor),
          tg = getGreen(targetColor),
          tb = getBlue(targetColor);

  return color((uint8_t)constrain(sr + t * (tr - sr), 0, 255),
               (uint8_t)constrain(sg + t * (tg - sg), 0, 255),
               (uint8_t)constrain(sb + t * (tb - sb), 0, 255));
}

void rainbowCycle(uint32_t *pixelArray, uint16_t j, float spectralCoverage) {
  uint16_t i;
  for (i = 0; i < NPIXELS; i++) {
    pixelArray[i] =  wheel((byte)(spectralCoverage * ((i * 256 / NPIXELS) + j)));
  }
}
#endif
