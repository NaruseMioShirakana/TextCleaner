/*
0. ���ܰ������Զ����������е�[��,��]������תƴ����һ��һ������ĸ+ȫƴ����������תƴ����һ�Զ࣬����ĸ+ȫƴ����
1. �汾��V1.0   ���ڣ�2019��06��06��
2. ���飺
	https://blog.csdn.net/weixin_38887369/article/details/91047524   // ����Դ��Ŀ����
	https://blog.csdn.net/weixin_38887369                            // 
3. ��Ȩ���� qq:2271590144,����
4. ʹ������:c++,ʹ�ÿ⣺qt
5. qt��ֻʹ���� qstring qstringlist qvector������㲻��ʹ��qt,ֱ��ʹ�ñ�׼��c++Ҳ�ɣ�ֻ��Ҫ�����ٵĸĶ�
   ���ʹ�ñ�׼��c++��,�Ķ����£�
   qstring     -> string
   qstringlist -> vector<string>
   qvector     -> vector
   a. cpp�ļ��еĴ����300������,���ԸĶ�����
   b. [vector,qvector],[string,qstring] �����ƶȼ��ߣ��ܶຯ������һ���ģ����Ը�����Ҳ����
   c. ʹ�ñ�׼��stringЧ�ʻ����
6. ʵ�����ò��ԣ�
	a. �Ѿ����ã�ûʲô����
	b. �ٶȲ��ԣ�������win10ϵͳ + i5-8265U + ���߳��� + ÿ��3���� ���ֲܴڵ��ٶȲ��Խ������
	   getComPingyinForStr() => 50 ��/ms
	   getNamePingyin()      => 100��/ms
7. ʹ�÷���������ֱ�ӿ����ļ���.h�ļ�����ע�� �� ��������ҳ�濪�����ڶ�������ַ 

���£�
	V2.0 2020��04��10�գ�
	1. ����c++�汾����Ҫʹ��wstring
	2. ɾ���ֿ��е�: ','
	3. ���ĺ����жϹ������鿴isHanziChar(wchar_t wch);
*/
#pragma once

#include <string>
#include <vector>
using namespace std;


