#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <codecvt>
#include <comutil.h>  
#pragma comment(lib, "comsuppw.lib")
using namespace std;
wstring to_wstring(const string& s)
{
	_bstr_t t = s.c_str();
	wchar_t* pwchar = (wchar_t*)t;
	wstring result = pwchar;
	return result;
}
int main()
{
	//提示信息
	cout << "请确保\"zx.txt\"在当前文件夹内再继续!\n";
	cout << "注意\"zx.txt\"内不能有多余的空格,换行,注释等!\n";
	system("pause");
	ifstream in;//创建读取需要的类
	in.open("zx.txt");//打开读取文件
	if (!in.is_open())//检测zx.txt是否打开
	{
		cout << "\"zx.txt\"没有打开!\n即将退出程序!\n";
		system("pause");
		exit(-1);
	}
	//开始处理文本
	vector<string> zx;//使用vector容器,无需担心使用数组固定长度导致的缓冲区溢出
	string temp;//临时读取的字符串,保存到vector容器里
	int i = 0;//保存读取的总行数
	while (!in.eof())
	{
		getline(in, temp);//读取每行的字符串然后保存在临时字符串里
		zx.push_back(temp);//临时字符串再放入vector容器中
		++i;//读取一行后+1
	}
	in.close();//关闭读取文件
	//输出处理后的文本
	if (i >= 50)
	{
		cout << "alias *Crosshair-1 \"echo *Crosshair-1;apply_crosshair_code " + zx[0] + ";alias *Crosshair-next *Crosshair-2" + ";alias *Crosshair-last *Crosshair-" + to_string(i) + "\"\n";
		cout << "alias *Crosshair-2 \"echo *Crosshair-2;apply_crosshair_code " + zx[1] + ";alias *Crosshair-next *Crosshair-3" + ";alias *Crosshair-last *Crosshair-1\"\n";
		cout << "alias *Crosshair-3 \"echo *Crosshair-3;apply_crosshair_code " + zx[2] + ";alias *Crosshair-next *Crosshair-4" + ";alias *Crosshair-last *Crosshair-2\"\n";
		cout << "...\n";
		cout << "因为太长已省略" + to_string(i - 6) + "行输出!!!\n";
		cout << "...\n";
		cout << "alias *Crosshair-" + to_string(i - 2) + " \"echo *Crosshair-" + to_string(i - 2) + ";apply_crosshair_code " + zx[i - 3] + ";alias *Crosshair-next *Crosshair-" + to_string(i - 1) + ";alias *Crosshair-last *Crosshair-" + to_string(i - 3) + "\"\n";
		cout << "alias *Crosshair-" + to_string(i - 1) + " \"echo *Crosshair-" + to_string(i - 1) + ";apply_crosshair_code " + zx[i - 2] + ";alias *Crosshair-next *Crosshair-" + to_string(i) + ";alias *Crosshair-last *Crosshair-" + to_string(i - 2) + "\"\n";
		cout << "alias *Crosshair-" + to_string(i) + " \"echo *Crosshair-" + to_string(i) + ";apply_crosshair_code " + zx[i - 1] + ";alias *Crosshair-next *Crosshair-1" + ";alias *Crosshair-last *Crosshair-" + to_string(i - 1) + "\"\n";
	}
	else
	{
		cout << "alias *Crosshair-1 \"echo *Crosshair-1;apply_crosshair_code " + zx[0] + ";alias *Crosshair-next *Crosshair-2" + ";alias *Crosshair-last *Crosshair-" + to_string(i) + "\"\n";
		for (size_t j = 1, k = i; j < i - 1; j++)
		{
			cout << "alias *Crosshair-" + to_string(j + 1) + " \"echo *Crosshair-" + to_string(j + 1) + ";apply_crosshair_code " + zx[j] + ";alias *Crosshair-next *Crosshair-" + to_string(j + 2) + ";alias *Crosshair-last *Crosshair-" + to_string(j) + "\"\n";
		}
		cout << "alias *Crosshair-" + to_string(i) + " \"echo *Crosshair-" + to_string(i) + ";apply_crosshair_code " + zx[i - 1] + ";alias *Crosshair-next *Crosshair-1" + ";alias *Crosshair-last *Crosshair-" + to_string(i - 1) + "\"\n";
	}
	wofstream out;
	out.open("crosshair.cfg");
	out.imbue(std::locale(out.getloc(), new std::codecvt_utf8<wchar_t, 0x10ffff, std::little_endian>));
	out << to_wstring("echo \"============================\"\necho \"=|Scmd:\\切换准星\"\necho \"============================\"\necho \"=1.切换为上一个准星\"\necho \"=2.切换为下一个准星\"\necho \"=3.临时保存当前的cfg\"\necho \"=4.加载临时保存的cfg\"\necho \"============================\"\necho \"=00.刷新\"\necho \"============================\"\nalias 1 *Crosshair-next\nalias 2 *Crosshair-last\nalias 3 \"host_writeconfig Scmd_crosshair_temp\"\nalias 4 \"exec Scmd_crosshair_temp\"\nalias 00 \"exec crosshair\"\n");
	out << to_wstring("alias *Crosshair-next *Crosshair-2;alias *Crosshair-last *Crosshair-" + to_string(i) + "\"\n");
	out << to_wstring("alias *Crosshair-1 \"echo *Crosshair-1;apply_crosshair_code " + zx[0] + ";alias *Crosshair-next *Crosshair-2" + ";alias *Crosshair-last *Crosshair-" + to_string(i) + "\"\n");
	for (size_t j = 1, k = i; j < i - 1; j++)
	{
		out << to_wstring("alias *Crosshair-" + to_string(j + 1) + " \"echo *Crosshair-" + to_string(j + 1) + ";apply_crosshair_code " + zx[j] + ";alias *Crosshair-next *Crosshair-" + to_string(j + 2) + ";alias *Crosshair-last *Crosshair-" + to_string(j) + "\"\n");
	}
	out << to_wstring("alias *Crosshair-" + to_string(i) + " \"echo *Crosshair-" + to_string(i) + ";apply_crosshair_code " + zx[i - 1] + ";alias *Crosshair-next *Crosshair-1" + ";alias *Crosshair-last *Crosshair-" + to_string(i - 1) + "\"");
	out.close();
	cout << "\n已完成!\n";
	//结束
	system("pause");
	return 0;
}