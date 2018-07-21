#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduboy2.h>
#include "bitmaps.h"

// make an instance of arduboy used for many functions
Arduboy2 arduboy;
SpritesB sprites;

#define STATE_TRANSITION  0 // stateTransition
#define STATE_GAME_PLAY   1 // stateGamePlay

byte gameState = STATE_TRANSITION;  // Initial game state

void drawCompressedWithMask(uint8_t x, uint8_t y, const uint8_t* bitmap, const uint8_t* mask) {
  arduboy.drawCompressed(x, y, mask, BLACK);
  arduboy.drawCompressed(x, y, bitmap, WHITE);
}

#endif // GLOBALS_H