// ----- �ⲿʹ�� ----- //
/* 
0. ��ȡ���ƴ��(һ���ܶԶ�),��������
1. eg: 
	getComPingyinForStr("���",fristPy,fullPy);    // fristPy =  "jg xg jh xh"  , fullPy =  "jiegong xiegong jiehong xiehong"
	getComPingyinForStr("���",fristPy,fullPy);    // fristPy =  "cc zc cz zz"  , fullPy =  "chacha zhacha chazha zhazha"
	getComPingyinForStr("ξ����",fristPy,fullPy);  // fristPy =  "wcm ycm"  , fullPy =  "weichimeng yuchimeng"
	getComPingyinForStr("��ʯ",fristPy,fullPy);    // fristPy =  "ld ls"  , fullPy =  "lidan lishi"
	getComPingyinForStr("С��",fristPy,fullPy);    // fristPy =  "xm"  , fullPy =  "xiaoming"
*/
int getComPingyinForStr(const wstring& inStr, wstring& outFrist_py, wstring& outFull_py);//ok
/*
0. ���ա������ֱ�תƴ�����ϸ��һһ��Ӧ�������ں���ǿתƴ��
1. ʹ���ˣ�������������ֿ� + �����ֳ��ö����ֿ� + ȫ�ֿ�
2. eg:
	str = getNamePingyin("��",true);   // str => "chun"
	str = getNamePingyin("��",false);  // str => "chun"
	
	str = getNamePingyin("��",true);   // str => "xie"
	str = getNamePingyin("��",false);  // str => "jie"
	
	str = getNamePingyin("��",true);   // str => "zhai"
	str = getNamePingyin("��",false);  // str => "di"

	str = getNamePingyin("��",true);   // str => "can"
	str = getNamePingyin("��",false);  // str => "can"

	str = getNamePingyin("����",true);   // str => "chanyu"
	str = getNamePingyin("����",false);  // str => "danyu"
*/
wstring getNamePingyin(const wstring& inStr, bool isLastName);//ok
/*
0. �Զ��з� �ա���
1. ����ֻ��Ӧ����ͨ�ĸ��գ������֣�������ڸ��ձ���û���ҵ�����: ���� = ��fullName.size() == 4�� ? fullName��ǰ�������ַ� �� fullName�ĵ�һ���ַ�
2. ��ע���ٶȵ����ϻ�����70�����������90�������Ǻ��Ե�������������ϣ�Ҳ��Ҫ��Ϊ���վ��������֣�(���й������������ϡ����ܴ����1���)
   ���磺���������ϡ����¾��ޡ�ť��»��ɫ�ϡ����꣨�Ҽ����ܶ�������ģ�
3. eg:
	wcout << L"������ֲ��ԣ�" << endl;
	wstring names[13] = { L"����̫һ", L"ξ��С��", L"�Ⲩ", L"����", L"�ձ���", L"��˧", L"����", L"����", L"����ʿ��ȱ��", L"������", L"�ջ���ķ", L"�Ϲ���", L"mack" };
	for (size_t i = 0; i < 13; i++)
	{
		wstring full, fist, last;
		full = names[i];
		myNameSplit(full, last, fist);
		wcout << full <<  L" => ��:" << last  <<L" ,��:" << fist << endl;
	}

	// ���
	������ֲ��ԣ�
	����̫һ	 => ��:���� ,��:̫һ
	ξ��С��	 => ��:ξ�� ,��:С��
	�Ⲩ		 => ��:��   ,��:��
	����		 => ��:��   ,��:��
	�ձ���		 => ��:��   ,��:����
	��˧		 => ��:��   ,��:˧
	����		 => ��:��   ,��:���
	����         => ��:��   ,��:��
	����ʿ��ȱ�� => ��:��   ,��:��ʿ��ȱ��
	������		 => ��:��   ,��:����
	�ջ���ķ     => ��:�ջ� ,��:��ķ
	�Ϲ���       => ��:�Ϲ� ,��:��
	mack         => ��:     ,��:mack
*/
void myNameSplit(const wstring& inFullName, wstring& outLastName, wstring& outFirstName);//ok


// ----- �ڲ���ʹ�� ----- //
/*
0. ��ȡһ�����ֵġ����С�ƴ��(����ĸ��ȫƴ)
1. ʹ���ֿ� �� hanziTables[]
2. �������Ϊ�գ���������͵��ڿ�
3. �������Ϊ�������ַ����򷵻غ�����һ��
4. inWord ֻ������һ�����֣����򷵻�-1
5. eg:
   getAllPingyinForWord("��",fristPy,fullPy); // fristPy => {"g","j"} , fullPy => {"gou","ju"}
   getAllPingyinForWord("��",fristPy,fullPy); // fristPy => {"l"}     , fullPy => {"long"}
*/
int getAllPingyinForWord(const wstring& inWord, vector<wstring>& outFrist_py, vector<wstring>& outFull_py); 
/*
0. ��ȡһ���ֵ�ƴ��,����Ƕ����ַ��س��ö���
1. ƫ�������ķ���ƫ��,���������ϵķ���ƫ��
2. �������Ϊ�գ���������͵��ڿ�
3. ʹ���ֿ⣺multiToneWordTable[]�������ֿ⣩+ hanziTables[]��ȫ�ֿ⣩
4. �������Ϊ�������ַ����򷵻غ�����һ��
5. �����ֵ�ȡ��������multiToneWordTable[]
6. inWord ֻ������һ�����֣�����ֱ�ӷŻ���������
7. eg:
   str = getNoRepeatPingyinForWord("��"); // str => "da"
   str = getNoRepeatPingyinForWord("��"); // str => "jie"
   str = getNoRepeatPingyinForWord("ʯ"); // str => "shi"
*/
wstring getNoRepeatPingyinForWord(const wstring& inWord);
/* 
0. ����Ƿ��Ǻ���
1. ��ͬ�ı��뷽ʽ��IDE��������Ҫ��ͬ������ֵ
*/
bool isHanziChar(wchar_t wch);
/* 
0. ���Ա��ֿ��ڱ�����������ʱ�ĺ��ֵı���ֵ
*/
void testHanziRang();