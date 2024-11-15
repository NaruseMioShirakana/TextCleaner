#include <string>
#include <thread>
#include <vector>
#include <unordered_map>
#include "openjtalk/open_jtalk-1.11/src/mecab/src/mecab.h"
#include "openjtalk/open_jtalk-1.11/src/njd/njd.h"
#include "openjtalk/open_jtalk-1.11/src/jpcommon/jpcommon.h"
#include "framework.h"
#include "openjtalk\\open_jtalk-1.11\\src\\text2mecab\\text2mecab.h"
#include "openjtalk\\open_jtalk-1.11\\src\\mecab2njd\\mecab2njd.h"
#include "openjtalk\\open_jtalk-1.11\\src\\njd_set_digit\\njd_set_digit.h"
#include "openjtalk\\open_jtalk-1.11\\src\\njd_set_pronunciation\\njd_set_pronunciation.h"
#include "openjtalk\\open_jtalk-1.11\\src\\njd_set_accent_phrase\\njd_set_accent_phrase.h"
#include "openjtalk\\open_jtalk-1.11\\src\\njd_set_accent_type\\njd_set_accent_type.h"
#include "openjtalk\\open_jtalk-1.11\\src\\njd_set_unvoiced_vowel\\njd_set_unvoiced_vowel.h"
#include "openjtalk\\open_jtalk-1.11\\src\\njd_set_long_vowel\\njd_set_long_vowel.h"
#include "openjtalk\\open_jtalk-1.11\\src\\njd2jpcommon\\njd2jpcommon.h"
#include <codecvt>
#include <regex>
#include <atomic>
#include "MJson/MJson.h"
#pragma comment(lib, "openjtalk\\openjtalk.lib")
#pragma comment(lib, "openjtalk\\hts_engine_API.lib")
#pragma comment(lib, "openjtalk\\hts_engine.lib")

std::wstring ChineseNumber[] = { L"零",L"一",L"二",L"三",L"四",L"五",L"六",L"七",L"八",L"九",L"十" };
std::wstring ChineseNumberDigit[] = { L"",L"十",L"百",L"千",L"万",L"十万",L"百万",L"千万",L"亿" };
std::vector<std::pair<std::wstring, std::wstring>> _CURRENCY_MAP{ {L"\\$", L"ドル"}, { L"¥", L"円" }, { L"£", L"ポンド" }, { L"€", L"ユーロ" } };
std::wregex NumberRegex(L"\\d+(?:\\.?\\d+)?");
std::wregex SignRegex(L"[!@#$%^&*()_+\\-=`~,./;'\\[\\]<>?:\"{}|\\\\。？！，、；：“”‘’『』「」（）〔〕【】─…·—～《》〈〉　]+");
std::wregex SignRegexSingle(L"[!@#$%^&*()_+\\-=`~,./;'\\[\\]<>?:\"{}|\\\\。？！，、；：“”‘’『』「」（）〔〕【】─…·—～《》〈〉　]");

#define _Impl_To_Int(Value) (_wtoi((Value).c_str()))

