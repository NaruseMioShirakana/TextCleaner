#include "myPinyin.h"

#define g_length_lastNameTable 554
#define g_length_multiToneWordTable 708
#define g_length_hanziTables 411

// ����-ƴ��
struct hanziTableS
{
	// ƴ��
	wstring first_py;  // ����ĸ
	wstring full_py;   // ȫƴ

	// ����
	wstring hanzis;
};

// �������Ϸ���
struct lastNameTableS
{
	wstring hanzi;
	wstring pinyi;
};

// ���ö�����
struct multiToneWordTableS
{
	wstring hanzi;
	wstring pinyi;
};


/* 
0. �����������(���������⡢�����⡢���ն���)
1. �����Լ����
3. ��Դ�ڸ����������ݵ�����
*/
lastNameTableS lastNameTable[g_length_lastNameTable] =
{
{ L"��" , L"zhao" },
{ L"Ǯ" , L"qian" },
{ L"��" , L"sun" },
{ L"��" , L"li" },
{ L"��" , L"zhou" },
{ L"��" , L"wu" },
{ L"֣" , L"zheng" },
{ L"��" , L"wang" },
{ L"��" , L"feng" },
{ L"��" , L"chen" },
{ L"��" , L"chu" },
{ L"��" , L"wei" },
{ L"��" , L"jiang" },
{ L"��" , L"shen" },
{ L"��" , L"han" },
{ L"��" , L"yang" },
{ L"��" , L"zhu" },
{ L"��" , L"qin" },
{ L"��" , L"you" },
{ L"��" , L"xu" },
{ L"��" , L"he" },
{ L"��" , L"lv" },
{ L"ʩ" , L"shi" },
{ L"��" , L"zhang" },
{ L"��" , L"kong" },
{ L"��" , L"cao" },
{ L"��" , L"yan" },
{ L"��" , L"hua" },
{ L"��" , L"jin" },
{ L"κ" , L"wei" },
{ L"��" , L"tao" },
{ L"��" , L"jiang" },
{ L"��" , L"qi" },
{ L"л" , L"xie" },
{ L"��" , L"zou" },
{ L"��" , L"yu" },
{ L"��" , L"bai" },
{ L"ˮ" , L"shui" },
{ L"�" , L"dou" },
{ L"��" , L"zhang" },
{ L"��" , L"yun" },
{ L"��" , L"su" },
{ L"��" , L"pan" },
{ L"��" , L"ge" },
{ L"��" , L"xi" },
{ L"��" , L"fan" },
{ L"��" , L"peng" },
{ L"��" , L"lang" },
{ L"³" , L"lu" },
{ L"Τ" , L"wei" },
{ L"��" , L"chang" },
{ L"��" , L"ma" },
{ L"��" , L"miao" },
{ L"��" , L"feng" },
{ L"��" , L"hua" },
{ L"��" , L"fang" },
{ L"��" , L"yu" },
{ L"��" , L"ren" },
{ L"Ԭ" , L"yuan" },
{ L"��" , L"liu" },
{ L"ۺ" , L"feng" },
{ L"��" , L"bao" },
{ L"ʷ" , L"shi" },
{ L"��" , L"tang" },
{ L"��" , L"fei" },
{ L"��" , L"lian" },
{ L"�" , L"cen" },
{ L"Ѧ" , L"xue" },
{ L"��" , L"lei" },
{ L"��" , L"he" },
{ L"��" , L"ni" },
{ L"��" , L"tang" },
{ L"��" , L"teng" },
{ L"��" , L"yin" },
{ L"��" , L"luo" },
{ L"��" , L"bi" },
{ L"��" , L"hao" },
{ L"��" , L"wu" },
{ L"��" , L"an" },
{ L"��" , L"chang" },
{ L"��" , L"yue" },
{ L"��" , L"yu" },
{ L"ʱ" , L"shi" },
{ L"��" , L"fu" },
{ L"Ƥ" , L"pi" },
{ L"��" , L"bian" },
{ L"��" , L"qi" },
{ L"��" , L"kang" },
{ L"��" , L"wu" },
{ L"��" , L"yu" },
{ L"Ԫ" , L"yuan" },
{ L"��" , L"bu" },
{ L"��" , L"gu" },
{ L"��" , L"meng" },
{ L"ƽ" , L"ping" },
{ L"��" , L"huang" },
{ L"��" , L"he" },
{ L"��" , L"mu" },
{ L"��" , L"xiao" },
{ L"��" , L"yin" },
{ L"Ҧ" , L"yao" },
{ L"��" , L"shao" },
{ L"տ" , L"zhan" },
{ L"��" , L"wang" },
{ L"��" , L"qi" },
{ L"ë" , L"mao" },
{ L"��" , L"yu" },
{ L"��" , L"di" },
{ L"��" , L"mi" },
{ L"��" , L"bei" },
{ L"��" , L"ming" },
{ L"�" , L"zang" },
{ L"��" , L"ji" },
{ L"��" , L"fu" },
{ L"��" , L"cheng" },
{ L"��" , L"dai" },
{ L"̸" , L"tan" },
{ L"��" , L"song" },
{ L"é" , L"mao" },
{ L"��" , L"pang" },
{ L"��" , L"xiong" },
{ L"��" , L"ji" },
{ L"��" , L"shu" },
{ L"��" , L"qu" },
{ L"��" , L"xiang" },
{ L"ף" , L"zhu" },
{ L"��" , L"dong" },
{ L"��" , L"liang" },
{ L"��" , L"du" },
{ L"��" , L"ruan" },
{ L"��" , L"lan" },
{ L"��" , L"min" },
{ L"ϯ" , L"xi" },
{ L"��" , L"ji" },
{ L"��" , L"ma" },
{ L"ǿ" , L"qiang" },
{ L"��" , L"jia" },
{ L"·" , L"lu" },
{ L"¦" , L"lou" },
{ L"Σ" , L"wei" },
{ L"��" , L"jiang" },
{ L"ͯ" , L"tong" },
{ L"��" , L"yan" },
{ L"��" , L"guo" },
{ L"÷" , L"mei" },
{ L"ʢ" , L"sheng" },
{ L"��" , L"lin" },
{ L"��" , L"diao" },
{ L"��" , L"zhong" },
{ L"��" , L"xu" },
{ L"��" , L"qiu" },
{ L"��" , L"luo" },
{ L"��" , L"gao" },
{ L"��" , L"xia" },
{ L"��" , L"cai" },
{ L"��" , L"tian" },
{ L"��" , L"fan" },
{ L"��" , L"hu" },
{ L"��" , L"ling" },
{ L"��" , L"huo" },
{ L"��" , L"yu" },
{ L"��" , L"wan" },
{ L"֧" , L"zhi" },
{ L"��" , L"ke" },
{ L"��" , L"zan" },
{ L"��" , L"guan" },
{ L"¬" , L"lu" },
{ L"Ī" , L"mo" },
{ L"��" , L"jing" },
{ L"��" , L"fang" },
{ L"��" , L"qiu" },
{ L"��" , L"miao" },
{ L"��" , L"gan" },
{ L"��" , L"xie" },
{ L"Ӧ" , L"ying" },
{ L"��" , L"zong" },
{ L"��" , L"ding" },
{ L"��" , L"xuan" },
{ L"��" , L"ben" },
{ L"��" , L"deng" },
{ L"��" , L"yu" },
{ L"��" , L"shan" },
{ L"��" , L"hang" },
{ L"��" , L"hong" },
{ L"��" , L"bao" },
{ L"��" , L"zhu" },
{ L"��" , L"zuo" },
{ L"ʯ" , L"shi" },
{ L"��" , L"cui" },
{ L"��" , L"ji" },
{ L"ť" , L"niu" },
{ L"��" , L"gong" },
{ L"��" , L"cheng" },
{ L"��" , L"ji" },
{ L"��" , L"xing" },
{ L"��" , L"hua" },
{ L"��" , L"pei" },
{ L"½" , L"lu" },
{ L"��" , L"rong" },
{ L"��" , L"weng" },
{ L"��" , L"xun" },
{ L"��" , L"yang" },
{ L"�" , L"yu" },
{ L"��" , L"hui" },
{ L"��" , L"zhen" },
{ L"��" , L"qu" },
{ L"��" , L"jia" },
{ L"��" , L"feng" },
{ L"��" , L"rui" },
{ L"��" , L"yi" },
{ L"��" , L"chu" },
{ L"��" , L"jin" },
{ L"��" , L"ji" },
{ L"��" , L"bing" },
{ L"��" , L"mi" },
{ L"��" , L"song" },
{ L"��" , L"jing" },
{ L"��" , L"duan" },
{ L"��" , L"fu" },
{ L"��" , L"wu" },
{ L"��" , L"wu" },
{ L"��" , L"jiao" },
{ L"��" , L"ba" },
{ L"��" , L"gong" },
{ L"��" , L"mu" },
{ L"��" , L"kui" },
{ L"ɽ" , L"shan" },
{ L"��" , L"gu" },
{ L"��" , L"che" },
{ L"��" , L"hou" },
{ L"�" , L"mi" },
{ L"��" , L"peng" },
{ L"ȫ" , L"quan" },
{ L"ۭ" , L"xi" },
{ L"��" , L"ban" },
{ L"��" , L"yang" },
{ L"��" , L"qiu" },
{ L"��" , L"zhong" },
{ L"��" , L"yi" },
{ L"��" , L"gong" },
{ L"��" , L"ning" },
{ L"��" , L"qiu" },
{ L"��" , L"luan" },
{ L"��" , L"bao" },
{ L"��" , L"gan" },
{ L"��" , L"tou" },
{ L"��" , L"li" },
{ L"��" , L"rong" },
{ L"��" , L"zu" },
{ L"��" , L"wu" },
{ L"��" , L"fu" },
{ L"��" , L"liu" },
{ L"��" , L"jing" },
{ L"ղ" , L"zhan" },
{ L"��" , L"shu" },
{ L"��" , L"long" },
{ L"Ҷ" , L"ye" },
{ L"��" , L"xing" },
{ L"˾" , L"si" },
{ L"��" , L"shao" },
{ L"۬" , L"gao" },
{ L"��" , L"li" },
{ L"��" , L"ji" },
{ L"��" , L"bo" },
{ L"ӡ" , L"yin" },
{ L"��" , L"su" },
{ L"��" , L"bai" },
{ L"��" , L"huai" },
{ L"��" , L"pu" },
{ L"ۢ" , L"tai" },
{ L"��" , L"cong" },
{ L"��" , L"e" },
{ L"��" , L"suo" },
{ L"��" , L"xian" },
{ L"��" , L"ji" },
{ L"��" , L"lai" },
{ L"׿" , L"zhuo" },
{ L"��" , L"lin" },
{ L"��" , L"tu" },
{ L"��" , L"meng" },
{ L"��" , L"chi" },
{ L"��" , L"qiao" },
{ L"��" , L"yin" },
{ L"��" , L"yu" },
{ L"��" , L"xu" },
{ L"��" , L"nai" },
{ L"��" , L"cang" },
{ L"˫" , L"shuang" },
{ L"��" , L"wen" },
{ L"ݷ" , L"shen" },
{ L"��" , L"dang" },
{ L"��" , L"zhai" },
{ L"̷" , L"tan" },
{ L"��" , L"gong" },
{ L"��" , L"lao" },
{ L"��" , L"pang" },
{ L"��" , L"ji" },
{ L"��" , L"shen" },
{ L"��" , L"fu" },
{ L"��" , L"du" },
{ L"Ƚ" , L"ran" },
{ L"��" , L"zai" },
{ L"۪" , L"li" },
{ L"Ӻ" , L"yong" },
{ L"�S" , L"xi" },
{ L"�" , L"qu" },
{ L"ɣ" , L"sang" },
{ L"��" , L"gui" },
{ L"�" , L"pu" },
{ L"ţ" , L"niu" },
{ L"��" , L"shou" },
{ L"ͨ" , L"tong" },
{ L"��" , L"bian" },
{ L"��" , L"hu" },
{ L"��" , L"yan" },
{ L"��" , L"ji" },
{ L"ۣ" , L"jia" },
{ L"��" , L"pu" },
{ L"��" , L"shang" },
{ L"ũ" , L"nong" },
{ L"��" , L"wen" },
{ L"��" , L"bie" },
{ L"ׯ" , L"zhuang" },
{ L"��" , L"yan" },
{ L"��" , L"chai" },
{ L"��" , L"qu" },
{ L"��" , L"yan" },
{ L"��" , L"chong" },
{ L"Ľ" , L"mu" },
{ L"��" , L"lian" },
{ L"��" , L"ru" },
{ L"ϰ" , L"xi" },
{ L"��" , L"huan" },
{ L"��" , L"ai" },
{ L"��" , L"yu" },
{ L"��" , L"rong" },
{ L"��" , L"xiang" },
{ L"��" , L"gu" },
{ L"��" , L"yi" },
{ L"��" , L"shen" },
{ L"��" , L"ge" },
{ L"��" , L"liao" },
{ L"��" , L"yu" },
{ L"��" , L"zhong" },
{ L"��" , L"ji" },
{ L"��" , L"ju" },
{ L"��" , L"heng" },
{ L"��" , L"bu" },
{ L"��" , L"du" },
{ L"��" , L"geng" },
{ L"��" , L"man" },
{ L"��" , L"hong" },
{ L"��" , L"kuang" },
{ L"��" , L"guo" },
{ L"��" , L"wen" },
{ L"��" , L"kou" },
{ L"��" , L"guang" },
{ L"»" , L"lu" },
{ L"��" , L"que" },
{ L"��" , L"dong" },
{ L"ŷ" , L"ou" },
{ L"�" , L"shu" },
{ L"��" , L"wo" },
{ L"��" , L"li" },
{ L"ε" , L"wei" },
{ L"Խ" , L"yue" },
{ L"��" , L"kui" },
{ L"¡" , L"long" },
{ L"ʦ" , L"shi" },
{ L"��" , L"gong" },
{ L"��" , L"she" },
{ L"��" , L"nie" },
{ L"��" , L"chao" },
{ L"��" , L"gou" },
{ L"��" , L"gou" },
{ L"��" , L"ao" },
{ L"��" , L"rong" },
{ L"��" , L"leng" },
{ L"��" , L"zi" },
{ L"��" , L"xin" },
{ L"��" , L"kan" },
{ L"��" , L"na" },
{ L"��" , L"jian" },
{ L"��" , L"rao" },
{ L"��" , L"kong" },
{ L"��" , L"zeng" },
{ L"ĸ" , L"mu" },
{ L"ɳ" , L"sha" },
{ L"ؿ" , L"nie" },
{ L"��" , L"yang" },
{ L"��" , L"ju" },
{ L"��" , L"xu" },
{ L"��" , L"feng" },
{ L"��" , L"chao" },
{ L"��" , L"guan" },
{ L"��" , L"kuai" },
{ L"��" , L"xiang" },
{ L"��" , L"zha" },
{ L"��" , L"hou" },
{ L"��" , L"jing" },
{ L"��" , L"hong" },
{ L"��" , L"you" },
{ L"��" , L"zhu" },
{ L"Ȩ" , L"quan" },
{ L"��" , L"lu" },
{ L"��" , L"gai" },
{ L"��" , L"yi" },
{ L"��" , L"huan" },
{ L"��" , L"gong" },
{ L"��ٹ" , L"moqi" },
{ L"˾��" , L"sima" },
{ L"�Ϲ�" , L"shangguan" },
{ L"ŷ��" , L"ouyang" },
{ L"�ĺ�" , L"xiahou" },
{ L"���" , L"zhuge" },
{ L"����" , L"wenren" },
{ L"����" , L"dongfang" },
{ L"����" , L"helian" },
{ L"�ʸ�" , L"huangpu" },
{ L"ξ��" , L"yuchi" },
{ L"����" , L"gongyang" },
{ L"�̨" , L"tantai" },
{ L"��ұ" , L"gongye" },
{ L"����" , L"zongzheng" },
{ L"���" , L"puyang" },
{ L"����" , L"chunyu" },
{ L"����" , L"chanyu" },
{ L"̫��" , L"taishu" },
{ L"����" , L"shentu" },
{ L"����" , L"gongsun" },
{ L"����" , L"zhongsun" },
{ L"��ԯ" , L"xuanyuan" },
{ L"���" , L"linghu" },
{ L"����" , L"zhongli" },
{ L"����" , L"yuwen" },
{ L"����" , L"zhangsun" },
{ L"Ľ��" , L"murong" },
{ L"����" , L"xianyu" },
{ L"����" , L"luqiu" },
{ L"˾ͽ" , L"situ" },
{ L"˾��" , L"sikong" },
{ L"����" , L"qiguan" },
{ L"˾��" , L"sikou" },
{ L"�붽" , L"zhangdu" },
{ L"�ӳ�" , L"ziju" },
{ L"���" , L"zhuansun" },
{ L"��ľ" , L"duanmu" },
{ L"����" , L"wuma" },
{ L"����" , L"gongxi" },
{ L"���" , L"qidiao" },
{ L"����" , L"yuezheng" },
{ L"����" , L"rangsi" },
{ L"����" , L"gongliang" },
{ L"�ذ�" , L"tuoba" },
{ L"�й�" , L"jiagu" },
{ L"�׸�" , L"zaifu" },
{ L"�b��" , L"guliang" },
{ L"��" , L"jin" },
{ L"��" , L"chu" },
{ L"��" , L"yan" },
{ L"��" , L"fa" },
{ L"��" , L"ru" },
{ L"۳" , L"yan" },
{ L"Ϳ" , L"tu" },
{ L"��" , L"qin" },
{ L"�θ�" , L"duangan" },
{ L"����" , L"baili" },
{ L"����" , L"dongguo" },
{ L"����" , L"nanmen" },
{ L"����" , L"huyan" },
{ L"��" , L"gui" },
{ L"��" , L"hai" },
{ L"����" , L"yangshe" },
{ L"΢" , L"wei" },
{ L"��" , L"sheng" },
{ L"��" , L"yue" },
{ L"˧" , L"shuai" },
{ L"��" , L"gou" },
{ L"��" , L"kang" },
{ L"��" , L"kuang" },
{ L"��" , L"hou" },
{ L"��" , L"you" },
{ L"��" , L"qin" },
{ L"����" , L"liangqiu" },
{ L"����" , L"zuoqiu" },
{ L"����" , L"dongmen" },
{ L"����" , L"ximen" },
{ L"��" , L"shang" },
{ L"Ĳ" , L"mou" },
{ L"��" , L"she" },
{ L"٦" , L"nai" },
{ L"��" , L"bo" },
{ L"��" , L"shang" },
{ L"�Ϲ�" , L"nangong" },
{ L"ī" , L"mo" },
{ L"��" , L"ha" },
{ L"��" , L"qiao" },
{ L"��" , L"da" },
{ L"��" , L"nian" },
{ L"��" , L"ai" },
{ L"��" , L"yang" },
{ L"١" , L"tong" },
{ L"����" , L"diwu" },
{ L"��" , L"yan" },
{ L"��" , L"fu" },
{ L"��" , L"he" },
{ L"��" , L"ou" },
{ L"��" , L"piao" },
{ L"��" , L"po" },
{ L"Ա" , L"yun" },
{ L"ެ" , L"pi" },
{ L"��" , L"chong" },
{ L"��" , L"bi" },
{ L"��" , L"chen" },
{ L"�" , L"chuai" },
{ L"ۡ" , L"di" },
{ L"��" , L"fu" },
{ L"��" , L"fu" },
{ L"�" , L"gao" },
{ L"��" , L"gen" },
{ L"��" , L"guan" },
{ L"�" , L"gui" },
{ L"��" , L"guo" },
{ L"��" , L"cheng" },
{ L"��" , L"juan" },
{ L"��" , L"pang" },
{ L"��" , L"pi" },
{ L"��" , L"pu" },
{ L"��" , L"pu" },
{ L"��" , L"qi" },
{ L"��" , L"shao" },
{ L"��" , L"shao" },
{ L"��" , L"she" },
{ L"ͮ" , L"tong" },
{ L"��" , L"tuo" },
{ L"��" , L"wan" },
{ L"ξ" , L"wei" },
{ L"��" , L"xian" },
{ L"ϴ" , L"xian" },
{ L"ۨ" , L"xun" },
{ L"��" , L"yao" },
{ L"��" , L"yun" },
{ L"�" , L"yun" },
{ L"۩" , L"yun" },
{ L"���" , L"yangjue" },
{ L"�u" , L"yun" },
{ L"��" , L"zhai" },
{ L"��" , L"zhai" },
{ L"ռ" , L"zhan" },
{ L"��" , L"zhang" },
{ L"����" , L"zhonghang" },
{ L"��" , L"zhuo" },
{ L"��" , L"ze" },
{ L"��" , L"qin" },
};

