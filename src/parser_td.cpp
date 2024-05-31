#include <stack>
#include <string>
#include <string.h>
#include "parser_td.h"

namespace parser_td {
    pred_table_t::pred_table_t() {
        base[0][0].push_back(27);
        base[0][0].push_back(26);

        base[1][0].push_back(102);
        base[1][0].push_back(14);
        base[1][0].push_back(28);
        base[1][0].push_back(1);

        base[2][0].push_back(30);
        base[2][0].push_back(29);

        base[4][0].push_back(32);
        base[4][0].push_back(31);

        base[6][0].push_back(35);
        base[6][0].push_back(34);

        base[9][0].push_back(37);
        base[10][0].push_back(37);
        base[11][0].push_back(102);

        base[2][1].push_back(30);
        base[2][1].push_back(29);
        
        base[4][1].push_back(32);
        base[4][1].push_back(31);

        base[6][1].push_back(35);
        base[6][1].push_back(34);

        base[9][1].push_back(37);
        base[10][1].push_back(37);
        base[11][1].push_back(103);

        base[2][2].push_back(30);
        base[2][2].push_back(29);

        base[4][2].push_back(32);
        base[4][2].push_back(31);

        base[6][2].push_back(35);
        base[6][2].push_back(34);

        base[9][2].push_back(37);
        base[10][2].push_back(37);
        base[11][2].push_back(101);

        base[2][3].push_back(30);
        base[2][3].push_back(29);

        base[4][3].push_back(32);
        base[4][3].push_back(31);

        base[6][3].push_back(35);
        base[6][3].push_back(34);

        base[9][3].push_back(2);
        base[9][3].push_back(28);
        base[9][3].push_back(3);

        base[10][3].push_back(2);
        base[10][3].push_back(28);
        base[10][3].push_back(3);

        base[3][4].push_back(25);
        base[5][4].push_back(25);
        base[7][4].push_back(3);
        base[8][4].push_back(25);

        base[2][5].push_back(30);
        base[2][5].push_back(29);

        base[3][5].push_back(9);
        base[3][5].push_back(30);
        base[3][5].push_back(29);

        base[4][5].push_back(32);
        base[4][5].push_back(31);

        base[5][5].push_back(25);

        base[6][5].push_back(35);
        base[6][5].push_back(34);

        base[8][5].push_back(25);

        base[9][5].push_back(9);
        base[9][5].push_back(36);

        base[2][6].push_back(30);
        base[2][6].push_back(29);

        base[3][6].push_back(10);
        base[3][6].push_back(30);
        base[3][6].push_back(29);

        base[4][6].push_back(32);
        base[4][6].push_back(31);

        base[5][6].push_back(25);

        base[6][6].push_back(35);
        base[6][6].push_back(34);

        base[8][6].push_back(25);

        base[9][6].push_back(10);
        base[9][6].push_back(36);

        base[8][7].push_back(13);
        base[8][7].push_back(35);

        base[7][8].push_back(8);
        base[7][8].push_back(35);
        base[7][8].push_back(3);

        base[2][9].push_back(30);
        base[2][9].push_back(29);

        base[4][9].push_back(32);
        base[4][9].push_back(31);

        base[6][9].push_back(22);
        base[6][9].push_back(2);
        base[6][9].push_back(35);
        base[6][9].push_back(33);

        base[2][10].push_back(30);
        base[2][10].push_back(29);

        base[4][10].push_back(32);
        base[4][10].push_back(31);

        base[6][10].push_back(104);
        base[6][10].push_back(2);
        base[6][10].push_back(35);
        base[6][10].push_back(3);

        base[5][11].push_back(11);
        base[5][11].push_back(32);
        base[5][11].push_back(31);

        base[8][11].push_back(25);

        base[5][12].push_back(12);
        base[5][12].push_back(32);
        base[5][12].push_back(31);

        base[8][12].push_back(25);

        base[0][13].push_back(27);
        base[0][13].push_back(26);

        base[1][13].push_back(15);
        base[1][13].push_back(28);
        base[1][13].push_back(1);

        base[3][14].push_back(25);
        base[5][14].push_back(25);
        base[8][14].push_back(25);
        base[0][15].push_back(25);
    }

    int id2index(std::uint16_t id, const std::map<std::uint16_t, Symbol> &symbols) {
        if (id > 1000) {
            auto iter = symbols.find(id);
            if (iter != symbols.end()) {
                if (iter->second.type == 6)
                    return 2;
                else if (iter->second.type == 7)
                    return 0;
                else 
                    return -1;
            }
            else 
                return -1;   // 查找失败
        }

        switch (id) {
            case 0:
                return 15;
            case 1:
                return 14;
            case 2:
                return 3;
            case 3:
                return 4;
            case 8:
                return 8;
            case 9:
                return 5;
            case 10:
                return 6;
            case 11:
                return 11;
            case 12:
                return 12;
            case 13:
                return 7;
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
                return 10;
            case 22:
                return 9;
            // 以下为非终结符转换为行标
            case 26:
                return 0;
            case 27:
                return 1;
            case 28:
                return 2;
            case 29:
                return 3;
            case 30:
                return 4;
            case 31:
                return 5;
            case 32:
                return 6;
            case 33:
                return 7;
            case 34:
                return 8;
            case 35:
                return 9;
            case 36:
                return 10;
            case 37:
                return 11;
            default:
                return -1;
        }
    }

