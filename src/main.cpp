#include <iostream>
#include <string>
#include <sstream>
#include "lexer.h"
using namespace std;

int main(void)
{
    string str;
    cin >> str;
    istringstream in(str);
    lexer::analyze_print(in);
    // TODO解决空格问题
    return 0;
}