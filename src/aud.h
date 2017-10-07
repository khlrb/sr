#ifndef AUD_H
#define AUD_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

typedef enum flags { USE_DPCM=0x01, USE_STEREO=0x04, USE_16BIT=0x10 } flag_t;

typedef struct {
  uint8_t  version;
  uint8_t  header_size;
  uint16_t sample_rate;
  uint8_t  flags;
  uint16_t size;
} AudHeader;

int read_aud_header(FILE* file, AudHeader* header) {
  int r = 0;
  uint8_t* mab   = malloc(3);
  uint8_t sol[] = { 's', 'o', 'l' };

  fscanf(file, "%hhu", &header->version);
  fscanf(file, "%hhu", &header->header_size);
  fscanf(file, "%hhu", sol);
  fscanf(file, "%o", &header->sample_rate);
  fscanf(file, "%hhu", &header->flags);
  fscanf(file, "%o", &header->size);

  if (memcpy(mab,sol,3) != 0) {
    r = -1;
  }

  free(mab);

  return r;
}

int read_aud(FILE* in, FILE* out, AudHeader* header) {
  
}
  
#endif
