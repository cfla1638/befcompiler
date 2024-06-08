#include <stack>
#include "parser_bd.h"

namespace parser {
    // 动作表：正数代表是移进到该状态，负数代表用某文法展开式规约，9999代表acc
    int action_table[54][17] = {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{4,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0},{7,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,9999},{-2,0,0,0,0,0,0,0,0,0,0,0,0,-2,0,0,-2},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,0},{19,20,21,18,0,15,16,0,0,0,0,12,14,0,0,0,0},{-3,0,0,0,0,0,0,0,0,0,0,0,0,-3,0,0,-3},{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,0},{19,20,21,18,0,15,16,0,0,0,0,12,14,0,0,0,0},{0,0,0,0,0,23,24,0,0,0,0,0,0,0,22,0,0},{0,0,0,0,-8,-8,-8,25,26,0,0,0,0,0,-8,0,0},{0,0,0,0,-11,-11,-11,-11,-11,0,0,0,0,0,-11,0,0},{0,0,0,27,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,-16,-16,-16,-16,-16,28,0,0,0,0,-16,0,0},{0,0,0,29,0,0,0,0,0,0,0,0,0,0,0,0,0},{19,20,21,31,0,0,0,0,0,0,0,0,0,0,0,0,0},{19,20,21,33,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,-19,-19,-19,-19,-19,-19,-19,0,0,0,-19,0,0},{19,20,21,18,0,15,16,0,0,0,0,12,14,0,0,0,0},{0,0,0,0,-23,-23,-23,-23,-23,-23,-23,0,0,0,-23,0,0},{0,0,0,0,-24,-24,-24,-24,-24,-24,-24,0,0,0,-24,0,0},{0,0,0,0,-25,-25,-25,-25,-25,-25,-25,0,0,0,-25,0,0},{-5,0,0,0,0,0,0,0,0,0,0,0,0,-5,0,0,-5},{19,20,21,18,0,15,16,0,0,0,0,12,14,0,0,0,0},{19,20,21,18,0,15,16,0,0,0,0,12,14,0,0,0,0},{19,20,21,18,0,15,16,0,0,0,0,12,14,0,0,0,0},{19,20,21,18,0,15,16,0,0,0,0,12,14,0,0,0,0},{19,20,21,18,0,15,16,0,0,0,0,0,0,0,0,0,0},{19,20,21,18,0,15,16,0,0,0,0,0,0,0,0,0,0},{19,20,21,18,0,15,16,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,-17,-17,-17,-17,-17,-17,-17,0,0,0,-17,0,0},{19,20,21,18,0,15,16,0,0,0,0,12,14,0,0,0,0},{0,0,0,0,-18,-18,-18,-18,-18,-18,-18,0,0,0,-18,0,0},{19,20,21,18,0,15,16,0,0,0,0,12,14,0,0,0,0},{0,0,0,0,44,23,24,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,-6,-6,-6,25,26,0,0,0,0,0,-6,0,0},{0,0,0,0,-7,-7,-7,25,26,0,0,0,0,0,-7,0,0},{0,0,0,0,-9,-9,-9,-9,-9,0,0,0,0,0,-9,0,0},{0,0,0,0,-10,-10,-10,-10,-10,0,0,0,0,0,-10,0,0},{0,0,0,0,46,0,0,0,0,0,45,0,0,0,0,0,0},{0,0,0,0,-14,-14,-14,-14,-14,0,0,0,0,0,-14,0,0},{0,0,0,0,47,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,48,23,24,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,49,23,24,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,-20,-20,-20,-20,-20,-20,-20,0,0,0,-20,0,0},{19,20,21,18,0,15,16,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,-13,-13,-13,-13,-13,0,0,0,0,0,-13,0,0},{0,0,0,0,-15,-15,-15,-15,-15,0,0,0,0,0,-15,0,0},{0,0,0,0,-21,-21,-21,-21,-21,-21,-21,0,0,0,-21,0,0},{0,0,0,0,-22,-22,-22,-22,-22,-22,-22,0,0,0,-22,0,0},{0,0,0,0,51,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,-12,-12,-12,-12,-12,0,0,0,0,0,-12,0,0},{0,0,0,0,0,23,24,0,0,0,0,0,0,0,53,0,0},{-4,0,0,0,0,0,0,0,0,0,0,0,0,-4,0,0,-4}};

    // goto表
    int goto_table[54][8] = {{0,0,0,0,0,0,0,0},{0,2,3,0,0,0,0,0},{0,0,6,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,9,10,11,13,17},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,52,10,11,13,17},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,30},{0,0,0,0,0,0,0,32},{0,0,0,0,0,0,0,0},{0,0,0,34,10,11,13,17},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,35,11,13,17},{0,0,0,0,36,11,13,17},{0,0,0,0,0,37,13,17},{0,0,0,0,0,38,13,17},{0,0,0,0,0,0,39,17},{0,0,0,0,0,0,40,17},{0,0,0,0,0,0,41,17},{0,0,0,0,0,0,0,0},{0,0,0,42,10,11,13,17},{0,0,0,0,0,0,0,0},{0,0,0,43,10,11,13,17},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,50,17},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0}};

    // 所有文法展开式的左部
    std::uint16_t cfg_left[26] = {0, 38, 39, 39, 40, 40, 41, 41, 41, 42, 42, 42, 43, 43, 43, 43, 43, 44, 44, 44, 44, 44, 44, 45, 45, 45};

    // 所有文法展开式的右部

    std::vector<std::uint16_t> cfg_right[26] = {
        {}, //0
        {39}, //1
        {40}, //2
        {39, 40}, //3
        {102, 14, 41, 1}, //4
        {15, 41, 1}, //5
        {41, 9, 42}, //6
        {41, 10, 42}, //7
        {42}, //8
        {42, 11, 43}, //9
        {42, 12, 43}, //10
        {43}, //11
        {22, 2, 44, 8, 44, 3}, //12
        {22, 2, 44, 3}, //13
        {44, 13, 44}, //14
        {104, 2, 44, 3}, //15
        {44}, //16
        {9, 45}, //17
        {10, 45}, //18
        {45}, //19
        {2, 41, 3}, //20
        {9, 2, 41, 3}, //21
        {10, 2, 41, 3}, //22
        {102}, //23
        {103}, //24
        {101}, //25
    };

    int id2index(std::uint16_t id, const std::map<std::uint16_t, Symbol> &symbols) {
        if (id > 1000) {
            auto iter = symbols.find(id);
            if (iter != symbols.end()) {
                if (iter->second.type == 101)
                    return 2;
                else if (iter->second.type == 102)
                    return 0;
                else 
                    return -1;
            }
            else 
                return -1;   // 查找失败
        }

        switch (id) {
            case 0:
                return 16;
            case 1:
                return 14;
            case 2:
                return 3;
            case 3:
                return 4;
            case 8:
                return 10;
            case 9:
                return 5;
            case 10:
                return 6;
            case 11:
                return 7;
            case 12:
                return 8;
            case 13:
                return 9;
            case 14 :
                return 15;
            case 15:
                return 13;
            case 16:
            case 17:
                return 1;
            case 18:
            case 19:
            case 20:
            case 21:
            case 23:
            case 24:
                return 12;
            case 22:
                return 11;
            // 以下为非终结符转换为行标
            case 38:
                return 0;
            case 39:
                return 1;
            case 40:
                return 2;
            case 41:
                return 3;
            case 42:
                return 4;
            case 43:
                return 5;
            case 44:
                return 6;
            case 45:
                return 7;
            default:
                return -1;
        }
    }

    std::string id2symbol(uint16_t id, const std::map<std::uint16_t, Symbol> &symbols) {
        if (id > 1000) {
            auto iter = symbols.find(id);
            if (iter != symbols.end())
                return iter->second.str;
            else 
                return "";   // 查找失败
        }
        switch (id) {
            case 0:
                return "#";
            case 1:
                return ";";
            case 2:
                return "(";
            case 3:
                return ")";
            case 4:
                return "\n";
            case 5:
                return "\t";
            case 6:
                return " ";
            case 7:
                return "\r";
            case 8:
                return ",";
            case 9:
                return "+";
            case 10:
                return "-";
            case 11:
                return "*";
            case 12:
                return "/";
            case 13:
                return "^";
            case 14:
                return "=";
            case 15:
                return "?";
            case 16:
                return "PI";
            case 17:
                return "E";
            case 18:
                return "sin";
            case 19:
                return "cos";
            case 20:
                return "tg";
            case 21:
                return "ctg";
            case 22:
                return "log";
            case 23:
                return "lg";
            case 24:
                return "ln";
            case 25:
                return "epi";
            case 38:
                return "<start>";
            case 39:
                return "<program>";
            case 40:
                return "<statement>";
            case 41:
                return "<expr>";
            case 42:
                return "<term>";
            case 43:
                return "<factor>";
            case 44:
                return "<sign>";
            case 45:
                return "<number>";
            case 101:
                return "real";
            case 102:
                return "identifier";
            case 103:
                return "constant";
            case 104:
                return "keyword";
            default:
                return ""; // 返回空字符串表示未知ID
        }
    }

    inline bool is_nonterminals(std::uint16_t id) {
        return (id >= 38 && id <= 45);
    }

    // 打印语法树
    void print_syntax_tree(st_node_t* node, std::string prefix, bool is_last, const std::map<std::uint16_t, Symbol> &symbols) {
        if (node == nullptr)
            return ;
        std::cout << prefix;
        std::cout << (is_last ? "└── " : "├── ");
        std::cout << id2symbol(node->id, symbols) << std::endl;

        for (size_t i = 0; i < node->children.size(); ++i) {
            bool is_last_child = (i == node->children.size() - 1);
            std::string child_prefix = prefix + (is_last ? "    " : "│   ");
            print_syntax_tree(node->children[i], child_prefix, is_last_child, symbols);
        }
    }

    st_node_t * build_syntax_tree(std::vector<uint16_t> in, const std::map<std::uint16_t, Symbol> &symbols) {
        std::stack<uint16_t> symbol_stack;  // 符号栈
        std::stack<int> state_stack;        // 状态栈
        std::stack<st_node_t *> node_stack; // 没有双亲的树节点栈

        symbol_stack.push(0);
        state_stack.push(1);
        auto iter = in.begin();

        int col, action;
        while (true) {
            col = id2index(*iter, symbols);
            action = action_table[state_stack.top()][col];

            if (action == 9999) {   // acc
                return node_stack.top();
            }
            else if (action > 0) {  // 移进
                state_stack.push(action);
                symbol_stack.push(*iter);
                std::cout << "Match: " << id2symbol(*iter, symbols) << std::endl;
                iter++;
            }
            else if (action < 0) {  // 规约
                int cur_cfg = -action;
                st_node_t * parent = new st_node_t(cfg_left[cur_cfg]);

                // debug
                // std::cout << cfg_right[cur_cfg].size() << std::endl;
                // std::cout << "Reduce: " << id2symbol(cfg_left[cur_cfg], symbols) << " -> ";
                // for (auto i : cfg_right[cur_cfg]) {
                //     std::cout << id2symbol(i, symbols);
                // }
                // std::cout << std::endl;

                std::vector<st_node_t *> tmp;
                for (auto i = cfg_right[cur_cfg].rbegin(); i != cfg_right[cur_cfg].rend(); i++) {
                    state_stack.pop();
                    if (!node_stack.empty() && node_stack.top()->id == *i) {
                        tmp.push_back(node_stack.top());
                        node_stack.pop();
                    }
                    else {
                        tmp.push_back(new st_node_t(symbol_stack.top()));
                    }
                    symbol_stack.pop();
                }
                for (auto i = tmp.rbegin(); i != tmp.rend(); i++) {
                    parent->children.push_back(*i);
                }
                symbol_stack.push(cfg_left[cur_cfg]);
                node_stack.push(parent);

                int next_state = goto_table[state_stack.top()][id2index(cfg_left[cur_cfg], symbols)];
                if (!next_state) {
                    std::cerr << "Parser: failed to look up the goto table" << std::endl;
                    return nullptr;
                }
                state_stack.push(next_state);
            }
            else {      // 查表错误
                std::cerr << "Parser: failed to look up the action table" << std::endl;
                return nullptr;
            }
        }
    }


}