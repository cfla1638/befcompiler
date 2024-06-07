// 语法分析器
#ifndef H_PARSER
#define H_PARSER

#include <iostream>
#include <vector>
#include <map>
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
}


#endif