static const std::vector<std::pair<std::wregex, std::wstring>> _DefaultJapaneseReplaceRegexDict{
    {std::wregex(LR"(\r)"), L""}, {std::wregex(LR"(\n)"), L""}, {std::wregex(L" "), L"　"},
    {std::wregex(L"!"), L"！"}, {std::wregex(L"\""), L"”"}, {std::wregex(L"#"), L"＃"},
    {std::wregex(L"\\$"), L"＄"}, {std::wregex(L"%"), L"％"}, {std::wregex(L"&"), L"＆"},
    {std::wregex(L"'"), L"’"}, {std::wregex(L"\\("), L"（"}, {std::wregex(L"\\)"), L"）"},
    {std::wregex(L"\\*"), L"＊"}, {std::wregex(L"\\+"), L"＋"}, {std::wregex(L","), L"，"},
    {std::wregex(L"\\-"), L"−"}, {std::wregex(L"\\."), L"．"}, {std::wregex(L"\\/"), L"／"},
    {std::wregex(L"0"), L"０"}, {std::wregex(L"1"), L"１"}, {std::wregex(L"2"), L"２"},
    {std::wregex(L"3"), L"３"}, {std::wregex(L"4"), L"４"}, {std::wregex(L"5"), L"５"},
    {std::wregex(L"6"), L"６"}, {std::wregex(L"7"), L"７"}, {std::wregex(L"8"), L"８"},
    {std::wregex(L"9"), L"９"}, {std::wregex(L":"), L"："}, {std::wregex(L";"), L"；"},
    {std::wregex(L"<"), L"＜"}, {std::wregex(L"="), L"＝"}, {std::wregex(L">"), L"＞"},
    {std::wregex(L"\\?"), L"？"}, {std::wregex(L"@"), L"＠"}, {std::wregex(L"A"), L"Ａ"},
    {std::wregex(L"B"), L"Ｂ"}, {std::wregex(L"C"), L"Ｃ"}, {std::wregex(L"D"), L"Ｄ"},
    {std::wregex(L"E"), L"Ｅ"}, {std::wregex(L"F"), L"Ｆ"}, {std::wregex(L"G"), L"Ｇ"},
    {std::wregex(L"H"), L"Ｈ"}, {std::wregex(L"I"), L"Ｉ"}, {std::wregex(L"J"), L"Ｊ"},
    {std::wregex(L"K"), L"Ｋ"}, {std::wregex(L"L"), L"Ｌ"}, {std::wregex(L"M"), L"Ｍ"},
    {std::wregex(L"N"), L"Ｎ"}, {std::wregex(L"O"), L"Ｏ"}, {std::wregex(L"P"), L"Ｐ"},
    {std::wregex(L"Q"), L"Ｑ"}, {std::wregex(L"R"), L"Ｒ"}, {std::wregex(L"S"), L"Ｓ"},
    {std::wregex(L"T"), L"Ｔ"}, {std::wregex(L"U"), L"Ｕ"}, {std::wregex(L"V"), L"Ｖ"},
    {std::wregex(L"W"), L"Ｗ"}, {std::wregex(L"X"), L"Ｘ"}, {std::wregex(L"Y"), L"Ｙ"},
    {std::wregex(L"Z"), L"Ｚ"}, {std::wregex(L"\\["), L"［"}, {std::wregex(L"\\\\"), L"￥"},
    {std::wregex(L"\\]"), L"］"}, {std::wregex(L"\\^"), L"＾"}, {std::wregex(L"_"), L"＿"},
    {std::wregex(L"`"), L"‘"}, {std::wregex(L"a"), L"ａ"}, {std::wregex(L"b"), L"ｂ"},
    {std::wregex(L"c"), L"ｃ"}, {std::wregex(L"d"), L"ｄ"}, {std::wregex(L"e"), L"ｅ"},
    {std::wregex(L"f"), L"ｆ"}, {std::wregex(L"g"), L"ｇ"}, {std::wregex(L"h"), L"ｈ"},
    {std::wregex(L"i"), L"ｉ"}, {std::wregex(L"j"), L"ｊ"}, {std::wregex(L"k"), L"ｋ"},
    {std::wregex(L"l"), L"ｌ"}, {std::wregex(L"m"), L"ｍ"}, {std::wregex(L"n"), L"ｎ"},
    {std::wregex(L"o"), L"ｏ"}, {std::wregex(L"p"), L"ｐ"}, {std::wregex(L"q"), L"ｑ"},
    {std::wregex(L"r"), L"ｒ"}, {std::wregex(L"s"), L"ｓ"}, {std::wregex(L"t"), L"ｔ"},
    {std::wregex(L"u"), L"ｕ"}, {std::wregex(L"v"), L"ｖ"}, {std::wregex(L"w"), L"ｗ"},
    {std::wregex(L"x"), L"ｘ"}, {std::wregex(L"y"), L"ｙ"}, {std::wregex(L"z"), L"ｚ"},
    {std::wregex(L"\\{"), L"｛"}, {std::wregex(L"\\|"), L"｜"}, {std::wregex(L"\\}"), L"｝"},
    {std::wregex(L"~"), L"〜"}, {std::wregex(L"�"), L"？"}
};
static const std::wregex _PhonemeInfoRegex{ LR"((.*?)\^(.*?)\-(.*?)\+(.*?)=(.*?)/A:)" };
static const std::wregex _AInfoGroupRegex{ LR"(/A:(.*?)\+(.*?)\+(.*?)/B:)" };
static const std::wregex _BInfoGroupRegex{ LR"(/B:(.*?)\-(.*?)_(.*?)/C:)" };
static const std::wregex _CInfoGroupRegex{ LR"(/C:(.*?)_(.*?)\+(.*?)/D:)" };
static const std::wregex _DInfoGroupRegex{ LR"(/D:(.*?)\+(.*?)_(.*?)/E:)" };
static const std::wregex _EInfoGroupRegex{ LR"(/E:(.*?)_(.*?)\!(.*?)_(.*?)\-(.*?)/F:)" };
static const std::wregex _FInfoGroupRegex{ LR"(/F:(.*?)_(.*?)#(.*?)_(.*?)@(.*?)_(.*?)\|(.*?)_(.*?)/G:)" };
static const std::wregex _GInfoGroupRegex{ LR"(/G:(.*?)_(.*?)%(.*?)_(.*?)_(.*?)/H:)" };
static const std::wregex _HInfoGroupRegex{ LR"(/H:(.*?)_(.*?)/I:)" };
static const std::wregex _IInfoGroupRegex{ LR"(/I:(.*?)\-(.*?)@(.*?)\+(.*?)&(.*?)\-(.*?)\|(.*?)\+(.*?)/J:)" };
static const std::wregex _JInfoGroupRegex{ LR"(/J:(.*?)_(.*?)/K:)" };
static const std::wregex _KInfoGroupRegex{ LR"(/K:(.*?)\+(.*?)\-(.*?))" };

