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
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.
  4. Interprets integer expressions using the Data Lab 32-bit bit-vector
     model: results outside the signed range retain their low 32 bits.


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

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

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
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
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
#include "bits.h"

// P1
/* 
 * signMask - return a mask with only the most significant bit set (0x80000000)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int signMask(void) {
	return 1 << 31;
}

// P2
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1, bitXor(7, 7) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 2
 */
int bitXor(int x, int y) {
	return ~(~x & ~y) & ~(x & y);
}

// P3
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int negativePart(int x){
  	return (x >> 31) & (~x + 1);
}


// P4
/*
 * copyByteWithin - copy byte src of x to byte dst, leaving all other bytes unchanged
 *   Bytes are numbered from 0 (least significant) to 3 (most significant).
 *   You can assume 0 <= src <= 3 and 0 <= dst <= 3.
 *   Example: copyByteWithin(0x11223344, 0, 2) = 0x11443344
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int copyByteWithin(int x, int src, int dst) {
	int srcShift = src << 3;                  
    int dstShift = dst << 3;                  
    int srcByte = (x >> srcShift) & 0xFF;     
    int clearMask = ~(0xFF << dstShift);      
    return (x & clearMask) | (srcByte << dstShift); 
}

// P5
/* 
 * logicalShift - shift x to the right by n bits, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int logicalShift(int x, int n) {
	int shifted = x >> n;
    int mask = ~(((1 << 31) >> n) << 1);
    return shifted & mask;
}

// P6
/*
 * swapNibblePairs - swap the low and high 4 bits within each byte of x
 *   Examples: swapNibblePairs(0xAB) = 0xBA
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 18
 *   Rating: 4
 */
int swapNibblePairs(int x) {
	int low = (x & 0x0F0F0F0F) << 4;   // 取低4位，移到高4位
    int high = (x >> 4) & 0x0F0F0F0F;  // 取高4位，移到低4位
    return low | high;
}

// P7
/*
 * secondLowestZeroBit - return a mask that marks the position of the second least significant 0 bit
 *   Examples: secondLowestZeroBit(0xFFFFFFFA) = 0x4, secondLowestZeroBit(0x7FFFFFFF) = 0
 *             secondLowestZeroBit(-1) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */
int secondLowestZeroBit(int x) {
	int y = x | (x + 1);            
    return ~y & (y + 1);            
}

// P8
/*
 * oddParity - return the odd parity bit of x, that is,
 *      when the number of 1s in the binary representation of x is even, then the return 1, otherwise return 0.
 *   Examples: oddParity(5) = 1, oddParity(7) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 56
 *   Rating: 5
 */
int oddParity(int x) {
	int y = x ^ (x >> 16);
    y = y ^ (y >> 8);
    y = y ^ (y >> 4);
    y = y ^ (y >> 2);
    y = y ^ (y >> 1);
    return !(y & 1);
}

// P9
/* 
 * rotateRightBits - rotate x to right by n bits
 *   you can assume n >= 0
 *   Examples: rotateRightBits(0x12345678, 8) = 0x78123456
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 5
 */
int rotateRightBits(int x, int n) {
	n = n & 31;
    int left = (32 + ~n + 1) & 31;   // 计算左移量，避免移位32位
    int right = x >> n;              // 算术右移，可能补1
    int mask = ~(((1 << 31) >> n) << 1); // 构造掩码，清除算术右移补的1
    return (right & mask) | (x << left);
}

// P10
/*
 * roundEvenPow2 - round nonnegative x to the nearest multiple of 2^n.
 *   If x is exactly halfway between two multiples, choose the multiple whose
 *   quotient by 2^n is even.
 *   You can assume 0 <= x <= 0x3fffffff and 1 <= n <= 16.
 *   Examples: roundEvenPow2(10, 2) = 8, roundEvenPow2(14, 2) = 16
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 5
 */
int roundEvenPow2(int x, int n) {
	int mask = (1 << n) + ~0;
    int half = 1 << (n + ~0);
    int rem = x & mask;
    int down = x & ~mask;
    int up = (x + half) & ~mask;

    // 判断是否需要向上舍入
    // 条件1：rem > half  ->  diff > 0
    int diff = rem + ~half + 1;
    int gtHalf = !!(diff & ~(diff >> 31));  // 1 if diff > 0, else 0
    // 条件2：rem == half 且 up>>n 是偶数
    int isHalf = !diff;
    int upEven = !((up >> n) & 1);
    int useUp = gtHalf | (isHalf & upEven); // 1 或 0

    // 把 useUp 变成全 1 或全 0 的掩码
    int chooseUp = ~useUp + 1;  // 0 -> 0, 1 -> 0xFFFFFFFF

    return (up & chooseUp) | (down & ~chooseUp);           
}

