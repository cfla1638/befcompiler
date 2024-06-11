# befcompiler - 基本初等函数编译器
## 1 实验要求

本实验主要内容是实现一个初等函数运算语言的解释器或编译器。初等函数是由幂函数、指数函数、对数函数、三角函数、反三角函数与常数经过有限次的有理运算（加、减、乘、除）及有限次函数复合所产生、并且能用一个解析式表示的函数。

| 函数类型 | 函数名称        |
| -------- | --------------- |
| sin(x)   | 正弦函数        |
| cos(x)   | 余弦函数        |
| tg(x)    | 正切函数        |
| ctg(x)   | 余切函数        |
| x^y      | 幂函数/指数函数 |
| log(x,y) | 对数            |
| lg(x)    | 以10为底的对数  |
| ln(x)    | 以e为底的对数   |
| log(x)   | 以2为底的对数   |

初等函数运算语言一些约定如下：

1. 语言中仅使用实数这一种数据类型。所有常数、变量及表达式都为实数类型。
2. 语言中可以定义变量来存放数值，变量的定义方式与c语言中的标识符相同。
3. 可以通过赋值语句给变量赋值。
4. 表达式是一个初等函数（函数、变量、常数等通过四则运算或函数嵌套而成）。
5. 输出语句是：?<表达式>。将在界面上输出该表达式的值。如果其中有某一个变量没有赋值，那么将输出该表达式简化后的式子。

## 2 编译

`MinGW`

~~~cmd
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
cmake ..
make
~~~



## 3 程序使用

~~~cpp
-h, --help : 帮助文档

功能:
-l : 词法分析, 并打印结果
--ptd : 语法分析，自顶向下(top-down)
--pbu : 语法分析，自底向上(bottom-up)
-c, --calc : 计算初等函数语言的执行结果(语义分析)
 
输入方式:
-f <filename>: 从文件中输入
默认: 从命令行中输入
~~~





## 4 代码结构说明

~~~sh
+---include
|       cmdparser.h		# 解析命令行参数
|       lexer.h			# 词法分析器的头文件
|       parser_bu.h		# 自底向上的语法分析和语义分析
|       parser_td.h		# 自顶向下的语法分析
|       symbol.h		# 符号定义与符号表设计
|
+---src
|       lexer.cpp
|       main.cpp
|       parser_bu.cpp
|       parser_td.cpp
~~~





## 5 词法分析

### 5.1 正规式设计

~~~md
1: unsigned_real = (0|(1|2|...|9)(digit)*)(.digit*(1|2|...|9)|ε)
~~~

~~~md
2: identifier = (_|a|b|…|z|A|B|…|Z)(_|a|b|…|z|A|B|…|Z|0|1|…|9)* 且identifier的长度<=32
3.: keyword = sin|cos|tg|ctg|log|lg|ln
4: constant = PI/E
~~~

~~~md
5: operator = +|-|*|/|^|=|?
~~~

~~~md
6: delimiter = ;|(|)|\n|\t|\r|\s|,
~~~

> ASCII的空白字符
>
> 1. 空格（Space）：对应的ASCII码值是32。
> 2. 制表符（Tab）：对应的ASCII码值是9。
> 3. 换行符（Newline）：对应的ASCII码值是10。
> 4. 回车符（Carriage Return）：对应的ASCII码值是13。
>
> 
>
> 1. 空格：可以使用 `\s` 表示。
> 2. 制表符：可以使用 `\t` 表示。
> 3. 换行符：可以使用 `\n` 表示。
> 4. 回车符：可以使用 `\r` 表示。



## 6 自顶向下的语法分析

### 6.1 上下文无关文法

~~~CFG
<program>	->	<statement> | <program> <statement>
<statment>	->	Identifier = <expr>; | ?<expr>;
<expr>		->	<expr> + <term> | <expr> - <term> | <term>
<term>		->	<term> * <factor> | <term> / <factor> | <factor>
<factor>	->	log(<sign>,<sign>) | log(<sign>) | <sign>^<sign> | Keyword(<sign>) | <sign>
<sign> 		->	+<number> | -<number> | <number> | (<expr>) | +(<expr>) | -(<expr>)
<number> 	->	Identifier | Constant | real
注：keyword不包括log
~~~

### 6.2 LL(1)文法

