

#include <iostream>

#include <vector>

#include <utility>

#include <string>

#include <fstream>

#include <algorithm>

#include <cstdlib>

using namespace std;

//用来存储目标文件名

string file_name;

//提取文本文件中的信息。

string GetText();

//获得一个单词符号,从位置i开始查找。

//并且有一个引用参数j，用来返回这个单词最后一个字符在str的位置。

string GetWord(string str, int i, int &j);

//这个函数用来除去字符串中连续的空格和换行

//第一个参数为目标字符串，第二个参数为开始位置

//返回值为连续的空格和换行后的第一个有效字符在字符串的位置

int DeleteNull(string str, int i);

//判断i当前所指的字符是否为一个分界符，是的话返回真，反之假

bool IsBoundary(string str, int i);

//判断i当前所指的字符是否为一个运算符，是的话返回真，反之假

bool IsOperation(string str, int i);

//此函数将一个pair数组输出到一个文件中

void OutFile(vector<pair<int, string>> v);

//此函数接受一个字符串数组，对它进行词法分析，返回一个pair型数组

vector<pair<int, string>> analyst(vector<string> vec);

//此函数判断传递的参数是否为关键字，是的话，返回真，反之返回假

bool IsKey(string str);

int main()

{

    cout << "###########################\n";

    cout << "###copyright: Giftedbird###\n";

    cout << "###########################\n";

    string com1 = " ";

    string com2 = "\n";

    string fileline = GetText();

    int begin = 0, end = 0;

    vector<string> array;

    do

    {

        begin = DeleteNull(fileline, begin);

        string nowString;

        nowString = GetWord(fileline, begin, end);

        if (end == -1)

            break;

        if (nowString.compare(com1) && nowString.compare(com2))

            array.push_back(nowString);

        begin = end + 1;

    } while (true);

    vector<pair<int, string>> mid_result;

    mid_result = analyst(array);

    OutFile(mid_result);

    cout << "**********************************************************************\n";

    cout << "***程序已完成词法分析，分析结果已经存储在文件" << file_name << "中！！！***\n";

    cout << "**********************************************************************\n";

    system("pause");

    return 0;
}

//提取文本文件中的信息

string GetText()

{

    string file_name1;

    cout << "请输入源文件名（包括路径和后缀名）：";

    cin >> file_name1;

    ifstream infile(file_name1.c_str(), ios::in);

    if (!infile)

    {

        cerr << "哦！无法打开文件 " << file_name1.c_str() << " !!!" << endl;

        exit(-1);
    }

    cout << endl;

    char f[1000];

    infile.getline(f, 1000, EOF);

    infile.close();

    return f;
}

//获得一个单词符号,从位置i开始查找。

//并且有一个引用参数j，用来返回这个单词最后一个字符在原字符串的位置。

string GetWord(string str, int i, int &j)

{

    string no_use("(){} , ;　\n+=*/-<>\"");

    j = str.find_first_of(no_use, i);

    if (j == -1)

        return "";

    if (i != j)

        j--;

    return str.substr(i, j - i + 1);
}

//这个函数用来除去字符串中连续的空格和换行

//第一个参数为目标字符串，第二个参数为开始位置

//返回值为连续的空格和换行后的第一个有效字符在字符串的位置

int DeleteNull(string str, int i)

{

    for (;; i++)

        if (str[i] != ' ' && str[i] != '\n')

            return i;
}

//判断i当前所指的字符是否为一个分界符，是的话返回真，反之假

bool IsBoundary(string str, int i)

{

    int t;

    char arr[7] = {',', ';', '{', '}', '(', ')', '\"'};

    for (t = 0; t < 7; t++)

        if (str[i] == arr[t])

            return true;

    return false;
}

//判断i当前所指的字符是否为一个运算符，是的话返回真，反之假

bool IsOperation(string str, int i)

{

    int t;

    char arr[7] = {'+', '-', '*', '/', '=', '<', '>'};

    for (t = 0; t < 7; t++)

        if (str[i] == arr[t])

            return true;

    return false;
}

//此函数将一个个字符串数组输出到一个文件中

void OutFile(vector<pair<int, string>> v)

{

    cout << "请输入目标文件名（包括路径和后缀名）：";

    cin >> file_name;

    ofstream outfile(file_name.c_str(), ios::out);

    if (!outfile)

    {

        cerr << "哦！无法打开文件 " << file_name.c_str() << " !!!" << endl;

        exit(-1);
    }

    cout << endl;

    int i;

    outfile << "###########################\n";

    outfile << "###copyright: Giftedbird###\n";

    outfile << "###########################\n\n";

    for (i = 0; i < v.size(); i++)

        outfile << "<" << v[i].first << " , \"" << v[i].second << "\">" << endl;

    outfile << "\n\n*********************************\n";

    outfile.close();

    return;
}

//此函数接受一个字符串数组，对它进行词法分析，返回一个pair型数组

vector<pair<int, string>> analyst(vector<string> vec)

{

    vector<pair<int, string>> temp;

    int i;

    for (i = 0; i < vec.size(); i++)

    {

        if (vec[i].size() == 1)

        {

            if ((vec[i] == ">" || vec[i] == "<" || vec[i] == "!") && vec[i + 1] == "=")

            {

                string jk = vec[i];

                jk.append(vec[++i], 0, 1);

                pair<int, string> pp(4, jk);

                temp.push_back(pp);

                continue;
            }

            if ((vec[i] == "+" && vec[i + 1] == "+") || (vec[i] == "-" && vec[i + 1] == "-"))

            {

                string jk = vec[i];

                jk.append(vec[++i], 0, 1);

                pair<int, string> pp(4, jk);

                temp.push_back(pp);

                continue;
            }

            if (IsBoundary(vec[i], 0))

            {

                pair<int, string> pp(5, vec[i]);

                temp.push_back(pp);
            }

            else if (IsOperation(vec[i], 0))

            {

                pair<int, string> pp(4, vec[i]);

                temp.push_back(pp);
            }

            else if (vec[i][0] <= '9' && vec[i][0] >= '0')

            {

                pair<int, string> pp(3, vec[i]);

                temp.push_back(pp);
            }

            else

            {

                pair<int, string> pp(2, vec[i]);

                temp.push_back(pp);
            }
        }

        else if (vec[i][0] <= '9' && vec[i][0] >= '0')

        {

            pair<int, string> pp(3, vec[i]);

            temp.push_back(pp);
        }

        else if (IsKey(vec[i]))

        {

            pair<int, string> pp(1, vec[i]);

            temp.push_back(pp);
        }

        else

        {

            pair<int, string> pp(2, vec[i]);

            temp.push_back(pp);
        }
    }

    return temp;
}

//此函数判断传递的参数是否为关键字，是的话，返回真，反之返回假

bool IsKey(string str)

{

    string p[16] = {"char", "double", "int", "long", "double", "float", "for", "while", "do", "break", "continue", "switch", "short", "case", "return", "if"};

    vector<string> ppp(p, p + 16);

    int u;

    for (u = 0; u < ppp.size(); u++)

        if (!str.compare(ppp[u]))

            return true;

    return false;
}

//finished
