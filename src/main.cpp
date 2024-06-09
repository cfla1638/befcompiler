// 编码：GB2312
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "lexer.h"
#include "parser_td.h"
#include "parser_bu.h"
#include "cmdparser.h"

using namespace std;

int main(int argc, char** argv)
{
    /**
     * -h, --help : 帮助文档
     * 
     * 功能:
     * -l : 词法分析, 并打印结果
     * --ptd : 语法分析，自顶向下(top-down)
     * --pbu : 语法分析，自底向上(bottom-up)
     * -c, --calc : 计算初等函数语言的执行结果(语义分析)
     * 
     * 输入方式:
     * -f <filename>: 从文件中输入
     * 默认: 从命令行中输入
     */

    cmd_parser::cmd_parser cmd(argc, argv);
    if (argc == 1 || cmd.has_argument("-h") || cmd.has_argument("--help")) {
        // 打印帮助信息
        cout << "-h, --help: 显示帮助信息" << endl;

        cout << endl << "功能:" << endl;
        cout << "-l: 词法分析, 并打印结果" << endl;
        cout << "--ptd : 语法分析，自顶向下(top-down)" << endl;
        cout << "--pbu : 语法分析，自底向上(bottom-up)" << endl;
        cout << "-c, --calc : 计算初等函数语言的执行结果(语义分析)" << endl;

        cout << endl << "输入方式:" << endl;
        cout << "-f <filename>: 从文件中输入" << endl;
        cout << "默认: 从命令行中输入" << endl;
    }
    else if (cmd.has_argument("-l")) {
        // 词法分析
        if (cmd.has_argument("-f")) {
            ifstream in;
            in.open(cmd.get_argument_value("-f"), std::ios::in);
            if (in.is_open()) {
                lexer::analyze_print(in);
            }
            else
                std::cout << "fail to open file" << std::endl;
        }
        else {
            string code;
            string line;

            cout << ">> ";  // 显示初始提示符
            while (getline(cin, line)) {
                if (line.empty()) {
                    break;  // 如果输入的行为空，则结束输入
                }
                code += line + '\n';  // 将输入的行添加到代码字符串中
                cout << ">> ";  // 显示下一行的提示符
            }
            cout << "\033[F  \n";     // 消除最后一个“>> ”提示符
            istringstream in(code);
            lexer::analyze_print(in);
        }
    }
    else if (cmd.has_argument("--ptd")) {
        vector<uint16_t> out;
        map<uint16_t, Symbol> symbols;

        // 自顶向下的语法分析
        if (cmd.has_argument("-f")) {
            ifstream in;
            in.open(cmd.get_argument_value("-f"), std::ios::in);
            if (in.is_open()) {
                lexer::tokenize(in, out, symbols);
                parser_td::st_node_t * root = parser_td::parse(out, symbols);
                parser_td::print_syntax_tree(root, "", true, symbols);
            }
            else
                std::cout << "fail to open file" << std::endl;
        }
        else {
            string code;
            string line;

            cout << ">> ";  // 显示初始提示符
            while (getline(cin, line)) {
                if (line.empty()) {
                    break;  // 如果输入的行为空，则结束输入
                }
                code += line + '\n';  // 将输入的行添加到代码字符串中
                cout << ">> ";  // 显示下一行的提示符
            }
            cout << "\033[F  \n";     // 消除最后一个“>> ”提示符
            istringstream in(code);
            lexer::tokenize(in, out, symbols);
            parser_td::st_node_t * root = parser_td::parse(out, symbols);
            parser_td::print_syntax_tree(root, "", true, symbols);
        }
    }
    else if (cmd.has_argument("--pbu")) {
        vector<uint16_t> out;
        map<uint16_t, Symbol> symbols;

        // 自底向上的语法分析
        if (cmd.has_argument("-f")) {
            ifstream in;
            in.open(cmd.get_argument_value("-f"), std::ios::in);
            if (in.is_open()) {
                lexer::tokenize(in, out, symbols);
                parser::st_node_t * root = parser::build_syntax_tree(out, symbols);
                parser::print_syntax_tree(root, "", true, symbols);
            }
            else
                std::cout << "fail to open file" << std::endl;
        }
        else {
            string code;
            string line;

            cout << ">> ";  // 显示初始提示符
            while (getline(cin, line)) {
                if (line.empty()) {
                    break;  // 如果输入的行为空，则结束输入
                }
                code += line + '\n';  // 将输入的行添加到代码字符串中
                cout << ">> ";  // 显示下一行的提示符
            }
            cout << "\033[F  \n";     // 消除最后一个“>> ”提示符
            istringstream in(code);
            lexer::tokenize(in, out, symbols);
            parser::st_node_t * root = parser::build_syntax_tree(out, symbols);
            parser::print_syntax_tree(root, "", true, symbols);
        }
    }
    else if (cmd.has_argument("--calc") || cmd.has_argument("-c")) {
        vector<uint16_t> out;
        map<uint16_t, Symbol> symbols;

        // 自底向上的语法分析
        if (cmd.has_argument("-f")) {
            ifstream in;
            in.open(cmd.get_argument_value("-f"), std::ios::in);
            if (in.is_open()) {
                lexer::tokenize(in, out, symbols);
                parser::parse(out, symbols);
            }
            else
                std::cout << "fail to open file" << std::endl;
        }
        else {
            string code;
            string line;

            cout << ">> ";  // 显示初始提示符
            while (getline(cin, line)) {
                if (line.empty()) {
                    break;  // 如果输入的行为空，则结束输入
                }
                code += line + '\n';  // 将输入的行添加到代码字符串中
                cout << ">> ";  // 显示下一行的提示符
            }
            cout << "\033[F  \n";     // 消除最后一个“>> ”提示符
            istringstream in(code);
            lexer::tokenize(in, out, symbols);
            parser::parse(out, symbols);
        }
    }

    return 0;
}