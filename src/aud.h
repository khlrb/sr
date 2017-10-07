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

int read_aud_header(FILE*, AudHeader*);

int read_aud(FILE*, FILE*, AudHeader*);

int read_8bit_adpcm(FILE*, FILE*, AudHeader*);

#endif
