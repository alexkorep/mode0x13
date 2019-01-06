#ifndef KEYB_H
#define KEYB_H

unsigned char read_scancode() {
    unsigned char res;
    _asm {
        in al, 60h
        mov res, al
        in al, 61h
        or al, 128
        out 61h, al
        xor al, 128
        out 61h, al
    }
    return res;
}

#endif