// Inspired by https://www.shadertoy.com/view/3sfGzB
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "cga.h"
#include "keyb.h"
#include "vidbuf.h"
#include <iostream.h>

void randomLines() {
  for (int i = 0; i < 100; i++) {
    line(rand()%320, rand()%200,
         rand()%320, rand()%200, 1 + rand()%3);
  }
}

int main (void)
{
  if (!buffer) {
    printf("Video buffer is not initialized");
    return 1;
  }

  cgaInit();
  fillBuffer(0);
  randomLines();

  float angle = 0;
  const int radx = 40;
  const int rady = 40;
  do {

    flushBuffer(160 + cos(angle)*radx,
                100 + sin(angle)*rady,
                40, 40, -5, -5);
    angle += 0.01;
    // Exit on ESC
    if (read_scancode() == 1) return 0;
  } while (1);
}