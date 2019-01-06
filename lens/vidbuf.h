#ifndef VIDBUF_H
#define VIDBUF_H

#include <string.h>
#include "vga.h"

const unsigned int BUFSIZE = 320*200;
unsigned char *buffer = new unsigned char[BUFSIZE];

void setBufferPixel(const int x, const int y, const unsigned char color) {
  buffer[y*320+x] = color;
}

unsigned char getBufferPixel(const int x, const int y) {
  return buffer[y*320+x];
}

void fillBuffer(const unsigned char color) {
  memset(buffer, color, BUFSIZE);
}

unsigned char getLensBufferPixel(const int x, const int y,
                                 int lensX, int lensY,
                                 int lensW, int lensH,
                                 int shiftX, int shiftY) {
  int nx = x;
  int ny = y;
  long int xs = x - lensX;
  long int ys = y - lensY;
  long int rs = lensW*lensH;
  if (xs*xs + ys*ys < rs) {
    ny = y + shiftY;
    nx = x + shiftX;
  }
  return getBufferPixel(nx, ny);
}


void flushBuffer(int lensX, int lensY,
                 int lensW, int lensH,
                 int shiftX, int shiftY) {
  unsigned char far *p = (unsigned char far*)(0xA0000000L);
  //memcpy(p, buffer, BUFSIZE);
  for (unsigned int y = 0; y < 200; y++) {
    for (int x = 0; x < 320; x++) {
      const unsigned char color = getLensBufferPixel(x, y,
        lensX, lensY, lensW, lensH, shiftX, shiftY);
      p[x + y*320] = color;
    }
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