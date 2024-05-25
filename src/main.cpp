// ���룺GB2312
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "lexer.h"
#include "cmdparser.h"

using namespace std;

int main(int argc, char** argv)
{
    /**
     * -h, --help : �����ĵ�
     * 
     * ����:
     * -l : �ʷ�����, ����ӡ���
     * 
     * ���뷽ʽ:
     * -f <filename>: ���ļ�������
     * Ĭ��: ��������������
     */
    cmd_parser::cmd_parser cmd(argc, argv);
    if (argc == 1 || cmd.has_argument("-h") || cmd.has_argument("--help")) {
        // ��ӡ������Ϣ
        cout << "-h, --help: ��ʾ������Ϣ" << endl;

        cout << endl << "����:" << endl;
        cout << "-l: �ʷ�����, ����ӡ���" << endl;

        cout << endl << "���뷽ʽ:" << endl;
        cout << "-f <filename>: ���ļ�������" << endl;
        cout << "Ĭ��: ��������������" << endl;
    }
    else if (cmd.has_argument("-l")) {
        // �ʷ�����
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

            cout << ">> ";  // ��ʾ��ʼ��ʾ��
            while (getline(cin, line)) {
                if (line.empty()) {
                    break;  // ����������Ϊ�գ����������
                }
                code += line + '\n';  // �����������ӵ������ַ�����
                cout << ">> ";  // ��ʾ��һ�е���ʾ��
            }

            istringstream in(code);
            lexer::analyze_print(in);
        }
    }

    return 0;
}