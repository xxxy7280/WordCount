//D:\\WordCount\\201831061307\\Count\\input.txt
#include "pch.h"
#include <iostream>
#include<fstream>
//#include <string>
#include "Count.h"
using namespace std;
typedef struct node {
	string  str = "";//记录单词
	int length = 0;//存放词组长度
	int many = 0;//记录频率
}count;
FILE *fp;
node Words[10000];//存放单词
node numoftop[10000];
int numofwords = 0;//记录有多少个单词，不包括重复的；
//统计字符个数 单个字母，数字，空格，\t,\n
int  Cal::Characters()
{
	int count = 0;
	char ch;
	do
	{
		ch = fgetc(fp);
		if (ch<'Z'&&ch>'A' || ch<'z'&&ch>'a')
			count++;
		else if ((ch > '0' || ch == '0') && (ch < '10' || ch == '10'))
			count++;
		else if (ch == ' ' || ch == '\n' || ch == '\t')
			count++;
	} while (ch != EOF);
	rewind(fp);//文件指针指向文件开头，方便其他函数操作
	return count;
}
//统计单词个数 不区分大小写
int Cal::Word_s()
{
	char ch;
	ch = fgetc(fp);
	int wordcount = 0;
	while (ch != EOF)
	{
		if ((ch >= 'a'&&ch <= 'z') || (ch >= 'A'&&ch <= 'Z') || (ch >= '0'&&ch <= '9'))
		{
			while ((ch >= 'a'&&ch <= 'z') || (ch >= 'A'&&ch <= 'Z') || (ch >= '0'&&ch <= '9') || ch == '_')
			{
				ch = fgetc(fp);
			}
			wordcount++;
			ch = fgetc(fp);
		}
		else
		{
			ch = fgetc(fp);
		}
	}
	rewind(fp);
	return wordcount;
}
//统计文件有效行数
int Cal::Lines()
{
	int linecount = 1;
	int flag = 0;//辅助判断是否为空行
	char ch;
	ch = fgetc(fp);
	while (ch != EOF)
	{
		if (ch == '\n')
		{
			
			if(flag==0)
			linecount++;
			ch = fgetc(fp);
			flag = 1;
		}
		else
		{
			ch = fgetc(fp);
			flag = 0;
		}
	}
	
	rewind(fp);
	return linecount;
}
//统计文件中各单词的出现次数，最终只输出频率最高的10个。频率相同的单词，优先输出字典序靠前的单词
int  Cal::panduan(string temp)//判断所得字符串是否为单词
{
	int i = 1, a = 0, length;
	length = temp.length();
	if (temp == "")
		a = 0;
	else if (length < 4)//长度小于4时，则全部是字母才能算是单词
	{
		for (i = 1; i <= length; i++)
		{
			if (temp[i - 1] >= '0'&&temp[i - 1] <= '9')
			{
				a = 0;
				break;
			}
			else
			{
				a = 1;
			}
		}
	}
	else {
		for (i = 1; i <= 4; i++)//长度大于4时只需要判断前四个字符是否字母即可
		{
			if (temp[i - 1] >= '0'&&temp[i - 1] <= '9')
			{
				a = 0;
				break;
			}
			else
			{
				a = 1;
			}
		}
	}
	return a;//a=1代表该字符串是单词，a=0则表示该字符串不是单词
}

int  Cal::compare(string temp)//对新的单词与已存入的结构体数组的单词进行比较，
{
	int a = -1, i = 0;
	if (numofwords == 0)
		a = -1;//当结构体中没存放东西时，不用再比较
	for (i = 0; i < numofwords; i++)
	{
		if (temp == Words[i].str)
		{
			a = i;
			break;
		}
	}
	return a;
}