~~~CFG
<program>	->	<statement> <program> | ε
<statement>	->	Identifier = <expr>; | ?<expr>;
<expr>		->	<term> <E1>
<E1>		->	+ <term> <E1> | - <term> <E1> | ε
<term>		->	<factor> <T1>
<T1>		-> * <factor> <T1> | / <factor> <T1> | ε
<factor>	->	log(<sign> <F1> | <sign> <F2> | Keyword(<sign>)
<F1>		->	,<sign>) | )
<F2>		->	^<sign> | ε
<sign> 		->	+ <S1> | -<S1> | <number> | (<expr>)
<S1>		->	<number> | (<expr>)
<number>	->	Identifier | Constant | real
~~~

### 6.3 First集和Follow集

~~~CFG
First(<number>) = {Identifier, Constant, real}
First(<S1>) = {Identifier, Constant, real, (}
First(<sign>) = {Identifier, Constant, real, +, -, (}
First(<F2>) = {^, ε}
First(<F1>) = {,, )}
First(<factor>) = {log, Identifier, Constant, real, +, -, (, Keyword}
First(<T1>) = {*, /, ε}
First(<term>) = {log, Identifier, Constant, real, +, -, (, Keyword}
First(<E1>) = {+, -, ε}
First(<expr>) = {log, Identifier, Constant, real, +, -, Keyword}
First(<statement>) = {Identifier, ?}
First(<program>) = {Identifier, ?, ε}

Follow(<program>) = {#}
Follow(<statement>) = {#}
Follow(<expr>) = {;, )}
Follow(<E1>) = {;, )}
Follow(<term>) = {+, -, ;, )}
Follow(<T1>) = {+, -, ;, )}
Follow(<factor>) = {*, /, +, -, ;, )}
Follow(<F1>) = {*, /, +, -, ;, )}
Follow(<F2>) = {*, /, +, -, ;, )}
Follow(<sign>) = {,, ), ^, *, /, +, -, ;}
Follow(<S1>) = {,, ), ^, *, /, +, -, ;}
Follow(<number>) = {,, ), ^, *, /, +, -, ;}
~~~



### 6.4 预测分析表

见`./docs/预测分析表.xlsx`



## 7 自底向上的语法分析

### 7.1 增广文法

~~~cfg
<start>		->	<program>
<program>	->	<statement> | <program> <statement>
<statement>	->	Identifier = <expr>; | ?<expr>;
<expr>		->	<expr> + <term> | <expr> - <term> | <term>
<term>		->	<term> * <factor> | <term> / <factor> | <factor>
<factor>	->	log(<sign>,<sign>) | log(<sign>) | <sign>^<sign> | Keyword(<sign>) | <sign>
<sign> 		->	+<number> | -<number> | <number> | (<expr>) | +(<expr>) | -(<expr>)
<number> 	->	Identifier | Constant | real
~~~



### 7.2 带标号的CFG 

~~~cfg
(1) <start>		->	<program>
(2) <program>	->	<statement>
(3) <program>	->	<program> <statement>
(4) <statement>	->	Identifier = <expr>;
(5) <statement>	->	?<expr>;
(6) <expr>		->	<expr> + <term>
(7) <expr>		->	<expr> - <term>
(8) <expr>		->	<term>
(9) <term>		->	<term> * <factor>
(10) <term>		->	<term> / <factor>
(11) <term>		->	<factor>
(12) <factor>	->	log(<sign>,<sign>)
(13) <factor>	->	log(<sign>)
(14) <factor>	->	<sign>^<sign>
(15) <factor>	->	Keyword(<sign>)
(16) <factor>	->	<sign>
(17) <sign> 	->	+<number>
(18) <sign> 	->	-<number>
(19) <sign> 	->	<number>
(20) <sign> 	->	(<expr>)
(21) <sign> 	->	+(<expr>)
(22) <sign> 	->	-(<expr>)
(23) <number> 	->	Identifier
(24) <number> 	->	Constant
(25) <number> 	->	real
~~~

### 7.3 First集和Follow集

