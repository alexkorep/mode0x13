#ifndef VGA_H
#define VGA_H
#include <conio.h>

void vgaInit() {
  __asm {
    mov ah, 0
    mov al, 0x13
    int 10h
  }
}

void setPalette(unsigned char idx,
                unsigned char r,
                unsigned char g,
                unsigned char b) {
  outp(0x03c8, idx);
  outp(0x03c9, r);
  outp(0x03c9, g);
  outp(0x03c9, b);
}

#endif