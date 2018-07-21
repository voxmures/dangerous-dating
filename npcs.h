#ifndef NPCS_H
#define NPCS_H

const uint8_t* const PROGMEM npcBitmaps[] = {
  npc_head_00, npc_head_00_mask,
};

const char PROGMEM npcNames[] = {
  7,
  'K', 'Y', 'O', 'S', 'U', 'K', 'E', 
};

// NPC TEXTS: (START INDEX, NUM SENTENCES)
const byte PROGMEM npcTexts[] = {
  0, 3
};

// NPC DATA: (NAME INDEX, BITMAP INDEX, TEXTS INDEX)
const byte PROGMEM npcData[] = {
  0, 0, 0
};

#endif // NPCS_H
