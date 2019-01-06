#ifndef VGA_H
#define VGA_H

void vgaInit() {
  __asm {
    mov ah, 0
    mov al, 0x13
    int 10h
  }
}

#endif