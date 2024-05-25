#include <iostream>
#include <string>
#include "lexer.h"

namespace lexer {
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

    int get_lex_type(int state, const std::string &lexeme) {
        if (state == 1 || state == 2 || state == 4)
            return 1;   // real
        else if (state == 5) {
            if (lexeme == "sin" || lexeme == "cos" || lexeme == "tg" || lexeme == "ctg" || lexeme == "log" || lexeme == "lg" || lexeme == "ln")
                return 3;   // keyword
            if (lexeme == "PI" || lexeme == "E")
                return 4;   // constant
            return 2;
        }
        else if (state == 6) {
            return 5;   // operation
        }
        else if (state == 7) {
            return 6;   // delimiter
        }
        return -1; 
    }

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
            default:
                return false;
        }
    }

    void analyze_print(std::istream& in) {
        int state = 0, pre_state, index;
        char ch;
        std::string lexeme;

        while (in >> ch) {
            if ((index = char2index(ch)) == -1) {
                std::cerr << "Unrecognized character: \'" << ch << '\'' << std::endl;
                return;
            }
            pre_state = state;
            state = move[state][index];
            // td::cout << "nowstat:" << state << std::endl;
            if (state == 8) {
                if (!print_lexeme(pre_state, lexeme)) {
                    std::cerr << "Unrecognized lexeme: \'" << ch << '\'' << std::endl;
                    return ;
                }
                state = move[0][index];
                if (state == 8) {
                    std::cerr << "Unrecognized lexeme: \'" << ch << '\'' << std::endl;
                    return ;
                }
                lexeme.clear();
            }
            lexeme.push_back(ch);
        }
        if (!lexeme.empty())
            if (!print_lexeme(state, lexeme)) {
                std::cerr << "Unrecognized lexeme: \'" << ch << '\'' << std::endl;
                return ;
            }
    }
}