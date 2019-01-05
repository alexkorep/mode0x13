#ifndef CGA_H
#define CGA_H

void cgaPlot(int x, int y, int color)
{
	int b, m; /* bits and mask */
	unsigned char far *p;
	unsigned char c;

	/* address section differs depending on odd/even scanline */
	if (1 == (y & 0x1)) {
		p = (char far*)(0xB8002000L);
	} else {
		p = (char far*)(0xB8000000L);
	}

	/* divide by 2 (each address section is 100 pixels) */
	y >>= 1;

	/* start bit (b) and mask (m) for 2-bit pixels */
	switch (x & 0x3) {
		case 0:
			b = 6;
			m = 0xC0;
			break;
		case 1:
			b = 4;
			m = 0x30;
			break;
		case 2:
			b = 2;
			m = 0x0C;
			break;
		case 3:
			b = 0;
			m = 0x03;
			break;
	}

	/* divide X by 4 (2 bits for each pixel) */
	x >>= 2;

	/* 80 bytes per line (80 * 4 = 320), 4 pixels per byte */
	p += ((80 * y) + x);

	/* read current pixel */
	c = *p;

	/* remove bits at new position */
	c = c & ~m;

	/* set bits at new position */
	c = c | (color << b);

	/* write new pixel */
	*p = c;
}

char cgaGetPixel(int x, int y)
{
	int b, m; /* bits and mask */
	unsigned char far *p;
	unsigned char c;

	/* address section differs depending on odd/even scanline */
	if (1 == (y & 0x1)) {
		p = (char far*)(0xB8002000L);
	} else {
		p = (char far*)(0xB8000000L);
	}

	/* divide by 2 (each address section is 100 pixels) */
	y >>= 1;

	/* start bit (b) and mask (m) for 2-bit pixels */
	switch (x & 0x3) {
		case 0:
			b = 6;
			m = 0xC0;
			break;
		case 1:
			b = 4;
			m = 0x30;
			break;
		case 2:
			b = 2;
			m = 0x0C;
			break;
		case 3:
			b = 0;
			m = 0x03;
			break;
	}

	/* divide X by 4 (2 bits for each pixel) */
	x >>= 2;

	/* 80 bytes per line (80 * 4 = 320), 4 pixels per byte */
	p += ((80 * y) + x);

	/* read current pixel */
	c = *p;

	/* remove other bits */
	c = c & m;

	/* get color */
	c = c >> b;

	return c;
}


void cgaSetPalette(char palette) {
   asm {
        mov ah, 0Bh
        mov bh, 01h
        mov bl, palette
        int 10h
    }
}

void cgaInit() {
    asm {
        mov ah, 0
        mov al, 4
        int 10h
    }
}

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

#endif