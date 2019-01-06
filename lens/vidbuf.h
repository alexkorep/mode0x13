#ifndef VIDBUF_H
#define VIDBUF_H

#include <string.h>
#include "cga.h"

const unsigned int BUFSIZE = 80*200;
unsigned char *buffer = new unsigned char[320*200];

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

unsigned char getBufferPixel(const int x, const int y) {
  const unsigned int byte = y*80 + x/4;
  if (byte >= BUFSIZE) {
    return 0;
  }

  const int offset = 6 - (x%4)*2; // shift by this positions, 0 or 2 or 4 or 6
  unsigned char c = buffer[byte];
  c = c >> offset;
  return c & 0x3;
}


void setScreenPixel(int x, int y, const unsigned char color) {
	int b, m; /* bits and mask */
	unsigned char far *p;
	unsigned char c;
	if (1 == (y & 0x1)) {
		p = (unsigned char far*)(0xB8002000L);
	} else {
		p = (unsigned char far*)(0xB8000000L);
	}
	y >>= 1;
	switch (x & 0x3) {
		case 0:
			b = 6;
			m = 0xC0;
			break;
		case 1:
			b = 4;
			m = 0x30;
			break;
		case 2:
			b = 2;
			m = 0x0C;
			break;
		case 3:
			b = 0;
			m = 0x03;
			break;
	}
	x >>= 2;
	p += ((80 * y) + x);
	c = *p;
	c = c & ~m;
	c = c | (color << b);
	*p = c;
}

void fillBuffer(const unsigned char color) {
  memset(buffer, color, BUFSIZE);
}

void flushBuffer(int lensX, int lensY,
                 int lensW, int lensH,
                 int shiftX, int shiftY) {
  for (unsigned int y = 0; y < 200; y++) {
    unsigned char far *p = (1 == (y & 0x1))
      ? (unsigned char far*)(0xB8002000L)
      : (unsigned char far*)(0xB8000000L);
    const unsigned int row = y/2;
    for (int x = 0; x < 320; x++) {
      int nx = x;
      int ny = y;
      if (x >= lensX - lensW && x <= lensX + lensW &&
          y >= lensY - lensH && y <= lensY + lensH) {
        ny = y + shiftY;
        nx = x + shiftX;
      }
      const unsigned char color = getBufferPixel(nx, ny);
      setScreenPixel(x, y, color);
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