// P11
/* 
 * midpointTowardFirst - return the exact mathematical midpoint (x+y)/2
 *   without overflow. If the exact midpoint lies halfway between two
 *   integers, choose the adjacent integer that is closer to the first
 *   argument x.
 *   Examples: midpointTowardFirst(4, 7) = 5,
 *             midpointTowardFirst(7, 4) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 32
 *   Rating: 5
 */
int midpointTowardFirst(int x, int y) {
	int avg = (x & y) + ((x ^ y) >> 1);      // 无溢出平均
    int lost = (x ^ y) & 1;                  // 奇偶不同（中点）

    // 判断 x > y，避免溢出
    int sign_x = x >> 31;
    int sign_y = y >> 31;
    int diff = x + ~y + 1;
    int sign_diff = diff >> 31;
    // x > y 的条件：x 正 y 负，或 同号且 diff > 0
    int x_gt_y = (~sign_x & sign_y) | (~(sign_x ^ sign_y) & ~sign_diff & !!diff);

    int roundUp = lost & x_gt_y;
    return avg + roundUp;
}


// P12
/* 
 * isBetweenEitherOrder - return 1 when x lies in the inclusive interval whose
 *   endpoints are a and b. The endpoints may be given in either order.
 *   Example: isBetweenEitherOrder(5, 8, 3) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 48
 *   Rating: 7
 */
int isBetweenEitherOrder(int x, int a, int b) {
	// 1. Safe comparison: a < b without overflow
    int sa = a >> 31;
    int sb = b >> 31;
    int same_sign = ~(sa ^ sb);
    int diff_ab = a + ~b + 1;
    int sdiff_ab = diff_ab >> 31;

    // If same sign, use subtraction result; if different signs, a is less than b if a is negative (sa)
    int mask = (same_sign & sdiff_ab) | (~same_sign & sa);

    // 2. Determine min and max
    int min = (a & mask) | (b & ~mask);
    int max = (b & mask) | (a & ~mask);

    // 3. Check x >= min (overflow-safe comparison)
    int sx = x >> 31;
    int smin = min >> 31;
    int diff_min = x + ~min + 1;
    int sdiff_min = diff_min >> 31;
    int same_sign_min = ~(sx ^ smin);
    int x_ge_min = (same_sign_min & ~sdiff_min) | (~same_sign_min & ~sx);

    // 4. Check max >= x (overflow-safe comparison)
    int smax = max >> 31;
    int diff_max = max + ~x + 1;
    int sdiff_max = diff_max >> 31;
    int same_sign_max = ~(smax ^ sx);
    int max_ge_x = (same_sign_max & ~sdiff_max) | (~same_sign_max & ~smax);

    // 5. Combine and convert to 0 or 1
    return !!(x_ge_min & max_ge_x);              
}

// P13
/* 
 * mul5Sat - return x*5, and if x*5 overflow, change the result to 
 * INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 7
 */
int mul5Sat(int x) {
	int mul5 = (x << 2) + x;
    int sign_x = x >> 31;

    // x*5 不溢出的正负边界
    int lim_pos = 0x19999999;           // INT_MAX / 5
    int lim_neg = ~0x19999999 + 1;      // INT_MIN / 5 (-0x19999999)

    // 正溢出检测：x > lim_pos
    int pos_check = (x + ~lim_pos) >> 31; // x <= lim_pos 时为 -1，x > lim_pos 时为 0
    int pos_ovf = ~pos_check & ~sign_x;

    // 负溢出检测：x < lim_neg
    int neg_check = (x + ~lim_neg + 1) >> 31; // x < lim_neg 时为 -1，x >= lim_neg 时为 0
    int neg_ovf = neg_check & sign_x;

    int tmin = 1 << 31;
    int tmax = ~tmin;

    // 无溢出掩码
    int no_ovf_mask = ~(pos_ovf | neg_ovf);

    // 组合结果
    int sat_pos = tmax & pos_ovf;
    int sat_neg = tmin & neg_ovf;

    return (mul5 & no_ovf_mask) | sat_pos | sat_neg;
}