void  Cal::words()//从文件中读取单词
{
	fstream file("D:\\WordCount\\201831061307\\Count\\input.txt", ios::in);
	char c;
	int i = 0;
	string temp = "";
	while (file.get(c))
	{
		//while (c != ' '&&c != ','&&c != '.'&&c != '\r'&&c != '\n'&&c!='	')//排除掉除字母数字以外的符号
		while ((c >= '0'&&c <= '9') || (c <= 'z'&&c >= 'a') || (c <= 'Z'&&c >= 'A'))//除字母数字以外其余字符全部排除
		{
			if (c >= 'A'&&c <= 'Z')//若字符为大写字母则转换为小写字母
			{
				c += 32;
			}
			temp += c;
			file.get(c);
		}
		if (panduan(temp) == 1)
		{
			if (compare(temp) != -1)//若结构体中有相同的单词，则频率+1
			{
				i = compare(temp);
				Words[i].many++;
			}
			else {//结构体中没有相同的单词，则存入结构体中。
				Words[numofwords].str = temp;
				Words[numofwords].many = 1;
				Words[numofwords].length = temp.length();
				numofwords++;
			}
		}
		temp = "";
	}
}

void  Cal::sort()//按频率进行排序
{
	int i = 0, j = 0;
	node c;
	for (i = 0; i < numofwords - 1; i++)
	{
		for (j = i + 1; j < numofwords; j++)
		{
			if (Words[i].many < Words[j].many)
			{
				c = Words[i];
				Words[i] = Words[j];
				Words[j] = c;
			}
		}
	}
}
void  Cal::shuchu(int n)//按要求输出一定数量的单词
{
	int i = 0;
	for (i = 0; i < n; i++)
	{
		cout << "word:" << Words[i].str << endl << "num:" << Words[i].many << endl;
	}
}
void  Cal::All()//输出所有功能结果
{
	cout << "characters: " << Characters() << endl;
	cout << "words: " << Word_s() << endl;
	cout << "lines: " << Lines() << endl;
	for (int i = 0; i < numofwords - 1; i++)
	{
		cout << Words[i].str << "\t";
		cout << Words[i].many << endl;
	}
}
void  Cal::Output(string path)//输出到文件
{
	ofstream fout;
	string path_1="D:\\wordCount\\201831061307\\Count\\"+path;
	fout.open(path_1);
	//fout.open("D:\\wordCount\\201831061307\\Count\\output.txt");
	fout << "characters:  " << Characters() << endl;
	fout << "words:  " <<Word_s() << endl;
	fout << "lines:  " << Lines() << endl;
	for (int i = 0; i < numofwords - 1; i++)
	{
		fout <<  Words[i].str<< "\t";
		fout << Words[i].many << endl;
	}
	fout.close();
	cout << "成功写入文件"<<endl;
}
int main(int argc, char *argv[])
{
	Cal x;
	x.words();
	x.sort();
	if (strcmp(argv[1], "-f") == 0)
	{
		int n;
		cout << "输出频率前n的单词 " << "input n";
		cin >> n;
		x.shuchu(n);
	}
	else if(strcmp(argv[1], "-c") == 0 || strcmp(argv[1], "-w") == 0 || strcmp(argv[1], "-l") == 0 \
		|| strcmp(argv[1], "-a") == 0 || strcmp(argv[1], "-o") == 0)
	{
		errno_t  err;
		err = fopen_s(&fp, "D:\\WordCount\\201831061307\\Count\\eee.txt", "r+");
		if (fp == NULL)
		{
			cout << "The file can not be opened" << endl;
			exit(0);
		}
		else if (strcmp(argv[1], "-c") == 0)
		{

			cout << "characters: " << x.Characters() << endl;
		}

		else if (strcmp(argv[1], "-w") == 0)
		{
			cout << "words: " << x.Word_s() << endl;
		}

		else if (strcmp(argv[1], "-l") == 0)
		{

			cout << "lines: " << x.Lines() << endl;
		}
		else if (strcmp(argv[1], "-a") == 0)
		{
			x.All();
		}
		else if (strcmp(argv[1], "-o") == 0)
		{
			x.Output(argv[2]);
		}
		fclose(fp);
	}
	else
	{
		cout << "input error!" << endl;
	}
	return 0;
}