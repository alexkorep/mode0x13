// Inspired by https://www.shadertoy.com/view/3sfGzB
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "cga.h"
#include "keyb.h"
#include "vidbuf.h"
#include <iostream.h>

float trianglePos = 0.0;
void drawTriangle() {
  const int sz = 10;
  const int top = 20;
  const int x = 160 + sin(trianglePos)*50;
  line(x - sz/2, top, x + sz/2, top, 2);
  line(x - sz/2, top, x, top + sz, 2);
  line(x + sz/2 - 1, top, x - 1, top + sz, 2);
  trianglePos += 0.02;
}

float aimExtPos = 0.0;
void drawAimExt() {
  const int sz = 10;
  const int top = 25;
  const int bottom = 120;
  const int width = 60;

  line(160 - width, top, 160 - width, bottom, 1);
  line(160 + width, top, 160 + width, bottom, 1);

  const int linesCount = 5;
  const int step = (bottom - top)/linesCount;
  for (int i = 0; i < linesCount; i++) {
    const int y = top + i*step + aimExtPos;
    line(160 - width - sz, y, 160 - width, y, 1);
    line(160 + width + sz, y, 160 + width, y, 1);
  }
  aimExtPos += 1.0;
  if (aimExtPos >= step) {
    aimExtPos = 0;
  }
}

float aimIntPos = 0.5;
void drawAimInt() {
  const int sz = 12;
  const int top = 50;
  const int bottom = 100;
  const int width = 40;

  line(160 - width, top, 160 - width, bottom, 1);
  line(160 + width, top, 160 + width, bottom, 1);

  const int linesCount = 3;
  const int step = (bottom - top)/linesCount;
  for (int i = 0; i < linesCount; i++) {
    const int y = top + i*step + aimIntPos;
    line(160 - width + sz, y, 160 - width, y, 1);
    line(160 + width - sz, y, 160 + width, y, 1);
  }
  aimIntPos -= 0.2;
  if (aimIntPos <= 0) {
    aimIntPos = step;
  }
}

float aimTopPos = 0.0;
void drawAimTop() {
  const int sz = 4;
  const int top = 32;
  const int width = 40;

  const int linesCount = 6;
  const int step = 2*width/linesCount;
  for (int i = 0; i < linesCount; i++) {
    const int x = 160 - width + i*step + aimTopPos;
    line(x, top, x, top + sz, 1);
  }
  aimTopPos += 0.4;
  if (aimTopPos >= step) {
    aimTopPos = 0;
  }
}

float quadPos[4] = {0.0, 0.0, 0.0, 0.0};
void drawQuadrilateral() {
  const int x = 280;
  const int y = 140;
  const int w = 35;
  const int h = 35;
  const char color = 3;
  line(x-w, y-h, x+w, y-h, color);
  line(x-w, y+h, x+w, y+h, color);
  line(x-w, y-h, x-w, y+h, color);
  line(x+w, y-h, x+w, y+h, color);

  const int xpos[4] = {x, x + 20, x, x - 20};
  const int ypos[4] = {y - 20, y, y + 20, y};
  const float radx[4] = {2, 5, 6, 4};
  const float rady[4] = {5, 2, 4, 1};
  const float quadPosStep[4] = {0.03, 0.02, 0.04, 0.08};
  for (int i = 0; i < 4; i++) {
    const int j = (i <= 2) ? i + 1 : 0;
    line(xpos[i] + radx[i]*sin(quadPos[i]),
         ypos[i] + rady[i]*sin(quadPos[i]),
         xpos[j] + radx[j]*sin(quadPos[j]),
         ypos[j] + rady[j]*sin(quadPos[j]),
         1);
  }
  for (int k = 0; k < 4; k++) {
    quadPos[k] += quadPosStep[k];
  }
}

float mapPos = 0;
void drawMap() {
  const int x = 40;
  const int y = 150;
  const int w = 32;
  const int h = 24;
  const int xcount = 7;
  const int ycount = 6;
  const char color = 3;
  line(x-w, y-h, x+w, y-h, color);
  line(x-w, y+h, x+w, y+h, color);
  line(x-w, y-h, x-w, y+h, color);
  line(x+w, y-h, x+w, y+h, color);

  const int ystep = 2*h/ycount;
  const int xstep = 2*w/xcount;
  int i = 0;
  // hor lines
  for (i = 0; i < ycount; i++) {
    line(x-w, y-h+i*ystep+mapPos, x+w, y-h+i*ystep+mapPos, color);
  }
  // vert lines
  for (i = 0; i < xcount; i++) {
    line(x-w+i*xstep, y-h, x-w+i*xstep, y+h, color);
  }

  mapPos += 0.4;
  if (mapPos >= ystep) {
    mapPos = 0;
  }

  // Triangle
  const int sz = 10;
  const int tw = 12;
  line(x - tw/2, y + sz/2, x + tw/2, y + sz/2, 2);
  line(x - tw/2, y + sz/2, x, y - sz/2, 2);
  line(x + tw/2 - 1, y + sz/2, x - 1, y - sz/2, 2);
}

int main (void)
{
  if (!buffer) {
    printf("Video buffer is not initialized");
    return 1;
  }

  cgaInit();
  do {
    fillBuffer(0);

    drawTriangle();
    drawAimExt();
    drawAimInt();
    drawAimTop();
    drawQuadrilateral();
    drawMap();

    flushBuffer();

    // Exit on ESC
    if (read_scancode() == 1) return 0;
  } while (1);
}