struct PhonemeAndTone
{
    wchar_t Phoneme[8];
    int64_t Tone;
};

std::vector<std::wstring> SplitString(
    const std::wstring& _Input,
    const std::wregex& _Regex,
    const std::initializer_list<int>& _Sub = { -1 }
)
{
    std::vector<std::wstring> RtnVec;
    std::wsregex_token_iterator Iter(_Input.begin(), _Input.end(), _Regex, _Sub);
    std::wsregex_token_iterator End;
    for (; Iter != End; ++Iter)
        RtnVec.emplace_back(Iter->str());
    return RtnVec;
}

std::wstring NumberToChinese(double Number)
{
    std::wstring StrRtn;
    std::wstring InputStr = std::to_wstring(Number);
    const size_t PIndex = InputStr.find(L'.');
    std::wstring IntegerStr, FractionStr;
    if (PIndex != std::wstring::npos)
    {
        IntegerStr = InputStr.substr(0, PIndex);
        FractionStr = InputStr.substr(PIndex + 1);
        while (!FractionStr.empty() && FractionStr.back() == L'0')
            FractionStr.pop_back();
    }
    else
        IntegerStr = std::move(InputStr);

    if (IntegerStr != L"0")
    {
        size_t MaxIntegerStrLength = IntegerStr.length();
        for (; MaxIntegerStrLength > 0; --MaxIntegerStrLength)
            if (IntegerStr[MaxIntegerStrLength - 1] != L'0')
                break;
        if (MaxIntegerStrLength < 1)
            MaxIntegerStrLength = 1;

        const auto DigitNum = IntegerStr.length();
        for (size_t i = 0; i < MaxIntegerStrLength; i++)
        {
            const auto NumberIndex = IntegerStr[i] - L'0';
            const auto DigitIndex = DigitNum - i - 1;
            if (0 == NumberIndex)
            {
                if ((i > 0 && L'0' == IntegerStr[i - 1]) || i == IntegerStr.length() - 1)
                    continue;
                if (DigitIndex >= 4 && 0 == DigitIndex % 4)
                    StrRtn += ChineseNumberDigit[DigitIndex];
                else
                    StrRtn += ChineseNumber[NumberIndex];
            }
            else
            {
                StrRtn += ChineseNumber[NumberIndex];
                if (IntegerStr.length() == 2 && IntegerStr[0] == '1' && i == 0)
                    StrRtn.erase(0);
                if (0 == DigitIndex % 4)
                    StrRtn += ChineseNumberDigit[DigitIndex];
                else
                    StrRtn += ChineseNumberDigit[DigitIndex % 4];
            }
        }
    }
    else
        StrRtn += L"零";

    if (!FractionStr.empty())
        StrRtn += L"点";
    for (const auto FractionI : FractionStr)
    {
        const auto NumberIndex = FractionI - L'0';
        StrRtn += ChineseNumber[NumberIndex];
    }
    return StrRtn;
}

std::wstring ChineseNormalize(const std::wstring& _Input)
{
    std::wstring RtnStr;
    const auto StrVec = SplitString(_Input, NumberRegex, { -1, 0 });
    for (const auto& Str : StrVec)
    {
        if (std::regex_match(Str, NumberRegex))
            RtnStr += NumberToChinese(_wtof(Str.c_str()));
        else
            RtnStr += Str;
    }
    return RtnStr;
}

