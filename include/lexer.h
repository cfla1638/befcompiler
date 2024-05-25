// 词法分析器
#ifndef H_LEXER
#define H_LEXER

#include <iostream>


namespace lexer {
    // 接受字符串，输出词法分析后的记号流和符号表
    void tokenize(std::istream &in, std::ostream &out, std::ostream &symbol_table);
    void analyze_print(std::istream &in);
}

#endif