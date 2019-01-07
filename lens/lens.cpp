// Inspired by https://www.shadertoy.com/view/3sfGzB
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <iostream.h>
#include "vga.h"
#include "keyb.h"
#include "vidbuf.h"
#include "cat.h"

void randomLines() {
  for (int i = 0; i < 200; i++) {
    line(rand()%320, rand()%200,
         rand()%320, rand()%200, 1 + rand()%255);
  }
}

void drawCat() {
  outp(0x03c8, 0);
  for (int i = 0; i < 256; i++) {
    outp(0x03c9, picMap[i*4 + 0]/4);
    outp(0x03c9, picMap[i*4 + 1]/4);
    outp(0x03c9, picMap[i*4 + 2]/4);
  }

  for (unsigned int y = 0; y < 200; y++) {
    for (int x = 0; x < 320; x++) {
      buffer[x + y*320] = picMap[256*4 + x + y*320];
    }
  }
}

int main (void)
{
  if (!buffer) {
    printf("Video buffer is not initialized");
    return 1;
  }

  vgaInit();
  fillBuffer(0);
  drawCat();

  float an1 = 0;
  float an2 = 0;
  const int radx = 40;
  const int rady = 40;
  do {
    flushBuffer(160 + cos(an1)*radx,
                100 + sin(an2)*rady,
                60, 60, -8, -8);
    an1 += 0.07;
    an2 += 0.13;
    // Exit on ESC
    if (read_scancode() == 1) return 0;
  } while (1);
}