std::string to_byte_string(const std::wstring& input)
{
#ifdef _WIN32
    std::vector<char> ByteString(input.length() * 6);
    WideCharToMultiByte(
        CP_UTF8,
        0,
        input.c_str(),
        int(input.length()),
        ByteString.data(),
        int(ByteString.size()),
        nullptr,
        nullptr
    );
    return ByteString.data();
#else
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(input);
#endif
}

std::wstring to_wide_string(const std::string& input)
{
#ifdef _WIN32
    std::vector<wchar_t> WideString(input.length() * 2);
    MultiByteToWideChar(
        CP_UTF8,
        0,
        input.c_str(),
        int(input.length()),
        WideString.data(),
        int(WideString.size())
    );
    return WideString.data();
#else
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.from_bytes(input);
#endif
}

class OpenJTalk
{
public:
    friend class Instance;
    friend class std::shared_ptr<OpenJTalk>;
    struct _MyPhoneme { wchar_t P_2[8]; wchar_t P_1[8]; wchar_t P0[8]; wchar_t P1[8]; wchar_t P2[8]; };
    struct _MyA { int8_t A1; uint8_t A2; uint8_t A3; };
    struct _MyB { wchar_t B1[8]; wchar_t B2[8]; wchar_t B3[8]; };
    struct _MyC { wchar_t C1[8]; wchar_t C2[8]; wchar_t C3[8]; };
    struct _MyD { wchar_t D1[8]; wchar_t D2[8]; wchar_t D3[8]; };
    struct _MyE { uint8_t E1; uint8_t E2; bool E3; wchar_t E4[8]; bool E5; };
    struct _MyF { uint8_t F1; uint8_t F2; bool F3; wchar_t F4[8]; uint8_t F5; uint8_t F6; uint8_t F7; uint8_t F8; };
    struct _MyG { uint8_t G1; uint8_t G2; bool G3; wchar_t G4[8]; bool G5; };
    struct _MyH { uint8_t H1; uint8_t H2; };
    struct _MyI { uint8_t I1; uint8_t I2; uint8_t I3; uint8_t I4; uint8_t I5; uint8_t I6; uint8_t I7; uint8_t I8; };
    struct _MyJ { uint8_t J1; uint8_t J2; };
    struct _MyK { uint8_t K1; uint8_t K2; uint8_t K3; };
    struct FullContext
    {
        _MyPhoneme Phoneme;
        _MyA A; _MyB B; _MyC C; _MyD D; _MyE E;
        _MyF F; _MyG G; _MyH H; _MyI I; _MyJ J;
        _MyK K;
    };
    OpenJTalk(const char* folder)
    {
        mecab = new Mecab;
        njd = new NJD;
        jpcommon = new JPCommon;
        JPCommon_initialize(jpcommon);
        Mecab_initialize(mecab);
        NJD_initialize(njd);
        Mecab_load(mecab, folder);
    }
    ~OpenJTalk() {
        Refresh();
        if (mecab)
            Mecab_clear(mecab);
        if (njd)
            NJD_clear(njd);
        if (jpcommon)
            JPCommon_clear(jpcommon);
        delete mecab;
        delete njd;
        delete jpcommon;
        jpcommon = nullptr;
        mecab = nullptr;
        njd = nullptr;
    }
    void Refresh() const
    {
        if (njd)
            NJD_refresh(njd);
        if (mecab)
            Mecab_refresh(mecab);
        if (jpcommon)
            JPCommon_refresh(jpcommon);
    }
    static FullContext Extract(const std::wstring& _Context)
    {
        FullContext _TmpContext{};
        std::wsmatch Matched;
        if (std::regex_search(_Context, Matched, _PhonemeInfoRegex))
        {
            wcscpy_s(_TmpContext.Phoneme.P_2, Matched[1].str().c_str());
            wcscpy_s(_TmpContext.Phoneme.P_1, Matched[2].str().c_str());
            wcscpy_s(_TmpContext.Phoneme.P0, Matched[3].str().c_str());
            wcscpy_s(_TmpContext.Phoneme.P1, Matched[4].str().c_str());
            wcscpy_s(_TmpContext.Phoneme.P2, Matched[5].str().c_str());
        }
        if (std::regex_search(_Context, Matched, _AInfoGroupRegex))
        {
            _TmpContext.A.A1 = int8_t(_Impl_To_Int(Matched[1].str()));
            _TmpContext.A.A2 = uint8_t(_Impl_To_Int(Matched[2].str()));
            _TmpContext.A.A3 = uint8_t(_Impl_To_Int(Matched[3].str()));
        }
        if (std::regex_search(_Context, Matched, _BInfoGroupRegex))
        {
            wcscpy_s(_TmpContext.B.B1, Matched[1].str().c_str());
            wcscpy_s(_TmpContext.B.B2, Matched[2].str().c_str());
            wcscpy_s(_TmpContext.B.B3, Matched[3].str().c_str());
        }
        if (std::regex_search(_Context, Matched, _CInfoGroupRegex))
        {
            wcscpy_s(_TmpContext.C.C1, Matched[1].str().c_str());
            wcscpy_s(_TmpContext.C.C2, Matched[2].str().c_str());
            wcscpy_s(_TmpContext.C.C3, Matched[3].str().c_str());
        }
        if (std::regex_search(_Context, Matched, _DInfoGroupRegex))
        {
            wcscpy_s(_TmpContext.D.D1, Matched[1].str().c_str());
            wcscpy_s(_TmpContext.D.D2, Matched[2].str().c_str());
            wcscpy_s(_TmpContext.D.D3, Matched[3].str().c_str());
        }
        if (std::regex_search(_Context, Matched, _EInfoGroupRegex))
        {
            _TmpContext.E.E1 = uint8_t(_Impl_To_Int(Matched[1].str()));
            _TmpContext.E.E2 = uint8_t(_Impl_To_Int(Matched[2].str()));
            _TmpContext.E.E3 = _Impl_To_Int(Matched[3].str());
            wcscpy_s(_TmpContext.E.E4, Matched[4].str().c_str());
            _TmpContext.E.E5 = _Impl_To_Int(Matched[5].str());
        }
        if (std::regex_search(_Context, Matched, _FInfoGroupRegex))
        {
            _TmpContext.F.F1 = uint8_t(_Impl_To_Int(Matched[1].str()));
            _TmpContext.F.F2 = uint8_t(_Impl_To_Int(Matched[2].str()));
            _TmpContext.F.F3 = _Impl_To_Int(Matched[3].str());
            wcscpy_s(_TmpContext.F.F4, Matched[4].str().c_str());
            _TmpContext.F.F5 = uint8_t(_Impl_To_Int(Matched[5].str()));
            _TmpContext.F.F6 = uint8_t(_Impl_To_Int(Matched[6].str()));
            _TmpContext.F.F7 = uint8_t(_Impl_To_Int(Matched[7].str()));
            _TmpContext.F.F8 = uint8_t(_Impl_To_Int(Matched[8].str()));
        }
        if (std::regex_search(_Context, Matched, _GInfoGroupRegex))
        {
            _TmpContext.G.G1 = uint8_t(_Impl_To_Int(Matched[1].str()));
            _TmpContext.G.G2 = uint8_t(_Impl_To_Int(Matched[2].str()));
            _TmpContext.G.G3 = _Impl_To_Int(Matched[3].str());
            wcscpy_s(_TmpContext.G.G4, Matched[4].str().c_str());
            _TmpContext.G.G5 = _Impl_To_Int(Matched[5].str());
        }
        if (std::regex_search(_Context, Matched, _HInfoGroupRegex))
        {
            _TmpContext.H.H1 = uint8_t(_Impl_To_Int(Matched[1].str()));
            _TmpContext.H.H2 = uint8_t(_Impl_To_Int(Matched[2].str()));
        }
        if (std::regex_search(_Context, Matched, _IInfoGroupRegex))
        {
            _TmpContext.I.I1 = uint8_t(_Impl_To_Int(Matched[1].str()));
            _TmpContext.I.I2 = uint8_t(_Impl_To_Int(Matched[2].str()));
            _TmpContext.I.I3 = uint8_t(_Impl_To_Int(Matched[3].str()));
            _TmpContext.I.I4 = uint8_t(_Impl_To_Int(Matched[4].str()));
            _TmpContext.I.I5 = uint8_t(_Impl_To_Int(Matched[5].str()));
            _TmpContext.I.I6 = uint8_t(_Impl_To_Int(Matched[6].str()));
            _TmpContext.I.I7 = uint8_t(_Impl_To_Int(Matched[7].str()));
            _TmpContext.I.I8 = uint8_t(_Impl_To_Int(Matched[8].str()));
        }
        if (std::regex_search(_Context, Matched, _JInfoGroupRegex))
        {
            _TmpContext.J.J1 = uint8_t(_Impl_To_Int(Matched[1].str()));
            _TmpContext.J.J2 = uint8_t(_Impl_To_Int(Matched[2].str()));
        }
        if (std::regex_search(_Context, Matched, _KInfoGroupRegex))
        {
            _TmpContext.K.K1 = uint8_t(_Impl_To_Int(Matched[1].str()));
            _TmpContext.K.K2 = uint8_t(_Impl_To_Int(Matched[2].str()));
            _TmpContext.K.K3 = uint8_t(_Impl_To_Int(Matched[3].str()));
        }
        return _TmpContext;
    }
    void ExtractFullContext(const wchar_t* _InputText)
    {
        _MyData.clear();
        const auto Text = to_byte_string(_InputText);
        char Buffer[1024 * 8];
        text2mecab(Buffer, Text.c_str());
        Mecab_analysis(mecab, Buffer);
        mecab2njd(njd, Mecab_get_feature(mecab), Mecab_get_size(mecab));
        njd_set_pronunciation(njd);
        njd_set_digit(njd);
        njd_set_accent_phrase(njd);
        njd_set_accent_type(njd);
        njd_set_unvoiced_vowel(njd);
        njd_set_long_vowel(njd);
        njd2jpcommon(jpcommon, njd);
        JPCommon_make_label(jpcommon);
        const int label_size = JPCommon_get_label_size(jpcommon);
        char** label_feature = JPCommon_get_label_feature(jpcommon);
        _MyData.reserve(label_size);
        for (int i = 0; i < label_size; i++)
            _MyData.emplace_back(Extract(to_wide_string(label_feature[i])));
        Refresh();
    }
    void operator()(std::wstring InputSeq, std::vector<PhonemeAndTone>& OutRes)
    {
        for (const auto& it : _DefaultJapaneseReplaceRegexDict)
            InputSeq = std::regex_replace(InputSeq, it.first, it.second);
        ExtractFullContext(InputSeq.c_str());
        for (size_t Index = 0; Index < _MyData.size(); ++Index)
        {
            const auto& This = _MyData[Index];
            OutRes.emplace_back();
            wcscpy_s(OutRes.back().Phoneme, This.Phoneme.P0);
            if (wcscmp(This.Phoneme.P0, L"sil") == 0 || wcscmp(This.Phoneme.P0, L"pau") == 0)
                continue;

            const auto& Next = _MyData[Index + 1];
            int Next2;
            if (wcscmp(Next.Phoneme.P0, L"sil") == 0 || wcscmp(Next.Phoneme.P0, L"pau") == 0)
                Next2 = -1;
            else
                Next2 = Next.A.A2;
            if (This.A.A3 == 1 && Next2 == 1)
            {
                OutRes.emplace_back();
                OutRes.back().Phoneme[0] = L' ';
                OutRes.back().Tone = 0;
            }
            else if (This.A.A1 == 0 && Next2 == This.A.A2 + 1 && This.A.A2 != This.F.F1)
                OutRes.back().Tone = -1;
            else if (This.A.A3 == 1 && Next2 == 1)
                OutRes.back().Tone = 1;
        }
    }
protected:
    std::vector<FullContext> _MyData;
private:
    OpenJTalk(const OpenJTalk&) = delete;
    OpenJTalk(OpenJTalk&& right) noexcept = delete;
    OpenJTalk& operator=(const OpenJTalk&) = delete;
    OpenJTalk& operator=(OpenJTalk&& right) noexcept = delete;

