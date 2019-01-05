#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// #include <conio.h>
#include "cga.h"
#include "keyb.h"
#include "vidbuf.h"
#include <iostream.h>

void fill(unsigned char color) {
  unsigned char far *p1 = (char far*)(0xB8000000L);
  unsigned char far *p2 = (char far*)(0xB8002000L);
  for (int i = 0; i < 80*100; i++) {
    p1[i] = color;
    p2[i] = color;
  }
}

int main (void)
{
  if (!buffer) {
    printf("Video buffer is not initialized");
    return 1;
  }

  cgaInit();
  // for (unsigned int x = 0; x < 320; x++) {
  //   for (unsigned int y = 0; y < 200; y++) {
  //     //cgaPlot(x, y, color);
  //     unsigned int idx = x + y*320;
  //     const char color = buffer[idx];
  //     "1" >> cout;
  //   }
  //  }
  //printf("Hello!");

  // 00 00 00 00
  //  6  4  2  0
  // unsigned char c = 0;
  // for (int i = 0; i < 100; i++) {
  //   c = random(3) + 1;
  //   fill(c + c*2 + c*4 + c*6);
  // }

  unsigned char c = 0;
  do {
    for (int i = 0; i < 4; i++) {
      c = i%4;//random(4);
      fillBuffer(c + (c<<2) + (c<<4) + (c<<6));
      flushBuffer();
    }
    // printf("%u\n", c);

    // for (int i = 0; i > 1000; i++) {
    //   line(random(320), random(200),
    //       random(320), random(200), 1 + random(3));
    // }
    // Exit on ESC
    if (read_scancode() == 1) return 0;
  } while (1);
}