// 自底向上(Bottom-up)的语法分析器
#ifndef H_PARSER
#define H_PARSER

#include <cmath>
#include <iostream>
#include <map>
#include <stack>
#include <vector>
#include <utility>

#include "symbol.h"

namespace parser {
    // 语法树定义
    class st_node_t
    {
    public:
        st_node_t() = default;
        st_node_t(std::uint16_t _id) : id(_id) {}

        std::uint16_t id;
        std::vector<st_node_t *> children;
    };

    // 自底向上(Bottom-up)的语法分析
    st_node_t * build_syntax_tree(std::vector<uint16_t> in, const std::map<std::uint16_t, Symbol> &symbols);    // 构建分析树
    void print_syntax_tree(st_node_t* node, std::string prefix, bool is_last, const std::map<std::uint16_t, Symbol> &symbols);  // 打印分析树

    // 语法分析 & 语义分析：输出基本初等函数语言的执行结果
    bool parse(std::vector<uint16_t> in, std::map<std::uint16_t, Symbol> &symbols);
}


#endif