    Mecab* mecab = nullptr;
    NJD* njd = nullptr;
    JPCommon* jpcommon = nullptr;
};

class ChineseDict
{
public:
    friend class Instance;
    friend class std::shared_ptr<ChineseDict>;
    ChineseDict() = delete;
    void Search(std::wstring InputSeq, std::vector<PhonemeAndTone>& OutRes) {
        InputSeq = ChineseNormalize(InputSeq);
        if (std::regex_match(InputSeq, SignRegex))
        {
            std::wsregex_token_iterator Iter(InputSeq.begin(), InputSeq.end(), SignRegexSingle, 0);
            std::wsregex_token_iterator End;
            for (; Iter != End; ++Iter)
            {
                OutRes.emplace_back();
                wcscpy_s(OutRes.back().Phoneme, Iter->str().c_str());
                OutRes.back().Tone = 0;
            }
            return;
        }
        while (!InputSeq.empty())
        {
            for (size_t SearchLength = min(MaxSize, InputSeq.length()); SearchLength > 0; --SearchLength)
            {
                const auto SearchResult = _Dict.find(InputSeq.substr(0, SearchLength));
                if (SearchResult != _Dict.end() && SearchResult->second.Phone.size() == SearchResult->second.Tone.size())
                {
                    for (size_t i = 0; i < SearchResult->second.Phone.size(); ++i)
                    {
                        OutRes.emplace_back();
                        wcscpy_s(OutRes.back().Phoneme, SearchResult->second.Phone[i].c_str());
                        OutRes.back().Tone = static_cast<int64_t>((uint8_t)SearchResult->second.Tone[i]);
                    }
                    InputSeq = InputSeq.substr(SearchLength);
                    break;
                }
                if (SearchLength == 1)
                {
                    OutRes.emplace_back();
                    wcscpy_s(OutRes.back().Phoneme, L"[UNK]");
                    InputSeq = InputSeq.substr(1);
                }
            }
        }
    }
    ChineseDict(const char* path)
    {
        _Dict.clear();
        const MJson _DictJson(path);
        const auto Arr = _DictJson.GetMemberArray();
        for (const auto& it : Arr)
        {
            DictData _TmpData;
            const auto NameStr = to_wide_string(it.first);
            if (NameStr.size() > MaxSize)
                MaxSize = NameStr.size();
            for (const auto& phone : it.second["phoneme"].GetArray())
                _TmpData.Phone.emplace_back(to_wide_string(phone.GetString()));
            for (const auto& tone : it.second["tone"].GetArray())
                _TmpData.Tone.emplace_back(int8_t(tone.GetInt64()));
            _Dict[NameStr] = std::move(_TmpData);
        }
    }
private:
    struct DictData
    {
        std::vector<std::wstring> Phone;
        std::vector<int8_t> Tone;
    };
    size_t MaxSize = 0;
    std::unordered_map<std::wstring, DictData> _Dict;
};

