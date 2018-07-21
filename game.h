#ifndef GAME_H
#define GAME_H

#include "globals.h"
#include "npcs.h"
#include "text.h"

uint8_t currentNPC = 0;  // Initial NPC
uint8_t currentDialog = 255;
byte startText = 0;
byte numTexts = 0;

// NPC_STATUS: 0B00000000
//                      └> BLINKING
byte NPC_STATUS = 0;
bool BLINK_STATUS = false;  // FALSE: Opening eyes; TRUE: Closing eyes
byte BLINK_FRAME = 0;

void updateNPC() {
  // BLINK UPDATE  
  if (arduboy.everyXFrames(2)) {
    if (NPC_STATUS & 0x01) {
      if (!BLINK_STATUS) 
        BLINK_FRAME++;
      else BLINK_FRAME--;
      
      if (BLINK_FRAME == 2)
        BLINK_STATUS = true;
      
      if (BLINK_FRAME == 0) {
        BLINK_STATUS = false;
        NPC_STATUS ^= 0x01;
      }
    }
  }

  if (arduboy.everyXFrames(60))
    NPC_STATUS ^= 0x01;
}

void renderNPC(uint8_t x, uint8_t y) {
  uint8_t index = pgm_read_byte(&npcData[currentNPC * 3 + 1]);
  drawCompressedWithMask(x, y, pgm_read_byte(&npcBitmaps[index * 2]), pgm_read_byte(&npcBitmaps[index * 2 + 1]));
  sprites.drawPlusMask(x + 18, y + 11, kyosukeEyes_plus_mask, BLINK_FRAME); // TODO: Get bitmap from NPC DATA
}

void updateDialog() {
  if (currentDialog == 255) {
    byte dialog = pgm_read_byte(&npcData[currentNPC * 3 + 2]);
    byte index = pgm_read_byte(&npcTexts[dialog]);
    currentDialog = dialog;
    startText = index;
    numTexts = pgm_read_byte(&npcTexts[dialog + 1]) - 1;
    
    loadText(startText);
  }
  
  if (checkWordCount() && arduboy.justPressed(B_BUTTON)) {
    if (numTexts > 0) {
      loadText(++startText);
      numTexts--;
    }
  } 
  else 
    updateWordCount(arduboy.justPressed(B_BUTTON));
}

void renderDialog() {
  drawBubble(0, 46);
  drawText(4, 48);
}

bool stateGamePlay() {
  arduboy.fillScreen(BLACK);
  
  updateNPC();
  renderNPC(0, 0);

  updateDialog();
  renderDialog();
}

#endif // GAME_H
