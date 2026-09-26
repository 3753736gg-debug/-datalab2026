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
//德摩根定律//

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
    if (!x) {
        return !y;                  /* x 是 0：只有 y 也是 0 才同号 */
    }
    if (!y) {
        return 0;                   /* x 不是 0，y 是 0：不同号 */
    }
    return !((x ^ y) >> 31);        /* 都不是 0：比较符号位 */
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
    int r, s;   /* r：累计的答案；s：本步要加上的位数 */

    /* 第1步：第16~31位中有没有1？
     * 有：最高位至少在第16位，r = 1 << 4 = 16，
     *     再把 v 右移16位，让高16位降到低位继续找
     * 没有：r = 0，v 不变 */
    r = ((v >> 16) > 0) << 4;
    v = v >> r;

    /* 第2步：剩下的部分中，第8位及以上有没有1？
     * 有则 s = 8，v 右移8位，答案加8 */
    s = ((v >> 8) > 0) << 3;
    v = v >> s;
    r = r | s;

    /* 第3步：第4位及以上有没有1？
     * 有则 s = 4，v 右移4位，答案加4 */
    s = ((v >> 4) > 0) << 2;
    v = v >> s;
    r = r | s;

    /* 第4步：第2位及以上有没有1？
     * 有则 s = 2，v 右移2位，答案加2 */
    s = ((v >> 2) > 0) << 1;
    v = v >> s;
    r = r | s;

    /* 第5步：此时 v 只可能是 1、2、3（最多两位）
     * v 为 2 或 3 时最高位在第1位，v >> 1 = 1，答案加1
     * v 为 1 时最高位在第0位，v >> 1 = 0，答案不变 */
    r = r | (v >> 1);

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
    int ns, ms, d;
    ns = n << 3;                        /* 第 n 字节的起始位 = n * 8 */
    ms = m << 3;                        /* 第 m 字节的起始位 = m * 8 */
    d = ((x >> ns) ^ (x >> ms)) & 0xFF; /* 两个字节的异或值 a ^ b */
    return x ^ ((d << ns) | (d << ms)); /* 把 d 放到两个字节的位置上，再和 x 异或 */
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
    unsigned r;
    int i;
    r = 0;                      /* r 用来存结果，一开始全是 0 */
    i = 32;                     /* 一共要搬 32 位 */
    while (i) {                 /* i 不为 0 就继续 */
        r = (r << 1) | (v & 1); /* r 左移腾位置，把 v 的最低位放进来 */
        v = v >> 1;             /* v 右移，扔掉已经搬走的最低位 */
        i = i - 1;              /* 计数减 1 */
    }
    return r;
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
    int sign;
    sign = x & (1 << 31);               /* 只保留符号位，其余清零 */
    return (x >> n) ^ ((sign >> n) << 1); /* 把多补的 1 异或掉 */
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
    int n, s;
    x = ~x;                              /* 数左边的1 变成 数左边的0 */
    s = !(x >> 16) << 4; x = x << s; n = s;       /* 左边16位全是0？ */
    s = !(x >> 24) << 3; x = x << s; n = n + s;   /* 左边8位全是0？ */
    s = !(x >> 28) << 2; x = x << s; n = n + s;   /* 左边4位全是0？ */
    s = !(x >> 30) << 1; x = x << s; n = n + s;   /* 左边2位全是0？ */
    s = !(x >> 31);      x = x << s; n = n + s;   /* 最左1位是0？ */
    return n + !x;                       /* 原来全是1时，x 是 0，再加 1 得 32 */
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
    unsigned sign, a, e, frac, rnd;
    if (!x) return 0;                  /* ① 0 的浮点表示就是全 0 */

    sign = x & 0x80000000;             /* ② 取出符号位 */
    a = x;
    if (sign) a = -a;                  /* ③ 负数取绝对值 */

    e = 158;                           /* ④ 规格化，同时算指数 */
    while (a < 0x80000000) {
        a = a << 1;
        e = e - 1;
    }

    frac = (a >> 8) & 0x7FFFFF;        /* ⑤ 取出 23 位尾数，去掉开头的 1 */
    rnd = a & 0xFF;                    /* ⑥ 被扔掉的低 8 位，用来舍入 */
    if ((rnd > 0x80) | ((rnd == 0x80) & frac))
        frac = frac + 1;

    return sign + (e << 23) + frac;    /* ⑦ 三块拼起来 */
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
    unsigned s, exp, frac;

    /* ① 拆：把三个字段各自取出来 */
    s    = uf >> 31;                 /* 符号位 */
    exp  = (uf >> 23) & 0xFF;        /* 阶码 */
    frac = uf & 0x7FFFFF;            /* 尾数 */

    /* ② 判 + ③ 改：按三类分别处理 */
    if (exp == 0xFF) return uf;                 /* NaN / 无穷：原样返回 */

    if (exp == 0) {                             /* 非规格化数 */
        frac = frac << 1;                       /* 尾数翻倍 */
        if (frac >> 23) {                       /* 进位到阶码字段 */
            exp = 1;
            frac = frac & 0x7FFFFF;
        }
    } else {                                    /* 规格化数 */
        exp = exp + 1;                          /* 阶码加 1 */
        if (exp == 0xFF) frac = 0;              /* 溢出为无穷，尾数清零 */
    }

    /* ④ 组：拼回 32 位 */
    return (s << 31) | (exp << 23) | frac;
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
    unsigned sign, exp, m;
    int E, r;

    sign = uf2 >> 31;                 /* 符号位 */
    exp  = (uf2 >> 20) & 0x7FF;       /* 11 位阶码 */
    E = exp - 1023;                   /* 真实指数 */

    if (E < 0) return 0;              /* |x| < 1，向零舍入得 0 */
    if (E > 30) return 0x80000000;    /* 超出 int 范围（含 NaN、无穷） */

    m = (1 << 31) | ((uf2 & 0xFFFFF) << 11) | (uf1 >> 21);  /* 拼出 32 位有效数字 */
    r = m >> (31 - E);                /* 右移定位小数点，同时截断小数部分 */

    if (sign) r = -r;                 /* 恢复符号 */
    return r;
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
    if (x > 127)   return 0x7F800000;      /* 太大：返回 +INF */
    if (x >= -126) return (x + 127) << 23; /* 规格化数 */
    if (x >= -149) return 1 << (x + 149);  /* 非规格化数 */
    return 0;                              /* 太小：返回 0 */
}
