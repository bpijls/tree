#ifndef _COLORMAP_H
#define _COLORMAP_H

class Colormap {
  private:
    uint32_t *colorArray = NULL;
    uint8_t nColors = 0;

  public:

    Colormap() {
    }

    void addColor(uint32_t newColor) {

      uint32_t *tempArray = new uint32_t[nColors + 1];
      for (int iColor = 0; iColor < nColors; iColor++)
        tempArray[iColor] = colorArray[iColor];

      tempArray[nColors] = newColor;
      nColors++;
      
      delete colorArray;
      colorArray = tempArray;
    }

    uint32_t getColor(float t) {
      if (nColors == 0) return 0;
      if (nColors == 1) return colorArray[0];

      float colorIndex = t * (nColors - 1);
      uint8_t startIndex = floor(colorIndex),
              endIndex = ceil(colorIndex);

      float tColor = colorIndex - startIndex;

      return lerpColor(tColor, colorArray[startIndex], colorArray[endIndex]);
    }
};

#endif
