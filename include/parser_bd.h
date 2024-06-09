// �﷨������
#ifndef H_PARSER
#define H_PARSER

#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include "symbol.h"

namespace parser {
    // �﷨������
    class st_node_t
    {
    public:
        st_node_t() = default;
        st_node_t(std::uint16_t _id) : id(_id) {}

        std::uint16_t id;
        std::vector<st_node_t *> children;
    };

    // �﷨������str(1)
    st_node_t * build_syntax_tree(std::vector<uint16_t> in, const std::map<std::uint16_t, Symbol> &symbols);
    // ��ӡ�﷨��
    void print_syntax_tree(st_node_t* node, std::string prefix, bool is_last, const std::map<std::uint16_t, Symbol> &symbols);

    // �﷨���� & �������
    bool parse(std::vector<uint16_t> in, std::map<std::uint16_t, Symbol> &symbols);
}


#endif