// P14
/* 
 * classifyAdd3 - classify the exact mathematical sum x+y+z.
 *   Return 1 if the sum is greater than INT_MAX, -1 if it is less than
 *   INT_MIN, and 0 otherwise. You may not use a wider integer type.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 52
 *   Rating: 7
 */
int classifyAdd3(int x, int y, int z) {
	int sum1 = x + y;
    int sign_x = x >> 31;
    int sign_y = y >> 31;
    int sign_z = z >> 31;
    int sign_sum1 = sum1 >> 31;

    // 第一步溢出检测 (x + y)
    int pos_ovf1 = ~sign_x & ~sign_y & sign_sum1;
    int neg_ovf1 = sign_x & sign_y & ~sign_sum1;

    int sum2 = sum1 + z;
    int sign_sum2 = sum2 >> 31;

    // 第二步溢出检测 (sum1 + z)
    int pos_ovf2 = ~sign_sum1 & ~sign_z & sign_sum2;
    int neg_ovf2 = sign_sum1 & sign_z & ~sign_sum2;

    int any_pos_ovf = pos_ovf1 | pos_ovf2;
    int any_neg_ovf = neg_ovf1 | neg_ovf2;

    // 使用加法组合结果，避免按位或导致的 1 | -1 = -1 问题
    return (any_pos_ovf & 1) + (any_neg_ovf & -1);
}

// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of expression f*3/2 for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   Use round-to-nearest-even. Preserve the sign of both +0 and -0.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 60
 *   Rating: 7
 */
unsigned floatScaleThreeHalves(unsigned uf) {
	unsigned sign = uf >> 31;
    unsigned exp = (uf >> 23) & 0xFF;
    unsigned frac = uf & 0x7FFFFF;

    // 处理 NaN 和无穷大
    if (exp == 0xFF) return uf;
    // 处理 +0 和 -0
    if (exp == 0 && frac == 0) return uf;

    // 处理非规格化数 (exp == 0)
    if (exp == 0) {
        unsigned temp = frac * 3;
        unsigned new_frac = temp >> 1;
        unsigned remainder = temp & 1;

        // 向偶数舍入
        if (remainder && (new_frac & 1)) {
            new_frac++;
        }

        // 检查进位
        if (new_frac & 0x800000) {
            exp = 1;
            new_frac &= 0x7FFFFF;
        }
        return (sign << 31) | (exp << 23) | new_frac;
    }

    // 处理规格化数 (exp != 0)
    unsigned m = 0x800000 | frac;
    unsigned temp = m * 3;
    unsigned new_m = temp >> 1;
    unsigned remainder = temp & 1;

    // 向偶数舍入
    if (remainder && (new_m & 1)) {
        new_m++;
    }
	// 检查是否溢出到高位（进位到阶码）
    if (new_m & 0x1000000) {
        remainder = new_m & 1;
        new_m >>= 1;
        if (remainder && (new_m & 1)) {
            new_m++;
        }
        exp++;
    }

    // 处理阶码溢出为无穷大
    if (exp >= 0xFF) {
        return (sign << 31) | 0x7F800000;
    }

    unsigned new_frac = new_m & 0x7FFFFF;
    return (sign << 31) | (exp << 23) | new_frac;
}

// P16
/* 
 * floatRoundEven - round the floating-point value represented by uf to the
 *   nearest integer, with halfway cases rounded to the even integer. Return
 *   the bit-level representation of that integer as a single-precision float.
 *   If rounding produces zero, preserve the input sign; thus a negative
 *   value that rounds to zero returns -0. When uf is NaN or infinity,
 *   return uf unchanged.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 65
 *   Rating: 10
 */
