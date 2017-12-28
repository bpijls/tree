#ifndef _COLORMAPCYCLESTATE_H
#define _COLORMAPCYCLESTATE_H

#include "Colormap.h"

class ColormapCycleState : public DisplayState {
  public:

    Colormap colorMap;

    ColormapCycleState() {
      colorMap.addColor(0x00FF0000);
      colorMap.addColor(0x0000FF00);
      colorMap.addColor(0x000000FF);
    }

    void update(float dt) {
      float tColor = sin(frameCount / 500.0 * 2 * PI) / 2 + 0.5;
      uint32_t pixelColor = colorMap.getColor(tColor);
      arrayClearColor(pixelArray, pixelColor);
    }

};

#endif