/*
0. �����ֱ� 
1. �����ע�ͱ�ʾ���ǣ������ʣ����������� ���ա����ֱ��ʾ������������
2. ��Դ�� hanziTables[]�������������У�û����©��
3. ������ѡ�ж�������
   a. ѡ���ö��� ��
		{ "��" , "hong" },      // gong  
		{ "��" , "bo" },        // bao
		{ "��" , "chai" },      // ca
   b. ѡ�����ƴ�����Բ³����ֵĶ����������ִ��֪���Ƕ����֣���������'ju'��������Բµ�����'��'�����������'gou'�㻹�ܲµ�������'��'��...
		{ "��" , "ju" },        // gou
		{ "��" , "pang" },      // bang
		{ "��" , "gei" },       // ji
		{ "��" , "ai" },        // yi
		{ "��" , "da" },        // dai
		{ "��" , "pao" },       // bao
   c. ѡ�з����϶���
		{ "��" , "chou" },      // qiu ����������ʱ��qi��
		{ "��" , "jie" },       // xie ���⣺������ʱ��xi��
		{ "��" , "ceng" },      // zeng������������ʱ��z��ng
   d. ѡ�������бȽϿ��ܳ��ֵ���,��������ӿ���ǡ�÷��������Ĺ��򣬵��������ֶ�ɸѡ������ʱȷʵ���ǵ��ⷽ����������Ϊ��Щ�����ֵ�����һЩ����������������Բ����ܱ���������ʹ�ã���Ϊɸѡʱû��¼����������ӿ��ܲ�����
		{ "ʢ" , "sheng" },     // cheng �� ïʢ��maoSheng����ʢ��(chengFan)
		{ "ʯ" , "shi" },       // dan    �� ��ʯ��
		{ "��" , "jin" },       // qin guan
		{ "ǿ" , "qiang" },     // jiang , ��ǿ��qiang������ǿ��jiang��
   e. ��Ҫ��������ϵ�ģ�������û���ˣ�ֻ�ܲ����������ԭ����ѭ��abcd��
		{ "��" , "ping" },      // bing �� ��Ļ������
		{ "��" , "bu" },        // bo ��   ռ�����ܲ�
*/
multiToneWordTableS multiToneWordTable[g_length_multiToneWordTable] =
{
{ L"��" , L"e" },         // si a
{ L"߹" , L"ya" },        // a
{ L"��" , L"a" },         // e
{ L"��" , L"he" },        // ha ke a
{ L"��" , L"yan" },       // a
{ L"��" , L"sha" },       // a
{ L"�^" , L"ci" },        // ka lu ai
{ L"�" , L"li" },        // ai
{ L"�_" , L"ai" },        // suo 
{ L"��" , L"xi" },        // ai
{ L"��" , L"yi" },        // ai
{ L"�G" , L"ei" },        // ai
{ L"��" , L"ai" },        // yi 
{ L"��" , L"yi" },        // ai
{ L"��" , L"yi" },        // ai
{ L"�g" , L"ai" },        // he 
{ L"��" , L"chang" },     // an
{ L"��" , L"guang" },     // an
{ L"��" , L"yan" },       // an
{ L"��" , L"han" },       // an
{ L"��" , L"an" },        // e 
{ L"��" , L"ang" },       // hang 
{ L"�n" , L"yang" },      // ang
{ L"��" , L"yang" },      // ang
{ L"��" , L"ao" },        // wa 
{ L"��" , L"xiao" },      // ao
{ L"ز" , L"ao" },        // yao 
{ L"��" , L"ao" },        // niu 
{ L"�" , L"ha" },        // ba
{ L"��" , L"li" },        // si xi ba
{ L"��" , L"ba" },        // pa 
{ L"�" , L"ba" },        // pa
{ L"��" , L"bo" },        // bai  ba
{ L"��" , L"pa" },        // ba
{ L"��" , L"ba" },        // pa
{ L"��" , L"pa" },        // ba
{ L"�B" , L"bai" },       // wa 
{ L"��" , L"bai" },       // ke 
{ L"İ" , L"mo" },        // bai
{ L"��" , L"bai" },       // bo 
{ L"��" , L"ban" },       // pan 
{ L"��" , L"ban" },       // pan 
{ L"�m" , L"pan" },       // ban
{ L"��" , L"pan" },       // ban
{ L"��" , L"bang" },      // pang 
{ L"��" , L"pang" },      // bang
{ L"��" , L"bang" },      // beng 
{ L"��" , L"bang" },      // bei 
{ L"�s" , L"bang" },      // peng 
{ L"��" , L"bang" },      // pang 
{ L"��" , L"pao" },       // bao
{ L"��" , L"bao" },       // fu 
{ L"��" , L"bo" },        // bao
{ L"��" , L"bao" },       // bu pu 
{ L"��" , L"pao" },       // bao
{ L"Ј" , L"pao" },       // bao
{ L"��" , L"bao" },       // pu 
{ L"��" , L"pu" },        // bao
{ L"��" , L"bao" },       // pu 
{ L"��" , L"bei" },       // pi po 
{ L"��" , L"bei" },       // pi 
{ L"��" , L"bei" },       // bo 
{ L"��" , L"bei" },       // pi 
{ L"��" , L"ben" },       // bi 
{ L"��" , L"hang" },      // ben
{ L"�Z" , L"ta" },        // ku lai bi
{ L"͌" , L"bi" },        // e 
{ L"�q" , L"bi" },        // pi 
{ L"��" , L"pi" },        // bi
{ L"�u" , L"pai" },       // bi
{ L"��" , L"bi" },        // pi 
{ L"��" , L"mi" },        // bi
{ L"��" , L"mi" },        // bi
{ L"��" , L"bi" },        // pi 
{ L"��" , L"pi" },        // bi
{ L"�" , L"pi" },        // bi
{ L"��" , L"bian" },      // pian 
{ L"��" , L"bian" },      // pian 
{ L"��" , L"bian" },      // pian 
{ L"��" , L"bian" },      // pian 
{ L"�" , L"shao" },      // biao
{ L"��" , L"biao" },      // piao 
{ L"��" , L"pao" },       // biao
{ L"��" , L"fen" },       // bin
{ L"��" , L"bing" },      // bin
{ L"��" , L"ping" },      // bing
{ L"�" , L"geng" },      // bing
{ L"��" , L"bu" },        // bo
{ L"�z" , L"da" },        // bo
{ L"��" , L"po" },        // bo
{ L"��" , L"po" },        // tuo bo
{ L"��" , L"pu" },        // bu
{ L"��" , L"chai" },      // ca
{ L"��" , L"ca" },        // cha 
{ L"��" , L"si" },        // cai
{ L"��" , L"can" },       // cen san shen 
{ L"�d" , L"can" },       // zan 
{ L"��" , L"chan" },      // shan can
{ L"��" , L"chan" },      // can
{ L"�" , L"zang" },      // cang
{ L"��" , L"cang" },      // zang 
{ L"�e" , L"o" },         // ce
{ L"��" , L"ce" },        // ke o 
{ L"��" , L"ce" },        // ze zhai 
{ L"�k" , L"ce" },        // jia 
{ L"��" , L"cheng" },     // ceng
{ L"��" , L"ceng" },      // zeng 
{ L"��" , L"cha" },       // chai ci 
{ L"��" , L"zha" },       // cha
{ L"��" , L"cha" },       // zha 
{ L"�" , L"cha" },       // zha 
{ L"�" , L"zha" },       // cha
{ L"�" , L"cha" },       // zha 
{ L"ɲ" , L"sha" },       // cha
{ L"��" , L"zha" },       // cha
{ L"��" , L"chai" },      // zhai 
{ L"Ə" , L"chai" },      // zhi 
{ L"��" , L"cuo" },       // chai
{ L"��" , L"dan" },       // shan chan
{ L"��" , L"chan" },      // shan 
{ L"��" , L"chang" },     // zhang 
{ L"��" , L"tang" },      // chang
{ L"�" , L"chang" },     // tang 
{ L"��" , L"chuo" },      // chao
{ L"��" , L"chao" },      // zhuo 
{ L"��" , L"chao" },      // jiao 
{ L"��" , L"chao" },      // zhao 
{ L"��" , L"zhao" },      // chao
{ L"��" , L"chao" },      // zhao 
{ L"��" , L"che" },       // ju 
{ L"��" , L"chi" },       // che
{ L"��" , L"chen" },      // tian 
{ L"��" , L"cheng" },     // chen
{ L"��" , L"dang" },      // cheng
{ L"��" , L"tang" },      // cheng
{ L"��" , L"cheng" },     // sheng 
{ L"ʢ" , L"sheng" },     // cheng
{ L"��" , L"cheng" },     // deng 
{ L"��" , L"di" },        // chi
{ L"��" , L"zhi" },       // chi
{ L"ӿ" , L"yong" },      // chong
{ L"��" , L"chong" },     // hui 
{ L"��" , L"zhong" },     // chong
{ L"��" , L"zhong" },     // chong
{ L"��" , L"chou" },      // qiu 
{ L"��" , L"chou" },      // dao 
{ L"��" , L"niu" },       // chou
{ L"��" , L"chou" },      // xiu 
{ L"��" , L"zhu" },       // chu
{ L"��" , L"zhu" },       // chuzhe 
{ L"��" , L"chu" },       // xu 
{ L"�m" , L"chu" },       // ti 
{ L"��" , L"chu" },       // xu 
{ L"�H" , L"xu" },        // chua
{ L"�" , L"chuo" },      // chuai
{ L"��" , L"chuan" },     // zhuan 
{ L"��" , L"chuan" },     // guan 
{ L"��" , L"zhuang" },    // chuang
{ L"׵" , L"zhui" },      // chui
{ L"�T" , L"dchun" },     // ui 
{ L"�S" , L"ruo" },       // chuo
{ L"��" , L"zi" },        // ci
{ L"��" , L"zi" },        // ci
{ L"��" , L"si" },        // ci
{ L"��" , L"cong" },      // zong 
{ L"�B" , L"song" },      // cong
{ L"��" , L"zu" },        // cu
{ L"Ȥ" , L"qu" },        // cu
{ L"ǈ" , L"zou" },       // cuan
{ L"��" , L"zan" },       // cuan
{ L"��" , L"cui" },       // sui 
{ L"��" , L"dun" },       // cun
{ L"��" , L"zan" },       // cuo
{ L"��" , L"ku" },        // ta yi da
{ L"�" , L"da" },        // ta 
{ L"�" , L"ta" },        // da
{ L"��" , L"dan" },       // da
{ L"��" , L"da" },        // dai 
{ L"��" , L"tai" },       // da
{ L"߾" , L"dai" },       // tai 
{ L"��" , L"dai" },       // tai 
{ L"��" , L"dan" },       // shan 
{ L"�r" , L"dan" },       // zhan 
{ L"ʯ" , L"shi" },       // dan
{ L"��" , L"tan" },       // dan
{ L"�" , L"dan" },       // tan 
{ L"�h" , L"dao" },       // ri 
{ L"߶" , L"dao" },       // tao 
{ L"��" , L"dao" },       // tao 
{ L"��" , L"de" },        // di 
{ L"��" , L"di" },        // de
{ L"��" , L"di" },        // de
{ L"��" , L"de" },        // dei 
{ L"�N" , L"de" },        // dei 
{ L"��" , L"di" },        // mi 
{ L"��" , L"ti" },        // di
{ L"��" , L"di" },        // zhai 
{ L"ۗ" , L"di" },        // zhi 
{ L"�m" , L"di" },        // duo 
{ L"�W" , L"ti" },        // di
{ L"��" , L"dian" },      // yan 
{ L"��" , L"dian" },      // tian 
{ L"��" , L"dian" },      // tian 
{ L"��" , L"niao" },      // diao
{ L"��" , L"tiao" },      // zhou diao
{ L"�" , L"diao" },      // yao 
{ L"�A" , L"die" },       // xi 
{ L"�i" , L"die" },       // yi 
{ L"�" , L"die" },       // zha 
{ L"��" , L"die" },       // she 
{ L"�H" , L"zhi" },       // die
{ L"��" , L"ding" },      // zheng 
{ L"�" , L"ding" },      // ting 
{ L"��" , L"ting" },      // ding
{ L"��" , L"tong" },      // dong
{ L"��" , L"dong" },      // tong 
{ L"��" , L"dong" },      // tong 
{ L"�" , L"tong" },      // dong
{ L"��" , L"dou" },       // du 
{ L"��" , L"du" },        // dou
{ L"��" , L"du" },        // dou
{ L"��" , L"du" },        // ge 
{ L"�^" , L"du" },        // she 
{ L"��" , L"duo" },       // du
{ L"��" , L"yi" },        // du
{ L"��" , L"dun" },       // dui
{ L"��" , L"dui" },       // dun 
{ L"��" , L"dun" },       // zhuan 
{ L"��" , L"tun" },       // dun
{ L"�J" , L"dun" },       // shun 
{ L"�V" , L"wu" },        // ya duo ji 
{ L"��" , L"tuo" },       // duo
{ L"��" , L"duo" },       // hui 
{ L"��" , L"o" },         // e
{ L"��" , L"o" },         // si e
{ L"�k" , L"e" },         // ta
{ L"��" , L"mi" },        // e
{ L"��" , L"e" },         // wu 
{ L"Ŷ" , L"o" },         // e
{ L"��" , L"e" },         // yi 
{ L"��" , L"e" },         // yan 
{ L"��" , L"mi" },        // eng
{ L"Ğ" , L"nao" },       // er
{ L"٦" , L"er" },        // nai 
{ L"��" , L"fa" },        // fei 
{ L"�N" , L"fa" },        // po 
{ L"��" , L"fan" },       // pan 
{ L"��" , L"pan" },       // fan
{ L"��" , L"fan" },       // po 
{ L"��" , L"fang" },      // pang 
{ L"��" , L"pang" },      // fang
{ L"��" , L"fu" },        // fei
{ L"��" , L"fu" },        // fei
{ L"��" , L"fen" },       // pen 
{ L"��" , L"feng" },      // ping 
{ L"��" , L"fo" },        // fu 
{ L"��" , L"fou" },       // pi 
{ L"ݳ" , L"fu" },        // piao 
{ L"�a" , L"mian" },      // fu
{ L"��" , L"pu" },        // fu
{ L"�f" , L"ga" },        // ri 
{ L"�L" , L"xi" },        // la  ga
{ L"܅" , L"ya" },        // ga
{ L"��" , L"jia" },       // ga
{ L"٤" , L"ga" },        // jia qie 
{ L"��" , L"xia" },       // ga
{ L"��" , L"ka" },        // ga
{ L"��" , L"zha" },       // ya  ga
{ L"��" , L"jie" },       // gai
{ L"��" , L"gai" },       // ge 
{ L"��" , L"jian" },      // gan
{ L"��" , L"gan" },       // han 
{ L"��" , L"gan" },       // gong 
{ L"��" , L"kang" },      // gang
{ L"�" , L"gang" },      // zhuang 
{ L"��" , L"gao" },       // hao 
{ L"�o" , L"mei" },       // gao
{ L"��" , L"gao" },       // hao 
{ L"�g" , L"ge" },        // ri 
{ L"�|" , L"xi" },        // ge
{ L"�{" , L"ge" },        // xi 
{ L"��" , L"yi" },        // ge
{ L"��" , L"ge" },        // he 
{ L"��" , L"ge" },        // ka luo 
{ L"��" , L"ge" },        // ji 
{ L"ت" , L"ge" },        // li 
{ L"��" , L"ge" },        // ha 
{ L"��" , L"he" },        // ge
{ L"��" , L"luo" },       // ge
{ L"��" , L"gei" },       // ji 
{ L"��" , L"gen" },       // hen 
{ L"��" , L"hong" },      // gong
{ L"�y" , L"gong" },      // hong 
{ L"��" , L"ju" },        // gou
{ L"��" , L"gou" },       // ju 
{ L"��" , L"gua" },       // gu
{ L"��" , L"jia" },       // gu
{ L"��" , L"gu" },        // hu 
{ L"��" , L"gu" },        // yu 
{ L"��" , L"gu" },        // yu 
{ L"��" , L"ku" },        // gu
{ L"��" , L"jia" },       // gu
{ L"��" , L"gu" },        // he hu 
{ L"��" , L"gu" },        // jia 
{ L"��" , L"gu" },        // hu 
{ L"��" , L"gua" },       // kuo 
{ L"��" , L"lun" },       // guan
{ L"��" , L"jin" },       // qin guan
{ L"ݸ" , L"guan" },      // wan 
{ L"��" , L"gui" },       // kui 
{ L"��" , L"gui" },       // jun qiu 
{ L"�@" , L"gui" },       // hui wei 
{ L"��" , L"gui" },       // hua xie 
{ L"��" , L"jiu" },       // gui
{ L"��" , L"jiong" },     // gui
{ L"Ȳ" , L"que" },       // gui
{ L"��" , L"gui" },       // ju 
{ L"��" , L"hui" },       // gui 
{ L"��" , L"gui" },       // jue 
{ L"��" , L"wo" },        // guo
{ L"�a" , L"ha" },        // ri 
{ L"�C" , L"ru" },        // me  ha
{ L"��" , L"tu" },        // ha
{ L"��" , L"xi" },        // ha na 
{ L"�m" , L"ta" },        // ha
{ L"Ϻ" , L"xia" },       // ha
{ L"��" , L"ke" },        // hai
{ L"��" , L"hai" },       // hei 
{ L"��" , L"huan" },      // hai
{ L"��" , L"hai" },       // he 
{ L"��" , L"kang" },      // hang
{ L"��" , L"xing" },      // hang heng
{ L"��" , L"keng" },      // hang
{ L"��" , L"xiang" },     // hang
{ L"��" , L"he" },        // hao
{ L"�j" , L"he" },        // wo 
{ L"��" , L"he" },        // hu huo 
{ L"��" , L"he" },        // hu 
{ L"��" , L"xia" },       // he
{ L"�n" , L"xie" },       // he
{ L"��" , L"he" },        // kao 
{ L"��" , L"hei" },       // mo 
{ L"Ϸ" , L"xi" },        // hu hui 
{ L"��" , L"wu" },        // hu
{ L"�" , L"hu" },        // xu 
{ L"��" , L"hu" },        // xia 
{ L"��" , L"ku" },        // hu
{ L"�" , L"xu" },        // hua
{ L"ۨ" , L"xun" },       // huan
{ L"��" , L"yuan" },      // huan
{ L"��" , L"huan" },      // qiong xuan 
{ L"ѣ" , L"xuan" },      // huan
{ L"�" , L"wei" },       // hui
{ L"��" , L"hun" },       // hui
{ L"�" , L"hui" },       // sui 
{ L"��" , L"hui" },       // kuai 
{ L"�" , L"hui" },       // kuai 
{ L"��" , L"yue" },       // hui
{ L"��" , L"hun" },       // xun 
{ L"��" , L"qi" },        // ji
{ L"��" , L"qi" },        // ji
{ L"��" , L"ji" },        // qi 
{ L"��" , L"ji" },        // qi 
{ L"ؽ" , L"ji" },        // qi 
{ L"��" , L"ji" },        // jie 
{ L"��" , L"qi" },        // ji
{ L"ϵ" , L"xi" },        // ji
{ L"��" , L"ji" },        // qi 
{ L"��" , L"ji" },        // zhai 
{ L"��" , L"jie" },       // ji
{ L"��" , L"jia" },       // lun 
{ L"��" , L"qie" },       // jia
{ L"��" , L"jia" },       // xia 
{ L"��" , L"jia" },       // xia 
{ L"��" , L"jia" },       // jie 
{ L"ǳ" , L"qian" },      // jian
{ L"��" , L"jian" },      // qian 
{ L"��" , L"jian" },      // nan 
{ L"��" , L"jian" },      // xian 
{ L"��" , L"kan" },       // jian
{ L"��" , L"jiang" },     // qiang 
{ L"��" , L"jiang" },     // xiang 
{ L"ǿ" , L"qiang" },     // jiang
{ L"��" , L"jiao" },      // qiao 
{ L"��" , L"jiao" },      // yao 
{ L"��" , L"jiao" },      // jue 
{ L"��" , L"jiao" },      // jue 
{ L"��" , L"jiao" },      // yao 
{ L"��" , L"jiao" },      // jue 
{ L"��" , L"jiu" },       // qiu jiao
{ L"��" , L"jiao" },      // zhuo 
{ L"�" , L"qiao" },      // jiao
{ L"��" , L"jiao" },      // jue 
{ L"У" , L"xiao" },      // jiao
{ L"��" , L"kai" },       // jie
{ L"��" , L"jie" },       // ju 
{ L"�e" , L"xie" },       // jie
{ L"��" , L"jie" },       // xie 
{ L"��" , L"jin" },       // qin 
{ L"��" , L"jing" },      // jin
{ L"��" , L"liang" },     // jing
{ L"��" , L"liang" },     // jing
{ L"��" , L"qie" },       // ju
{ L"��" , L"ju" },        // zu 
{ L"��" , L"qu" },        // ju
{ L"��" , L"qie" },       // ju
{ L"��" , L"ju" },        // zui 
{ L"�c" , L"qu" },        // ju
{ L"��" , L"ju" },        // qu 
{ L"Ȧ" , L"quan" },      // juan
{ L"��" , L"juan" },      // quan 
{ L"�m" , L"quan" },      // juan
{ L"��" , L"jun" },       // juan
{ L"��" , L"que" },       // jue
{ L"��" , L"xue" },       // jue
{ L"��" , L"jun" },       // yun 
{ L"��" , L"qun" },       // jun
{ L"��" , L"jun" },       // xun 
{ L"�a" , L"jun" },       // qu 
{ L"�J" , L"ka" },        // yi 
{ L"�Q" , L"ka" },        // mi mo xi ��
{ L"" , L"li" },        // xi ka
{ L"��" , L"ke" },        // nou zi ka
{ L"��" , L"si" },        // yi ka
{ L"��" , L"ka" },        // qia 
{ L"��" , L"mu" },        // wu ke
{ L"ޑ" , L"o" },         // pi ke
{ L"�i" , L"o" },         // ke
{ L"��" , L"ke" },        // qiao 
{ L"��" , L"wei" },       // kui
{ L"�u" , L"luo" },       // la
{ L"��" , L"luo" },       // lao  la
{ L"��" , L"la" },        // xi 
{ L"��" , L"la" },        // zha 
{ L"�" , L"lai" },       // la
{ L"ݹ" , L"liang" },     // lang
{ L"��" , L"liao" },      // lao
{ L"��" , L"lao" },       // mu 
{ L"�" , L"liao" },      // lao
{ L"��" , L"luo" },       // lao
{ L"��" , L"lao" },       // luo 
{ L"�Y" , L"te" },        // wu le
{ L"�V" , L"mu" },        // le
{ L"��" , L"lei" },       // le
{ L"��" , L"yue" },       // le
{ L"��" , L"lei" },       // le
{ L"��" , L"luo" },       // ta lei
{ L"��" , L"leng" },      // ling 
{ L"�M" , L"li" },        // wa 
{ L"�" , L"li" },        // luo 
{ L"��" , L"li" },        // yue 
{ L"��" , L"li" },        // luo 
{ L"��" , L"liang" },     // lia
{ L"�f" , L"liu" },       // liao
{ L"ޤ" , L"liao" },      // lu 
{ L"��" , L"lie" },       // ri 
{ L"��" , L"liu" },       // lu 
{ L"½" , L"lu" },        // liu
{ L"µ" , L"lu" },        // liu
{ L"��" , L"long" },      // shuang 
{ L"Ū" , L"nong" },      // long
{ L"��" , L"lou" },       // lv 
{ L"¶" , L"lu" },        // lou
{ L"��" , L"lv" },        // lu 
{ L"��" , L"luo" },       // lv
{ L"��" , L"shuai" },     // lv
{ L"��" , L"m" },         // mou 
{ L"ķ" , L"mu" },        // m
{ L"�x" , L"si" },        // ma
{ L"��" , L"na" },        // zi ma ��
{ L"�I" , L"zi" },        // ma
{ L"Ĩ" , L"mo" },        // ma
{ L"Ħ" , L"mo" },        // ma
{ L"��" , L"mai" },       // man 
{ L"��" , L"mai" },       // mo 
{ L"��" , L"wan" },       // man
{ L"��" , L"meng" },      // mang
{ L"å" , L"mang" },      // meng 
{ L"ð" , L"mao" },       // mo 
{ L"�W" , L"shi" },       // me ��
{ L"��" , L"mo" },        // ne me ��
{ L"û" , L"mei" },       // mo 
{ L"��" , L"mi" },        // mei
{ L"��" , L"mi" },        // mei
{ L"��" , L"wen" },       // men
{ L"��" , L"wei" },       // men
{ L"��" , L"min" },       // meng
{ L"��" , L"ne" },        // zu mi ��
{ L"�q" , L"ming" },      // mi
{ L"��" , L"mian" },      // wen 
{ L"��" , L"mian" },      // sheng 
{ L"��" , L"miu" },       // mou miao
{ L"ؿ" , L"mie" },       // nie 
{ L"�C" , L"ne" },        // o ye mo
{ L"�i" , L"ri" },        // mo ��
{ L"��" , L"wu" },        // mo
{ L"ģ" , L"mo" },        // mu 
{ L"��" , L"wan" },       // mo
{ L"Ī" , L"mo" },        // mu 
{ L"��" , L"wa" },        // mo
{ L"Ĳ" , L"mou" },       // mu 
{ L"��" , L"na" },        // ne nei nuo 
{ L"��" , L"nan" },       // na
{ L"��" , L"na" },        // nai ne nei 
{ L"��" , L"nei" },       // na
{ L"��" , L"na" },        // ne 
{ L"��" , L"na" },        // nuo 
{ L"ܵ" , L"nai" },       // reng 
{ L"��" , L"nao" },       // nu 
{ L"�L" , L"o" },         // se ne
{ L"��" , L"wu" },        // ng
{ L"�R" , L"po" },        // pu ni
{ L"�M" , L"o" },         // ni ��
{ L"��" , L"ni" },        // niao 
{ L"��" , L"yi" },        // ni 
{ L"ճ" , L"zhan" },      // nian
{ L"��" , L"nian" },      // nie 
{ L"շ" , L"zhan" },      // nian
{ L"��" , L"niao" },      // sui 
{ L"��" , L"ning" },      // zhu 
{ L"ǂ" , L"xi" },        // nu ��
{ L"��" , L"nuo" },       // re 
{ L"ű" , L"nve" },       // yao 
{ L"��" , L"qu" },        // ou 
{ L"��" , L"xi" },        // pa ��
{ L"��" , L"pai" },       // pa
{ L"�C" , L"ying" },      // pai ��
{ L"��" , L"po" },        // pai
{ L"��" , L"pang" },      // pan
{ L"��" , L"pin" },       // pan
{ L"��" , L"xi" },        // pao ��
{ L"��" , L"pu" },        // po  piao
{ L"�" , L"pin" },       // ping 
{ L"�n" , L"po" },        // ri �� 
{ L"��" , L"qi" },        // xi 
{ L"�p" , L"qi" },        // yi 
{ L"��" , L"qi" },        // xi 
{ L"��" , L"qi" },        // yin 
{ L"ٹ" , L"si" },        // qi
{ L"��" , L"qing" },      // qi
{ L"��" , L"qi" },        // xie 
{ L"��" , L"qie" },       // qi
{ L"Ǧ" , L"qian" },      // yan 
{ L"��" , L"xian" },      // qian
{ L"ݡ" , L"qian" },      // xun 
{ L"�{" , L"xian" },      // qian
{ L"��" , L"xian" },      // qian
{ L"��" , L"xi" },        // qian
{ L"ٻ" , L"qian" },      // qing 
{ L"�" , L"qie" },       // qian
{ L"ȸ" , L"que" },       // qiao
{ L"��" , L"qiao" },      // shao 
{ L"��" , L"qin" },       // qing 
{ L"��" , L"tan" },       // qin
{ L"��" , L"qin" },       // zhen 
{ L"��" , L"qing" },      // zheng 
{ L"��" , L"qiu" },       // you 
{ L"ȯ" , L"quan" },      // xuan 
{ L"��" , L"shao" },      // que
{ L"��" , L"yao" },       // rao
{ L"��" , L"ruo" },       // re
{ L"��" , L"shen" },      // ren
{ L"�u" , L"za" },        // ri ��
{ L"�t" , L"zu" },        // ri ��
{ L"�r" , L"sao" },       // ri ��
{ L"�c" , L"ya" },        // ri ��
{ L"̃" , L"sa" },        // ri ��
{ L"�P" , L"te" },        // sa ��
{ L"�j" , L"su" },        // sa ��
{ L"��" , L"ying" },      // sa ��
{ L"��" , L"sa" },        // sha 
{ L"˼" , L"si" },        // sai
{ L"��" , L"sai" },       // se 
{ L"��" , L"shen" },      // san
{ L"��" , L"zao" },       // sao
{ L"ɫ" , L"se" },        // shai 
{ L"ɼ" , L"shan" },      // sha
{ L"ɯ" , L"sha" },       // suo 
{ L"��" , L"sha" },       // suo 
{ L"ҭ" , L"ye" },        // sha
{ L"��" , L"she" },       // sha
{ L"��" , L"ti" },        // sha
{ L"��" , L"xia" },       // sha
{ L"��" , L"shi" },       // shai
{ L"դ" , L"shan" },      // zha 
{ L"��" , L"yan" },       // shan
{ L"��" , L"tang" },      // shang
{ L"��" , L"xiao" },      // shao
{ L"��" , L"shao" },      // tiao 
{ L"��" , L"she" },       // yu 
{ L"��" , L"zhe" },       // she
{ L"��" , L"she" },       // yi 
{ L"Ҷ" , L"ye" },        // xie she
{ L"ʰ" , L"shi" },       // she
{ L"�" , L"she" },       // xi 
{ L"˭" , L"shui" },      // shei
{ L"�]" , L"shi" },       // shen ��
{ L"ݷ" , L"shen" },      // xin 
{ L"ʲ" , L"shen" },      // shi 
{ L"�" , L"shen" },      // zhen 
{ L"��" , L"sheng" },     // xing 
{ L"ʡ" , L"sheng" },     // xing 
{ L"��" , L"xu" },        // shi
{ L"ʶ" , L"shi" },       // zhi 
{ L"ʳ" , L"shi" },       // si yi 
{ L"��" , L"shi" },       // zhi 
{ L"��" , L"si" },        // shi
{ L"��" , L"zhi" },       // shi
{ L"�" , L"shi" },       // zhe 
{ L"��" , L"shu" },       // shou
{ L"ݱ" , L"tu" },        // shu
{ L"��" , L"shu" },       // zhu 
{ L"��" , L"shu" },       // zhu 
{ L"��" , L"shu" },       // zhu 
{ L"˵" , L"shuo" },      // tuo yue shui
{ L"��" , L"song" },      // zhong 
{ L"��" , L"su" },        // xiu 
{ L"��" , L"suo" },       // su
{ L"�[" , L"tui" },       // ta ��
{ L"��" , L"tuo" },       // ta
{ L"̶" , L"tan" },       // xun 
{ L"��" , L"tao" },       // yao 
{ L"��" , L"yo" },        // zhao te ��
{ L"߯" , L"tui" },       // te
{ L"�`" , L"ti" },        // zhi 
{ L"��" , L"yi" },        // ti
{ L"��" , L"xi" },        // ti
{ L"��" , L"tong" },      // zhuang 
{ L"�M" , L"tuo" },       // tui
{ L"��" , L"tui" },       // tun 
{ L"��" , L"tun" },       // zhun 
{ L"��" , L"wei" },       // wai
{ L"��" , L"wan" },       // yu 
{ L"��" , L"you" },       // wang
{ L"��" , L"wang" },      // wu 
{ L"��" , L"wei" },       // xu 
{ L"β" , L"wei" },       // yi 
{ L"ξ" , L"wei" },       // yu 
{ L"��" , L"yi" },        // wei
{ L"ε" , L"wei" },       // yu 
{ L"��" , L"wo" },        // zhua 
{ L"��" , L"wan" },       // yuan wo 
{ L"�" , L"yu" },        // wu
{ L"�" , L"wu" },        // yu 
{ L"��" , L"yi" },        // xi ��
{ L"��" , L"ze" },        // xi ��
{ L"��" , L"zhe" },       // xi
{ L"ϴ" , L"xi" },        // xian 
{ L"ϳ" , L"xi" },        // xian 
{ L"��" , L"xian" },      // xuan 
{ L"��" , L"xiao" },      // xue 
{ L"а" , L"xie" },        // ye 
{ L"��" , L"ying" },       // xing
{ L"ф" , L"you" },        // xiu
{ L"��" , L"yu" },         // xu 
{ L"�^" , L"zhu" },        // xu
{ L"�" , L"yin" },        // xun
{ L"��" , L"yan" },        // ya
{ L"��" , L"yan" },        // ye 
{ L"��" , L"yin" },        // yan
{ L"ܾ" , L"yuan" },       // yan
{ L"Լ" , L"yue" },        // yao
{ L"��" , L"yao" },        // you zhou 
{ L"Կ" , L"yao" },        // yue 
{ L"ק" , L"zhuai" },      // ye
{ L"��" , L"yu" },         // yo
{ L"�" , L"yong" },       // yu 
{ L"��" , L"you" },        // zhu 
{ L"��" , L"zhou" },       // yu
{ L"��" , L"yun" },        // yu
{ L"Ա" , L"yuan" },       // yun 
{ L"��" , L"zha" },        // za
{ L"��" , L"zan" },        // za
{ L"��" , L"za" },         // zan 
{ L"զ" , L"za" },         // ze zha 
{ L"��" , L"zai" },        // zi 
{ L"��" , L"zi" },         // zai
{ L"��" , L"zang" },       // zhuang 
{ L"��" , L"ze" },         // zhai 
{ L"��" , L"ze" },         // zhai 
{ L"��" , L"zong" },       // zeng
{ L"��" , L"zhuo" },       // zhao
{ L"��" , L"zhou" },       // zhao
{ L"צ" , L"zhua" },       // zhao
{ L"��" , L"zhe" },        // zhei 
{ L"֨" , L"zhi" },        // zi 
{ L"ף" , L"zhu" },        // zhou
{ L"��" , L"zhuo" },       // zhu
{ L"ת" , L"zhuan" },      // zhuai
{ L"׬" , L"zhuan" },      // zuan 
{ L"�e" , L"zuan" },       // zhuan
{ L"��" , L"zui" },        // zi

{ L"��", L"ba" },           // bo 
{ L"�x", L"pa" },           // ba
{ L"��", L"ban" },          // pan 
{ L"��", L"ban" },          // bo pan 
{ L"��", L"bao" },          // bo 
{ L"��", L"bao" },          // bo 
{ L"ެ", L"fan" },          // bo
{ L"�A", L"gu" },           // hu 
{ L"��", L"heng" },         // hang
{ L"��", L"heng" },         // hang
{ L"��", L"ya" },           // he
{ L"�e", L"song" },         // yu 
{ L"��", L"zuo" },          // chuai
{ L"��", L"cuo" },          // zuo 
{ L"��", L"zuo" },          // ze
{ L"��", L"zhuo" },         // zuo 
};

