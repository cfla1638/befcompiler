// 用于解析命令行参数
#ifndef H_CMDPARSER
#define H_CMDPARSER

#include <iostream>
#include <string>
#include <vector>

namespace cmd_parser
{
    // 解析命令行参数
    class cmd_parser {
    private:
        std::vector<std::string> arguments;

    public:
        // 构造函数
        cmd_parser(int argc, char** argv) {
            for (int i = 1; i < argc; i++) {
                arguments.push_back(argv[i]);
            }
        }

        // 判断有无参数
        bool has_argument(const std::string& arg) const {
            for (const std::string& argument : arguments) {
                if (argument == arg) {
                    return true;
                }
            }
            return false;
        }

        // 获取参数的值
        std::string get_argument_value(const std::string& arg) const {
            for (int i = 0; i < arguments.size() - 1; i++) {
                if (arguments[i] == arg) {
                    return arguments[i + 1];
                }
            }
            return "";
        }
    };

} // namespace cmd_parser

#endif