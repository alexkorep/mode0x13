#include <stdio.h>
#include <stdlib.h>
#include <iostream.h>

const unsigned int BUFSIZE = 320*200;
unsigned char *buffer = new unsigned char[BUFSIZE];

int main (void)
{
  if (!buffer) {
    printf("Video buffer is not initialized");
    return 1;
  }

  printf("All good");
  return 0;
}