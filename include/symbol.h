#ifndef H_SYMBOL
#define H_SYMBOL

#include <cstdint>
#include <string>

/** id  symbol  type    解释
 *  0    #      1       分隔符
 *  1    ;      1
 *  2    (      1
 *  3    )      1
 *  4    \ n    1
 *  5    \ t    1
 *  6    \ s    1
 *  7    \ r    1
 *  8    ,      1
 *  9    +      2       操作符
 *  10   -      2
 *  11   *      2
 *  12   /      2
 *  13   ^      2
 *  14   =      2
 *  15   ?      2
 *  16   PI     3       常量
 *  17   E      3
 *  18   sin    4       关键字
 *  19   cos    4
 *  20   tg     4
 *  21   ctg    4
 *  22   log    4
 *  23   lg     4
 *  24   ln     4
 *  25   epi    /
 *  
 *  26   <program>      5     非终结符  
 *  27   <statement>    5
 *  28   <expr>         5
 *  29   <E1>           5
 *  30   <term>         5
 *  31   <T1>           5
 *  32   <factor>       5
 *  33   <F1>           5
 *  34   <F2>           5
 *  35   <sign>         5
 *  36   <S1>           5
 *  37   <number>       5
 *  
 *  --   real           6       实数
 *  --   identifier     7       标识符
 * 
 *  1001
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
    int type;
    static int next_id;
};

#endif