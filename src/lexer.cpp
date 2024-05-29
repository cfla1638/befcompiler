#include <iostream>
#include <string>
#include "lexer.h"

int Symbol::next_id = 1001;

namespace lexer {
    // 状态转移矩阵
    int move[8][7] = {
        {1, 2, 8, 5, 5, 6, 7},
        {8, 8, 3, 8, 8, 8, 8},
        {2, 2, 3, 8, 8, 8, 8},
        {3, 4, 8, 8, 8, 8, 8},
        {3, 4, 8, 8, 8, 8, 8},
        {5, 5, 8, 5, 5, 8, 8},
        {8, 8, 8, 8, 8, 8, 8},
        {8, 8, 8, 8, 8, 8, 8}
    };

    // 将字符转换成状态转移矩阵的列索引
    int char2index(char ch) {
        if (ch == '0')
            return 0;
        else if (ch >= '1' && ch <= '9')
            return 1;
        else if (ch == '.')
            return 2;
        else if (ch == '_')
            return 3;
        else if (ch >= 'a' && ch <= 'z')
            return 4;
        else if (ch >= 'A' && ch <= 'Z')
            return 4;
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' || ch == '=' || ch == '?')
            return 5;
        else if (ch == ';' || ch == '(' || ch == ')' || ch == '\n' || ch == '\r' || ch == '\t' || ch == ' ' || ch == ',')
            return 6;
        else    // 非法字符
            return -1;
    }

    // 判断当前单词是何种类型的单词
    int get_lex_type(int state, const std::string &lexeme) {
        if (state == 1 || state == 2 || state == 4)
            return 1;   // real
        else if (state == 5) {
            if (lexeme.size() > 32)
                return -2;  // 标识符长度超过32
            if (lexeme == "sin" || lexeme == "cos" || lexeme == "tg" || lexeme == "ctg" || lexeme == "log" || lexeme == "lg" || lexeme == "ln")
                return 3;   // keyword
            if (lexeme == "PI" || lexeme == "E")
                return 4;   // constant
            return 2;       // identifier
        }
        else if (state == 6) {
            return 5;   // operation
        }
        else if (state == 7) {
            return 6;   // delimiter
        }
        return -1; 
    }

    // 根据单词的种类，将其打印到终端中，返回值代表该单词是否合法
    bool print_lexeme(int state, const std::string &lexeme) {
        switch (get_lex_type(state, lexeme))
        {
            case 1:
                std::cout << "< Real\t" << lexeme << "\t>" << std::endl;
                return true;
            case 2:
                std::cout << "< Identifier\t" << lexeme << "\t>" << std::endl;
                return true;
            case 3:
                std::cout << "< Keyword\t" << lexeme << "\t>" << std::endl;
                return true;
            case 4:
                std::cout << "< Constant\t" << lexeme << "\t>" << std::endl;
                return true;
            case 5:
                std::cout << "< Operation\t" << lexeme << "\t>" << std::endl;
                return true;
            case 6:
                std::cout << "< Delimiter\t" << lexeme << "\t>" << std::endl;
                return true;
            case -2:
                std::cout << "Invalid identifier: " << lexeme << ", identifier length should not exceed 32" << std::endl;
                return false;
            default:
                std::cerr << "Unrecognized lexeme: \'" << lexeme << '\'' << std::endl;
                return false;
        }
    }

    void analyze_print(std::istream& in) {
        int state = 0, pre_state, index;
        char ch;
        std::string lexeme;

        // 仍有字符输入
        while (in >> ch) {
            // 将字符转换为索引
            if ((index = char2index(ch)) == -1) {
                std::cerr << "Unrecognized character: \'" << ch << "\'\tASCII: <" << (int)ch << ">" << std::endl;
                return;
            }

            // 接受字符，状态转移
            lexeme.push_back(ch);
            pre_state = state;
            state = move[state][index];

            // 转移到一个非法的状态(预示着当前单词识别结束)
            if (state == 8) {
                if (lexeme.size() > 1)  //如果size == 1,则说明第一个字符就是非法字符，此时应直接打印错误信息
                    lexeme.pop_back();  //吐出刚才引起转移到非法状态的字符

                // 检查当前单词是否合法
                if (!print_lexeme(pre_state, lexeme))
                    return ;
                lexeme.clear();
                
                // 识别一个新的单词, 状态从0开始转移
                lexeme.push_back(ch);
                state = move[0][index];
                if (state == 8) {   // 如果第一个字符就转移到了一个非法状态
                    std::cerr << "Unrecognized lexeme: \'" << ch << '\'' << std::endl;
                    return ;
                }
            }
        }

        // 无字符输入，处理剩下的字符
        if (!lexeme.empty())
            if (!print_lexeme(state, lexeme))
                return ;
    }

