#ifndef TEXT_H
#define TEXT_H

#include <Tinyfont.h>
#include "globals.h"
#include "dictionary.h"

#define BUBBLE_WIDTH  128
#define BUBBLE_HEIGHT 18
#define MAX_WORD_PER_LINE 24

Tinyfont tinyfont = Tinyfont(arduboy.sBuffer, Arduboy2::width(), Arduboy2::height());

unsigned char textBox[75];
byte wordCount = 0;

void loadText(byte index) {
  uint8_t start = pgm_read_byte(&sentences[index]);
  byte sentenceSize = pgm_read_byte(&library[start]);
  textBox[0] = sentenceSize;
  uint8_t i = 1;
  for (uint8_t j = start + 1; j < start + 1 + sentenceSize; j++) {
    textBox[i++] = pgm_read_byte(&library[j]);
  }

  wordCount = 0;  // Reset wordcount
}

void drawBubble(uint8_t x, uint8_t y) {
  arduboy.drawRoundRect(x, y, BUBBLE_WIDTH, BUBBLE_HEIGHT, 3);
}

void drawText(uint8_t ini_x, uint8_t ini_y) {
  uint8_t x = ini_x;
  uint8_t y = ini_y;
  for (uint8_t i = 0; i < wordCount; i++) {
    tinyfont.printChar(textBox[i + 1], x, y);

    if ((i + 1) % MAX_WORD_PER_LINE == 0) {
      x = ini_x;
      y += 5;
    }
    else x += 5;
  }
}

void updateWordCount(bool finish) {
  if (finish)
    wordCount = textBox[0];

  if (arduboy.everyXFrames(2) && wordCount < textBox[0])
    wordCount++;
}

bool checkWordCount() {
  return (wordCount == textBox[0]);
}

#endif // TEXT_H
