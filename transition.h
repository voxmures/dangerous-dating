#ifndef TRANSITION_H
#define TRANSITION_H

#include "globals.h"

byte transitionMap[4] = {
  0b00000000,
  0b00010000,
  0b00000000,
  0b00000000
};

uint8_t transitionFrame = 1;
bool transitionDecrease = false;

void updateTransition() {
  if (arduboy.everyXFrames(2)) {
    if (!transitionDecrease)
      transitionFrame++;
    else
      transitionFrame--;
      
    if (transitionFrame == 32)
      transitionDecrease = true;
  }
}

void renderTransition() {
  arduboy.fillScreen(BLACK);

  uint8_t tempFrame = transitionFrame;
  for (uint8_t i = 0; i < 4; i++) {
    if (tempFrame == 0)
      return;
            
    byte row = transitionMap[i];
    uint8_t rowFrame = tempFrame;

    byte mask = 0b10000000;
    for (uint8_t j = 0; j < 8; j++) {
      if (rowFrame == 0)
        continue;
        
      sprites.drawPlusMask(j * 16, i * 16, (row & mask) ? skullTransition_plus_mask : heartTransition_plus_mask, min(rowFrame - 1, 5));
      mask = mask >> 1;
      rowFrame--;
    }
    tempFrame--;
  }
}

bool stateTransition() {
  if(transitionFrame == 0)
    return true;

  updateTransition();
  renderTransition();
}

#endif // TRANSITION_H