    uint16_t symbol2id(const std::string &symbol) {
        if (symbol == "#")
            return 0;
        else if (symbol == ";")
            return 1;
        else if (symbol == "(")
            return 2;
        else if (symbol == ")")
            return 3;
        else if (symbol == "\n")
            return 4;
        else if (symbol == "\t")
            return 5;
        else if (symbol == " ")
            return 6;
        else if (symbol == "\r")
            return 7;
        else if (symbol == ",")
            return 8;
        else if (symbol == "+")
            return 9;
        else if (symbol == "-")
            return 10;
        else if (symbol == "*")
            return 11;
        else if (symbol == "/")
            return 12;
        else if (symbol == "^")
            return 13;
        else if (symbol == "=")
            return 14;
        else if (symbol == "?")
            return 15;
        else if (symbol == "PI")
            return 16;
        else if (symbol == "E")
            return 17;
        else if (symbol == "sin")
            return 18;
        else if (symbol == "cos")
            return 19;
        else if (symbol == "tg")
            return 20;
        else if (symbol == "ctg")
            return 21;
        else if (symbol == "log")
            return 22;
        else if (symbol == "lg")
            return 23;
        else if (symbol == "ln")
            return 24;
        else if (symbol == "epi")
            return 25;
        else if (symbol == "<program>")
            return 26;
        else if (symbol == "<statement>")
            return 27;
        else if (symbol == "<expr>")
            return 28;
        else if (symbol == "<E1>")
            return 29;
        else if (symbol == "<term>")
            return 30;
        else if (symbol == "<T1>")
            return 31;
        else if (symbol == "<factor>")
            return 32;
        else if (symbol == "<F1>")
            return 33;
        else if (symbol == "<F2>")
            return 34;
        else if (symbol == "<sign>")
            return 35;
        else if (symbol == "<S1>")
            return 36;
        else if (symbol == "<number>")
            return 37;
        else
            return -1;
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
            case 26:
                return "<program>";
            case 27:
                return "<statement>";
            case 28:
                return "<expr>";
            case 29:
                return "<E1>";
            case 30:
                return "<term>";
            case 31:
                return "<T1>";
            case 32:
                return "<factor>";
            case 33:
                return "<F1>";
            case 34:
                return "<F2>";
            case 35:
                return "<sign>";
            case 36:
                return "<S1>";
            case 37:
                return "<number>";
            default:
                return ""; // 返回空字符串表示未知ID
        }
}

    inline bool is_nonterminals(uint16_t id) {
        return (id >= 26 && id <= 37);
    }

    st_node_t * parse(std::vector<uint16_t> in, const std::map<std::uint16_t, Symbol> &symbols) {
        pred_table_t pred;
        std::stack<uint16_t> symbol_stack;
        std::stack<st_node_t *> node_stack;

        st_node_t * root = new st_node_t;
        root->id = symbol2id("<program>");

        symbol_stack.push(symbol2id("#"));
        symbol_stack.push(symbol2id("<program>"));

        node_stack.push(nullptr);
        node_stack.push(root);

        auto iter = in.begin();
        uint16_t cur_id;
        st_node_t * cur_node;
        int row, col;
        while (!symbol_stack.empty() && iter != in.end()) {
            cur_id = symbol_stack.top();
            cur_node = node_stack.top();
            symbol_stack.pop();
            node_stack.pop();

            // debug
            // std::cout << "cur_input:\t" << id2symbol(*iter) << std::endl;
            // std::cout << "cur_pred:\t" << id2symbol(cur_id) << std::endl;
            

            if (is_nonterminals(cur_id)) {      // 非终结符
                row = id2index(cur_id, symbols);
                col = id2index(*iter, symbols);               

                if (row < 0 || col < 0) {
                    std::cerr << "Parser: Unable to convert symbol to index" << std::endl;
                    return nullptr;
                }

                if (pred.base[row][col].empty()) {
                    std::cerr << "Parser: Table lookup failed, unable to predict next token sequence" << std::endl;
                    std::cerr << "Current nonterminals: " << cur_id << std::endl;
                    std::cerr << "Current token: " << *iter << std::endl;
                    return nullptr;
                }

                if (pred.base[row][col][0] != 25) {
                    std::vector<st_node_t *> rev_node;  // 用于暂存生成的树节点指针
                    for (auto it = pred.base[row][col].rbegin(); it != pred.base[row][col].rend(); it++) {
                        uint16_t tmp_id = *it;
                        if (*it >= 101 && *it <= 104)
                            tmp_id = *iter;
                        st_node_t * tmp_node = new st_node_t(tmp_id);
                        symbol_stack.push(tmp_id);
                        node_stack.push(tmp_node);
                        rev_node.push_back(tmp_node);

                        // debug
                        // std::cout << "push " << id2symbol(tmp_id) << std::endl;
                    }
                    // debug
                    // std::cout << id2symbol(cur_id) << " -> ";

                    for (auto it = rev_node.rbegin(); it != rev_node.rend(); it++) {
                        cur_node->children.push_back(*it);
                        
                        // debug
                        // std::cout << id2symbol((*it)->id) << " ";
                    }
                    // debug
                    // std::cout << std::endl;
                }
            }
            else {      // 终结符
                if (cur_id == *iter) {      // match
                    std::cout << "Match: " << id2symbol(cur_id, symbols) << std::endl;
                    iter++;
                }
                else {
                    std::cerr << "Unable to match " << id2symbol(cur_id, symbols) << std::endl;
                    return nullptr;
                }
            }
            // getchar();
        }
        return root;
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
}