#include <iostream>

using namespace std;

/* *
 *  all numbers from the 1st ed.
 */

// 2.42
int swapBytes(int x, int y) {
    int lsbMaskGet = ~(~0 << 8);
    int lsbMaskClear = ~0 << 8;
//    cout << bitset<32>(lsbMaskGet) << endl;
//    cout << bitset<32>(lsbMaskClear) << endl;

    y &= lsbMaskClear;
    y |= x & lsbMaskGet;

    printf("0x%.8x", y);
    return y;
}
int swapBytes2(int x, int y) {
    int lsbMaskGet = 0xff;
    int lsbMaskClear = ~0xff;

    y &= lsbMaskClear;
    y |= x & lsbMaskGet;

    printf("0x%.8x", y);
    return y;
}

// 2.43
int anyBit(int x) {
    int lsb = x & 0xff;
    return (x != 0) && (x != -1) && (lsb != 0) && (lsb != -1);
}
int anyBit2(int x) {
    int lsb = x & 0xff;

    // we may also use !!~x
    return !!x && !!(x + 1) && !!lsb && !!(lsb + 1);
}

// 2.45
int intSizeIs32() {
    int tmin = 1 << 31;
    int tmax = ~tmin;
    printf("0x%.8x\n", tmin);
    return tmin - 1 == tmax;
}
int intSizeIs32v2() {
    int msb = 1 << 31;
    int beyond = 2 << 31;
    printf("0x%.8x\n", beyond);
    return msb && !beyond;
}

// 2.52
unsigned replaceByte(unsigned x, int i, unsigned char b) {

    unsigned clearMask = (-1 << 8) << 8 * i; //~(((1 << 8) - 1) << 8 * i);
    printf("0x%.8x\n", clearMask);
    unsigned setMask = b << 8 * i;
    printf("0x%.8x\n", setMask);

    return (x & clearMask) | setMask;
}

// 2.44
int isShiftIsArithm() {
    return ((1 << 31) >> 31) & 1;
}

// 2.53 logical shift using arithmetic shift
unsigned srl(unsigned x, int k) {

    unsigned xsra = (int) x >> k;

    if (k == 0) {
        return xsra;
    } else {
        int mask = (1 << (32 - k)) - 1;
        printf("0x%.8x\n", mask);
        return xsra & mask;
    }
}

// from other version of datalab
/*
 * copyLSB - set all bits of result to least significant bit of x
 *   Example: copyLSB(5) = 0xFFFFFFFF, copyLSB(6) = 0x00000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int copyLSB(int x) {
    printf("0x%.8x\n", x - 1);
    printf("0x%.8x\n", x & (x -1));
    return x - (x & (x -1));
}

int main() {

    unsigned x = 0x60;
//    printf("0x%.8x\n", copyLSB(x));
    printf("0x%.8x\n", -x);
    printf("0x%.8x\n", ~x+1);
    printf("0x%.8x\n", x & (~x+1));

    return 0;
}




















