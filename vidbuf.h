#ifndef VIDBUF_H
#define VIDBUF_H

#include <string.h>
#include "cga.h"

const unsigned int BUFSIZE = 80*200;
unsigned char *buffer = new unsigned char[BUFSIZE];

void setBufferPixel(const int x, const int y, const unsigned char color) {
  const unsigned int byte = y*80 + x/4;
  if (byte >= BUFSIZE) {
    return;
  }

  const int offset = 6 - (x%4)*2; // shift by this positions, 0 or 2 or 4 or 6
  const char m = 0x3 << offset; // 00000011 or 00001100 or 00110000 or 11000000
  unsigned char c = buffer[byte];
  c = c & ~m;
  c = c | (color << offset);
  buffer[byte] = c;
}

void fillBuffer(const unsigned char color) {
  memset(buffer, color, BUFSIZE);
}

void flushBuffer() {
  for (unsigned int y = 0; y < 200; y++) {
    unsigned char far *p = (1 == (y & 0x1))
      ? (char far*)(0xB8002000L)
      : (char far*)(0xB8000000L);
    const unsigned int row = y/2;
    _fmemcpy((void far*)(p + 80*row),
             (const void far*)(buffer + y*80),
             80);
  }
}

void swap(float* a, float* b) {
  float tmp = *a;
  *a = *b;
  *b = tmp;
}

void line(float x1, float y1, float x2, float y2, const int color )
{
  // Bresenham's line algorithm
  const char steep = (fabs(y2 - y1) > fabs(x2 - x1));
  if (steep) {
    swap(&x1, &y1);
    swap(&x2, &y2);
  }
  if(x1 > x2) {
    swap(&x1, &x2);
    swap(&y1, &y2);
  }

  const float dx = x2 - x1;
  const float dy = fabs(y2 - y1);

  float error = dx / 2.0f;
  const int ystep = (y1 < y2) ? 1 : -1;
  int y = (int)y1;

  const int maxX = (int)x2;

  for(int x=(int)x1; x<maxX; x++) {
    if (steep) {
      setBufferPixel(y, x, color);
    } else {
      setBufferPixel(x, y, color);
    }

    error -= dy;
    if (error < 0) {
      y += ystep;
      error += dx;
    }
  }
}

#endif