void getRealSokuon(std::wstring& tmpStr)
{
    tmpStr = std::regex_replace(tmpStr, std::wregex(L"Q([↑↓]*[kg])"), L"k#$1");
    tmpStr = std::regex_replace(tmpStr, std::wregex(L"Q([↑↓]*[tdjʧ])"), L"t#$1");
    tmpStr = std::regex_replace(tmpStr, std::wregex(L"Q([↑↓]*[sʃ])"), L"s$1");
    tmpStr = std::regex_replace(tmpStr, std::wregex(L"Q([↑↓]*[pb])"), L"p#$1");
}

void getRealHatsuon(std::wstring& tmpStr)
{
    tmpStr = std::regex_replace(tmpStr, std::wregex(L"N([↑↓]*[pbm])"), L"m$1");
    tmpStr = std::regex_replace(tmpStr, std::wregex(L"N([↑↓]*[ʧʥj])"), L"n^$1");
    tmpStr = std::regex_replace(tmpStr, std::wregex(L"N([↑↓]*[tdn])"), L"n$1");
    tmpStr = std::regex_replace(tmpStr, std::wregex(L"N([↑↓]*[kg])"), L"ŋ$1");
}

void getIpaStr1(std::wstring& tmpStr)
{
    tmpStr = std::regex_replace(tmpStr, std::wregex(L"ts"), L"ʦ");
    tmpStr = std::regex_replace(tmpStr, std::wregex(L"u"), L"ɯ");
    tmpStr = std::regex_replace(tmpStr, std::wregex(L"j"), L"ʥ");
    tmpStr = std::regex_replace(tmpStr, std::wregex(L"y"), L"j");
    tmpStr = std::regex_replace(tmpStr, std::wregex(L"ni"), L"n^i");
    tmpStr = std::regex_replace(tmpStr, std::wregex(L"nj"), L"n^");
    tmpStr = std::regex_replace(tmpStr, std::wregex(L"hi"), L"çi");
    tmpStr = std::regex_replace(tmpStr, std::wregex(L"hj"), L"ç");
    tmpStr = std::regex_replace(tmpStr, std::wregex(L"f"), L"ɸ");
    tmpStr = std::regex_replace(tmpStr, std::wregex(L"I"), L"i*");
    tmpStr = std::regex_replace(tmpStr, std::wregex(L"U"), L"ɯ*");
    tmpStr = std::regex_replace(tmpStr, std::wregex(L"r"), L"ɾ");
}

