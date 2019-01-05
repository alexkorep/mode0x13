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

#endif