    // tokenize版本的print_lexeme，其功能和print_lexeme类似；该函数返回单词tokenize后的id，并修改符号表symbols
    bool to_token(int state, const std::string &lexeme, uint16_t &token, std::map<std::uint16_t, Symbol> &symbols) {
        Symbol s;
        bool in_symbols = false;    // 标记符号表中是否有同名单词
        uint16_t id;                // 配合上一个变量，记录同名单词的id

        switch (get_lex_type(state, lexeme))
        {
            case 1:
                // 遍历符号表，看符号表中是否已有该单词
                for (auto i : symbols) {
                    if (i.second.str == lexeme) {
                        in_symbols = true;
                        id = i.first;
                    }
                }
                
                if (in_symbols) 
                    token = id;
                else {
                    s.set(lexeme, 6);
                    symbols[s.id] = s;
                    token = s.id;
                }
                return true;
            case 2:
                // 遍历符号表，看符号表中是否已有该单词
                for (auto i : symbols) {
                    if (i.second.str == lexeme) {
                        in_symbols = true;
                        id = i.first;
                    }
                }

                if (in_symbols) 
                    token = id;
                else {
                    s.set(lexeme, 7);
                    symbols[s.id] = s;
                    token = s.id;
                }
                return true;
            case 3:
                if (lexeme == "sin")
                    token = 18;
                else if (lexeme == "cos")
                    token = 19;
                else if (lexeme == "tg")
                    token = 20;
                else if (lexeme == "ctg")
                    token = 21;
                else if (lexeme == "log")
                    token = 22;
                else if (lexeme == "lg")
                    token = 23;
                else if (lexeme == "ln")
                    token = 24;
                return true;
            case 4:
                if (lexeme == "PI")
                    token = 16;
                else if (lexeme == "E")
                    token = 17;
                return true;
            case 5:
                if (lexeme == "+")
                    token = 9;
                else if (lexeme == "-")
                    token = 10;
                else if (lexeme == "*")
                    token = 11;
                else if (lexeme == "/")
                    token = 12;
                else if (lexeme == "^")
                    token = 13;
                else if (lexeme == "=")
                    token = 14;
                else if (lexeme == "?")
                    token = 15;
                return true;
            case 6:
                if (lexeme == ";")
                    token = 1;
                else if (lexeme == "(")
                    token = 2;
                else if (lexeme == ")")
                    token = 3;
                else if (lexeme == "\n")
                    token = 4;
                else if (lexeme == "\t")
                    token = 5;
                else if (lexeme == " ")
                    token = 6;
                else if (lexeme == "\r")
                    token = 7;
                else if (lexeme == ",")
                    token = 8;
                return true;
            case -2:
                std::cout << "Invalid identifier: " << lexeme << ", identifier length should not exceed 32" << std::endl;
                return false;
            default:
                std::cerr << "Unrecognized lexeme: \'" << lexeme << '\'' << std::endl;
                return false;
        }
    }

    void tokenize(std::istream &in, std::vector<std::uint16_t> &out, std::map<std::uint16_t, Symbol> &symbols) {
        int state = 0, pre_state, index;
        char ch;
        uint16_t token;
        std::string lexeme;
        out.clear();

        // 仍有字符输入
        while (in >> ch) {
            // 将字符转换为索引
            if ((index = char2index(ch)) == -1) {
                std::cerr << "Unrecognized character: \'" << ch << "\'\tASCII: <" << (int)ch << ">" << std::endl;
                return;
            }

            // 接受字符，状态转移
            lexeme.push_back(ch);
            pre_state = state;
            state = move[state][index];

            // 转移到一个非法的状态(预示着当前单词识别结束)
            if (state == 8) {
                if (lexeme.size() > 1)  //如果size == 1,则说明第一个字符就是非法字符，此时应直接打印错误信息
                    lexeme.pop_back();  //吐出刚才引起转移到非法状态的字符

                // 检查当前单词是否合法
                if (!to_token(pre_state, lexeme, token, symbols))
                    return ;
                else if (token < 4 || token > 7)
                    out.push_back(token);
                lexeme.clear();
                
                // 识别一个新的单词, 状态从0开始转移
                lexeme.push_back(ch);
                state = move[0][index];
                if (state == 8) {   // 如果第一个字符就转移到了一个非法状态
                    std::cerr << "Unrecognized lexeme: \'" << ch << '\'' << std::endl;
                    return ;
                }
            }
        }
        // 无字符输入，处理剩下的字符
        if (!lexeme.empty())
            if (!to_token(state, lexeme, token, symbols))
                return ;
            else if (token < 4 || token > 7)
                out.push_back(token);
        
        out.push_back(0);
    }
}