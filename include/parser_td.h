// �﷨������
#ifndef H_PARSER
#define H_PARSER

#include <iostream>
#include <vector>
#include <map>
#include "symbol.h"


namespace parser_td {
    // �﷨������
    class st_node_t
    {
    public:
        st_node_t() = default;
        st_node_t(std::uint16_t _id) : id(_id) {}

        std::uint16_t id;
        std::vector<st_node_t *> children;
    };

    // Ԥ�������
    class pred_table_t {
    public:
        pred_table_t();     // ��ʼ��Ԥ�������
        std::vector<std::uint16_t> base[12][17];
    };

    st_node_t * parse(std::vector<uint16_t> in, const std::map<std::uint16_t, Symbol> &symbols);
    void print_syntax_tree(st_node_t* node, std::string prefix, bool is_last, const std::map<std::uint16_t, Symbol> &symbols);
}

#endif