void getIpaStr2(std::wstring& tmpStr)
{
    tmpStr = std::regex_replace(tmpStr, std::wregex(L"u"), L"ɯ");
    tmpStr = std::regex_replace(tmpStr, std::wregex(L"ʧ"), L"tʃ");
    tmpStr = std::regex_replace(tmpStr, std::wregex(L"j"), L"ʥ");
    tmpStr = std::regex_replace(tmpStr, std::wregex(L"y"), L"j");
    tmpStr = std::regex_replace(tmpStr, std::wregex(L"ni"), L"n^i");
    tmpStr = std::regex_replace(tmpStr, std::wregex(L"nj"), L"n^");
    tmpStr = std::regex_replace(tmpStr, std::wregex(L"hi"), L"çi");
    tmpStr = std::regex_replace(tmpStr, std::wregex(L"hj"), L"ç");
    tmpStr = std::regex_replace(tmpStr, std::wregex(L"f"), L"ɸ");
    tmpStr = std::regex_replace(tmpStr, std::wregex(L"I"), L"i*");
    tmpStr = std::regex_replace(tmpStr, std::wregex(L"U"), L"ɯ*");
    tmpStr = std::regex_replace(tmpStr, std::wregex(L"r"), L"ɾ");
}

void getIpaStr3(std::wstring& tmpStr)
{
    tmpStr = std::regex_replace(tmpStr, std::wregex(L"n^"), L"ȵ");
    tmpStr = std::regex_replace(tmpStr, std::wregex(L"ʃ"), L"ɕ");
    tmpStr = std::regex_replace(tmpStr, std::wregex(L"#"), L"̚");
    //tmpStr = std::regex_replace(tmpStr, std::wregex(L"((?:^|\\s)(?:ts|tɕ|[kpt])"), L"$1ʰ");
}

