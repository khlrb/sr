#include "aud.h"

uint8_t SOL3[] = { 0, 1, 2, 3, 6, 0xA, 0xF, 0x15 };


int read_aud_header(FILE* in, AudHeader* header) {
  int r = 0;
  uint8_t* mab   = malloc(4);
  uint8_t sol[] = { 's', 'o', 'l', '\0' };

  fread(&header->version, sizeof(uint8_t), 1, in);
  fread(&header->header_size, sizeof(uint8_t), 1, in);
  fread(mab, sizeof(uint8_t), 4, in);
  fread(&header->sample_rate, sizeof(uint16_t), 1, in);
  fread(&header->flags, sizeof(uint8_t), 1, in);
  fread(&header->size, sizeof(uint16_t), 1, in);

  if (memcpy(mab,sol,4) != 0) {
    r = -1;
  }

  free(mab);

  return r;
}

int read_aud(FILE* in, FILE* out, AudHeader* header) {
  return 0;
}

int read_8bit_adpcm(FILE* in, FILE* out, AudHeader* header) {
  uint8_t current = 0x80;
  uint8_t buff = 0;
  uint8_t t = 0;

  for(uint16_t i = 0; i < header->size; ++i) {
    fread(&buff, sizeof(uint8_t), 1, in);

    t = buff >> 4;

    if (t & 8)
      current -= SOL3[0xf-t];
    else
      current += SOL3[t];

    fwrite(&current, sizeof(uint8_t), 1, out);

    t = buff & 0x0f;

    if (t & 8)
      current -= SOL3[0xf-t];
    else
      current += SOL3[t];

    fwrite(&current, sizeof(uint8_t), 1, out);
  }

  return 0;
}

