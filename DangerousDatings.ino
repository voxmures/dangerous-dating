/*
  DANGEROUS DATING
 
  Made by The Indie Juice: http://theindiejuice.com
 
  2018 - JOAQUÍN "金" CAMPOS

  Game License: MIT : https://opensource.org/licenses/MIT

  Story, characters, sprites, tiles, design and art: copyrighted to The Indie Juice
*/

#include "globals.h"
#include "transition.h"
#include "game.h"

typedef bool (*FunctionPointer) ();

const FunctionPointer PROGMEM mainGameLoop[] = {
  stateTransition,
  stateGamePlay,
};

void setup() {
  arduboy.begin();
  arduboy.setFrameRate(30);
  Serial.begin(9600); // DEBUG
}

void loop() {
  if (!(arduboy.nextFrame())) return;
  arduboy.pollButtons();

  if (((FunctionPointer) pgm_read_word(&mainGameLoop[gameState]))()) {
    gameState++;  // Next game state
  }
  
  arduboy.display();
}
