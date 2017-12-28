#ifndef _RAINBOWSTATE_H
#define _RAINBOWSTATE_H

class RainbowState : public DisplayState {
  public:
    RainbowState() {

    }

    void update(float dt) {
      uint8_t hue = (frameCount/2) % 256;
      rainbowCycle(pixelArray, frameCount/2, 2.0);
    }
};

#endif
