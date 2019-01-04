#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "cga.h"

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
      cgaPlot(y, x, color);
    } else {
      cgaPlot(x, y, color);
    }

    error -= dy;
    if (error < 0) {
      y += ystep;
      error += dx;
    }
  }
}

int main (void)
{
  cgaInit();

  for (int i = 0; i < 1000; i++) {
    line(random(320), random(200),
         random(320), random(200), 1 + random(3));
  }

  getchar ();
  return 0;
}