void replaceSymbol(std::wstring& tmpStr)
{
    tmpStr = std::regex_replace(tmpStr, std::wregex(L"。"), L".");
    tmpStr = std::regex_replace(tmpStr, std::wregex(L"、"), L",");
    tmpStr = std::regex_replace(tmpStr, std::wregex(L"？"), L"?");
    tmpStr = std::regex_replace(tmpStr, std::wregex(L"！"), L"!");
}

class Instance
{
public:
    Instance() = delete;
    Instance(const wchar_t* _Path)
    {
        auto OjtPath = _Path + std::wstring(L"/Japanese");
        auto ChinsesDictPath = _Path + std::wstring(L"/Chinese/dict.json");
        _OpenJTalk = std::make_shared<OpenJTalk>(to_byte_string(OjtPath).c_str());
        _ChineseDict = std::make_shared<ChineseDict>(to_byte_string(ChinsesDictPath).c_str());
    }

    void* Convert(
        const std::wstring& InputText,
        const std::string& LanguageID,
        const void*
    )
    {
        OutRes.clear();
        auto InputSeq = SplitString(InputText, std::wregex(LR"([\r\n])"));
        if (LanguageID == "Chinese")
        {
            for (const auto& it : InputSeq)
                _ChineseDict->Search(it, OutRes);
        }
        else if (LanguageID == "Japanese")
        {
            for (const auto& it : InputSeq)
                _OpenJTalk->operator()(it, OutRes);
        }
        else
            return nullptr;
        if (OutRes.empty())
            return nullptr;
        OutRes.emplace_back();
        wcscpy_s(OutRes.back().Phoneme, L"[EOS]");
        OutRes.back().Tone = INT64_MAX;
        return OutRes.data();
    }

    void* GetExtraInfo() const
    {
        if (_OpenJTalk->_MyData.empty())
            return nullptr;
        _OpenJTalk->_MyData.emplace_back();
        _OpenJTalk->_MyData.back().Phoneme.P_2[0] = L'[';
        _OpenJTalk->_MyData.back().Phoneme.P_1[0] = L'E';
        _OpenJTalk->_MyData.back().Phoneme.P0[0] = L'O';
        _OpenJTalk->_MyData.back().Phoneme.P1[0] = L'S';
        _OpenJTalk->_MyData.back().Phoneme.P2[0] = L']';

        return _OpenJTalk->_MyData.data();
    }

private:
    std::shared_ptr<OpenJTalk> _OpenJTalk;
    std::shared_ptr<ChineseDict> _ChineseDict;
    std::vector<PhonemeAndTone> OutRes;
};

void* CreateInstance(const wchar_t* Parameter)
{
    return new Instance(Parameter);
}
void DestoryInstance(void* _Instance)
{
    delete static_cast<Instance*>(_Instance);
}
void* Convert(void* _Instance, const wchar_t* InputText, const char* LanguageID, const void*)
{
    return static_cast<Instance*>(_Instance)->Convert(InputText, LanguageID, nullptr);
}
void* GetExtraInfo(void* _Instance)
{
    return static_cast<Instance*>(_Instance)->GetExtraInfo();
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    return TRUE;
}

