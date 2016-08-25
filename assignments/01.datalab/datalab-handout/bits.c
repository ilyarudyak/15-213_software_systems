/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 *   
 *   Solution: de Morgan law
 */
int bitAnd(int x, int y) {
  return ~(~x|~y);
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 *   
 *   Solution: standard operation
 */
int getByte(int x, int n) {
  return ( x >> 8 * n ) & 0xff;

}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 *   Solution: this is a problem from the book (2.53 in 1 st ed.). 
 *   Idea is quite simple - we use a mask 0...01...1 with n 0s and 
 *   handle case when n == 0 separately - not to use 32 bit shift (undefined in C). 
 */
int logicalShift1(int x, int n) {
  // this is my original solution: idea is the same
  // I even consider the case of n == 0 to correctly implement left shift 
  // (hence these expressions: (~!n +1) and (!n - 1))
  // the only difference: I use -1 to create mask and they shift 1 and substract 1
  // which approach is better? can we actually use my approach?
  return ( (~!n + 1) & x ) + ( (!n - 1) & ( (x >> n) & ~( ~0 << (32 - n) ) ) );
}
int logicalShift2(int x, int n) {

    int xsra = x >> n;

    if (n == 0) {
        return xsra;
    } else {
        int mask = (1 << (32 - n)) - 1;
        return xsra & mask;
    }
}
int logicalShift(int x, int n) {
  return logicalShift2(x, n);
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int countBits(int x, int shift) {

    x >>= shift;

    int u0 = 1,      u1 = 1 << 1, u2 = 1 << 2, u3 = 1 << 3;
    int u4 = 1 << 4, u5 = 1 << 5, u6 = 1 << 6, u7 = 1 << 7;

    int w = ((x & u0) >> 0) + ((x & u1) >> 1) + ((x & u2) >> 2) + ((x & u3) >> 3) +
            ((x & u4) >> 4) + ((x & u5) >> 5) + ((x & u6) >> 6) + ((x & u7) >> 7);

    return w;
} 
int bitCount1(int x) {
  return countBits(x, 0) + countBits(x, 8) + countBits(x, 16) + countBits(x, 24);
}
int bitCount(int x) {
  return 0;
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 *   
 *   Solution: idea - if x != 0 then x or -x has sign bit
 *   (x | -x) >> 31 == -1
 *
 *   Solution below is mine. Optimized solution:
 *   ((x | (~x + 1)) >> 31) + 1
 */
int bang(int x) {
    int u = x >> 31;
    int v = (~x + 1) >> 31;
    int w = (u | v) & 1;
    int z = (~w + 1) + 1;
  return z;
}

/* ------------------------------------------------------------------ */



/* 
 * tmin - return minimum two's complement integer (TMin = 0x80...)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  return 1 << 31;
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
// int fitsBits0(int x, int n) {
//   int TMin_n = -(1 << (n-1));
//   int TMax_n = (1 << (n-1)) - 1;
//   int w1 = (TMin_n <= x); int w2 = (x <= TMax_n);
//   printf("Tmin=0x%.8x Tmax=0x%.8x w1=%d w2=%d\n", TMin_n, TMax_n, w1, w2);
  
//   printf("x=0x%.8x n=%d\n", x, n);

//   int mask1 = ~(-1 << (n - 1));
//   printf("mask1=0x%.8x\n", mask1);
//   int mask2 = (mask1 << 1) + 1;
//   printf("mask2=0x%.8x\n", mask2);

//   int u = (x ^ (x & mask1));
//   int v = (x ^ (x & mask2));

//   int res;
//   if (x >= 0) { res = u == 0; printf("%s", "x is non-negative ");}
//   else { res = v == 0; printf("%s", "x is negative ");}
//   printf("u=0x%.8x v=0x%.8x res=%d\n\n", u, v, res);
//   return res;
// }
// int fitsBits1(int x, int n) {
//   // int mask = -1 << (n - 1);
//   // int u = x & mask;
//   // int v = (x & mask) ^ mask;




// }
int fitsBits2(int x, int n) {
      // step zero: convert n to n - 1
  int m = n + ( ~0 ) ;
  // first, get the sign (either 1 or 0)
  int sign = ( x >> 31 ) & 1;

  // second, convert the sign into a "mask" (all bits either 0 or 1)
  int mask = ~(sign + ~0); 

  // then xor with x, all leading bits will go away 
  x = x ^ mask;

  // now shift right n - 1 times
  x = x >> (m);

  return !x;  
}
int fitsBits3(int x, int n) {
  int mask = x >> 31;
  return !(((~x & mask) + (x & ~mask)) >> (n + ~0));
}
int fitsBits4(int x, int n) {
  int a = 33 + ~n; // 32 - n
  int b = ((x << a) >> a); // we get all 0s or 1s at first 32 - n + 1 positions
  return !(b + ~x + 1); // we just compare with x: b - x == 0
}
int fitsBits(int x, int n) {
  return fitsBits2(x, n);
}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 *
 *   Solution: this is from lecture.
 */
int divpwr2(int x, int n) {

  if (x > 0) {
    return x >> n;
  } else {
    return (x + (1 << n) - 1) >> n;
  }
    
  
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return ~x + 1;
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 *   
 *   Solution: if we don't have TMin we need only to check if -x has sign bit
 *   (0 doesn't have this property). This check gives us 1 for positives and 0 
 *   otherwise. (Problem: Tmin = -Tmin).
 *   So we have to distinguish positive numbers and Tmin as well and then use
 *   logical AND. And this is simple - Tmin has sign bit.
 */
int isPositive(int x) {
  return ((x >> 31) ^ 1) & ((~x + 1) >> 31) & 1;
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isNonNegative(int x) {
  return ((x >> 31) & 1) == 0;
}
int isLessOrEqual(int x, int y) {
  if (x <= 0 && y >= 0) {
      return 1;
  } else if (x >= 0 && y >= 0) {
      return isNonNegative(y - x);
  } else {
      return x <= y; 
  }
  
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
  return 2;
}






// float point 
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
 return 2;
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
  return 2;
}
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
  return 2;
}




















