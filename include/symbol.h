#ifndef H_SYMBOL
#define H_SYMBOL

#include <cstdint>
#include <string>
#include <map>

/**
 * @brief 符号表解决方案
 * 每个符号都有一个id，type以及若干属性
 * 符号表中分为四种类型的符号分别是:
 *  - 普通的终结符，例如+, - 他们不需要在内存中实例化
 *  - 特殊的终结符，包括real, identifier, constant，他们虽然是终结符，但需要在内存中实例化
 *    因此他们有一个type标记他们的类型，有一个id区分每一个实例
 *  - 非终结符，需要在内存中实例化，因此有一个type标记他们的类型，有一个id区分每一个实例
 *  - keyword，是一个复合的非终结符，它包括sin, cos。 ... 不需要再内存中实例化
 *  
 *  对于任意符号，当该符号的id < 1000时，它的type = id。用于表示那些不需要在内存中实例化的「普通的终结符」
 *  、「特殊的终结符」的原型、「非终结符」的原型、复合的「keyword」和「keyword」的具体终结符。
 *  若 id > 1000 , 则id只起到区分彼此的作用，而type表示它们的类型。
 *  所有的type属于{id | id < 1000 且 id 有定义}
 */


/** id  symbol  type
 *  0    #      0
 *  1    ;      1
 *  2    (      2
 *  3    )      3
 *  4    \ n    4
 *  5    \ t    5
 *  6    \ s    6
 *  7    \ r    7
 *  8    ,      8
 *  9    +      9
 *  10   -      10
 *  11   *      11
 *  12   /      12
 *  13   ^      13
 *  14   =      14
 *  15   ?      15
 *  16   PI     16
 *  17   E      17
 *  18   sin    18
 *  19   cos    19
 *  20   tg     20
 *  21   ctg    21
 *  22   log    22
 *  23   lg     23
 *  24   ln     24
 *  25   epi    25
 *  
 *  26   <program>      26  
 *  27   <statement>    27
 *  28   <expr>         28
 *  29   <E1>           29
 *  30   <term>         30
 *  31   <T1>           31
 *  32   <factor>       32
 *  33   <F1>           33
 *  34   <F2>           34
 *  35   <sign>         35
 *  36   <S1>           36
 *  37   <number>       37
 * 
 *  38   <start>        38
 *  39   <program>      39
 *  40   <statement>    40
 *  41   <expr>         41
 *  42   <term>         42
 *  43   <factor>       43
 *  44   <sign>         44
 *  45   <number>       45
 * 
 *  46   shift          46
 *  47   reduce         47
 *  
 *  仅在预测分析表中使用
 *  101   real           6
 *  102   identifier     7
 *  103   constant
 *  104   keyword
 * 
 *  1001...     各种实例
 */

class Symbol
{
public:
    Symbol() = default;
    Symbol(std::string str, int type) : str(str), type(type) { id = next_id; next_id++; }

    void set(std::string _str, int _type) {
        str = _str;
        type = _type;
        id = next_id;
        next_id++;
    }

    std::uint16_t id = 0;   // 无符号的16位整数类型，取值范围为0到65535
    std::string str;        // 字符串表示
    int type;               // type = 6 real type = 7 identifier
    static int next_id;

    // 后添加的属性
};


#endif