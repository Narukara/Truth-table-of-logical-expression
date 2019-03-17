// LogicTableOfTF.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

//cnt字符个数
int cnt = 0, chval[26] = {};

//获取真值表中的字符
void getAlpha(string str, char *chs, int &cnt)
{
	//26个字母
	int ch[26] = {};

	for (int i = 0; i < (int)str.length(); ++i) {
		//函数原型： int isalpha(int ch);
		//功能：如果参数是字母字符，函数返回非零值，否则返回零值。
		if (isalpha(str[i]))
		{
			//获得字符对应的位置数
			ch[str[i] - 'a'] ++; 
		}
	}

	//获取真值表中的字符 
	for (int i = 0; i < 26; ++i) {
		if (ch[i])
		{
			chs[cnt++] = i + 97;
		}
	}
}

//表达式替换数值
string shuzhitihuan(string str, int chval[26])
{
	string st = "";
	for (int i = 0; i < str.size(); ++i) {
		if (str[i] <= 'z' && str[i] >= 'a') {
			st += chval[str[i] - 'a'] ? "1" : "0";
		}
		else st += str[i];
	}
	return st;
}

//去除(1)(0)
void qvkuohao(string & str)  
{
	string st = "";
	for (int i = 0; i < str.size(); ++i) {
		if (str[i] == '(' && i + 2 < str.size() && str[i + 2] == ')') {
			st += str[i + 1];
			i += 2;
		}
		else st += str[i];
	}
	str = st;
}

//运算部分——按照优先级排顺序
//取非
void qvfei(string &str)
{
	string st = "";
	for (int i = 0; i < str.size(); ++i) {
		if (str[i] == '!' && i + 1 < str.size() && str[i + 1] == '0') {
			st += '1';
			i++;
		}
		else if (str[i] == '!' && i + 1 < str.size() && str[i + 1] == '1') {
			st += '0';
			i++;
		}
		else st += str[i];
	}
	str = st;
}
//取合取
void qvheqv(string &str)
{
	string st = "";
	for (int i = 0; i < str.size(); ++i) {
		if (str[i] == '1' && i + 2 < str.size() && str[i + 2] == '1' && str[i + 1] == '*') {
			st += '1';
			i += 2;
		}
		else if (i + 2 < str.size() && str[i + 1] == '*' && ((str[i] == '1' && str[i + 2] == '0')
			|| (str[i] == '0' && str[i + 2] == '1') || (str[i] == '0' && str[i + 2] == '0'))) {
			st += '0';
			i += 2;
		}
		else st += str[i];
	}
	str = st;
}
//取析取
void qvxiqv(string & str)
{
	string st = "";
	for (int i = 0; i < str.size(); ++i) {
		if (str[i] == '0' && i + 2 < str.size() && str[i + 2] == '0' && str[i + 1] == '|') {
			st += '0';
			i += 2;
		}
		else if (i + 2 < str.size() && str[i + 1] == '|' && ((str[i] == '1' && str[i + 2] == '0')
			|| (str[i] == '0' && str[i + 2] == '1') || (str[i] == '1' && str[i + 2] == '1'))) {
			st += '1';
			i += 2;
		}
		else st += str[i];
	}
	str = st;
}
//取蕴含表达式
void qvyunhan(string &str)
{
	string st = "";
	for (int i = 0; i < str.size(); ++i) {
		if (str[i + 1] == '>' && str[i] == '1' && str[i + 2] == '0') {
			st += '0';
			i += 2;
		}
		else if (str[i + 1] == '>' && ((str[i] == '1' && str[i + 2] == '1')
			|| str[i] == '0' && (str[i + 2] == '1' || str[i + 2] == '0'))) {
			st += '1';
			i += 2;
		}
		else st += str[i];
	}
	str = st;
}
//取等值表达式
void qvdengzhi(string &str)
{
	string st = "";
	for (int i = 0; i < str.size(); ++i) {
		if (str[i + 1] == '-' && ((str[i] == '1' && str[i + 2] == '1') || (str[i] == '0' && str[i + 2] == '0'))) {
			st += '1';
			i += 2;
		}
		else if (str[i + 1] == '-' && ((str[i] == '1' && str[i + 2] == '0') || (str[i] == '0' && str[i + 2] == '1'))) {
			st += '0';
			i += 2;
		}
		else st += str[i];
	}
	str = st;
}

int main()
{
	string str, tmp;
	char chs[26];
	cout << "逻辑表达式帮助：\r\n\
			1.只能用小写字母，因为写到这里我的腰顶不住了。\r\n\
			2.符号取用:非! 合取* 析取 | 蕴含 > 等值 - \r\n\
			3.可以参考一下加减乘除运算的写法（逆波兰、堆栈）\r\n\
			4.为什么写不出上面那个？\r\n\
			5.因为我菜。" << endl;
	cout << "请输入您的逻辑表达式(只能用小写字母)：";
	cin >> str;//输入表达式
	getAlpha(str, chs, cnt);  //只讨论小写字母，获取表达式中的字符
	tmp = str;

	//输出第一行	p  q  p|q
	for (int j = 0; j < cnt; ++j) {
		cout << chs[j] << "\t";
	}
	cout << tmp;
	cout << endl;

	//2的n次方种情况
	for (int i = 0; i < pow(2, cnt); ++i) {
		for (int j = 0; j < cnt; ++j) { //赋值过程
			chval[chs[j] - 'a'] = (1 & (i >> (cnt - 1 - j)));
		}
		for (int j = 0; j < cnt; ++j) {
			cout << chval[chs[j] - 'a'] << "\t";
		}
		str = shuzhitihuan(str, chval);
		while (str.size() != 1) {
			qvkuohao(str);
			qvfei(str);
			qvheqv(str);
			qvxiqv(str);
			qvyunhan(str);
			qvdengzhi(str);
		}
		for (int i = 0; i < tmp.size() / 2; ++i) cout << ' ';
		cout << str << endl;
		str = tmp;
	}

	//(p>q)*(!r>p)*!q
	getchar();
}
