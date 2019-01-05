#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include "cga.h"
#include "keyb.h"
#include<iostream.h>


int main (void)
{
  cgaInit();

  do {
    line(random(320), random(200),
         random(320), random(200), 1 + random(3));

    // Exit on ESC
    if (read_scancode() == 1) return 0;
  } while (1);
  return 0;
}