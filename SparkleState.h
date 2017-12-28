#ifndef _SPARKLESTATE_H
#define _SPARKLESTATE_H

#include "DisplayState.h"
#include "SpringyValue.h"
#include "Colormap.h"

class SparkleState : public DisplayState {

  private:
    Colormap colorMap;
    SpringyValue springs[NPIXELS];
    uint16_t sparkleRate = 8;    

  public:

    SparkleState() {      
      colorMap.addColor(0x00883300);
      colorMap.addColor(0x00AA3300);
      colorMap.addColor(0x00CCEE00);      
      colorMap.addColor(0x007777AA);
    }

    void update(float dt) {

      if ((frameCount % sparkleRate) == 0) {
        uint8_t pixelIndex = random(0, NPIXELS);
        springs[pixelIndex].c = random(1, 10);
        springs[pixelIndex].k = random(1.1, 2);
        springs[pixelIndex].perturb(200.0);
      }

      for (int iPixel = 0; iPixel < NPIXELS; iPixel++) {
        springs[iPixel].update(dt);
        float springValue = abs(springs[iPixel].x);
        uint32_t pixelColor = colorMap.getColor(springValue / 200.0);        
        pixelArray[iPixel] = pixelColor;
      }
    }
};

#endif
