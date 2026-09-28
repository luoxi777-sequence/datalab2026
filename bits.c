/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~(~x | ~y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(~x & ~y) & ~(x & y);
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    if (!x) return !y;
    if (!y) return 0;
    return !((x >> 31) ^ (y >> 31));
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
  int r = 0;
  int t;

  t = v > 0xFFFF;
  v = v >> (t << 4);
  r = r | (t << 4);
  t = v > 0xFF;
  v = v >> (t << 3);
  r = r | (t << 3);
  t = v > 0xF;
  v = v >> (t << 2);
  r = r | (t << 2);
  t = v > 0x3;
  v = v >> (t << 1);
  r = r | (t << 1);
  r = r | (v > 1);
  return r;
}
/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
  int n8 = n << 3;
  int m8 = m << 3;
  int bn = (x >> n8) & 0xFF;
  int bm = (x >> m8) & 0xFF;
  int d = bn ^ bm;
  return x ^ ((d << n8) | (d << m8));
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
  v = (v >> 16) | (v << 16);
  v = ((v & 0xFF00FF00) >> 8) | ((v & 0x00FF00FF) << 8);
  v = ((v & 0xF0F0F0F0) >> 4) | ((v & 0x0F0F0F0F) << 4);
  v = ((v & 0xCCCCCCCC) >> 2) | ((v & 0x33333333) << 2);
  v = ((v & 0xAAAAAAAA) >> 1) | ((v & 0x55555555) << 1);
  return v;
}
/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
  return (x >> n) & ~(((1 << 31) >> n) << 1);
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
  int y = ~x;
  y = y | (y >> 1);
  y = y | (y >> 2);
  y = y | (y >> 4);
  y = y | (y >> 8);
  y = y | (y >> 16);
  y = y + (~((y >> 1) & 0x55555555) + 1);
  y = (y & 0x33333333) + ((y >> 2) & 0x33333333);
  y = (y + (y >> 4)) & 0x0F0F0F0F;
  y = y + (y >> 8);
  y = y + (y >> 16);
  y = y & 0x3F;
  return 32 + (~y + 1);
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
  unsigned ux, sign, frac, drop, half, kept;
  int e;

  if (x == 0) return 0;
  ux = x;
  sign = 0;
  if (ux >> 31) {
    sign = 0x80000000;
    ux = -ux;
  }
  e = 31;
  while (!(ux >> e))
    e = e - 1;
  if (e > 23) {
    int d = e - 23;
    kept = ux >> d;
    drop = ux - (kept << d);
    half = 1 << (d - 1);
    kept = kept & 0x7FFFFF;
    if (drop > half) kept = kept + 1;
    else if (drop == half)
      kept = kept + (kept & 1);
    frac = kept;
  } else {
    frac = (ux << (23 - e)) & 0x7FFFFF;
  }
  return sign + ((e + 127) << 23) + frac;
}
/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
  unsigned exp = (uf >> 23) & 0xFF;
  if (exp == 255) return uf;
  if (exp == 0)
    return (uf & 0x80000000) | ((uf & 0x7FFFFF) << 1);
  return (uf & 0x807FFFFF) | ((exp + 1) << 23);
}
/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
  unsigned m;
  int e, result, sign;

  sign = uf2 >> 31;
  e = ((uf2 >> 20) & 0x7FF) - 1023;
  if (e >= 31) return 0x80000000;
  if (e < 0) return 0;
  m = ((uf2 & 0xFFFFF) | 0x100000) << 11;
  m = m | (uf1 >> 21);
  result = m >> (31 - e);
  if (sign) result = -result;
  return result;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
  if (x > 127) return 0x7F800000;
  if (x >= -126) return (x + 127) << 23;
  if (x >= -149) return 1 << (x + 149);
  return 0;
}