~~~cfg
first(<number>) = {Identifier, Constant, real}
first(<sign>) = {+, -, Identifier, Constant, real, (}
first(<factor>) = {log, +, -, Identifier, Constant, real, (, Keyword}
first(<term>) = {log, +, -, Identifier, Constant, real, (, Keyword}
first(<expr>) = {log, +, -, Identifier, Constant, real, (, Keyword}
first(<statement>) = {Identifier, ?}
first(<program>) = {Identifier, ?}
first(<start>) = {Identifier, ?}

follow(<start>) = {#}
follow(<program>) = {Identifier, ?, #}
follow(<statement>) = {Identifier, ?, #}
follow(<expr>) = {;, +, -, )}
follow(<term>) = {;, +, -, ), *, /}
follow(<factor>) = {;, +, -, ), *, /}
follow(<sign>) = {,, ), ;, +, -, *, /, ^}
follow(<number>) = {,, ), ;, +, -, *, /, ^}
~~~



### 7.4 活前缀DFA

~~~cfg
state: 1
<start> -> .<program>

<program> -> .<statement> | .<program> <statement>
<statement> -> .Identifier = <expr>; | .?<expr>;

<program> : 2
<statement> : 3
Identifier : 4
? : 5
~~~

~~~cfg
state: 2
<start> -> <program>.
<program> -> <program> . <statement>

<statement> -> .Identifier = <expr>; | .?<expr>;

<statement> : 6
Identifier : 7
? : 5
~~~

~~~cfg
state: 3
<program> -> <statement>.
~~~

~~~cfg
state: 4
<statement> -> Identifier . = <expr>;

= : 8
~~~

~~~cfg
state: 5
<statement> -> ?.<expr>;

<expr> -> .<expr> + <term> | .<expr> - <term> | .<term>
<term> -> .<term> * <factor> | .<term> / <factor> | .<factor>
<factor> -> .log(<sign>,<sign>) | .log(<sign>) | .<sign>^<sign> | .Keyword(<sign>) | .<sign>
<sign> -> .+<number> | .-<number> | .<number> | .(<expr>) | .+(<expr>) | .-(<expr>)
<number> ->	.Identifier | .Constant | .real

<expr> : 9
<term> : 10
<factor> : 11
log : 12
<sign> : 13
Keyword : 14
+ : 15
- : 16
<number> : 17
( : 18
Identifier : 19
Constant : 20
real : 21
~~~

~~~cfg
state: 6
<program> -> <program> <statement>.
~~~

~~~cfg
state: 7
<statement> -> Identifier . = <expr>;

= : 8
~~~

~~~cfg
state: 8
<statement> -> Identifier = .<expr>;

<expr> -> .<expr> + <term> | .<expr> - <term> | .<term>
<term> -> .<term> * <factor> | .<term> / <factor> | .<factor>
<factor> -> .log(<sign>,<sign>) | .log(<sign>) | .<sign>^<sign> | .Keyword(<sign>) | .<sign>
<sign> -> .+<number> | .-<number> | .<number> | .(<expr>) | .+(<expr>) | .-(<expr>)
<number> ->	.Identifier | .Constant | .real

<expr> : 52
<term> : 10
<factor> : 11
log : 12
<sign> : 13 
Keyword : 14
+ : 15
- : 16
<number> : 17
( : 18
Identifier : 19 
Constant : 20
real : 21
~~~

~~~cfg
state: 9
<statement> -> ?<expr> . ;
<expr> -> <expr> . + <term> | <expr> . - <term>

; : 22
+ : 23
- : 24
~~~

~~~cfg
state: 10
<expr> -> <term>.
<term> -> <term> . * <factor> | <term> . / <factor>

* : 25
/ : 26
~~~

~~~cfg
state: 11
<term> -> <factor>.
~~~

~~~cfg
state: 12
<factor> -> log.(<sign>,<sign>) | log.(<sign>)

( : 27
~~~

~~~cfg
state: 13
<factor> -> <sign> . ^<sign> | <sign>.

^ : 28
~~~

~~~cfg
state: 14
<factor> -> Keyword.(<sign>)

( : 29
~~~

~~~cfg
state: 15
<sign> -> + . <number> | + . (<expr>)

<number> ->	.Identifier | .Constant | .real

<number> : 30
( : 31
Identifier : 19
Constant : 20
real : 21
~~~

~~~cfg
state: 16
<sign> -> - . <number> | - . (<expr>)

<number> ->	.Identifier | .Constant | .real

<number> : 32
( : 33
Identifier : 19
Constant : 20
real : 21
~~~

~~~cfg
state: 17
<sign> -> <number>.
~~~

~~~cfg
state: 18
<sign> ->  ( . <expr>)

<expr> -> .<expr> + <term> | .<expr> - <term> | .<term>
<term> -> .<term> * <factor> | .<term> / <factor> | .<factor>
<factor> -> .log(<sign>,<sign>) | .log(<sign>) | .<sign>^<sign> | .Keyword(<sign>) | .<sign>
<sign> -> .+<number> | .-<number> | .<number> | .(<expr>) | .+(<expr>) | .-(<expr>)
<number> ->	.Identifier | .Constant | .real

<expr> : 34
<term> : 10
<factor> : 11
log : 12
<sign> : 13
Keyword : 14
+ : 15
- : 16
<number> : 17
( : 18
Identifier : 19
Constant : 20
real : 21
~~~

~~~cfg
state: 19
<number> ->	Identifier.
~~~

~~~cfg
state: 20
<number> ->	Constant.
~~~

~~~cfg
state: 21
<number> ->	real.
~~~

~~~cfg
state: 22
<statement> -> ?<expr>;.
~~~

~~~cfg
state: 23
<expr> -> <expr> + . <term>

<term> -> .<term> * <factor> | .<term> / <factor> | .<factor>
<factor> -> .log(<sign>,<sign>) | .log(<sign>) | .<sign>^<sign> | .Keyword(<sign>) | .<sign>
<sign> -> .+<number> | .-<number> | .<number> | .(<expr>) | .+(<expr>) | .-(<expr>)
<number> ->	.Identifier | .Constant | .real

<term> : 35
<factor> : 11
log : 12
<sign> : 13
Keyword : 14
+ : 15
- : 16
<number> : 17
( : 18
Identifier : 19
Constant : 20
real : 21
~~~

~~~cfg
state 24:
<expr> -> <expr> - . <term>

<term> -> .<term> * <factor> | .<term> / <factor> | .<factor>
<factor> -> .log(<sign>,<sign>) | .log(<sign>) | .<sign>^<sign> | .Keyword(<sign>) | .<sign>
<sign> -> .+<number> | .-<number> | .<number> | .(<expr>) | .+(<expr>) | .-(<expr>)
<number> ->	.Identifier | .Constant | .real

<term> : 36
<factor> : 11
log : 12
<sign> : 13
Keyword : 14
+ : 15
- : 16
<number> : 17
( : 18
Identifier : 19
Constant : 20
real : 21
~~~

~~~cfg
state: 25
<term> -> <term> * . <factor>

<factor> -> .log(<sign>,<sign>) | .log(<sign>) | .<sign>^<sign> | .Keyword(<sign>) | .<sign>
<sign> -> .+<number> | .-<number> | .<number> | .(<expr>) | .+(<expr>) | .-(<expr>)
<number> ->	.Identifier | .Constant | .real

<factor> : 37
log : 12
<sign> : 13
Keyword : 14
+ : 15
- : 16
<number> : 17
( : 18
Identifier : 19
Constant : 20
real : 21
~~~

~~~cfg
state: 26
<term> -> <term> / . <factor>

<factor> -> .log(<sign>,<sign>) | .log(<sign>) | .<sign>^<sign> | .Keyword(<sign>) | .<sign>
<sign> -> .+<number> | .-<number> | .<number> | .(<expr>) | .+(<expr>) | .-(<expr>)
<number> ->	.Identifier | .Constant | .real

<factor> : 38
log : 12
<sign> : 13
Keyword : 14
+ : 15
- : 16
<number> : 17
( : 18
Identifier : 19
Constant : 20
real : 21
~~~

~~~cfg
state: 27
<factor> -> log( . <sign>,<sign>) | log( . <sign>)

<sign> -> .+<number> | .-<number> | .<number> | .(<expr>) | .+(<expr>) | .-(<expr>)
<number> ->	.Identifier | .Constant | .real

<sign> : 39
+ : 15
- : 16
<number> : 17
( : 18
Identifier : 19
Constant : 20
real : 21
~~~

~~~cfg
state: 28
<factor> -> <sign> ^ . <sign>

<sign> -> .+<number> | .-<number> | .<number> | .(<expr>) | .+(<expr>) | .-(<expr>)
<number> ->	.Identifier | .Constant | .real

<sign> : 40
+ : 15
- : 16
<number> : 17
( : 18
Identifier : 19
Constant : 20
real : 21
~~~

~~~cfg
state: 29
<factor> -> Keyword( . <sign>)

<sign> -> .+<number> | .-<number> | .<number> | .(<expr>) | .+(<expr>) | .-(<expr>)
<number> ->	.Identifier | .Constant | .real

<sign> : 41
+ : 15
- : 16
<number> : 17
( : 18
Identifier : 19
Constant : 20
real : 21
~~~

~~~cfg
state: 30
<sign> -> + <number>.
~~~

~~~cfg
31
<sign> ->  + ( .<expr>)

<expr> -> .<expr> + <term> | .<expr> - <term> | .<term>
<term> -> .<term> * <factor> | .<term> / <factor> | .<factor>
<factor> -> .log(<sign>,<sign>) | .log(<sign>) | .<sign>^<sign> | .Keyword(<sign>) | .<sign>
<sign> -> .+<number> | .-<number> | .<number> | .(<expr>) | .+(<expr>) | .-(<expr>)
<number> ->	.Identifier | .Constant | .real

<expr> : 42
<term> : 10
<factor> : 11
log : 12
<sign> : 13
Keyword : 14
+ : 15
- : 16
<number> : 17
( : 18
Identifier : 19
Constant : 20
real : 21
~~~

~~~cfg
32
<sign> -> - <number>.
~~~

~~~cfg
33
<sign> ->  - ( .<expr>)

<expr> -> .<expr> + <term> | .<expr> - <term> | .<term>
<term> -> .<term> * <factor> | .<term> / <factor> | .<factor>
<factor> -> .log(<sign>,<sign>) | .log(<sign>) | .<sign>^<sign> | .Keyword(<sign>) | .<sign>
<sign> -> .+<number> | .-<number> | .<number> | .(<expr>) | .+(<expr>) | .-(<expr>)
<number> ->	.Identifier | .Constant | .real

<expr> : 43
<term> : 10
<factor> : 11
log : 12
<sign> : 13
Keyword : 14
+ : 15
- : 16
<number> : 17
( : 18
Identifier : 19
Constant : 20
real : 21
~~~

~~~cfg
34
<sign> -> (<expr> .)
<expr> -> <expr> . + <term> | <expr> . - <term>

) : 44
+ : 23
- : 24
~~~

~~~cfg
35
<expr> -> <expr> + <term>.
<term> -> <term> . * <factor> | <term> . / <factor>

* : 25
/ : 26
~~~

~~~cfg
36
<expr> -> <expr> -  <term>.
<term> -> <term> . * <factor> | <term> . / <factor>

* : 25
/ : 26
~~~

~~~cfg
37
<term> -> <term> * <factor>.
~~~

~~~cfg
38
<term> -> <term> / <factor>.
~~~

~~~cfg
39
<factor> -> log(<sign> . ,<sign>) | log(<sign> . )

, : 45
) : 46
~~~

~~~cfg
40
<factor> -> <sign> ^ <sign>.
~~~

~~~cfg
41
<factor> -> Keyword(<sign> . )

) : 47
~~~

~~~cfg
42
<sign> ->  + (<expr> . )
<expr> -> <expr> . + <term> | <expr> . - <term>

) : 48
+ : 23
- : 24
~~~

~~~cfg
43
<sign> ->  - (<expr> . )
<expr> -> <expr> . + <term> | <expr> . - <term>

) : 49
+ : 23
- : 24
~~~

~~~cfg
44
<sign> -> (<expr>).
~~~

~~~cfg
45
<factor> -> log(<sign>, . <sign>)

<sign> -> .+<number> | .-<number> | .<number> | .(<expr>) | .+(<expr>) | .-(<expr>)
<number> ->	.Identifier | .Constant | .real

<sign> : 50
+ : 15
- : 16
<number> : 17
( : 18
Identifier : 19
Constant : 20
real : 21
~~~

~~~cfg
46
<factor> -> log(<sign>).
~~~

~~~cfg
47
<factor> -> Keyword(<sign>).
~~~

~~~cfg
48
<sign> ->  + (<expr>).
~~~

~~~cfg
49
<sign> ->  - (<expr>).
~~~

~~~cfg
50
<factor> -> log(<sign>, <sign> . )

) : 51
~~~

~~~cfg
51
<factor> -> log(<sign>, <sign>).
~~~

~~~cfg
52
<statement> -> Identifier = <expr> . ;
<expr> -> <expr> . + <term> | <expr> . - <term>

; : 53
+ : 23
- : 24
~~~

~~~cfg
53
<statement> -> Identifier = <expr>; .
~~~



### 7.5 语法分析伪代码

~~~md
主要部分1：语法分析
	输入：词法分析生成的记号流
	输出：语法树 或 错误信息

初始化语法分析树，根节点设为nullnptr
定义三个栈，存符号、状态和没有parent的树的结点
	向存符号的栈内压入#，并向存状态的栈内压入0
	while记号流未遍历完毕
		根据状态栈栈顶和当前遍历到的终结符进行查表，得到动作
		if 动作是acc
			返回树节点栈的栈顶
		else if 动作是shift
			往状态栈压入查表得到的新的状态
			往符号栈压入当前遍历到的符号
			游标向后移，表示到了记号流的下一个记号
		else if 动作是reduce
			得到文法式的左部，为它构建树节点; (符号表建立对应的表项)
			得到文法式右部的长度，符号栈和状态栈弹出相应数量的符号或状态
			
			for 文法产生式右部的每一个符号(逆序)：
				if 树节点栈不空 and 当前文法产生式右部的符号与树节点栈顶相同
					直接弹出树节点栈的栈顶，并将其设置为文法产生式左部节点的孩子
				else
					根据弹出的符号生成新的树节点，并将其设置为文法产生式左部节点的孩子
					
			将文法产生式的左部压入符号栈
			将文法产生式左部的树节点压入树节点栈
			根据文法产生式的左部和当前状态栈栈顶查goto表
			if goto表对应的值存在
				将该状态压入状态栈
			else
				返回错误
		else
			返回错误

~~~



### 7.6 移进规约分析表

见`./docs/移进规约分析表.xlsx`



### 7.7 一个分析示例

| 剩余输入      | 符号栈                     | 状态栈        | 动作 |
| ------------- | -------------------------- | ------------- | ---- |
| x=1;y=2;?x+y; | #                          | 1             | s4   |
| =1;y=2;?x+y;  | #x                         | 1 4           | s8   |
| 1;y=2;?x+y;   | #x=                        | 1 4 8         | s21  |
| ;y=2;?x+y;    | #x=1                       | 1 4 8 21      | r25  |
| ;y=2;?x+y;    | #x=<number>                | 1 4 8 17      | r19  |
| ;y=2;?x+y;    | #x=<sign>                  | 1 4 8 13      | r16  |
| ;y=2;?x+y;    | #x=<factor>                | 1 4 8 11      | r11  |
| ;y=2;?x+y;    | #x=<term>                  | 1 4 8 10      | r8   |
| ;y=2;?x+y;    | #x=<expr>                  | 1 4 8 52      | s53  |
| y=2;?x+y;     | #x=<expr>;                 | 1 4 8 52 53   | r4   |
| y=2;?x+y;     | #<statement>               | 1 3           | r2   |
| y=2;?x+y;     | #<program>                 | 1 2           | s7   |
| =2;?x+y;      | #<program>y                | 1 2 7         | s8   |
| 2;?x+y;       | #<program>y=               | 1 2 7 8       | s21  |
| ;?x+y;        | #<program>y=2              | 1 2 7 8 21    | r25  |
| ;?x+y;        | #<program>y=<number>       | 1 2 7 8 17    | r19  |
| ;?x+y;        | #<program>y=<sign>         | 1 2 7 8 13    | r16  |
| ;?x+y;        | #<program>y=<factor>       | 1 2 7 8 11    | r11  |
| ;?x+y;        | #<program>y=<term>         | 1 2 7 8 10    | r8   |
| ;?x+y;        | #<program>y=<expr>         | 1 2 7 8 52    | s53  |
| ?x+y;         | #<program>y=<expr>;        | 1 2 7 8 52 53 | r4   |
| ?x+y;         | #<program> <statement>     | 1 2 6         | r3   |
| ?x+y;         | #<program>                 | 1 2           | s5   |
| x+y;          | #<program>?                | 1 2 5         | s19  |
| +y;           | #<program>?x               | 1 2 5 19      | r23  |
| +y;           | #<program>?<number>        | 1 2 5 17      | r19  |
| +y;           | #<program>?<sign>          | 1 2 5 13      | r16  |
| +y;           | #<program>?<factor>        | 1 2 5 11      | r11  |
| +y;           | #<program>?<term>          | 1 2 5 10      | r8   |
| +y;           | #<program>?<expr>          | 1 2 5 9       | s23  |
| y;            | #<program>?<expr>+         | 1 2 5 9 23    | s19  |
| ;             | #<program>?<expr>+y        | 1 2 5 9 23 19 | r23  |
| ;             | #<program>?<expr>+<number> | 1 2 5 9 23 17 | r19  |
| ;             | #<program>?<expr>+<sign>   | 1 2 5 9 23 13 | r16  |
| ;             | #<program>?<expr>+<factor> | 1 2 5 9 23 11 | r11  |
| ;             | #<program>?<expr>+<term>   | 1 2 5 9 23 35 | r6   |
| ;             | #<program>?<expr>          | 1 2 5 9       | s22  |
|               | #<program>?<expr>;         | 1 2 5 9 22    | r5   |
|               | #<program><statement>      | 1 2 6         | r3   |
|               | #<program>                 | 1 2           | acc  |



## 8 语义分析

### 8.1 翻译方案

~~~cfg
(1) <start>		->	<program>
(2) <program>	->	<statement>
(3) <program>	->	<program> <statement>
(4) <statement>	->	Identifier = <expr>;
	if (exist(<expr>.val))
		Identifier.val = <expr>.val;
	else {
		Identifier.val = 'NOT EXIST';
		Identifier.code = <expr>.code;
	}
		
(5) <statement>	->	?<expr>;
	print(<expr>.code)
(6) <expr>		->	<expr> + <term>
	if (exist(<expr2>.val) and exist(<term>.val)) {
		<expr1>.val = <expr2>.val + <term>.val
		<expr1>.code = <expr1>.val;
	}
	else {
		<expr1>.val = 'NOT EXIST'
		<expr1>.code = <expr2>.code + <term>.code;
	}
(7) <expr>		->	<expr> - <term>
	if (exist(<expr2>.val) and exist(<term>.val)) {
		<expr1>.val = <expr2>.val - <term>.val
		<expr1>.code = <expr1>.val;
	}
	else {
		<expr1>.val = 'NOT EXIST'
		<expr1>.code = <expr2>.code * <term>.code;
	}
(8) <expr>		->	<term>
	<expr>.code = <term>.code
	<expr>.val = <term>.val
(9) <term>		->	<term> * <factor>
	if (exist(<term2>.val) and exist(<factor>.val)) {
		<term1>.val = <term2>.val * <factor>.val
		<term1>.code = <term1>.val;
	}
	else {
		<term1>.val = 'NOT EXIST'
		<term1>.code = <term2>.code * <factor>.code;
	}
(10) <term>		->	<term> / <factor>
	if (exist(<term2>.val) and exist(<factor>.val)) {
		检查参数合法性
		<term1>.val = <term2>.val / <factor>.val
		<term1>.code = <term1>.val;
	}
	else {
		<term1>.val = 'NOT EXIST'
		<term1>.code = <term2>.code / <factor>.code;
	}
(11) <term>		->	<factor>
	<term>.code = <factor>.code
	<term>.val = <factor>.val
(12) <factor>	->	log(<sign>,<sign>)
	if (exist(<sign1>) && exist(<sign2>)) {
		检查参数合法性合法性
		<factor>.val = log(<sign1>,<sign2>)
		<factor>.code = <factor>.val;
	}
	else {
		<factor>.val = 'NOT EXIST';
		<factor>.code = log(<sign1>.code, <sign2>.code);		
	}
(13) <factor>	->	log(<sign>)
	if (exist(<sign>) {
		检查参数合法性合法性
		<factor>.val = log(<sign>)
		<factor>.code = <factor>.val;
	}
	else {
		<factor>.val = 'NOT EXIST';
		<factor>.code = log(<factor>.code);		
	}
(14) <factor>	->	<sign>^<sign>
	if (exist(<sign1>) && exist(<sign2>)) {
		检查参数合法性合法性
		<factor>.val = <sign1>^<sign2>
		<factor>.code = <factor>.val;
	}
	else {
		<factor>.val = 'NOT EXIST';
		<factor>.code = <sign1>.code^<sign2>.code;		
	}
(15) <factor>	->	Keyword(<sign>)
	if (exist(<sign>.val)) {
		检查<sign>.val是否合法
		<factor>.val = Keyword(<sign>.val);
		<factor>.code = <factor>.val();
	}
	else {
		<factor>.val = 'NOT EXIST';
		<factor>.code = Keyword(<sign>.code);
	}
(16) <factor>	->	<sign>	
	<factor>.val = <sign>.val;
	<factor>.code = <sign>.code;
(17) <sign> 	->	+<number>
	if (exist(<number>.val)) {
		<sign>.val = <number>.val;
		<sign>.code = <sign>.val;
	}
	else {
		<sign>.val = 'NOT EXIST';
		<sign>.code = <number>.code;
	}
(18) <sign> 	->	-<number>
	if (exist(<number>.val)) {
		<sign>.val = -<number>.val;
		<sign>.code = <sign>.val;
	}
	else {
		<sign>.val = 'NOT EXIST';
		<sign>.code = -<number>.code;
	}
(19) <sign> 	->	<number>
	if (exist(<number>.val)) {
		<sign>.val = <number>.val;
		<sign>.code = <sign>.val;
	}
	else {
		<sign>.val = 'NOT EXIST';
		<sign>.code = <number>.code;
	}
(20) <sign> 	->	(<expr>)
	if (exist(<expr>.val)) {
		<sign>.val = <expr>.val;
		<sign>.code = <expr>.val;
	}
	else {
		<sign>.val = 'NOT EXIST';
		<sign>.code = (<expr>.code);
	}
(21) <sign> 	->	+(<expr>)
	if (exist(<expr>.val)) {
		<sign>.val = +<expr>.val;
		<sign>.code = <expr>.val;
	}
	else {
		<sign>.val = 'NOT EXIST';
		<sign>.code = +(<expr>.code);
	}
(22) <sign> 	->	-(<expr>)
	if (exist(<expr>.val)) {
		<sign>.val = -<expr>.val;
		<sign>.code = <expr>.val;
	}
	else {
		<sign>.val = 'NOT EXIST';
		<sign>.code = -(<expr>.code);
	}
(23) <number> 	->	Identifier
	if (exist(Identifier.val)) {
		<number>.val = Identifier.val;
		<number>.code = Identifier.val;
	} 
	else {
		<number>.val = 'NOT EXIST';
		<number>.code = Identifier.code;
	}
(24) <number> 	->	Constant
	<number>.code = Constant.val, <number>.val = Constant.val
(25) <number> 	->	real
	<number>.code = real.val, <number>.val = real.val
~~~

### 8.2 语义分析伪代码

~~~md
主要部分1：语法分析
	输入：词法分析生成的记号流
	输出：语义分析的结果

初始化语法分析树，根节点设为nullnptr
定义三个栈，存符号、状态和 新规约出来的非终结符
	向存符号的栈内压入#，并向存状态的栈内压入0
	while记号流未遍历完毕
		根据状态栈栈顶和当前遍历到的终结符进行查表，得到动作
		if 动作是acc
			return ;
		else if 动作是shift
			往状态栈压入查表得到的新的状态
			往符号栈压入当前遍历到的符号
			游标向后移，表示到了记号流的下一个记号
		else if 动作是reduce
			得到文法式的左部，为它构建符号表项(new_symbol);
			得到文法式右部的长度，符号栈和状态栈弹出相应数量的符号或状态
			
			定义一个传递语义动作参数的vector(「参数vector」)
			for 文法产生式右部的每一个符号(逆序)：
				if 非终结符栈不空 and 当前文法产生式右部的符号与非终结符栈栈顶相同
					弹出非终结符栈栈顶，将其压入「参数vector」
				else if 当前符号是 Identifier/Constant/Real/Keyword
					将其压入参数栈栈顶
			
			semantic_analysis(cfg_id, new_symbol.id, 「参数vector」, symbols)
			将文法产生式的左部压入符号栈
			将new_symbol.id压入「非终结符栈」
			根据文法产生式的左部和当前状态栈栈顶查goto表
			if goto表对应的值存在
				将该状态压入状态栈
			else
				返回错误
		else
			返回错误
~~~