unsigned floatRoundEven(unsigned uf) {
	unsigned sign = uf >> 31;
    unsigned exp = (uf >> 23) & 0xFF;
    unsigned frac = uf & 0x7FFFFF;

    // 1. NaN 或 Infinity 直接返回
    if (exp == 0xFF) {
        return uf;
    }

    // 2. 绝对值小于 1.0 (exp < 127)
    if (exp < 127) {
        if (exp < 126) {
            return sign << 31;
        }
        if (exp == 126 && frac == 0) {
            return sign << 31;
        }
        return (sign << 31) | (127 << 23); // 四舍五入到 1.0 或 -1.0
    }

    int shift = 23 - (exp - 127);
    if (shift <= 0) {
        return uf; // 整数范围太大，没有小数位需要舍入
    }

    // 3. 包含隐含的 leading 1 计算完整的尾数/整数值
    unsigned full_frac = (1 << 23) | frac;
    unsigned int_part = full_frac >> shift;
    unsigned mask = (shift >= 32) ? 0xFFFFFFFF : ((1U << shift) - 1);
    unsigned frac_part = full_frac & mask;
    unsigned half = 1U << (shift - 1);

	unsigned round_up = 0;
    if (frac_part > half) {
        round_up = 1;
    } else if (frac_part == half) {
        if (int_part & 1) {
            round_up = 1;
        }
    }

    unsigned rounded_val = int_part + round_up;
    if (rounded_val == 0) {
        return sign << 31;
    }

    // 4. 将舍入后的整数重新转换为浮点数表示
    unsigned temp = rounded_val;
    unsigned msb = 0;
    while (temp > 1) {
        temp >>= 1;
        msb++;
    }

    unsigned res_exp = 127 + msb;
    unsigned res_frac;
    if (msb >= 23) {
        res_frac = (rounded_val >> (msb - 23)) & 0x7FFFFF;
    } else {
        res_frac = (rounded_val << (23 - msb)) & 0x7FFFFF;
    }

    // 5. 检查指数溢出（变为 Infinity）
    if (res_exp >= 0xFF) {
        return (sign << 31) | (0xFF << 23);
    }

    return (sign << 31) | (res_exp << 23) | res_frac;
}

// P17
/*
 * float_i2f - Return bit-level equivalent of expression (float) x.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 40
 *   Rating: 10
 */
unsigned float_i2f(int x) {
	if (x == 0) {
        return 0;
    }

    unsigned sign = x >> 31;
    unsigned abs_x = x;
    if (sign) {
        abs_x = -x;
    }

    int highest_bit = 31;
    while (!(abs_x & (1 << highest_bit))) {
        highest_bit--;
    }

    unsigned exp = 127 + highest_bit;

   
    unsigned frac;
    if (highest_bit <= 23) {
        frac = (abs_x << (23 - highest_bit)) & 0x7FFFFF;
    } else {
        int shift = highest_bit - 23;
        frac = (abs_x >> shift) & 0x7FFFFF;

        unsigned dropped = abs_x & ((1 << shift) - 1);
        unsigned half = 1 << (shift - 1);

        int round_up = 0;
        if (dropped > half) {
            round_up = 1;
        } else if (dropped == half) {
            if (frac & 1) {
                round_up = 1;
            }
        }

        if (round_up) {
            frac++;
            if (frac & 0x800000) {
                frac = 0;
                exp++;
            }
        }
    }

    return (sign << 31) | (exp << 23) | (frac & 0x7FFFFF);
}



// P18
/*
 * bitCount - return count of number of 1's in the binary representation of x
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 10
 */
int bitCount(int x) {
	int mask1 = 0x55 | (0x55 << 8);       
    mask1 = mask1 | (mask1 << 16);        
    int mask2 = 0x33 | (0x33 << 8);       
    mask2 = mask2 | (mask2 << 16);       
    int mask4 = 0x0F | (0x0F << 8);       
    mask4 = mask4 | (mask4 << 16);        
    int mask8 = 0xFF | (0xFF << 16);      
    int mask16 = 0xFF | (0xFF << 8);     

    int count = (x & mask1) + ((x >> 1) & mask1);
    count = (count & mask2) + ((count >> 2) & mask2);
    count = (count & mask4) + ((count >> 4) & mask4);
    count = (count & mask8) + ((count >> 8) & mask8);
    count = (count & mask16) + ((count >> 16) & mask16);

    return count;
}

// P19
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 34
 *   Rating: 10
 */
int bitReverse(int x) {

    x = ((x >> 16) & 0x0000FFFF) | ((x & 0x0000FFFF) << 16);
    
    x = ((x >> 8) & 0x00FF00FF) | ((x & 0x00FF00FF) << 8);
    
    x = ((x >> 4) & 0x0F0F0F0F) | ((x & 0x0F0F0F0F) << 4);

    x = ((x >> 2) & 0x33333333) | ((x & 0x33333333) << 2);
    
    x = ((x >> 1) & 0x55555555) | ((x & 0x55555555) << 1);
    
    return x;
	
}