/*
0. ����ƴ������Դ�� http://xh.5156edu.com/pinyi.html ����Ҫ�Լ���ȡ���ݣ�
1. ��'bo'���'��' ; 'de'���'��' ; 'wan'���'��' ; 'ta'���'��'
  ����ȡ����������ȱʧ������վ�����⣬����ֱ�Ӳ�ȫ��
2. �� �� v ����
3. ����
	ȥ�� '' ԭ����'ʭ'�ĺ��� 20200410
	ȥ�� '' ԭ����'�E'�ĺ��� 20200410
*/
hanziTableS hanziTables[g_length_hanziTables] =
{
{ L"a", L"a", L"߹���ǰ�����H�ą�" },
{ L"a", L"ao", L"�����`�E���n�����J�T����ໆ�����E�ᓳ�H�x�������K֒֓���O�����q����ܳز�b�j�ְ��O�����\ᮍC������S�W�񋮑R�É��ĎS�������`" },
{ L"a", L"ang", L"���a�n���찺�n�����l" },
{ L"a", L"ai", L"���������ְ����������X�߰������ܔ����B�}���I�̚��l�G�Ⱛ���t���G�@�c���\���i�������v�����ȉa���ۅ���訃v�批�����B���g�a�ᑹ���}�L�K�r�P�a�^��H�_�o" },
{ L"a", L"an", L"���㰲��^���ւ����C�sȀ�j�W�u���YɎ����O�Q�K�c�V�g��폫q��눃���������崙����O�@���������I���t���F�@�ݰ�؁�B���" },

{ L"b", L"bai", L"�����נ۰ٲ���İ�ؖ���]�ڔ[�o�����ܰݔ��W�޻��bٔ�v�B�q����" },
{ L"b", L"ba", L"�R�ˁ��ͰȖ[�X��᱒U�ŊB�̖���M�ΰʰƆ^�j�^�����؊��Ξ��_�j���R�y���T���������Z�в��y�Ӱ��ˈ��հ�ڕ���T�E�x҆�F�w�ԉ�屙�i���" },
{ L"b", L"ban", L"���R������ߔʰ��C�X�Όї��n�������L���ӻ{���k�Z��雰����芔��m�E���t�O���[��k��Ά" },
{ L"b", L"bang", L"������ߙ�����R���D�󽉰񠥰�g���԰�����������s�Y���M����Ő�r�^" },
{ L"b", L"bao", L"��������ږ��������������f���}�J��_�����������A𱱣�p���ᱤ��~�������h�R�d��م�����d���ٱ���蘱����dǘЈ���E���b󎱩̙�U�ރ��ٱ����؏��t��˝" },
{ L"b", L"ben", L"���y�ڠ���Q�����M�������Ђ��G�L���ٜ`��" },
{ L"b", L"bei", L"�鱰���ȱ����G���d���Ǳ�ˍ�l���m��������ؐ���K�p���T�������p�N㣗f�����f�D�i���K��F��������͓�ՐʶF�����R��c�^݅�L�v���͆h" },
{ L"b", L"beng", L"�ȵp�R�����a�l�n���ԾX���®g�����E�e�a잱űð��J�g�l��G���a" },
{ L"b", L"bi", L"�n���ƚȗ�[�P�SΓ���q�sݩ��ذ�Ȗa�������a�ӯH�˚������ʻz�����P�ɹu؄�ұرϱձӁ�ם��ߛށ�f�P�Wƃ������n������ڱіī��R���������Ћ�����]�[������]�a���P���㹰z���������v���S�C͚�Ա����s��G����􏒱�ɜ�bD�ԯw���α̱α������ža��v�E���K�Ɲ��X���ڏY�Ա�޵���`�o�v�Iۋ��娔��ۊ`�@�{����V�g���S�x�{�L�K��z�E�F�C�����Z͌��" },
{ L"b", L"bian", L"�ߞ�����q��p�Ԡ��K�����D����Q����߄߅���c�b�e�������H���۷H���u�x���͒\�M�������f���c��Ҍ�̱��O�r�g՗��Ō����l���p�q׃�O" },
{ L"b", L"biao", L"輱���T�Ա�W�Yà�R�������E���w���˟ϱ���񦴂�쮃��[րˑ�d�g�Sٙ�A�����j�k�l�n�s�Q�������Օ�l�F�~�l���" },
{ L"b", L"bie", L"����h��T�M��̋�����e�a�r���X����" },
{ L"b", L"bin", L"ߓ����򗀗��ϱ�����e�f�h�Ĭ��ك����l�ٞI�M̞�p���l�E�_ϙ�\�������P��Ĝ�����x�W" },
{ L"b", L"bing", L"�����겢�������ޒ��ı����v�u�T�m���\�m������箱}�s���}������A�u��V�@�ՁK����v��p���������@�m�h���" },
{ L"b", L"bo", L"���h�i�������Ĳ��C�j�\�����������C��ࣜ��B�\�у`ެ�󲥓��G�R�@��Q���������J���������R���N�`���B���z�ಬ�����`�_���J��𾲳ȕ���t�A������K�����C�gŇ���������k�D���c�F��N���c�U�~�o�P�n�����m�p�\�q�����}�����X����L�Y�z�N" },
{ L"b", L"bu", L"�͎�m������c�J�q�G�K����߲���������a�L�Q�����āѲ��h�i�����Ж������ϒ��҈��[����bɞ�E�Y�^�X�^���~" },

{ L"c", L"ca", L"����c����g�n�k" },
{ L"c", L"cai", L"�Ʋ²ŲƲ�ؔ���u���ɂ����u��ʒ�Ɨ����P�Z�Ȍq�˲̿n" },
{ L"c", L"can", L"�΅������{�����Ђ��۲��вϲњ��M�]�L�T�Q�ҕ��K�p���_�d���o�Ӳ������L�ӠN�֍���|" },
{ L"c", L"cang", L"�X�ց����Բ��]�Ղ}������n�����@œ�I갲��ى�P" },
{ L"c", L"cao", L"�ٲٲڕ���ɘ�Ѝ���F���G����[�H�ݐ��x�H���_��" },
{ L"c", L"ce", L"����Բ���R�������������Y�����m�ߜy���Źk�ZɃ�����u�e��" },
{ L"c", L"cen", L"�΍��么����q" },
{ L"c", L"ceng", L"������Ӎ�}��" },
{ L"c", L"cha", L"��Q�K��a����ǲ�c�����ʲ��ő������l��舓��˶g⪍����xԈ�鶲�����ۂ���d�g���ɲ����x���pԌ" },
{ L"c", L"chai", L"�O�P�β���O��٭���}����Ə�ӐЃ��ϊ��" },
{ L"c", L"chan", L"�{��{����җ�g���i���b�v�g����濲���������������]�S�a�{�܋������C头v���M���s�e����󸄭�ʇ����f���p�s���K�B׋����i�C�P�⛺�}�Ʋ����a�b�ۄ����I�r���~�����o���p�A�P֝�U�Ϟ�׀�㳃���ϲ������]�" },
{ L"c", L"chang", L"�������t����潲��C�d��m�_����K�����������������M�L���ȳ��O�䳣�D���c�^�щj�χL�q���������l����㮳����Y�S����`���˳����������k�o���^" },
{ L"c", L"che", L"����܇�e��p�q��͒�߳���������ފ��E�s�����J�����زu�" },
{ L"c", L"chao", L"���������������N���n�̽˸S���˳��z�����}�R���ȳ��J�V�{�C֚���|�q�����l�������e" },
{ L"c", L"chen", L"�ӳ��ח�����D�oՀ�_�n������������ލƐ�_�k�ꐖחF���Hܕ�����\�ן��c���m������R�I�l�����mڒ���׉}���{�~�ٕ�įM�������f��Y�Z���߇����r׏�G" },
{ L"c", L"cheng", L"�p�����ߗ��Ƴӛլb�������ɕ����W�l�r�Q���œ����̿B�d�X��f�V���|���p���ة�ɖb���J���ǳ��^�k���w���ǁ\�������A������Ô��ʢ�̓Z���ν��f�͗����\��S����䅮��Ν��~�șr�j���r�D���ѳҐ����G��" },
{ L"c", L"chi", L"�Ԋw�����q�򿻌�����E���W�����ʓ��ղl���i�v��|�A�ΰV�c�~���[�ڳ۳س�ދ���渇�K�ֳ��h�d�P�W�M�g�Y�}ܯ�k�t�����~�s�߅������L�ݳޅq���n�N�ܐu���E�n�I�D�l�r�X����߳��o�����Òx���Ȑp��г���뷟U��������S�v�M��@���o�y�J�B��چ�����u�J" },
{ L"c", L"chong", L"���_����ӿ�ҫ�����������n�o�Z��ی������꙳獃�r�~�u���x����Ì�肋_�|" },
{ L"c", L"chou", L"���r���o�N�ߠ��ٱ����Ǔ��㰽[�����{���ԗ���O�n��I�l���g���΋ᙄ�b�Ů��I�~�Pׇ׉�|��E�����������h���{���W�c���\" },
{ L"c", L"chua", L"�H" },
{ L"c", L"chu", L"���������،�iۻ�������c���Z�a�������I�n�e�����a���z�X�N�����г��r�陻�R�X�ƴ�̎�����������ҝ郦�s�A�s��ء�I�a�X���{�e����m���ǽI�G���s�䴤���zՑ���b������ĕ�b�|���Z�l�{" },
{ L"c", L"chuan", L"�ݴ�밴��������x�����״����ĺ@ݎ��F���N�b�w���[�����A�k�i�E" },
{ L"c", L"chuang", L"�V�����������������R�������l�����}�J��k�y������" },
{ L"c", L"chuai", L"�����u�����������" },
{ L"c", L"chui", L"�������������ǔ�����׵���D��鳹��N�m�q" },
{ L"c", L"chun", L"�I�~���N�a�@�������t��ݐ���������j���ݻ���̼�Ë�������Ȝ��Oɔ�_���c�T�������o�òQك��" },
{ L"c", L"cong", L"���ʴч��Ɖ�ȐS�����ИB�[ɐ���^���Н����ڕ��B讲j�Z�b�C�S�W�E�^�Ӵԏ����ď����Ȑ��Q���|�Y�z�{�p�S���q�����ߠ��ߑmց" },
{ L"c", L"ci", L"�̲��ګu���e��ڝ�d�W�qυ���ʫy��Ĉ������ȴ��e�~�ǴȮN�˴Ŵ��@����i�F��B�y�Q�o�]�\�ˁ՛��r�J�c���Ł�p��Ƙ��Ǆ���y�a�nΈ�^" },
{ L"c", L"chuo", L"�O�}�ִ������u�d�ƊŋS�Cਛ����Q�U�b�z�����U���f���p�q" },
{ L"c", L"cu", L"�I���c�����[���������Ð����{�|���u�K�ב�Ȥ�q�m��ۀ�q���y�����A�" },
{ L"c", L"cou", L"�՜�����ݏ" },
{ L"c", L"cun", L"ߗ�����Z�������~������ׄY���v" },
{ L"c", L"cuan", L"��ߥ��ڔx�f�ǈ�ܙ��m�緉�ܚ���ۺx�Z��" },
{ L"c", L"cui", L"��Ü�Ń��������N�����ݘ����\�J�y��~�������Q���y�y��������������㲟n륬X���\��ċă�W�P���xě" },
{ L"c", L"cuo", L"���u������i���\̑�ύձ����c���P�������z��v�z�s�u�ȴ����Hﱴ��x�S�e" },

{ L"d", L"da", L"�����Ǹ���઴��ד҉��}�p�]���ޅއމ������Q�E���e�}�����A���Q���z�_�Q�����R��σ�N�^�����󁇚����o�z�J�J��" },
{ L"d", L"dang", L"���������Y���}���ǭc�d�}ř���K�W�����ԓ��[�h������ו���ʈW��������ЋP�T�ծG닍ɝ��X�^ځʎ���n�T�U�D���o" },
{ L"d", L"dan", L"���l�����g��N���n�����l�G����[���S���Fэ����ٚ����X�R���[���b���m���y���㵧�恍�d�ۓ��y�^đ�l�r��ʯ�����������X���m�D������ࢆ����̆�����͞�E�g�Q��Ʌ�d�n�d�������V���}�Z�D�Q�Wٜ�����K" },
{ L"d", L"dai", L"��߾���y�����x��������a߰���ʎ����窈������������܍ؖ����ܤ�f�Hܖ���D�J�x�F�K�����}�D�l��ŕ�������O�n�y�^" },
{ L"d", L"de", L"�ćN�z�Û�������ｏԵ��u�ص�" },
{ L"d", L"dao", L"����߶��]��s�����C�ҵ���ꉍu���������v�I��쌧�Z�W�F�����\�x���������K���I�����R����ŏ�m�p�|�c�R܄����h�O�͘�" },
{ L"d", L"dei", L"�N��" },
{ L"d", L"deng", L"�Ƶ��O�\�⋿���O�~���ŵ�ꭵ����Q���سΉ�����㙞�R�Ř" },
{ L"d", L"den", L"�O�Y" },
{ L"d", L"dia", L"��" },
{ L"d", L"di", L"ص���͏��D�I�~Д��ƈ��������h�����ᴔ�L�f���m�ϵ���vݶ�ӵЗb�����{�����V�E�Ե��H�L����ˋ���pۗ�C�]�e�M�}ۡ�sڮ�k��~�ׅ�֒��ܠ��ƒ�ǜ�B�h�g���W�؈h�m�A�ܫZ�l���K���ۂd淵�ޞ���b�З\��ǅ���������K���W�X��馵ޘN�E�f�C�V�d���[���r�O�����S�y���d�B�y�R�E��" },
{ L"d", L"die", L"�����B�|���A�U������g�i�]�y�W������x�\�P�e�g�@������ܦ�隊���G����L��с�H�޵�Ŏՙ�������H��ې��A�l�B�ۆO��" },
{ L"d", L"diao", L"����a�@�򏬊P���q���h�J���M�f�c����y�����m��F�ŏt�������@��ӎ�������y�uɉ�H����{�L����y�S" },
{ L"d", L"dian", L"�������ٍѵᘈ������ۆ�����o���p�d����H��L�����_�s���c�������������������U����͟늉|���՘�崐�����" },
{ L"d", L"diu", L"���G���M�A" },
{ L"d", L"ding", L"���ꎊ���ඤ������B������w�J�c��픶��������Y疶���G��ӆ�}���bग��붧�ִO�V�r��" },
{ L"d", L"du", L"�������^����`�A��������������t�i�L���E�X��^���ٙ����{���y�����~�x�G�K�o�b��tט���ƶ¶Ĭo��ـ�G�Vܶ�Ŷʊ����T���|�ɶ�Ζ僚����C󼅶��" },
{ L"d", L"dou", L"�ʄr���t�������X���z���h�����׶���^�����K���W�����Y���H�×uÖ���k��Z�L���L�]�^�`�a�c" },
{ L"d", L"dong", L"�����|���{ᴕk�𴂔Ǉ������Ċต���X�[���C����ʐ�ٶ���Չ������������ޓ��ἒ������ؑ���Ϝ��L���P���H" },
{ L"d", L"dui", L"���щ[�y�q�����X�Ӷԃ������ҵq��꠶��Խ�������T���c�A���}�B�m�V" },
{ L"d", L"duan", L"�Z�ǋe��у�H�̶ζ�Ș�ЉF�Ѭ��a鲶ʹV������呔��Y�f" },
{ L"d", L"duo", L"�����Ͷ߄��ޚǔ����և�����씣�����Ưk�Z�A�����I�Զ�\�m�����ᒗ�Ö��∑��綶捓��s�ٶ��o�r��E���D܀���b�m�w�y���������G������z�K��V" },
{ L"d", L"dun", L"�֐����P��Չ����Ǡ�������H������O���������ޚ�۶����g���D�J�q�����v�]��" },

{ L"e", L"e", L"������������ވ�Ň��S��k����ݭŶ��Ӟ�e�xﰱ�����M�d�f�~�P���~�Z�[�F���q��������ѳb�����ն������]�����������O�_ج���F����ٳX�S�H�@�����Lܗ�r���v���׈�񜊐��Q�`Ⅼc���~���i�Yʂ�{�I�鑔A�@�F�d�J�����t���L׆�|�y�{����͌���E�k��" },
{ L"e", L"en", L"�C���쟸�W��" },
{ L"e", L"ei", L"�G�O" },
{ L"e", L"eng", L"�E��" },
{ L"e", L"er", L"�s�������z���H�Y�X�����s����L�x�[����X���bĞ�W���������Ƕ������������s�D����n߃���p�r٦�n�����@�E�^Ԡ�޻�ڍ" },

{ L"f", L"fa", L"����o�k�l�N���������z��ƞ���V���츟����X�P�y�U�����t�ᷨ�c�������m��ʆ���z" },
{ L"f", L"fang", L"�η������P���ʠ����K�Eړ�[�p�h�������������÷��ݷĕP�X���f�����낍�L��J�ň�" },
{ L"f", L"fan", L"���鮉����ެᦇh�̑�����������N�c�x�O�Y���G�F�K�i�������o�t�w�ȷ��B�C�����u�����[ć�X���T�������x�\����ϛ���P���B������������i���������܏ӌ؜�D�F���G�J�˹�ݙ�~" },
{ L"f", L"feng", L"���K���N�~��O��`�����L��o���Q����׍��t�h��ȗ���^���A�t���h�l�S��Qۺ�t�����I�b�p�K���h�ͷꜽ���Tł�m�쓞���p��҃���S���ٺ���u���R�L�P�iو�S" },
{ L"f", L"fen", L"�ַҎ��Է׷ՕS���v�����mӟ�ӗ��r�p��B�i�B���}��ڷ؞ǖD���i�_�`�����k�V��ʈ�˪���������J�k�������r�M�M�O�R���v�ݏk�e�޷ܶl�Ƿ�߃f��ď�^�S����a�j�b" },
{ L"f", L"fei", L"�T�������w�ƷȊ���d���U���q�q��p�����I�[�W�a�E�y�������N�F�d�˷̊O㭗�����ʄ�u���������������{�Ϸ��^�h�х��|ꊂn�X�Q�Ў��M���ЏU�հC���n�O����]" },
{ L"f", L"fou", L"����v����뀚��]" },
{ L"f", L"fo", L"�����u��" },
{ L"f", L"fu", L"��ߑ��߻�m���c���i�Q�u�N���C�X�������ü����a�����[�~�����w�W�����A�J�F�ʁT��������i���_��ܽ�]�������@�稅���ƅ������킷���s�����ޮw�t���ۮ�I���������bݳ�Г���������J�M��̒�����E���A���븢��ȃ�n�J���Dŀ�R�V�O�����ݽ����J�_�h�f��q��ᥝ�ݗ�~�H�D���L���v�i�f���⸸�����ԏ}�����M�a�Y����ᜒѸ������G�r͗�港�o�\�`���f���U�븼��������������}�c��Ӈؓ�����y�TЕ�b�k���D��傾�����i�c�����|��҄�c�ָ��ڸ����}ч���l��ʍ�x��Vݕ�ѿ`َ����𥸲�v�K�E�ӶO" },

{ L"g", L"ga", L"���٤�ȿ��Q������ٸ��m�V�����p�f�L܅" },
{ L"g", L"gai", L"������@�D���Y�����|�����w�B�W�^�dԓ��Ľiؤ�_������Ƹ��}����ȑ�wꮸŘ��[���y" },
{ L"g", L"gang", L"�ԃ�տ��ٸڸܸ��b�h�I�M�����ָ���Ւ��G���������V��s���۟��������ޑ�" },
{ L"g", L"gan", L"�ɸ��|���˔��\�Ί��������͸����Ỉ�Q�ό��m�N�l�����v���Q���r�ѸϹC�U�Ҷ������s�ϝ�ߦ�����h�N꺱Y礃����ƽC�l�_�֘o�g�C���M��" },
{ L"g", L"gao", L"��޸��o�{�w�V��غ�����R����p�z�����k�����ǐ������������X��c޻˛��怸�۬��ھ�z����ﯹl�a�J䆅�" },
{ L"g", L"gei", L"���o" },
{ L"g", L"ge", L"�����M���ّ��I����𛿩������˸������w���g�R抅τ���ƌ�󒚸�ت������\���x�Z���k�Ü�ܪ롘����x�w����k�Ӫ��Yݑ�s�k�u�Z�R�P���ϸ���������򴂀���ѹw�t�g�|���{����" },
{ L"g", L"geng", L"���j���u�����@�ٟ��c�f�K���s�}�����Q�c��y��箹������������i���한��" },
{ L"g", L"gen", L"��������ب��ݢ�^�j" },
{ L"g", L"gu", L"���q�ù��}��Ƃ���������B�f�g���Թ������L�M�������u�챶������H���O���Y�����ڬ��ȹɿ����l����Ɔ����댽�b���⒘��A�����b�Ű��Y�S�M�[�J�����kݞ�Wk�X�M�̹ʹ˃������č��ؗ��͵�����l�d���A��EÙ��" },
{ L"g", L"gou", L"���乵���۹��YН�h���^��ѐ���������x�a������T�V�v�m���U�xڸ�x���������ڹ����_ԍ�g����œk���혋��ُ�M" },
{ L"g", L"gong", L"���������^������r�������żk�n���m��򼹪���@����b���p�E�C�b��y�����ù������풍���\��g���yؕ�ߟ˸�" },
{ L"g", L"guai", L"�ԓ����Ֆʖ��L�y���֐s" },
{ L"g", L"gua", L"�Ϲ�������I�O���o�����|�W���m�օ��Є�����ڴ�q�Ғ솧�G�\ԟ���N" },
{ L"g", L"guan", L"�ع��ڹٹ���ҋ��ݸ�F�׸A�v���H�Q�K���P���b�^�ݬg�`�p��݄�]�^�e�o�A�j���O���ᛌ���ʹߐ�؞�����T�����k�������q�I暹୏�����ٵe����X�}��" },
{ L"g", L"gui", L"���棹�ߞ��Ɨ����v�����w���OҎ�@�ˋ��F�哱�|�ً����������Y�n�q�w�v�h�Q�o���k�l峚�������{�����i����܉����Q�М�͊�mԎ�����j���Q�۹���Ȳ������Ϊg�K�F���}�ZΚ�ʄ�������u�W�z�I�^���q���W�^�Z�i��" },
{ L"g", L"guang", L"�]�➻�Ӟ՞�ƚ�ۊ������D�櫇���_�Z��U�����V�E�S�U���Q" },
{ L"g", L"gun", L"ح��Ж結�����ɀ���L�F�i��݁�����P����֏" },
{ L"g", L"guo", L"���ÆF�������冩��ƹ������u�������变�H偏��X���������������N�X���b�I��s��l��Ǒ�����x餘���@�[���{�R�^�B�J" },

{ L"h", L"han", L"������c������E�����H�A�������������T�H�i�Λ����ʗc�ϬH�����������]�b�K�w���n�s���Ⱥ��G�\�J�[�{����I�\�������R�t�����պ��~�F�\�y��͔���U���h���L���I�d���h��Α�����u�A�n֛��[�ˠ�" },
{ L"h", L"hai", L"�����˻��������ܟQ�V�����o������������h" },
{ L"h", L"ha", L"�ǹ������xϺ��U�a�C����m" },
{ L"h", L"hao", L"ƒ��޶�^��]���������ƪ|�Ѻ����s�_����婺���ϖ�D�q�úº�껕a�G�m���ĆS�Ɛh���B����z�|̖�镵�����������A���ذ�����尞��h" },
{ L"h", L"hang", L"�������fކ�Ԕ㺼��������a������ؘ�R�W�V�@����" },
{ L"h", L"hen", L"����앁�����ԋ��" },
{ L"h", L"hei", L"�\���˺ٝ�" },
{ L"h", L"he", L"ڭ�ǒu�B�����X����Ϛ�����κͅ��A�����ӱA���C�P���»t�vᗺɺ˔����B���Ԝz�к��M�����Z򢐲�杼������Ԇ��؀�F�u������i�M��Θ��K�g�H�[�H��҇�����Y���Ł޺؈��YЎ�y�Z���n�R�E�۟����ֺպ��G�F�y�և��_�e�Q�K�S�e���j�f�g" },
{ L"h", L"hong", L"���˅Ԟ�������ܟ�p���E���Fްݓ均��Z����k������Y�K���Ⱥ�f�y���a���`��t�銼ݦ�����ļ��o�f��{���A�v�b���s�|Ȉȇ���D���p��~�f�C��딏�ޮ����Z�y�{ڧӏ�{�U�Н���\�" },
{ L"h", L"heng", L"��ߛꐐÆ�к�a�����t�����a�Ѻ�M����޿�U�C��" },
{ L"h", L"hu", L"���IϷ����~���~�~�U�����m�����O��㱜X̏ܠ��i��F���ĺ��XĊ֗�_������ͮ@���˺��a�����W���`��⩓��������|�Η��������S�P���������k�g��Ι�e�L�b��]�E�����C�{�[�R��䰂s�L��̕���G�t���u���������S�����Z�������O��H���������ͽ��A���������d���������U��m�n�����o����I�s��" },
{ L"h", L"hua", L"����������k�f�����芣�A���E�D�����W���焝�h��Δ�n�y֜�f��������������덆�O�������iԒ���嘥����Ֆՠ�X�p�E�f�N���ɳ��I�A�j" },
{ L"h", L"huan", L"����B�Z�b�JࠇȌAⵑךgג؎�O��ۨ���B�`䡻����P�~���f�b���}�x�v��������律�߀�a�D�h�o�I�q�]�Q�S�G�X�߭����������Kۼ�J�»������ѣ����h�ջ��������o�Q�ѻ����~�������阬��ߧː���k�Z�d" },
{ L"h", L"huai", L"��������ё��ќ���ўx���j�x�������|" },
{ L"h", L"hou", L"�J��@�jȉ�����T����������F�J�A�f�\�����C��ƙ���˛�����ܩ�_�����`�c" },
{ L"h", L"hun", L"��e���Ի��������ȝ�E�J�M��F���������Ɯ���q�Q�@ڻ�[��������G��k�O�o��՟" },
{ L"h", L"huang", L"�x�����Y�r�M�E�Ż���˂����Sȏ���؆ŋh���N�҈�̻͘R���B���ꪍ����Ŋ���W�k�����c����ڇ�b�u�m�U���U�О�Εs�ъN��ԅ���m�e�ƙ����n�Ͱ��w��" },
{ L"h", L"huo", L"���������凗���d߫��ͻ�����ߘ����‟��tⷛ[������i�񒻱n�X؛���������������^���x���C�@�_�N���o�f���첈���m��޽��hş�ɕ��G���\�Z�_�[��" },
{ L"h", L"hui", L"Ϸ�Ҟ��ڶ�ԻӒ�����Є����F���Y���^�]�D�����������Ԝ�Nы���j�v���E�x����Ğ`�s���߻؇�ݏh�j��ޒ�o��Y�C�D�`���z͠�t��ڻٚ����S�m�e�܌������x䫻��ܻ����U�߻����{�����}���@������_����R�������VԐ�i�d���a�G�]ޥ�����H�}�����ۙB�M�Ϫ����C�D���_�d˙�_�b�Z�g�D�x�~󳇤���L�P�M���i���T�u��w��H�_" },

{ L"j", L"ji", L"����ߴ���W�������Z��ܸ�ἡ������䖈�����޼���������|����������������U���O���������Kゃ_�N�f�������n�s�uՃ���܇\����Z�C�S�Լ��Y�H�e�^���ي�s�����f�u����I�^����Q�a�Z�y�^�a�~�W�i�W҈�b�A҉��������������᧼����ؽ�B٥�u�������u���Ÿ��f�V�������d�h�C����꫼��O���J��鮼������a�l��c�l���N����ު�m񤹜�a�e݋Ύ�v�崒�Qۈ�ŝ���g�P�U�W�V�e�}���M�j��͛��ø�������������ؙW�m�D�l���Ɣ��Ǽ���ϵ�Ɉj�����˼����������ȼo��Ɩƈ���Ӌӛ������̼��m�����ʏ¼ļŜgȗ�D���U�E�n��_�s�@���H�΄ޝT�P�I�b�I����������HՂ�ꕸ�]�̼����E���J�j�����o���Y���u��۔�H�a�T���հU�}���R�n���^�D���C�n�V�z�q�K�L�ۓ��V�^" },
{ L"j", L"jiang", L"�����������{�����w��������΅�{�K�։����^�Q���䮟���P�\�F���������׉D�X�\�Y�����v���vG���x�ή�筏�ǿ�{���ߝ@�ړ���T�n�u��֘��" },
{ L"j", L"jie", L"�ڽ��ܽԽ��A�Ӓ��կ^�ֽ��ஆ֋m���ꗸ��Ý�����M��f��֊�X�����m�݌�ڦ�g�ٌ�f�t�M�ܯC�w�oڵ�E����ޗ����ӓ�}���ʂ�ǝ漍��ݒ��K̈́�e�Y�}����]�˓��﹝��ԑ͝�H�P�m�����ٽ�ɕ���Q��R�m�d�ɎюY�O�^�@�O�^ϝϘ�V����d���nw�N��۽����ý��ëd��V��v�|���򻐅�Ȇ������p��͎�]��ћ��Y��A" },
{ L"j", L"jiao", L"ܴ������ƛ����母j����������������̗���ս����x���B���zĉ���o�p�Խ������B�t�������ý��T�ǽ�ٮ�ƽ��ؽʞ�w�����Ž½��нg�R�]����_븟����e���]�qד胂�ل����ɑ����C�ݭd�f���U�K�������R���ЅӒ�὾�ӊ��У�νϔ������^��]�����U�ҽ͍��ݝ��Ъ���ˊ�I��ڊ�_���" },
{ L"j", L"jian", L"ꧼ�Լ��߼�ǳ���l��芦�������]���G�\�����Լ꽦��Ȃ�g�e�����{�ߗ�R�D�����̼��`�{��}�Ϙ��zʗ���Z��V��e�J�K�D�����h�N�p���M���x���Y�����t�[�f����̂�d�~�����ż�����Ȃ��񒳜���������g���d��������ЉA�p�B���ُ������a��ꯑ���]���u�M�O�z���ֈ���O�����C�x�rϕ�牞��{�v�W�}�|����Ҋ�������������𫅽������k���焐�ɏ��I��[���ڙ�{饔��`�����O���c�u�Ԅ��������GՐ�v���`�{�T�G�I�]�����G�{�������R���W���U�Z�S�VŞ�Y�B�a�b�{��b������" },
{ L"j", L"jia", L"�ӼЊA٤�z�~�v��������䤚��ϛѼ����_���k����ʪo�`�k�e�Ǽ����j؆�m����גS�]��ۣ�P���v�k�Í��꩑��W�̼�͐�O�]�e�a���Gᵅ��w�μؼ֔ϼًT�˔З��Z⛘��\�����x�ۼݼܼގ��k�r�{�چ�O" },
{ L"j", L"jiu", L"�L����`��𯾿�j�m�����\౾��A���F�[�������b�žÁX�`��C�e�ľ��i�¼��N��탅E�ɾʾξ��і���w�B�ǾȾ͎��H�ˏG�֑W���f���J���Y�n���w��" },
{ L"j", L"ju", L"���H�Ғ]�Лt���ь��ھԾ�ꏚ������r�ҳ^�D�x����ݛ􍇊ۋJ����ڠ�B���K������Aŉ�vՇ�g�|�x�~�L�ϙh�����֛��I����`�h�Ն���H�����]������R���z����V���q۞�G���e�^�A�M�l�׾ڹ��۾���ؒ����_�����X�e��H���e���z�c�޾�ڪ��ߚ�����ܛ�����j���ߕZ���Ҿ���Ƃ�Ѝ�i�`���n�����Ͼ�����̘�e�������ې��u�X������������ޑ��M����Z��؋�����M�L���F" },
{ L"j", L"jiong", L"��Ոs�爷�o��S�W����ěs����ޛ�C�ӟK�N�G�������T����ѕ���y�E" },
{ L"j", L"jing", L"�y�i�l���������������G�p�܊��S��캔�ݼ�U��ȅ���澦���������H���������~�L���@�����S���ٌc�G�g�H�·��q�������K����㽭E�Z�`�����iς�����n���򾻛��\�����o��ޟ�������������x�Q�J�}�Ä�����t�d��������e�V���n�o���ߞs�X�R�����Y" },
{ L"j", L"jin", L"��񁗽��Ľ���b�����M�򫃼����Q���Y������\�T�v�������B������Ǟ�����H�����˝Wɓ�۾o��誃��\֔�~����桾�����������ݣ��������x���M�����ƜÌ��|���M�����V���B�q��Nف�������|��a�n�P�B�����\�n��" },
{ L"j", L"jun", L"�����J����Ђ܊�����q�S�T�����x�A��ҟ㗰����z���f����z�����Ϳ��}��������ܿ������a���BȚ�������h�D�����b�y�����K���E�F�Q�R�U�h�|" },
{ L"j", L"juan", L"������Ȧ�]�K���Z�����g���Å۾펙��ǚ�����m�Ė�F�������̾�������۲���C�C���I�v���C�g�^�C���\�z" },
{ L"j", L"jue", L"�پ�ތ֌؁|�ތH���]���ܽ��`�{�Q�񛉫i�k����N�O�D���������X��������ҏ���E�b���ȍ�ڑ�f�}�����kҙ�~�^�����ܬ��i�`�_�����tⱇoާʅ�ؑ��@�D�呉�ә@��Ĕ�����q�p�H�u���F�B�~��������Z�XӁ�ߞ��ݾ�P��������؏�j�" },

{ L"k", L"ka", L"���ǿ����������l�J�����Q�^�B����" },
{ L"k", L"kai", L"���K�_���瘿����]�����������܄P���̐𿬉N�a�Ǖ��|�z�G�a��͞����ѐ��b" },
{ L"k", L"ken", L"�G���\�ѿҿ��c�~�o�������w���y" },
{ L"k", L"kao", L"����}�@������������������D�����w���W" },
{ L"k", L"kan", L"�������迱��������Ƀݿ�٩��ݨ�����K�M���|��R���a�b���{�۴|��R�_��" },
{ L"k", L"ke", L"�\�����Ǡ�������������`ڐ�¯z�V���d���ɓt����P�}���W�����w���f�L�ǿȚ������U��᳞ܜf�ʔ����P�˿̄Ą˿͍Q㡊Ŀ���봈��_����ې��ྴR�~ŋ�n��S����ޑ�����ķi��" },
{ L"k", L"kang", L"���T�~���`���ܝo�����^���{�_�K�����Hߒ���ʠ迹�㿻���" },
{ L"k", L"kua", L"��E���F٨��㒿��ڏ���g�~" },
{ L"k", L"ku", L"��ߠ�L�ݖ���ܥ��ڜ�����p��@����竂V�s��\�F��f෯���ѝ���Z��" },
{ L"k", L"kou", L"�ҿ�������g�ڄ�ߵ�ېD���t����@����ޢ�f�A�]�p�d" },
{ L"k", L"kong", L"�����Ǜ�������w�I�y�׿ֿ��" },
{ L"k", L"keng", L"�l���Ԋs�Ӓ��n��דּ����U���L��H" },
{ L"k", L"kuan", L"�팈���C���y�p�E��L�T�U�w" },
{ L"k", L"kuai", L"�c����w�S�����ۦ������ښC�K���������~�X�Ҫ���Ē�[���d�Q" },
{ L"k", L"kui", L"�����l㦿����Q̝��N�h���u���k��ظ�����Y�ґ���������`��K���w�j���ẁ�u���i������ퟴjۓ�|�錺����ఋ���������Tʉ�Ň]�|�����}���d��Ą�r���A��" },
{ L"k", L"kuang", L"��ߝ��ڲ�ћ��b�N�q��n�H�E���[��ڿܒܜ�N�\�Ń��������ۿ����D�r��p�ܱq�m��T���_�L�A�k�q�����Y�p��Ƿ����V�k�k" },
{ L"k", L"kun", L"�������T��Ǎ�^�����j�������d�hт�J����@���K���O�{�H�A����͉חy�������X�����������ٱ��ܝ�" },
{ L"k", L"kuo", L"�����������ҹQ�u�v�����S��p�A韔U�N�H�T�U" },

{ L"l", L"lan", L"���������������ȟ��������쵃������@�{�[���]�L�s�h���E�a�@�m�k�����r�ڔ��w���ۻ_׎�_��Ҁ�|�e�������������Y�E�����G�Ћ����[�G�������C�|���ĠA�E���f���������h�" },
{ L"l", L"la", L"������ǉ�����y������ǓX�r��ˈ��������Y���`���h���|ė��F�D�j�m�����J�_Ϟ�n�L���B�u" },
{ L"l", L"lai", L"���g������䵗�嬨�|�[���F�򆋋@�[���Z�R�㗮�[���X���s�n����Q�H���D���s�A�}�lه�m�s�`�D�|���]�[�Z" },
{ L"l", L"lang", L"ॄ����O���Dݹ�ǗO�v�ȋ��Ŕ���ﶳ�����͙Ņ�^�H�q�똸�Z��ʖJ�Rɇ�i�L�T�ύ~�ˈ����" },
{ L"l", L"lao", L"�̓��̈́��η��ԛ���[�������X���ʑ��A���o��������S�����N�K�ѪJ�`�᫙�����L�����j������싪�Z�����x�Q�g�~�z���U" },
{ L"l", L"leng", L"��}ܨ�㶠�G�J�䂒��㶱��k" },
{ L"l", L"le", L"�������b���I߷�A���֫W��i�՘S�E퉘��{�����w�Y�V" },
{ L"l", L"li", L"���^������{�V������~��P��Ǘଠ��������Ń�]�����ˌV�����L؂�����џ���k�r����ւ�r�[��x޼��߆�����\�v�P�~����G�����y�C�c���g�h���{�P�~�Z���G����ٵ�b�h�q�������e���Y�N���墶Y������ߊ�k�u�������������^��߿�������������l�����n���������߳P�\ٳ����ƍ۪�ݖ������������ۛ����ݰ�������wت���j�����ҋK�Ú�������������́�����E���W���W�T�����W�����s�����F�G΀���t�_��v�ю_�W���`󜴕�O�ؠiϋ����]�^�����i˞�|���r�ȵZ���[Ϡ�s�c�X�������B���[�`���b�]Ӏ�V�є���ׁ�^�Z�����c�o�M�@����{�H����" },
{ L"l", L"lei", L"���ۂ���ɠ���Ю������ܿw�b�ش����z���W���n�r�D�[�h�Y̅���}�F����ڳ���ݽt�C�C���u�ڴ���ˉ���N���XϜ���{�|������P��������I����L�[�G���K��h�q�a��" },
{ L"l", L"lia", L"��" },
{ L"l", L"lian", L"�����������B�����������Xɏ���i�ǆ��U�Y����Ҝ���nў�z�V���t��奝��O΋���I֋ۚ�R������`��󹞃�H��砻^�d�������ϓ��I���������aĘ�c���`�_���������I�j�t������鬬��򾚝��b倚���n�����~" },
{ L"l", L"liang", L"���Zݹ����������c��������ܮ��݈�@�Z�I�������z�|����Þ�o�W�n���u���]���������Ȝ����gՏ�v�y" },
{ L"l", L"liao", L"���G�����Č��l�k���ȍ۝x�����ڍ���弋���|���ŭVĂ�ǘ����ӸX�i����ْ�Iێ�\ˀ�נr�v�f�s�m���������ޤ���t�R�͌��������̸N���" },
{ L"l", L"lie", L"�����ӄ�����Ɣޘ�֊�䣛������҆`�I�������Ԫd�}�~�󟭎{�V���h���C�Y�����Q���v��" },
{ L"l", L"lin", L"�������t���ك������ܕ����մ@�Թ����O�������ת���꥟��ݭU����׮��R���L���O�l�۞�������[�H�z�j�݄C�ԝ������ޏ[�ݙ_�R�S�ߐt���ޟi�U����V���C�A���\�k�`" },
{ L"l", L"liu", L"���֝�ۉ���q䯔�������鮑�^������]�s�򋈍����v�����������e��m���H�]�@�Y������y���g��˘�B�d�t�s�i�V������ΗB���P�ﳾ^��S�ޙP�[����½���A�gµ�Ҵz�s�C�w�f�j�w" },
{ L"l", L"ling", L"����c��{����ߏ��ʊ������ږE�`���s�{��n�_�g���g����R��������O�����@�e���z������f�Cښ�����kɈ����q��c�C�s��|�w�o�C����ʙ�ΠU���h�N۹���g�������������HЇ���I�X����h�`" },
{ L"l", L"long", L"���������Еo���ʸo��������¡�����V�������\����X�N�a�b�{���d�z�ɭ����t�V���a�b�����\�L�[�@�F�H�_�x�G�T¤£¢��T�]���ŉƔn�_Ū�U�Y���L" },
{ L"l", L"lou", L"§�k¦�����䜾�¥�U�f�V�s�I�D�Ә������eŔ�N�}֌���t�V�y�Ѝⓧ�v�R¨�tª��©���������U¶�o" },
{ L"l", L"lu", L"��ߣ�}�]��¬«®����¯��������y���S­���e���R�o���o�J�]���G�m�t���쭈�F���A�V�B���r�z�z�B�|�R�u±²°�u³��̔ɝ�F�o�����{�֓�t��Z�ڙ�ś���@�u���P�f½��¼���v�V¸��ꑄΊ���Ǌ�˜G�O�t��¹��»���f�ۃJ�����J�Fµ�T�`·����ޤ�I�L�����n�¾�ј��r�j�Xڀ�h��j�cºʀ����F��ۍ�J�A���غ����G�c�n´�I��e¶�U��́��f�^���_" },
{ L"l", L"lv", L"¿�����|�љ�˃�H�����L�H�������×o�~�����������ƃE�������X���@�o�|�����Ɉ���������Ȅ���˾G�v�]�y������V�l���r" },
{ L"l", L"luan", L"���������Ç��������F�n�D�a�\�J��������c�L�K̉��莰f�g�[����ᛁy" },
{ L"l", L"lue", L"�����D�s�x" },
{ L"l", L"lve", L"����ﲈG" },
{ L"l", L"lun", L"�Ւ��������_���������ւ�ꍇ��Sǒ�E�������@�K�F�b�]݆�i��M��������Փ��" },
{ L"l", L"luo", L"�ۆ����b������������T������������_�T���Z󻃬߉�}�M�{������j��ބs���z���s����I��e���忩��R�����ӛ����ѳ��j�ȹJԛ�à�������B�i�T�z�u" },

{ L"m", L"m", L"߼��ķ" },
{ L"m", L"mai", L"���h����ݤ�I�X��۽����ω������}���]���u�~�@�A�{" },
{ L"m", L"ma", L"�}��IĨ���鋌��Ħ����q�r�h������������R�w�Ԭ��aΛ��i��迵l���U��زK�O�M�q�R��K�x�����W" },
{ L"m", L"man", L"������á�������`�����m��֙�z���N�M���U�Ҍ̜����M���\枲������K�Aᣪ�����ܬ���ט��ܝٿz�N�Z" },
{ L"m", L"mang", L"����â����æ���x�nåä�Z���}ã����W���K�����I��˯g�{���Mçǃ��Ɵ������ϑ" },
{ L"m", L"mao", L"è؈�Yëì����é����Eܚ�F�~���ê���w������^����Ӊ�î�������í�F�Tɋ���d�pï��ðó���g�ґ���Q�|�rñ�u�ʕ�裐���ò��c��" },
{ L"m", L"mei", L"û�]�bƀöõ��ü�zݮ�dÊ÷�C�����؜��Bý����P�s�C鹘Múø�����̉r�Yù�[���Ӕu�B�q��ÿ������o�����Z��þ�ʠB�z�V�e�Ò{�i�����|�t������ڛ�m�c�����i�S�n��" },
{ L"m", L"me", L"�Wô���C�ۇ��Q����" },
{ L"m", L"men", L"����������j���T�Y��ǖ�ЭJ�`�{��̊�ː����F����" },
{ L"m", L"meng", L"���ɔB���må��m�Ȝ��������{�����pޫ���̝����ʕ�����s�������������W�X��L�������������i�B����Q�����Ή�����D" },
{ L"m", L"mi", L"���в[����������oԙ�i�����������O�z���C�[�������J�j�S�۔}�������J������d��m�������ߜ}Ȏ�U㝝��B��ڢ����^�ڐ\��ٵz�a�s��ғҒ�ܜP�����q��Қ�Q�ۘa���Z�D�e�ןǃ�Ǝȝ��k�����]���A���Q�҇Ù�" },
{ L"m", L"mian", L"��P�u������i�޾d�X�e������������D��������a�����ł������x���ϱ�����ﾒ���t�|�r�����@�E�M�I" },
{ L"m", L"miao", L"����b�����ž�������������������F��������k�Q���яR" },
{ L"m", L"min", L"�����劓ẐB�F�G�a�R���F�����ŬY�\�z�C�x⌾r����s�F���b�����������딕�����������h�w�ǜ�������}�o�����O����ϟ�����I" },
{ L"m", L"mie", L"ؿ����_�P����}�����I�p�����f�̙��T��`�f�x��" },
{ L"m", L"ming", L"�������b����ڤ���L���p�q�鋓�uԚ��Q�i������K�⊱���D������" },
{ L"m", L"miu", L"����և" },
{ L"m", L"mo", L"�����ތ�������ģġĤ���NĦ��ĥ�Uփք�֋ߔV�xĢ�rħ�����Ĩ��ĩ�\ûĭİ���Ԏ���z�{���b����ðĪ�e�t���]�u����Q���{͈���s���Įį������a����ī�a�h���Ĭ���_�ˏ�j�Z��g�c��C���i�Q�J����" },
{ L"m", L"mou", L"��Ĳ��ٰ�ސcı�������_�\���E����ĳ" },
{ L"m", L"mu", L"뤚�ģĸĵĶķ�oĴ�r�y�э\���k�c�������a�[ľĿ��Ĳ�����������њ�Īǀ�]���ļ�HĻ��Ĺ�f����Ľĺ��ō뎿}���J���V" },

{ L"n", L"na", L"���ϒ��Æ���擁p���~���ŅȊ{�����G������М�{��ܘ�v���y�c��i���M����" },
{ L"n", L"nai", L"�G�Y��ܵ���ʯG�iޕ�Ă�ᝋ�٦����������ؾєΗ�r" },
{ L"n", L"nan", L"�����Вo�����O���~�~�ъ��骕��Q�y���l�D��������ڋR�a" },
{ L"n", L"nao", L"ث�ΐF�Ӎp�������i⮴L�ώH���u�D�D���t�L�j���Ր���×�D�ߐ�觋��X�Z�����m�[Ğ" },
{ L"n", L"nang", L"����e���L�Ι�����߭�����Q" },
{ L"n", L"ne", L"������ګ�Œf���G�C�����L" },
{ L"n", L"nei", L"�Ċ���Õ�F�H�����ڃ��ǚߚ��M" },
{ L"n", L"nen", L"��ۋ�" },
{ L"n", L"neng", L"��" },
{ L"n", L"ng", L"����" },
{ L"n", L"ni", L"���������������u�v���\�ߌɜN����e�З��C��D�U�r�r؃�������F�u�M����٣���s�����v����컕��T�W�����o�M�ۚ����f����z�Ӑ�����狤�����Q�yā���ڙ��R�M" },
{ L"n", L"nian", L"���������j�P���|ճ�����R��T�ݜV����շ��݂��Ӻvۅ�fۜ�T�`إ�����ň��" },
{ L"n", L"niang", L"��݋����|�" },
{ L"n", L"niao", L"�������B���U�\��љ����������" },
{ L"n", L"nie", L"����I�}ؿ���[���������[���ǌ����������W�f�h�������y���L�Q�Y�R�������E���Z�����H���m�X�q�A�b�f���bב��D�" },
{ L"n", L"nin", L"������À" },
{ L"n", L"ning", L"���r����š����希|�������������F�Q�����f�ޙ��_�V�H�����AŢ���Ý�" },
{ L"n", L"niu", L"�ţ���S��ŤŦ��Ȗ�ť�~�y�o���" },
{ L"n", L"nou", L"������A�e�����" },
{ L"n", L"nong", L"ũٯŨ��ŧ���r�s�zʝ�⇁ē�\�`�Z�v�a�a�x���T�YŪ�����J�P" },
{ L"n", L"nu", L"ū�����۹@�wŬ���γe��ŭ�Փxǂ" },
{ L"n", L"nv", L"Ů�ϻs�S�\�Z�H��" },
{ L"n", L"nuan", L"�f�q��ů�`" },
{ L"n", L"nun", L"�Q" },
{ L"n", L"nve", L"űŰ" },
{ L"n", L"nuo", L"����Ų�j�ЙD��ŵ�S��������ﻘ`�L�Zہ埼K��ų�X�zŴ" },

{ L"o", L"ou", L"��کŽŷŹ�Ÿ�p���W�k�T�p��֎˚����tŻ��ż�U�I�q��ź��Y�a" },
{ L"o", L"o", L"��Ŷ�C���jޑ�e����p�M�L�i�q" },

{ L"p", L"pa", L"�Ț�r�t�ɰqſ�už��������Ғ����ᝏ�x������В��" },
{ L"p", L"pai", L"��ٽ�ǪT�ŗ��ƹu݇�����țf���ߜk�����W�C" },
{ L"p", L"pan", L"���e�_���������ݛ����ְ����A�g���������P�ͿT����ۘ�o�b�Q�m���а�c���՞Π����������j���G��b���" },
{ L"p", L"pang", L"���p�����t�Q���݅��������}���ϰ���������������I�o���T�ֱ~" },
{ L"p", L"pao", L"�ג������a�������󈃞��ڠ�����Ј�N��������E�尒�h�s�B�P�^��ь" },
{ L"p", L"pei", L"�ސC�S���[���k������������p�r䞂_��������������췫�������]���\Ʉ" },
{ L"p", L"pen", L"�燊��\����Ȇ�ԅ��M��" },
{ L"p", L"pi", L"ا������������̖����y����B�������u�y�됁���\���w�t�W�Y���y�i������B�C���q�F�G��Ƥ�o�����Y������ۯ��ƣ��o�n�u��ơ������Ƣ�M�����������m�R���Q���f�K�d���`ܱ�Kƥ�������k����ØƦ��a�|��ߨ��񱇺ƨ�ēF�ǋ�ٷK��Ƨ������@Ʃ�V�G��ޑ" },
{ L"p", L"peng", L"���ꛀ��y��y��Z�J�o���p���s�y�M���l����ܡ���H����ēs�X�k����@����՟���u�~�A��U�������e�e�X��i�J�u�m���A�v���������s݃" },
{ L"p", L"pian", L"Ƭ���ƫ�x����ƪ�@�������A��F�X�M���j����N��Ґ�G՛ƭ�_�]" },
{ L"p", L"piao", L"Ʊ����я�Ư��Ʈ����H���h�g�w����ư�i�Qݳ��~�g�o��G�����G��B" },
{ L"p", L"pie", L"�ҔƲ�ȓ�Ƴد���v��" },
{ L"p", L"ping", L"ƹ�jٷ泛ڳf�E�Z��ƽ��ƻ�Zƾ��ƺ�ҫr�g�������Lƿ�gƼ���K��ɑ̓���J�B�v�u���Z�z�R���k�{�G�q�q�΍J" },
{ L"p", L"pin", L"��ƴ氳W�I�|�P�Dƶ�n��ؚ�V��Ƶ���d�O������AƷ�����Ƹ�W" },
{ L"p", L"po", L"�������������������N�H���e�w�k��۶�X�M𫷱�����ό������O���p�g�ȍF�����^���Ƴk�B�ɜ��b�ǁn�R�K" },
{ L"p", L"pou", L"�ʊ˒g�h���������r���V���" },
{ L"p", L"pu", L"�����˒p����̯j��ۓ䝪���O�����и���ǎ�h�уW�T����豷o��r�ٟ�h�b�������ԟM�Շ����ו��E���뫙k���V��璱��m�n�����؎}�R" },

{ L"q", L"qi", L"��ހ�������������V���ݒݜD�����ݗR��������ڔ��������[�҉x��i�e���h�p��t���K��آ�������ߏ���᪌����䁅��o���X��Oٹ���~ꋔ����T�V�[��Ƹg����ܙږ�H��ݽ�W������X�����嗎����������w�J���o���D�R��L�������B�D�Qޭ�W���s�������������U�TĚ�u�}���I���GŠϓ����O����ߌ��ܻ���轫^����цu�M����������粗�����_���H�M�������������Z���H������ؽ�[������ә�֚�����ݜ�������Ԝ든���P�\�s�ʇr����Ӵw�����~τ��烍��z�B�����K" },
{ L"q", L"qia", L"�����֓������g�Mڞ었X�Ǣǡ�m�s����" },
{ L"q", L"qian", L"ǧ��ǪܷǨǤ�d���T�U�Fᩖe�@�ݙ�ǥ�Oǣ����OǦ�@�T�����R��ǫ�`�U�eǩ�L��幓�庑a�w��Ս��t�v�����o�p���k�q�q�R�R�S�`�a����R�����qǰݡ��Ǯǯ�kܝǬ����b�x�`ȓ�j�y���Q�E���p���nǱ���{ǭ�N�X�b�c�`�K����ǳ�ɜ\ǲ�d�S��Ǵ���`�lǷ�X��������]ٻ��ǵ������Ƕ�|�`㻉q�g�PǸ�G�����R݀�y����d�x�Z�c" },
{ L"q", L"qing", L"�f�i�������W����x��[�������X�A���p������[��_���͆��隄��ȍ�����畦������������������핎��F�NՈ�������׃�ٻ�ᚠ�������m�c�����D���|��" },
{ L"q", L"qie", L"�аm٤������Ӆ����ԅL������㫛���͉���㻖A����D�o囷l�@�`" },
{ L"q", L"qin", L"���������V�]�J�����W���H�z��������ˎ��Q�����ZǛ�����l���B�����s��d�٬l����쀋���ۑ[�������V�ܝ��Ց�������ψ�j�a�T���c�v����ތ��u�O�ąa�߆wǙ��l���C�p" },
{ L"q", L"qiao", L"���b��ȸ���������^�Ú������f�N�����������ش���@���Rډ�E�A�������J���ǟ�~���̃S�ۘ���㾽��w�a�����֟��Ԙ��Ư����N�Sڈ��˖�y�X������~���~��ڽ�������V�|�s�˓��m���I�[�N" },
{ L"q", L"qiang", L"ǼǺ����ǹ��ޫo�m���]����ǻ�ن�}��������z��������蓬�[�m��ۄۖ�j�I��ǿǾ��ǽ���@�\�N���Z���ԙ{��Ś�b���u�����߿��H�j�����ܟ���" },
{ L"q", L"qiu", L"���H����w�n��k�|�ǋp���c鱜�ɒ�j�~���Eڂ�h���F�G�b���p�q�@�������L�@����U�_�F������A��ٴӈӉ���aᖆp�i��ޝ���z����W�䚂�U햜r�����ύ��H����͏�����p���g���G�M�b���F�����A�z���U�I" },
{ L"q", L"qu", L"�����J�r�ҁ�ڰ��ᫍE���|�o���l��Р�������^�a���x���L�л��m�l�t�男�n�o�L�@��Dڅ�|�N����������O��۾�����aǆ�P�����Tȁ�@ޡ�S�z���J�g�����޾�ߞ����J묙�c��R����d���Y��ȡ�lȢ�s�y΃ȣ�xȥ���`���^����Ȥ��C�z��U�Y�d" },
{ L"q", L"que", L"Ȳȱ���U��ȳ��ȴ�s�����j�ȸȷ�����׉U�nȵ���Fȶ��U�`�_�|頠P�I�C�o�]" },
{ L"q", L"qiong", L"�����o�^�������{�̹H�^�ğw�z����͋�|�������Ų`�F�w�K�W���}˕���\����" },
{ L"q", L"quan", L"�I���Ȧ�����ѹ��zȫȨ��ڹ�犺���Z���wȪ����ȭ��Ȭ�o��������ț���h�ܠŬ��b�jԏ���I�����m�ȩ�����g�e�k���jȧ�S�E��Ȯ���繾J̆Ȱȯ�����j�X��T�B" },
{ L"q", L"qun", L"����Ҏ��l�nȹȺ�t�d��" },

{ L"r", L"rao", L"��������ʁ���Y�����N�_���v�@" },
{ L"r", L"rang", L"�·y�����Z�K����ȿ��`�X�������}�Ñ��j׌" },
{ L"r", L"ran", L"���VЀЅЙ�c��Ȼ��ׇYȼ����Ƚ�ۊ�Ⱦ�z�v�L" },
{ L"r", L"re", L"�������ȟ�" },
{ L"r", L"reng", L"�����w�i�e�ܵ" },
{ L"r", L"ren", L"�������ɖZ�����\��e���������Y�ߖᶉ���r�ЄU��ך�����Ҍ�⿠�����k�����M�s���żx��ܐӕ�G�e���H�V�m��z�~�g��J" },
{ L"r", L"rong", L"����������Ǝ���ޚ��t�ݟV���ɓr��q�s�m�܍ʋ��ؘx�Řs�۷Z���^�Fђ���΍��V�h�g�q��ϔ�ߌ]�c���P�շ\" },
{ L"r", L"ri", L"���R���z�J�V�~�_�a�g�f�i�h�n�u�t�r��Ŗ�c̃" },
{ L"r", L"rou", L"���b�ỀÅ�|�Y���n�Q�y�\���j��݊������k�~���k�q��`�k" },
{ L"r", L"ru", L"ߏ������㒝����M�x�T�S��pʇ���n����޸�����������}��p���N�����r�J���������䋇��d�C�d�]" },
{ L"r", L"rui", L"�c�qި�M���t�G�B�G�H���ǛI������T�����J��" },
{ L"r", L"ruan", L"��ɉ��������Xܛ���\�}�Q�M��݉�w�O" },
{ L"r", L"run", L"�����c�t����Č" },
{ L"r", L"ruo", L"���څ����eټ���S�c�x���m��O�k�}���U��" },

{ L"s", L"sang", L"ɥ��ɣ�ʘ�ɤ����ј��r�" },
{ L"s", L"san", L"���q����맚Ʌx�Р��Lɡ��ɢ���̼R�V�W���D�o���^�d��" },
{ L"s", L"sai", L"˼�����H�����ˇT�����|�w���wِ����" },
{ L"s", L"sa", L"�������Q생����aئ�������l�`��ʔ�S�_���P�j�o���M̃" },
{ L"s", L"sao", L"��ɦ��ɧ�����A�����b�X�}���fɨ��ɩܣ����������r" },
{ L"s", L"seng", L"ɮ�O" },
{ L"s", L"sen", L"ɭ�ؘ��I" },
{ L"s", L"se", L"�~ɫ��ɬ���Ĝi�끚m��ɪ�����o�C�����������i���i�w�N�Q���m֠�o�L�n" },
{ L"s", L"sha", L"ɱɼɳɴɲɰ��ɯ�~�Q�}����E�𳏓�ɷ�e�Ęf��ҭ����������|�\��ɶɵ�����S���������ÏB������������" },
{ L"s", L"shai", L"ɸ���Y�k���iɫɹ��" },
{ L"s", L"shang", L"�����������@���K�C�g�ʑ^�����D�xօ�l��������͘��p��L�J�l�A�Ќ��v紾y�" },
{ L"s", L"shan", L"ɽ��ߍɾ�h��ɼ����ɻ橊��G����ɺդ��È�Z��ܑ����ែ��Ǆ���ɿ���A�����������c��������ꄞ��W���������@ڨ���޵�Ә���]�����Ɨ������۷�R�ɉ��������蔻�`���ӶU�Ŵ����b���π������~٠�i���W�X�Z" },
{ L"s", L"she", L"����ޮ���f�h�d���������F���^��ͅ���Ҷ�������h��ʰ�������O�h���������㓔�J�b�χ�s�M��؞��z��" },
{ L"s", L"shao", L"�z���������ԟ��p���������i�ʟ���}������斶�x�����ۅpۿ��Ќ�ڊ��B���K��ʖ" },
{ L"s", L"shei", L"˭" },
{ L"s", L"shen", L"��J������p���ڷ���A�늍�𖸚᷌�|���r��vݷ�m�`��������Y���[ȐɆ�KԖ�֮e�Q�B����M�����_���Y��ʲ�����h��ߕ�z����������ן���B��Ք���T���ֲs�c���}�\���ςL�Y�رsÌ�������I�}�������͖�B�v���ޘY�]" },
{ L"s", L"shou", L"�������������׈��������������ڛ�緯l�f�ۉ��ݾR���F�" },
{ L"s", L"shi", L"ʬʧʦ��ߟʫ�\ʭ��ʨʩ�ƛ����J�PȞʪ������N���AԊ�{�����O���[���tѠ��圝��X���P�|�ʮ�ʲʯʱʶʵ�g�E�zʳ�u��ʴʰ���]��ݪ�r�Y�����҉P�J���t�g�������R��ʷʸ�d��ʹʻʼʺ�j���E��ʿ����ʾ�����F���ƅb��ʽ���~�������ԅ����Ӗ������g�����ѐ^�c���Ã������űi�x�����������ҕ���B߱�֏ʓJ�����P�ݏs�Y�߱��lԇ����v���k�m�]�S�O�K՞՜���ɋ��}��u����n�W�y�۸b�֟��Z���|�]�t" },
{ L"s", L"sheng", L"�����j�����Ζ��N����Ɓꅫ{���}��Ϝ������H����|�������I���K�Wʡ�򂯜�ʥʤ�ɕ��˄�ʢ�Kʣ���Ӭ]�}���|�oً�i���J�T" },
{ L"s", L"shu", L"�������x�������ݱٿ���⼂���Y���g�Ċ��ܓ����E��`��먚������S�\�ߘ�ݔ�_�]���d�e������������q�H����������������\��P˟�e�l�����X���������J�O�C���X��ˡ�������D�R�g�V���_��w�����������Q�f뗝�����T̠���^�O" },
{ L"s", L"shua", L"ˢ�ˣ�X" },
{ L"s", L"shuang", L"˫��ˬ˪�p�Z�׋����{�t�d�C�L�U�w�S�Y�u���B�`" },
{ L"s", L"shuan", L"��˩�V˨���Y" },
{ L"s", L"shuai", L"˥ˤ˦˧�����i" },
{ L"s", L"shui", L"˭ß�l��ˮ��˵����絈˰���c˯" },
{ L"s", L"shun", L"�J˱˳�˴ʊ���i�p˲�B" },
{ L"s", L"song", L"���ɖ�������ڡ��ݿ�������s���ԝ둡����e�������B���ؑZ��d���������A����b��m" },
{ L"s", L"shuo", L"˵�h�f��˸˷��˶�F���������ôT���l�q�p" },
{ L"s", L"si", L"�S����˿˾�i˽�q�Ђh˼�l�̌�����w��˹�z�j���D�t�@�˶L�E���F�Q�l���f��˻�z˺ʑ�P��·�J�\�a�z�l�r���D���ȁ��������ᛅ����Ł���K�y������������ٹ���Ơ�ʳ�~�B�囗���]�t���LҖ�r�����|��{�T�ʜ���[���x������" },
{ L"s", L"sou", L"�Ń���n���L�r���Cಪv����쬓����������g�}�t�`�p���������޴˒���P�ԯ��\" },
{ L"s", L"su", L"�ծd�ָ@�շd���V�K�Ň��׫T���ߛ�������x�٫��ػ����V�X���Ղ����V�C�h��܉O�i����ݜ����p���ۘj���h�x���_�M�c�ɑ������i���q˂���Xۑ����T�j" },
{ L"s", L"suan", L"⡯i��W�{���g����" },
{ L"s", L"sui", L"���V������]�a�����������m�������U���S�l��Ď�v�聂��Z���ǈ������q�r��B����ܷ[���w�r�ݙp�X�j��u���`�����Z���\�w��}ݴ" },
{ L"s", L"sun", L"����ݥ�O�s�q�p��ʘ�V�������S�p龹����{�Z��" },
{ L"s", L"suo", L"ɯ�j��涒����������������ȓ����t�w�z�s����������������ŕ�і���F�i��a��C���R�R���_" },

{ L"t", L"ta", L"���������k�����B�����d�Nя̤������̡�]���H������j̢�˪H����������e�`�����齝ߓ��w�J�\���̣���O�F�D�Y���n�c�@�Z�ݠ[�k���m" },
{ L"t", L"tan", L"̮̰�Z�a���j؝̲̯�c̱���Z�����c̳�۰��̸����Ő�����̵�W̷̶������Մ�]���U����A�̴�t��˓���T�v؍�Z����̹��̻�I̺�N�g�������a�ƭf̾̿̽���@̼�l�U" },
{ L"t", L"tai", L"̨��L̦̥ۢ�@�r��̧�ƞ�Ǡ�����U�_�x�~�T��޷�E�ꙅ�F߾̫�����̭�L����̬���v̩̪⁜̑B�M" },
{ L"t", L"tao", L"��߶�|��������d�|�����ώ��������_�lݝ���z�N�w��ޏ����ӆG���җ������������i�I�T���[���P�uػ��ӑ��" },
{ L"t", L"tang", L"��列��R�ʄ��v���T��ۏ�M�U���n�����Ć��o���y�G���������y�f�K��g�Ŵg�C�̘����L�}�Z���Q�h�n�y�O�S�����Ȃ�����������E憃��ܠ�����̓��C�|" },
{ L"t", L"te", L"��߯������c�Y�PÎ��" },
{ L"t", L"teng", L"Ć���ۯ\�����ܝb��߂�Ο�g�`�������v���L�T̄�I�L" },
{ L"t", L"tiao", L"��٬�����f���w�K���������G�x�l���V��ɂɊ�������p��������x�f���i�q�I�x��A�I�Ӌ����нrқ�q���g" },
{ L"t", L"tian", L"��̊����L�j�V�p���p�����bx������\�J����\���ٓ��[�g�K�k�k�D�c�l���傁���L���`���_�󱙯t����q�C�`���q��" },
{ L"t", L"ti", L"�����������R���`�f�e����簂��q����v羐��X�䶔���H��v���ٲV�|�Y�zʃ�Ӿ���ڄ��ۇ����p�{�}�Y�f�����[�_�����n�e܃�w���뛢��m���������ϒ��P���G������W���{�Y󍚏�S���󞭃���Gڌ" },
{ L"t", L"tie", L"���G�����z�N���u�㎃c��F�����" },
{ L"t", L"tou", L"͵�ʋ��U�W�B��ͷͶ���^���}���W�e͸" },
{ L"t", L"tu", L"͹�_ͺ�d�Lͻ�ޒ؜���ȋ�f����W�C��ͼ��ݱͽ;��x��Ϳ���^���˓\�����\⊍ĉT�\�]�O�������T�D�E�G�B��I���h�����M���ʆl�Q��ރ��ǁܢ�r�B��" },
{ L"t", L"tong", L"����ͨ�]�p��Ɍ�ט���ͬͮ١����MἍd�L�I������zͩ�����U��ͭ��ͯ���UԘͪ�P�~�n������������H�ՕӖSĀ���Էrͫ�jͳͱͰ�yͲ�c����ʹ�h�Q�q" },
{ L"t", L"ting", L"����͡����[�����N�H����a �dߋ͢��ͥͤͣ���Í��s�ѹj���w����b�F���N�k�K��ͦ���P��EÉ��ͧ�F�P�b�c" },
{ L"t", L"tuan", L"�l�ĈC��؇�Ň��҄����`�F�_���i��昼a�o��������蜨щ" },
{ L"t", L"tun", L"�̅וH��l�N�p���͈d�ڏ��X�vܔ���Z�����`���ę�����" },
{ L"t", L"tui", L"߯��ɗ˔�w���P�����j�k�n�s�L�~۝�Q�ȃUۃ�h�M�ˊ�����͑���D�[" },
{ L"t", L"tuo", L"ر��י��ВL���l٢�����k�ϒ�˵�M�h�ɒ�ЛӚ���Ó�X��y�e���u���ՠ��A���������ȳaІ�F�q���Ɉ��W�P���j�����r�D���K�n����C���������֗����E�z���ؚ��[��ڗ��������E�X�D" },

{ L"w", L"wa", L"�ܰ�����������洷��|���z����H�ܓ��Νj�D�|�c������ߜ����[���v�����e�m퀮B�M" },
{ L"w", L"wai", L"�J���Z���������" },
{ L"w", L"wei", L"�yΣί����������Ԇ���Ȗ�n�ˍ��f�G�̜՗ܘLԕ��΢�O�k�A�Jޱ�V���L�g�hΡ�S��ΪΤ��Χ����Υ���훔�_�e���fΦ��ΨάΩ�^�͋W�����`�������SΫ��ɖ�����W���d�H�ò��W����ΰαέ�Yβγ���䢛���U����΂�ή���|�_�u�[�]�\��⫝̸w�JȔ�Ώ@�ە��������|��^�ۓ��^���l�Q��Ն�c�l�e���S��n�]�t�w�|������δλƄζθηꦅ�ǋν�}ξ��ι�y�μ��ε�S�V�o�o��ο�����l�o�]�K���^�W�G�Eκ�j�E˗�A���G�v���~�Z�^׈�ˉ��U" },
{ L"w", L"wang", L"�̌����􌷌������������w�^������������������D������͇�\�W�y�s�͞_��ނ���������R" },
{ L"w", L"wen", L"�j���d���X�����v�Aʕ�nݘݜ���M�������[���ƞ������P�y�ӫ����m�b���Y�j��Ν����R���I�Z�؁��ǅВ^���W�ɗSÂ�ȷg���ʊp�����|���b�h�����跉e��w" },
{ L"w", L"wan", L"������������G�����㝟���Ϟ���\ܹ�������e��w����ؙ���B�D���{ݸ��D�n纈���i���X�����핈���������U�O�n�l�j��e�d�񊀒�Á���f���k���[�s�H�o�Tٖ�~�@�^�v���T" },
{ L"w", L"weng", L"���˜��lΊ�f�O�؊T����R���\�w��޳�Y���N" },
{ L"w", L"wo", L"������ݫ�n���i�u����ุC��΁�b�Ҋ��Ӂ���뿖����P�ܛ���ᢋ_���՟s�җ��O�ӲY��ğ�x���}�j" },
{ L"w", L"wu", L"أ�����v�ۛ@�A�����זg��ݛ����ٶ�������w���G�_�T��Ώ���u��������������ǅ��Nƕ�`��Ӎ}䴛��ു�@��c�o���oʏ����N�M�w���O���~�R������������������b���ꂗ�A���Ê��������ĴI���ʬ��葓���T�����W�y�^�R�@��������N�����������J�J�t���W����򐚐��|���������F�����}��뉍ΊV�׉]�͟���`�ȸP��H�I�F�\�F�F���Y�V" },

{ L"x", L"xi", L"Ϧ��ߐ��ϫ�����Vϣ�k������Z�[���Y�jۭ��`���b�Ɋ���仪L����������ϢϤ���N�T�R줕��Nϧϩ�X�_���l��ݾ���q�m�yϬ������������ϡ����������ӟ��w���YϪ��������Ϩ�~��k�FҠ�g���mϥ�����q�ҋĄD�ؘ��쨟�����Ή�O���a؉���l��G�H�q�O�׎`�G�Y�T�@���}�^�{�^�@�d�����ؠx��ӂ�����Pӄ�ϰ�Eϯ����Ϯ��ϱ�t�j���d�v�����@��ϭ֐����I�e�w��@�u�Nϴ����ϳ��ϲ���}�|�b�c���S��]�����L�l�u���kے�t�^�����h�[�cϷ⾌�ϵ��ϸۧ�O��_�_�S�S�A�����@�Ҽ��M�i���b�I϶�������K���V�����̷G������ʓ�B�]�_���̟�q�]�M�S�U�a�ڎ|�L����ǂ�{�Q�������S����" },
{ L"x", L"xia", L"��Ϻ�B�i���P��Ϲ�r�yϻ�����b���Ͽ���Ԟ��{���M���������{꘼��糈�ڹd��r��ϾϽ�W�lʛ�[�Y��ϼ�ݠ�_���h�T�p�B���ůK�Ļ��òLՒ��������]�Y��" },
{ L"x", L"xian", L"���Ɍ����Ȋh����믖}�i�x�얞��ݲ����������уM�m��ʇJ��T���W�����v��r�D��۟�M���s�`�o�N�]�v�w���Ё��҅���j�ѱ]�̒�浊ދM�p�L�����e�f̀��������ӮQ��t�t�{�S�����������P�_ݍ�B�G�vˁ�U�y���D���������A��ϴ�Ԟ��򹍁����`ϳ��͘�е��{����㊹��U���M��޺���Ҕg�\���]�N�`�@����������������`�h��܊����s���{�Z�׈��ɬF�����������m�ٻ��d���w�g�n�^�Q���}�ȑ��Z���D�W�h�R���G�@�n�I�`���E���j�v" },
{ L"x", L"xiang", L"��ܼ�����_�l�m�������x���e�G��|č���������֭����v��J���������Ԗ���|��Ԕ�K�큉�����J�}�����}�A���aφ�������z�W�����������i���������V󭇻�}�P" },
{ L"x", L"xiao", L"����Ф�Ʌ������P����篎�����n�����^̍��V���n�^���e�h���������ٽ��`��E���X�R�N�����߇^��ąʒ���Y���{���}�]�S�r�n���t�v���n�χ̇��u�j��D��̇���U�����F���qС������q�~�S�j�԰�Т���k�D���߂jЦУЧХ�唬ԉ�[�V�C�[��^�Ô��M" },
{ L"x", L"xing", L"�ˠ��ǈ��U���ʟ��w���q�����S�d�w�H�۰��]����������΁��D�������藊�����]͍����o�t�hʡ�M��ߩ�����������n����㬛�Ȋ�m�N���B�Q�_" },
{ L"x", L"xin", L"����ߔ����о�|�ÞԖ���꿱^ݷ�r���D�dп��Q�\����нܰ���Q�����W熁��c��ض�J��܌�MÒ�Ɵ{�^��g�" },
{ L"x", L"xie", L"Щ���n�aШЪЫϐҶа��Э��в�f�G���e�lЮ�����|�~�{�~бг�ɽe���������Я���n��Ь�q����ߢ���E���C�X���X�P�p�y�@א��дѪ�挑ˆ�Ğ��йк�m����������ж�lм�L�c�ǂĂ��c��е�X�u��л�ыr�͉f�D������р��������ⳎO��и����ޯ�Z�I��x�C�Ɖ�a�C�^�Tзϒ嬠y�a�k�i�K��" },
{ L"x", L"xiong", L"�����փ���כܺ���ڛ��r�M���r�KԞق���ܟß���ל�w�锸�U" },
{ L"x", L"xu", L"��������L��������Ӓ�S�S��̐��נ���T���H̓횽������q����uʌ���[�H���d՚�_�^֞�z�]��P�`�T��۵��[��ڼ�銐��򫍆ĕ�Ԃ�P�����[���S��B���^��T��r�V�U���d��䪕v�~�����A����T���������Ä��������{�[�����A�[휜���A�㘏�s����w�N�W�V�{���v˅�m�r�Cޣ" },
{ L"x", L"xiu", L"�݂c������Ñ����Ã��^�����㖘������T��}�G�q�v���ޜ����N��ᶍL�嫋����L�⽑����Pхф�Pΐ�����C�V�n�M�x" },
{ L"x", L"xue", L"���T�HѥѦ�j�m�YѨ�ālƋ�Nѧ��`Џ���W�G����K���{����ѩ���L�ɠ����y�����p�o�x�y���}�G" },
{ L"x", L"xuan", L"�����R�����t܎�]�����k���l��H�ːП����{�Ѭu�U�h�P���A���m�ʞ�֑�՝�X�C�M�Qύ���T�B�X���ثt�����I��͕����试Ùe�v�҆Iѡ�@�xѢ�_ȯ���R�ŕ]Ѥѣ��О�K���f�ֽk鸘C�C���R���X������K" },
{ L"x", L"xun", L"�_ѫ�����[�׉_Ѭ����`޹�����ĝ�`�Q���c�o�����eѲѰѮ�hۨѯ�pݡ��������r���՗D����ѭ���Mԃ�����x̶���R���@����y�S�\���_ѶѵѸ��ѱѴ���Fѷޙ����ѳӍӖӜ���Q���㶏�Z�d��ަ�e��R��" },

{ L"y", L"ya", L"��Ѿ�R߹ѹ��ѽ��Ѻ��ѻ��Ѽ��S��ŗ��f���E���s�����ѿᬅ��e�������۪c�����X���ÝQ�\��|�ޯP�s����{ʋ���L��҂ҁ���������끆܈�����o벒�Ӡ���I�m�y��嶖�B�E���V�c܅" },
{ L"y", L"yan", L"�������������͛����������糚���P۳�B�̝v���Z����Ë�c���E�iڥ������ܾ������Ӆ�I�����מϕV�P���r������Ǧ�Ί��ֆ��J�x�P�Z�ѽ��ۍ����ǉc�C��ԝ�N�B��̚鐅��������i�����r�s���}�h�����Z�W�فm�����]�mٲ�������D����۱���T�V�C���R�{�������ݕ�����s���ݍ�ъ�i�ʑ�{�y�t�d�����f�[���o���k�j���E��B���|�t�v���z�s��z�_���⊰�叩�S����������ҍ����ꚟg�����߆��㔩�_�����H�ٜĉ��̅������e�݋��П����e�V���������V�Y���Fٞ�����w���z�z�d�`�I��������ׅӃ��G��F����ח�V�W��������܂" },
{ L"y", L"yao", L"��زߺԼ���|�nҪ�@���@�����^������سҢ���Ƚ���Ҧ�i�������Ղx��Ҥ�e��ҥ�U����ң�b�ڋ��rҡ�u����l���u����G�H�t�A�C�P���|�{�c���_�i߈����]���a��q�Ö����wҧ�̱l���Ҩ���Q�ʜ��|�e��[�o�rű��ҩԿЉ��ș�O�o�ҝ���Ϊ��G�aˎ�d��ŗ��ҫ�f�_׊" },
{ L"y", L"yang", L"�늚�t�����o��j���Z������}���g�����t�r���D���ބ������󈔕[�f����ꖱ��ՓP�������������݌�U����^�u�R�F�n���օ���t�斳�������D�I�D�������^�B�Ĕa�Y�W������k�h�����ӵS" },
{ L"y", L"ye", L"��Ү��ҴҬ���S��ҭ�I�Jаү�����������y�U��ҲұҰ���S�c��ҵҶҷҳ�����wҹ��ק����퓒Ŗ�����Һ���~Ҹ���I���@���L�p��Еϰ��w�@�����Y�]�I�J�֔L�|���E�d�v�K�B�{�w�H�v�B�E�C��" },
{ L"y", L"yi", L"һ�o������ҽ�������t�����c�j��ҿ��~ҼҾ�ζB���F㞋��̉���C�p���}���t�����b�s�p�U��F�����݌bڱ�ޖs�ʛn�����ˠ������̐q�ݍ[ޖ��A�}��Ӕؗ�Ȗؖ�����Б�h���U�����Ɨ�͆�O�r�r�ŋf�����B�D�����ɟ��z�x�����KΒ�U�V�{���k�m�ڌ��͏�֖�F�J�~ׂ�������~�Ɣ����Ӂ�β�qސ������ᐸ�����ޠ�ЂÔ�r�i�C�v����p�}Ε���ڵEρŜ��T�t�V��߮�����䰬�d�����E���N��������ֈ`߽�����i�����k�p�ؖ������t�h��٫�����u���@��ớ������X���������i�p��ʳ���К����j�ś���㨈������݄��^�����[�\���T�U�c�N�p�z�W�`ژ�m���������|͂�v���������˃��x�{�G�~�v�m��Ԅ�����`�k�]���j��ɚ��M�����|�k�o���ׯ����ڟ֟�I�x�]Œ�D���쯖�e�jΜ�A�O��޲�ۋΎF���I�����������ܔ��c�٠J�W�jٌ؊�l�ٓ���ˇ˄�[�X�s�J�G�������{�y�g�h�[�����O�g�^ܲ�~���A���@̈�~ה�v���J��������" },
{ L"y", L"yin", L"�������f�����S��䦈����������ꔃ������P�s�Nܧ��ೋA���a�M���@���쐴����N���鞇��@�]퐃܁Z�����ߞ��՛�������|�Z��ӝӗ�C�������H�����w�����H۴�_��y���z�K���w���r�����l����������������_�i^�L���l�@�y�a�[�\���P���a�Ӱa׍ӡ����ط�������Z�J����S�E�\�����g���軃" },
{ L"y", L"ying", L"Ӧ��Ӣݺ��������Ӥ�k�����P�A�Q����ӧ���O�x�s��aӣ��Ї|���њ��팋��ߑ�ӥ�Z���D���G���t�c�[���ѭ��_�s�L�]���N�t���K�Wӭ������ӫӯӨөӪ���w���t���������L麃Oӱ��Ӭ��΄�H��Ξ�I���M�L�hӮ�����L�p�]ω�v�c�l孞��u�A�՞��Y���k۫�A�Ɨw��I��Ӱ�}�f��e獏_�g�`ӳ��Ӳ���{�j�ӗ@���C" },
{ L"y", L"yo", L"��Ӵࡆ���" },
{ L"y", L"yong", L"Ӷӵ��Ӹӹ����{Ӻ���Kܭ㼠��՝ѓ퇇���aӷ�M�t���O���b���x�I�b��J������ӽӾ��ٸ�Ԗ��~ӿ�������Ӝ�ԁ��Ӽ�M�ӏ����ӻ���x�����o�K�k�[�l" },
{ L"y", L"you", L"�������Q�ϛ|�čr��ޜ���~�y�H�n�����X���ə��i�l�����ɮh�Y�����͐J�U�M���֎��]ݯݵ�x�����I���K�[�q������♘A���j�f�������~�Oݒ���Q�����ρJ���h�hݬ��X���u��͜���B��뻠�����������٧���f�󠶵vޔ�N嶊��Նe�ʁ����z�R�Tф���ԌM" },
{ L"y", L"yue", L"Ի��Լ�s���E�܇����֑�뾊x��`�j�h����˵�x��Կ���R�Q��܋�Ð���Ծڔ�_Խ�����X�醺M�Ћ�[�߻C�g��g�S�~�^�a��N�l�V" },
{ L"y", L"yuan", L"���O�uԩԧ��w��Ԩ�a�e�m�Y�A���d���g�r͛���S�r�Q�x�t��������Ԫ��ߖ�O��԰ܾԱƊ�zԫ�ؒ���WԬԲԭ�T���ªjԮ������Ե�Դ�ƈ@�AܫԳ�����Vԯ�g�r�����Fѓ�z�m��x�~�Q�����@�w慙�߇�{���M��Զ�\�R�h䑉�Է��ԺԹ�c�������Ը�jц���" },
{ L"y", L"yu", L"�z���}���H�G��춷��|�u�E���ن����z���ځ���ߎ����楒T�f죫_�]���s���������GخƜ�������ʊ��������C���~��������h�土����΍���௘K���鮌�^��ń����褚Q�ܘ@�����Iш�O�v���u�k�N՘�|�u�D��ĭm�e�Lݛ��~�k���e�B���X�]�i�e�}�C�{������������ٶ�R������������P�h�����g��������c�r�����Z���Y��؅�����Z�˷{���r�Ԧ������R�S�����ș�����Ƒ���r��ԡ�����qԤ�ڳ_���@���N��ξ�МU�M��������֗������Z�~Ԣ�V�����Ɏ������S�����������ԣ����N�A���f�Ϝ����C��ε�h�T��z���s���Cع����hԥ�`�\�yʠə�ٝ��U�j���۟�ʚ�������[�I铴��R���r���O�N�K�q�h�|���P�M�u��z�������N�Z�O�����c�d�n�������H܆" },
{ L"y", L"yun", L"���C���Q��뵚蟾�[΂�S�Nٚ�Ȅ��Ɓ�ܿԱ�u�V硇����n�d�s�Ǜ��m�ż���y�l�ݐ��޹o���|�]�J�a�����m��d�@���\���E���q�a���pل�B�q�y����۩������i���\㳐��C����Z��ю����ʟ�Z�d�j�a�y�r˜�N퍒l" },

{ L"z", L"za", L"�����ћe���ٖ��N���H�N�ӛj����j�S�s�͇��{զ�u�U" },
{ L"z", L"zan", L"���ؙV�d�����a���ۂ̆����Ìv�S�ˇk���e�܃�����ڎ�ݕ��m���������Uۊ�Yٝ����A�Ԟ��{���`�{ד�" },
{ L"z", L"zao", L"�������sۛ��������闗��b�k������o�����r�_�V����Ł�r����Y�^�Yڋ���" },
{ L"z", L"zang", L"�M�ߠ����n�_�j��E�v�N���z�ʏn�Z���i�Q��Ġ�K��" },
{ L"z", L"zai", L"�֞����՞��Ԝ��ֲPن���������ْD�ڛ����d�P���f�K" },
{ L"z", L"ze", L"��g��z����զ��t����������؟��������K�����j�Ә��tՋ��c���jّ���]։Ϗ�`�v�B�Ǝٚ�꾕W�������k��" },
{ L"z", L"zeng", L"���������������I�Q���D����֟����{������gٛ��" },
{ L"z", L"zen", L"�����P" },
{ L"z", L"zei", L"�����\��ό�f�e" },
{ L"z", L"zha", L"��߸զ�s���閼�L��������������髄������u�ϰ��A���O����բըա�l੠��l���d��Q�~�z��գ�������W�~էթ����դ����o���p���ե����mɁ" },
{ L"z", L"zhai", L"�����ի��ժ�z�Sլ��ԙyխ�S���ծ�μ���կ�y�" },
{ L"z", L"zhan", L"ռմ��ձ칖��tճ��j�a��ղ�n���U߁�~�E땚ؚ�հ�r���d���@�}��D�gזն�sյչո�جW�K��շ���^�Q�\����ݚ�r��սջ�Cվ����Ǖտ����`�u����̛̜�f�O�J�`�պ" },
{ L"z", L"zhao", L"���Ȋ��Ў�����������D���q��噰���צ���Ӭ�����گ���ݪD�������A�����t�������D�|�w�נY�e�����^��" },
{ L"z", L"zhang", L"���ŏ���۵�@ɟ�l��������đP������\�����J�����Ɲq�����̒E�������˛Û�ϯo��։z�~�ί��d�w���b" },
{ L"z", L"zhe", L"�����چ����z�y�K�Y�E�qП���܆�����������Ԁ����ߡ�m�t�O�����U��ֆ֕���H�yׄ���������z�N���x�����@��J������V�p��" },
{ L"z", L"zhei", L"��" },
{ L"z", L"zhong", L"�Ё��O���d��q���қw���Ӗ����x���ԽK�{�@���W�V��Π��R��۠犻b����ڣ�������[�p�V�N�~�������يt��r�{��Ơ�\�������g�W�\�A" },
{ L"z", L"zheng", L"��������ں���������l����������῟A�w�۱k֢�t��ꍔ���b�@�o���t�`�������P�~�P���@�Y�d��c���𕓐����֤֣���^���^Պ�k�����g�C" },
{ L"z", L"zhi", L"֮��ֻ֧ش֥֭�E�D֨��֪֫��֦֯�������e�oЁ�U�b֬����u�d���]���A���w�\֩�u�p�T�����~�uִֶ��ֱ��ֵ���p�ְ�F����ֳ��ֲ�õ����ꭕ�c�������Z�e��Ĉ��{ۗە�d܁�U�ֹ�n��ּ���ƒW�bַֽ�^�p�nƇ��q�d���׳U�}��ָ���]Ə���W�Jֺ���T���Չ~��ˌ�j�W�����X��ʶ��־�����Έ�ۤތ����������������ś��Ζ��wֿ��y�l���������ͪO��З�������̯b��ؠ���dИ�a�����v�����������͍��������������@�N�e�e�􌅓��D���ɜ��y��uҞ�I���F�����|�k�ܷW�������ÔT�\�M��\�v�@�H�����a�����`�S��ٗ�z�s�S���}�T�Y���v�W�e�U�f��" },
{ L"z", L"zhou", L"�����߁�����מ��������X�b�B�@���L���b�B�����Q�c�{�q�k��@�a�T���L�p����S��J���F���H���B�����V�������`��ף��Bݧ�q������������Ȓ�k�U�_�L�u�t���U���������Q�N�E���" },
{ L"z", L"zhua", L"ץ�Γ�tĐ���צ" },
{ L"z", L"zhu", L"��ۥ٪����������������p�N��Z�D�H����w���x���T�i����f�}ˠ�z�^�����E�����q�ø����A�����𷔸��Iɍ��a�Tώ���E���F���������W�ؼ�����e�����Cꕎ�������}�ҝ����G��������������ס���^�������|��פގ�̒}עף���Ě����d���m�v��d�����A�����q�����A�O�]ڟ���L�h��[�������v���B�Z�|�T��" },
{ L"z", L"zhen", L"������֡����䫂ؑ�������w�莞���IȜ���z���Z���ڋ��������R��驘E��✶G��黴U�����������m�gݟ�P�E�y����r���_�����Ǳp���А�r�G�]�FҘ�\���}�b�j�t�I�m�������l�ꇂE������޼�����`�L���c�g�����c���" },
{ L"z", L"zhuai", L"קת�J" },
{ L"z", L"zhui", L"��׷��׵׶�F�K�x�d׹����׺�ĮI�J㷮��i�����Y׸�PՅ�^�Y��٘�V" },
{ L"z", L"zhuang", L"ׯױ�y���P�f��׮�[��װ���b���P��׳��״��՟`�״�ײ�" },
{ L"z", L"zhuan", L"ר����ש�z�������t�U�A�x�s�u�K��m�Hת�N�|�D�������ܞ���E���R׬�Q��׫׭�e�N�xٍ�N���M��" },
{ L"z", L"zhun", L"��ބ�d���׻��Ձ�q׼�̓��ʾM�R��" },
{ L"z", L"zhuo", L"׾��׽پ�����z�×��̘����qߪ�@��������V�Ɗ�׿�������O��Q�Ê��Ć��ŗ����ٔ����k���M�����ۓ����Վ�}�r�W�ɝ�媔ޔ�֑�홷�h��ϗ���C�|�S�X�m�B" },
{ L"z", L"zou", L"�������Y��ǈ�������u�j�tՌ��۸�P�O�|�w���[������" },
{ L"z", L"zong", L"���Ȃ��W�ۈ����Ƞ�f�����ؗޖQ�O�ٝ��C�h�C���r�����x��������Rۙ�i�R�A�i�`�Q�܂~�̒֓K�i���t���~���t�G���Q���ݕf�S�`���ռF���k�v�q�_" },
{ L"z", L"zi", L"�ЌI��֨��ƆƝ���ˊ������ʫR��|�a绶�������ǏȌ�t�̜��ї���ꢆ��܌U�ŵ��������Y�D�l�z��∷T�C�w������ݖ�O�Jڃ���S�t�o�p�U�������d�bɛ�Ӆ��j梊��c�f�I�I�������������B���������`�h���T���SƓ����������{���u�h�n������" },
{ L"z", L"zu", L"�������{�a�a������X�����嗽���n�����������~���ކ��M�{����t" },
{ L"z", L"zun", L"������������������V�V�gߤ�J���" },
{ L"z", L"zui", L"�ׅ�Ï�����`�x�����쇒�r���S�E������B���f�U����ީ�T��@�d�i" },
{ L"z", L"zuan", L"���@���j���g荺e�F�����j�y�g׬߬" },
{ L"z", L"zuo", L"���ܷs���g�}�В����i◶������鿖����������F����Њ�������y�zd��" }
};



int getComPingyinForStr(const wstring & inStr, wstring& outFrist_py, wstring& outFull_py)
{
	// --- ��������
	outFrist_py.clear();
	outFull_py.clear();
	if (inStr.empty())
	{
		return -1;
	}


	// --- ��ȡÿ���ֵ����ж���
	size_t numOfWord = inStr.size();
	vector<vector<wstring>> fristPys;
	vector<vector<wstring>> fullPys;
	for (size_t i_word = 0; i_word < numOfWord; i_word++)
	{
		vector<wstring> fristPy;
		vector<wstring> fullPy;
		getAllPingyinForWord(inStr.substr(i_word,1), fristPy, fullPy);

		fristPys.push_back(fristPy);
		fullPys.push_back(fullPy);
	}


	// --- ��ʼ�������
	vector<int> nowIndexList;
	vector<int> maxIndexList;
	int sum_maxIndexList = 0;
	for (size_t i = 0; i < numOfWord; i++)
	{
		nowIndexList.push_back(0);
		maxIndexList.push_back(int(fullPys[i].size()) - 1);
		sum_maxIndexList += maxIndexList[i];
	}


	// --- ��һ����ϣ����в��õ�һ����
	bool mustCombination = sum_maxIndexList > 0 ? true : false;
	for (size_t i = 0; i < numOfWord; i++)
	{
		outFrist_py += fristPys[i][0];
		outFull_py += fullPys[i][0];
	}


	// --- ѭ������
	while (mustCombination)
	{
		// --- �������
		bool alreadyRunOnce = false;
		for (size_t i = 0; i < numOfWord; i++)
		{
			if (alreadyRunOnce)
			{
				break;
			}

			if (maxIndexList[i] != 0)
			{
				if (nowIndexList[i] < maxIndexList[i])
				{
					alreadyRunOnce = true;
					nowIndexList[i]++;
				}
				else if (nowIndexList[i] == maxIndexList[i])
				{
					nowIndexList[i] = 0;
				}
			}
		}

		// --- �������ַ�
		outFrist_py += L" ";
		outFull_py += L" ";
		for (size_t i = 0; i < numOfWord; i++)
		{
			outFrist_py += fristPys[i][nowIndexList[i]];
			outFull_py += fullPys[i][nowIndexList[i]];
		}

		// --- �˳�����
		bool canOut = true;
		for (size_t i = 0; i < numOfWord; i++)
		{
			if (nowIndexList[i] != maxIndexList[i])
			{
				canOut = false;
				break;
			}
		}
		if (canOut)
		{
			break;
		}
	}


	// --- ����
	return 0;
}

wstring getNamePingyin(const wstring& inStr, bool isLastName)
{
	wstring outStr;

	// ----- ����
	if (isLastName)
	{
		// --- �ڰټ����в���
		for (size_t i = 0; i < g_length_lastNameTable; i++)
		{
			if (inStr == lastNameTable[i].hanzi)
			{
				outStr = lastNameTable[i].pinyi;
				break;
			}
		}
	}

	// --- ֱ�Ӻ��ֿ����
	if (outStr.empty())
	{
		for (size_t i = 0; i < inStr.size(); i++)
		{
			outStr += getNoRepeatPingyinForWord(inStr.substr(i,1));
		}
	}

	return outStr;
}

void myNameSplit(const wstring & inFullName, wstring& outLastName, wstring& outFirstName)
{
	const int doubleLastNameLength = 90;
	static wstring doubleLastName[doubleLastNameLength] =
	{
		L"ŷ��" , L"̫ʷ" , L"��ľ" , L"�Ϲ�" , L"˾��" , L"����" , L"����" , L"�Ϲ�" , L"��ٹ" , L"����" ,
		L"�ĺ�" , L"���" , L"ξ��" , L"����" , L"����" , L"�̨" , L"�ʸ�" , L"����" , L"���" , L"��ұ" ,
		L"̫��" , L"����" , L"����" , L"Ľ��" , L"����" , L"����" , L"����" , L"����" , L"˾ͽ" , L"����" ,
		L"˾��" , L"����" , L"�ӳ�" , L"����" , L"˾��" , L"����" , L"����" , L"���" , L"����" , L"����" ,
		L"���" , L"����" , L"�׸�" , L"����" , L"�ذ�" , L"�й�" , L"��ԯ" , L"���" , L"�θ�" , L"����" ,
		L"����" , L"����" , L"����" , L"����" , L"΢��" , L"����" , L"����" , L"����" , L"����" , L"����" ,
		L"����" , L"����" , L"��ɽ" , L"����" , L"����" , L"����" , L"����" , L"����" , L"����" , L"����" ,
		L"����" , L"���" , L"����" , L"����" , L"����" , L"�ٳ�" , L"����" , L"��ɣ" , L"��ī" , L"����" ,
		L"��ʦ" , L"����" , L"����" , L"�麣" , L"����" , L"����" , L"����" , L"����" , L"����" , L"����"
	};

	// --- ����зǺ����ַ���ֱ�ӷ���
	for (size_t i = 0; i < inFullName.size(); i++)
	{
		if (!isHanziChar(inFullName[i]))
		{
			outLastName = L"";
			outFirstName = inFullName;
			return;
		}
	}


	//
	outLastName = L"";
	outFirstName = L"";

	if (inFullName.empty())
	{
	}
	else if (inFullName.size() == 1)
	{
		outFirstName = inFullName;
	}
	else if (inFullName.size() == 2)
	{
		outLastName = inFullName[0];
		outFirstName = inFullName[1];
	}
	else
	{
		wstring guessLastName = inFullName.substr(0,2);
		for (int i = 0; i < doubleLastNameLength; i++)
		{
			if (guessLastName == doubleLastName[i])
			{
				outLastName = doubleLastName[i];
				outFirstName = inFullName.substr(2);
				break;
			}
		}

		if (outLastName.empty())
		{
			if (inFullName.size() == 4)
			{
				outLastName = inFullName.substr(0,2);
				outFirstName = inFullName.substr(2);
			}
			else
			{
				outLastName = inFullName[0];
				outFirstName = inFullName.substr(1);
			}			
		}
	}

}

int getAllPingyinForWord(const wstring& inWord, vector<wstring>& outFrist_py, vector<wstring>& outFull_py)
{
	// ֻ������һ���ַ�
	if (inWord.size() > 1)
	{
		return -1;
	}

	//
	outFrist_py.clear();
	outFull_py.clear();

	wchar_t wch = inWord[0];
	if (isHanziChar(wch))
	{
		for (int index_table = 0; index_table < g_length_hanziTables; index_table++)
		{
			if (hanziTables[index_table].hanzis.find(wch) != -1)
			{
				outFrist_py.push_back(hanziTables[index_table].first_py);
				outFull_py.push_back(hanziTables[index_table].full_py);
			}
		}
	}

	if (outFrist_py.empty())
	{
		outFrist_py.push_back(inWord);
	}
	if (outFull_py.empty())
	{
		outFull_py.push_back(inWord);
	}

	return 0;
}

wstring getNoRepeatPingyinForWord(const wstring& inWord)
{
	wstring outPingyin;

	// ֻ������һ���ַ�
	if (inWord.size() > 1)
	{
		return inWord;
	}

	// ----- ���ڶ����������ѯ
	for (int i = 0; i < g_length_multiToneWordTable; i++)
	{
		if (inWord == multiToneWordTable[i].hanzi)
		{
			outPingyin = multiToneWordTable[i].pinyi;
			break;
		}
	}

	// ----- ������ѯ
	if (!outPingyin.empty())
	{
		return outPingyin;
	}

	// ----- ��ȫ�ֿ����
	wchar_t wch = inWord[0];
	if (isHanziChar(wch))
	{
		for (int index_table = 0; index_table < g_length_hanziTables; index_table++)
		{
			if (hanziTables[index_table].hanzis.find(wch) != -1)
			{
				outPingyin = hanziTables[index_table].full_py;
				break;
			}
		}
	}

	//
	if (outPingyin.empty())
	{
		outPingyin = inWord;
	}

	// ----- ���ؽ��
	return outPingyin;
}

bool isHanziChar(wchar_t wch) {
	// ��vs2019 ��ʹ�� qstring ʱ
	// return (wch >= 0x4E00 && wch <= 0x9FA5) ? true : false; 
	
	// ��vs2019 ��ʹ�� wstring ʱ
	//return (wch >= 12570 && wch <= 64041) ? true : false;

	// ����һ�����з��� => ���ֲ������κ���©������Ӧ��������뷽ʽ���ɹ��˵�����������÷Ǻ����ַ���
	// ������ȡ׼ȷ�����䣬ʹ��testHanziRang()������
	return wch > 127 ? true : false;
}

void testHanziRang() {
	wstring str;
	for (size_t i = 0; i < g_length_hanziTables; i++)
	{
		str += hanziTables[i].hanzis;
	}

	int maxVal = 0;
	int minVal = 1000000000;
	wchar_t maxStr = L' ';
	wchar_t minStr = L' ';
	for (size_t i = 0; i < str.size(); i++)
	{
		int uncd = str[i];
		if (uncd > maxVal)
		{
			maxVal = uncd;
			maxStr = str[i];
		}
		if (uncd < minVal)
		{
			minVal = uncd;
			minStr = str[i];
		}
	}

	printf("\n���ֱ�����ԣ�\n");
	printf("��С����ֵ��%d , ������ֵ:%d , �ܺ�������(δȥ��)��%zd \n", minVal, maxVal,str.size());
	
	printf("��С����ֵ�ĺ��֣�%wc , ������ֵ�ĺ���: %wc \n", minStr, maxStr);
	
	// ��ע�⡿
	// �����ʹprintf���Դ�ӡwchar_t  
	// setlocale(LC_ALL, "");  // �ڳ�ʼ��ʱ�������
	// #include <iostream>     // ��Ӧ��ͷ�ļ�
}

