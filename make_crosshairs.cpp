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
	//��ʾ��Ϣ
	cout << "��ȷ��\"zx.txt\"�ڵ�ǰ�ļ������ټ���!\n";
	cout << "ע��\"zx.txt\"�ڲ����ж���Ŀո�,����,ע�͵�!\n";
	system("pause");
	ifstream in;//������ȡ��Ҫ����
	in.open("zx.txt");//�򿪶�ȡ�ļ�
	if (!in.is_open())//���zx.txt�Ƿ��
	{
		cout << "\"zx.txt\"û�д�!\n�����˳�����!\n";
		system("pause");
		exit(-1);
	}
	//��ʼ�����ı�
	vector<string> zx;//ʹ��vector����,���赣��ʹ������̶����ȵ��µĻ��������
	string temp;//��ʱ��ȡ���ַ���,���浽vector������
	int i = 0;//�����ȡ��������
	while (!in.eof())
	{
		getline(in, temp);//��ȡÿ�е��ַ���Ȼ�󱣴�����ʱ�ַ�����
		zx.push_back(temp);//��ʱ�ַ����ٷ���vector������
		++i;//��ȡһ�к�+1
	}
	in.close();//�رն�ȡ�ļ�
	//����������ı�
	if (i >= 50)
	{
		cout << "alias *Crosshair-1 \"echo *Crosshair-1;apply_crosshair_code " + zx[0] + ";alias *Crosshair-next *Crosshair-2" + ";alias *Crosshair-last *Crosshair-" + to_string(i) + "\"\n";
		cout << "alias *Crosshair-2 \"echo *Crosshair-2;apply_crosshair_code " + zx[1] + ";alias *Crosshair-next *Crosshair-3" + ";alias *Crosshair-last *Crosshair-1\"\n";
		cout << "alias *Crosshair-3 \"echo *Crosshair-3;apply_crosshair_code " + zx[2] + ";alias *Crosshair-next *Crosshair-4" + ";alias *Crosshair-last *Crosshair-2\"\n";
		cout << "...\n";
		cout << "��Ϊ̫����ʡ��" + to_string(i - 6) + "�����!!!\n";
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
	out << to_wstring("echo \"============================\"\necho \"=|Scmd:\\�л�׼��\"\necho \"============================\"\necho \"=1.�л�Ϊ��һ��׼��\"\necho \"=2.�л�Ϊ��һ��׼��\"\necho \"=3.��ʱ���浱ǰ��cfg\"\necho \"=4.������ʱ�����cfg\"\necho \"============================\"\necho \"=00.ˢ��\"\necho \"============================\"\nalias 1 *Crosshair-next\nalias 2 *Crosshair-last\nalias 3 \"host_writeconfig Scmd_crosshair_temp\"\nalias 4 \"exec Scmd_crosshair_temp\"\nalias 00 \"exec crosshair\"\n");
	out << to_wstring("alias *Crosshair-next *Crosshair-2;alias *Crosshair-last *Crosshair-" + to_string(i) + "\"\n");
	out << to_wstring("alias *Crosshair-1 \"echo *Crosshair-1;apply_crosshair_code " + zx[0] + ";alias *Crosshair-next *Crosshair-2" + ";alias *Crosshair-last *Crosshair-" + to_string(i) + "\"\n");
	for (size_t j = 1, k = i; j < i - 1; j++)
	{
		out << to_wstring("alias *Crosshair-" + to_string(j + 1) + " \"echo *Crosshair-" + to_string(j + 1) + ";apply_crosshair_code " + zx[j] + ";alias *Crosshair-next *Crosshair-" + to_string(j + 2) + ";alias *Crosshair-last *Crosshair-" + to_string(j) + "\"\n");
	}
	out << to_wstring("alias *Crosshair-" + to_string(i) + " \"echo *Crosshair-" + to_string(i) + ";apply_crosshair_code " + zx[i - 1] + ";alias *Crosshair-next *Crosshair-1" + ";alias *Crosshair-last *Crosshair-" + to_string(i - 1) + "\"");
	out.close();
	cout << "\n�����!\n";
	//����
	system("pause");
	return 0;
}