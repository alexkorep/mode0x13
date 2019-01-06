#include <stdio.h>

int main(int argc, char *argv[]) {
  printf("Hello, world!\n");

  __asm {
    mov ah, 0
    mov al, 4
    int 10h
  }

  return 0;
}
