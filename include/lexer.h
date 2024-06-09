// 词法分析器
#ifndef H_LEXER
#define H_LEXER

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "symbol.h"


namespace lexer {
    // 接受字符串，输出词法分析后的记号流和符号表
    void tokenize(std::istream &in, std::vector<std::uint16_t> &out, std::map<std::uint16_t, Symbol> &symbols);
    void analyze_print(std::istream &in);   // 接受字符串, 对字符串进行词法分析，并打印分析结果
}

#endif