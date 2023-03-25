#include "framework.h"
#include "openjtalk\\open_jtalk-1.11\\src\\text2mecab\\text2mecab.h"
#include "openjtalk\\open_jtalk-1.11\\src\\mecab\\src\\mecab.h"
#include "openjtalk\\open_jtalk-1.11\\src\\mecab2njd\\mecab2njd.h"
#include "openjtalk\\open_jtalk-1.11\\src\\njd\\njd.h"
#include "openjtalk\\open_jtalk-1.11\\src\\njd_set_digit\\njd_set_digit.h"
#include "openjtalk\\open_jtalk-1.11\\src\\njd_set_pronunciation\\njd_set_pronunciation.h"
#include "openjtalk\\open_jtalk-1.11\\src\\njd_set_accent_phrase\\njd_set_accent_phrase.h"
#include "openjtalk\\open_jtalk-1.11\\src\\njd_set_accent_type\\njd_set_accent_type.h"
#include "openjtalk\\open_jtalk-1.11\\src\\njd_set_unvoiced_vowel\\njd_set_unvoiced_vowel.h"
#include "openjtalk\\open_jtalk-1.11\\src\\njd_set_long_vowel\\njd_set_long_vowel.h"
#include "openjtalk\\open_jtalk-1.11\\src\\jpcommon\\jpcommon.h"
#include "openjtalk\\open_jtalk-1.11\\src\\njd2jpcommon\\njd2jpcommon.h"
#include <codecvt>
#include <regex>
#include <atomic>
#pragma comment(lib, "openjtalk\\pyopenjtalk-master\\lib\\open_jtalk\\openjtalk.lib")
#pragma comment(lib, "openjtalk\\pyopenjtalk-master\\lib\\hts_engine_API\\hts_engine_API.lib")
#pragma comment(lib, "openjtalk\\pyopenjtalk-master\\lib\\hts_engine_API\\hts_engine.lib")

enum class CleanerType
{
	Cleaner1,
    Cleaner2,
    Ipa1,
    Ipa2,
    Ipa3
};

//inline std::wstring* globalStrW = nullptr;

ThreadBoundData _CleanedData;

openjtalk* ojtins = nullptr;

std::string to_byte_string(const std::wstring& input)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(input);
}

std::wstring to_wide_string(const std::string& input)
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.from_bytes(input);
}

openjtalk::openjtalk()
{
    mecab = new Mecab;
    njd = new NJD;
    jpcommon = new JPCommon;
    JPCommon_initialize(jpcommon);
    Mecab_initialize(mecab);
    NJD_initialize(njd);
    Mecab_load(mecab, "cleaners\\");
}

openjtalk::openjtalk(const char* folder)
{
    mecab = new Mecab;
    njd = new NJD;
    jpcommon = new JPCommon;
    JPCommon_initialize(jpcommon);
    Mecab_initialize(mecab);
    NJD_initialize(njd);
    Mecab_load(mecab, folder);
}

openjtalk::~openjtalk()
{
    Mecab_clear(mecab);
    NJD_clear(njd);
    JPCommon_clear(jpcommon);
    delete mecab;
    delete njd;
    delete jpcommon;
    jpcommon = nullptr;
    mecab = nullptr;
    njd = nullptr;
}

void openjtalk::run_frontend(const char* input) const
{
    std::vector<char> buff(1024ull * 1024);
    text2mecab(buff.data(), input);
    Mecab_analysis(mecab, buff.data());
    mecab2njd(njd, Mecab_get_feature(mecab), Mecab_get_size(mecab));
    njd_set_pronunciation(njd);
    njd_set_digit(njd);
    njd_set_accent_phrase(njd);
    njd_set_accent_type(njd);
    njd_set_unvoiced_vowel(njd);
    njd_set_long_vowel(njd);
    //auto features = njd2feature(njd);

    //NJD_refresh(njd);
    Mecab_refresh(mecab);
    //return features;
}

std::vector<std::wstring> extract_fullcontext(const openjtalk& ojt, const char* text, bool run_marine = false)
{
    ojt.run_frontend(text);
    return ojt.make_label();
}

std::vector<std::wstring> openjtalk::make_label() const
{
    //feature2njd(njd, njd_features);
    njd2jpcommon(jpcommon, njd);
    JPCommon_make_label(jpcommon);
    const int label_size = JPCommon_get_label_size(jpcommon);
    char** label_feature = JPCommon_get_label_feature(jpcommon);
    std::vector<std::wstring> labels;
    labels.reserve(label_size);
    for (int i = 0; i < label_size; i++)
        labels.push_back(to_wide_string(label_feature[i]));
    JPCommon_refresh(jpcommon);
    NJD_refresh(njd);
    return labels;
}

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

void divide(std::wstring s, std::vector<std::wstring>& v, const std::wregex& reg)
{
    std::wsmatch mResult;
    while (regex_search(s, mResult, reg))
    {
        v.emplace_back(mResult[0].str());
        s = mResult.suffix();
    }
}

void CreateOjt(const wchar_t* folder)
{
    if (!ojtins)
        ojtins = new openjtalk(to_byte_string(folder).c_str());
}

CleanerType CheckType(std::wstring& input)
{
    size_t ret = input.find(L"[Japanese1]");
    if (ret != std::wstring::npos)
    {
        input = input.substr(11);
        return CleanerType::Cleaner1;
    }
    ret = input.find(L"[Japanese2]");
    if (ret != std::wstring::npos)
    {
        input = input.substr(11);
        return CleanerType::Cleaner2;
    }
    ret = input.find(L"[Ipa1]");
    if (ret != std::wstring::npos)
    {
        input = input.substr(6);
        return CleanerType::Ipa1;
    }
    ret = input.find(L"[Ipa2]");
    if (ret != std::wstring::npos)
    {
        input = input.substr(6);
        return CleanerType::Ipa2;
    }
    ret = input.find(L"[Ipa3]");
    if (ret != std::wstring::npos)
    {
        input = input.substr(6);
        return CleanerType::Ipa3;
    }
    return CleanerType::Cleaner2;
}

void Release()
{
    return;
}

void ReleaseOjt()
{
    delete ojtins;
    ojtins = nullptr;
}

void JapaneseCleaner(std::wstring& input)
{
    if (!ojtins)
        ojtins = new openjtalk();

    const std::wregex _characters(L"[A-Za-z\\d\u3005\u3040-\u30ff\u4e00-\u9fff\uff11-\uff19\uff21-\uff3a\uff41-\uff5a\uff66-\uff9d]");
    const std::wregex _marks(L"[^A-Za-z\\d\u3005\u3040-\u30ff\u4e00-\u9fff\uff11-\uff19\uff21-\uff3a\uff41-\uff5a\uff66-\uff9d]+");
    const std::wregex _sentence(L"[A-Za-z\\d\u3005\u3040-\u30ff\u4e00-\u9fff\uff11-\uff19\uff21-\uff3a\uff41-\uff5a\uff66-\uff9d]+");
    const std::wregex ph(L"\\-([^\\+]*)\\+");
    const std::wregex nm(L"/F:(\\d+)_");
    const std::wregex a11(L"/A:(\\-?[0-9]+)\\+");
    const std::wregex a22(L"\\+(\\d+)\\+");
    const std::wregex a33(L"\\+(\\d+)/");

    auto& CleanedString = _CleanedData.get();
    CleanedString.clear();

    const CleanerType Ctype = CheckType(input);

    if (!std::regex_search(input, _marks))
        input += L'。';
    std::vector<std::wstring> sentences;
    std::vector<std::wstring> marks;
    divide(input, sentences, _sentence);
    divide(input, marks, _marks);

    bool SymbolFirst = false;
    if (input.find(marks[0]) == 0)
        SymbolFirst = true;

    size_t SymbolIndex = 0;
    for (const auto & asentence : sentences)
    {
        if(SymbolFirst && SymbolIndex < marks.size())
            CleanedString += std::regex_replace(marks[SymbolIndex], std::wregex(L""), L"");
        auto labels = extract_fullcontext(*ojtins, to_byte_string(asentence).c_str());
        for (size_t it = 0; it < labels.size(); ++it)
        {
            std::wsmatch mResult;
            std::regex_search(labels[it], mResult, ph);
            std::wstring phoneme = mResult[1].str();
            if (phoneme == L"sil" || phoneme == L"pau")
                continue;
            else
            {
                phoneme = std::regex_replace(phoneme, std::wregex(L"ch"), L"ʧ");
                phoneme = std::regex_replace(phoneme, std::wregex(L"sh"), L"ʃ");
                phoneme = std::regex_replace(phoneme, std::wregex(L"cl"), L"Q");
                if (Ctype == CleanerType::Cleaner2)
                    phoneme = std::regex_replace(phoneme, std::wregex(L"ts"), L"ʦ");
                CleanedString += phoneme;
            }
            std::regex_search(labels[it], mResult, nm);
            const auto n_moras = _wtoi(mResult[1].str().c_str());
            std::regex_search(labels[it], mResult, a11);
            const auto a1 = _wtoi(mResult[1].str().c_str());
            std::regex_search(labels[it], mResult, a22);
            const auto a2 = _wtoi(mResult[1].str().c_str());
            std::regex_search(labels[it], mResult, a33);
            const auto a3 = _wtoi(mResult[1].str().c_str());
            std::regex_search(labels[it + 1], mResult, ph);
            std::wstring nephoneme = mResult[1].str();
            int a2_next;
            if (nephoneme == L"sil" || nephoneme == L"pau")
            	a2_next = -1;
            else
            {
                std::regex_search(labels[it + 1], mResult, a22);
                a2_next = _wtoi(mResult[1].str().c_str());
            }
            if (a3 == 1 && a2_next == 1)
                CleanedString += L' ';
            else if (a1 == 0 && a2_next == a2 + 1 && a2 != n_moras)
                CleanedString += L"↓";
            else if (a3 == 1 && a2_next == 1)
                CleanedString += L"↑";
        }
        if (!SymbolFirst && SymbolIndex < marks.size())
            CleanedString += std::regex_replace(marks[SymbolIndex], std::wregex(L""), L"");
        ++SymbolIndex;
    }
    if (Ctype != CleanerType::Cleaner1 && Ctype != CleanerType::Cleaner2)
    {
        getRealSokuon(CleanedString);
        getRealHatsuon(CleanedString);
    }
    switch(Ctype)
    {
    case CleanerType::Ipa1:
    {
        getIpaStr1(CleanedString);
        break;
    }
    case CleanerType::Ipa2:
    {
        getIpaStr2(CleanedString);
        break;
    }
    case CleanerType::Ipa3:
    {
        getIpaStr2(CleanedString);
        getIpaStr3(CleanedString);
        break;
    }
    default:
    {
        break;
    }
    }
    replaceSymbol(CleanedString);
}

const wchar_t* PluginMain(const wchar_t* input)
{
    std::wstring _inp = input;
    JapaneseCleaner(_inp);
    return _CleanedData.get().c_str();
}

/*
void getSPhoneme(std::wstring& tmpStr, const std::wstring& ita)
{
    const auto labels = extract_fullcontext(*ojtins, to_byte_string(ita).c_str());
    for (size_t it = 0; it < labels.size(); ++it)
    {
        const std::wregex ph(L"\\-([^\\+]*)\\+");
        const std::wregex nm(L"/F:(\\d+)_");
        const std::wregex a11(L"/A:(\\-?[0-9]+)\\+");
        const std::wregex a22(L"\\+(\\d+)\\+");
        const std::wregex a33(L"\\+(\\d+)/");
        std::wsmatch mResult;
        std::regex_search(labels[it], mResult, ph);
        std::wstring phoneme = mResult[1].str();
        if (phoneme == L"sil" || phoneme == L"pau")
            continue;
        else
        {
            phoneme = std::regex_replace(phoneme, std::wregex(L"ch"), L"ʧ");
            phoneme = std::regex_replace(phoneme, std::wregex(L"sh"), L"ʃ");
            phoneme = std::regex_replace(phoneme, std::wregex(L"cl"), L"Q");
            phoneme = std::regex_replace(phoneme, std::wregex(L"ts"), L"ʦ");
            tmpStr += phoneme;
        }
        std::regex_search(labels[it], mResult, nm);
        const auto n_moras = _wtoi(mResult[1].str().c_str());
        std::regex_search(labels[it], mResult, a11);
        const auto a1 = _wtoi(mResult[1].str().c_str());
        std::regex_search(labels[it], mResult, a22);
        const auto a2 = _wtoi(mResult[1].str().c_str());
        std::regex_search(labels[it], mResult, a33);
        const auto a3 = _wtoi(mResult[1].str().c_str());
        std::regex_search(labels[it + 1], mResult, ph);
        std::wstring nephoneme = mResult[1].str();
        int a2_next;
        if (nephoneme == L"sil" || nephoneme == L"pau")
            a2_next = -1;
        else
        {
            std::regex_search(labels[it + 1], mResult, a22);
            a2_next = _wtoi(mResult[1].str().c_str());
        }
        if (a3 == 1 && a2_next == 1)
            continue;
        else if (a1 == 0 && a2_next == a2 + 1 && a2 != n_moras)
            tmpStr += L"↓";
        else if (a3 == 1 && a2_next == 1)
            tmpStr += L"↑";
    }
}

const wchar_t* extractFullContext(const wchar_t* input)
{
    if (!ojtins)
        return nullptr;
    if (!globalStrW)
        globalStrW = new std::wstring;
    globalStrW->clear();
    const auto out = extract_fullcontext(*ojtins, to_byte_string(input).c_str());
    for (const auto& ph : out)
    {
        *globalStrW += ph;
        *globalStrW += L"\n";
    }
    return globalStrW->c_str();
}

const wchar_t* getKana(const wchar_t* input)
{
    if (!ojtins)
        return nullptr;
    if (!globalStrW)
        globalStrW = new std::wstring;
    globalStrW->clear();
    const std::wregex _marks(L"[^A-Za-z\\d\u3005\u3040-\u30ff\u4e00-\u9fff\uff11-\uff19\uff21-\uff3a\uff41-\uff5a\uff66-\uff9d]+");
    const std::wregex _sentence(L"[A-Za-z\\d\u3005\u3040-\u30ff\u4e00-\u9fff\uff11-\uff19\uff21-\uff3a\uff41-\uff5a\uff66-\uff9d]+");
    const std::wstring inputTxt = input;
    std::vector<std::wstring> sentences;
    std::vector<std::wstring> marks;
    divide(inputTxt, sentences, _sentence);
    divide(inputTxt, marks, _marks);
    size_t i = 0;
    for(const auto& ita : sentences)
    {
        ojtins->run_frontend(to_byte_string(ita).c_str());
        const auto features = ojtins->getfeature();
        for (const auto& it : features)
        {
            if (it.pos == std::string("記号"))
            {
                *globalStrW += to_wide_string(std::regex_replace(it.str, std::regex("’"), ""));
            }
            else
            {
                *globalStrW += to_wide_string(std::regex_replace(it.pron, std::regex("’"), ""));
            }
        }
        ojtins->refresh();
        if (i < marks.size())
        {
            *globalStrW += marks[i++];
        }
    }
    return globalStrW->c_str();
}

const wchar_t* getPhoneme(const wchar_t* input)
{
    if (!ojtins)
        return nullptr;
    if (!globalStrW)
        globalStrW = new std::wstring;
    globalStrW->clear();

    const std::wregex _marks(L"[^A-Za-z\\d\u3005\u3040-\u30ff\u4e00-\u9fff\uff11-\uff19\uff21-\uff3a\uff41-\uff5a\uff66-\uff9d]+");
    const std::wregex _sentence(L"[A-Za-z\\d\u3005\u3040-\u30ff\u4e00-\u9fff\uff11-\uff19\uff21-\uff3a\uff41-\uff5a\uff66-\uff9d]+");
    const std::wregex ph(L"\\-([^\\+]*)\\+");

    const std::wstring inputTxt = input;
    std::vector<std::wstring> sentences;
    std::vector<std::wstring> marks;
    divide(inputTxt, sentences, _sentence);
    divide(inputTxt, marks, _marks);
    size_t i = 0;
    for (const auto& ita : sentences)
    {
        const auto labels = extract_fullcontext(*ojtins, to_byte_string(ita).c_str());
        for (const auto& it : labels)
        {
            std::wsmatch mResult;
            std::regex_search(it, mResult, ph);
            std::wstring phoneme = mResult[1].str();
            if (phoneme == L"sil" || phoneme == L"pau")
                continue;
            else
            {
                phoneme = std::regex_replace(phoneme, std::wregex(L"ch"), L"ʧ");
                phoneme = std::regex_replace(phoneme, std::wregex(L"sh"), L"ʃ");
                phoneme = std::regex_replace(phoneme, std::wregex(L"cl"), L"Q");
                phoneme = std::regex_replace(phoneme, std::wregex(L"ts"), L"ʦ");
                *globalStrW += phoneme;
            }
        }
        if (i < marks.size())
            *globalStrW += marks[i++];
    }
    return globalStrW->c_str();
}

const wchar_t* getRomaji(const wchar_t* input)
{
    if (!ojtins)
        return nullptr;
    if (!globalStrW)
        globalStrW = new std::wstring;
    globalStrW->clear();

    const std::wregex _marks(L"[^A-Za-z\\d\u3005\u3040-\u30ff\u4e00-\u9fff\uff11-\uff19\uff21-\uff3a\uff41-\uff5a\uff66-\uff9d]+");
    const std::wregex _sentence(L"[A-Za-z\\d\u3005\u3040-\u30ff\u4e00-\u9fff\uff11-\uff19\uff21-\uff3a\uff41-\uff5a\uff66-\uff9d]+");
    const std::wregex ph(L"\\-([^\\+]*)\\+");

    const std::wstring inputTxt = input;
    std::vector<std::wstring> sentences;
    std::vector<std::wstring> marks;
    divide(inputTxt, sentences, _sentence);
    divide(inputTxt, marks, _marks);
    size_t i = 0;
    for (const auto& ita : sentences)
    {
        const auto labels = extract_fullcontext(*ojtins, to_byte_string(ita).c_str());
        for (const auto& it : labels)
        {
            std::wsmatch mResult;
            std::regex_search(it, mResult, ph);
            std::wstring phoneme = mResult[1].str();
            if (phoneme == L"sil" || phoneme == L"pau")
                continue;
            else
            {
                phoneme = std::regex_replace(phoneme, std::wregex(L"cl"), L"Q");
                *globalStrW += phoneme;
            }
        }
        if (i < marks.size())
            *globalStrW += marks[i++];
    }
    return globalStrW->c_str();
}

const wchar_t* getIpa1(const wchar_t* input)
{
    if (!ojtins)
        return nullptr;
    if (!globalStrW)
        globalStrW = new std::wstring;
    globalStrW->clear();

    const std::wregex _marks(L"[^A-Za-z\\d\u3005\u3040-\u30ff\u4e00-\u9fff\uff11-\uff19\uff21-\uff3a\uff41-\uff5a\uff66-\uff9d]+");
    const std::wregex _sentence(L"[A-Za-z\\d\u3005\u3040-\u30ff\u4e00-\u9fff\uff11-\uff19\uff21-\uff3a\uff41-\uff5a\uff66-\uff9d]+");
    const std::wstring inputTxt = input;
    std::vector<std::wstring> sentences;
    std::vector<std::wstring> marks;
    divide(inputTxt, sentences, _sentence);
    divide(inputTxt, marks, _marks);
    size_t i = 0;
    for (const auto& ita : sentences)
    {
        std::wstring tmpStr;
        getSPhoneme(tmpStr, ita);
        getIpaStr1(tmpStr);
        *globalStrW += tmpStr;
        if (i < marks.size())
            *globalStrW += marks[i++];
    }
    return globalStrW->c_str();
}

const wchar_t* getIpa2(const wchar_t* input)
{
    if (!ojtins)
        return nullptr;
    if (!globalStrW)
        globalStrW = new std::wstring;
    globalStrW->clear();

    const std::wregex _marks(L"[^A-Za-z\\d\u3005\u3040-\u30ff\u4e00-\u9fff\uff11-\uff19\uff21-\uff3a\uff41-\uff5a\uff66-\uff9d]+");
    const std::wregex _sentence(L"[A-Za-z\\d\u3005\u3040-\u30ff\u4e00-\u9fff\uff11-\uff19\uff21-\uff3a\uff41-\uff5a\uff66-\uff9d]+");
    const std::wstring inputTxt = input;
    std::vector<std::wstring> sentences;
    std::vector<std::wstring> marks;
    divide(inputTxt, sentences, _sentence);
    divide(inputTxt, marks, _marks);
    size_t i = 0;
    for (const auto& ita : sentences)
    {
        std::wstring tmpStr;
        getSPhoneme(tmpStr, ita);
        getIpaStr2(tmpStr);
        *globalStrW += tmpStr;
        if (i < marks.size())
            *globalStrW += marks[i++];
    }
    return globalStrW->c_str();
}

const wchar_t* getIpa1WithBlank(const wchar_t* input)
{
    if (!ojtins)
        return nullptr;
    if (!globalStrW)
        globalStrW = new std::wstring;
    globalStrW->clear();

    const std::wregex _marks(L"[^A-Za-z\\d\u3005\u3040-\u30ff\u4e00-\u9fff\uff11-\uff19\uff21-\uff3a\uff41-\uff5a\uff66-\uff9d]+");
    const std::wregex _sentence(L"[A-Za-z\\d\u3005\u3040-\u30ff\u4e00-\u9fff\uff11-\uff19\uff21-\uff3a\uff41-\uff5a\uff66-\uff9d]+");
    const std::wstring inputTxt = input;
    std::vector<std::wstring> sentences;
    std::vector<std::wstring> marks;
    divide(inputTxt, sentences, _sentence);
    divide(inputTxt, marks, _marks);
    size_t i = 0;
    const std::wregex blankPos(L"([aiueo↓↑AIUEOQN])([AIUEOaiueoʦʃʧbcdfghjklmnpqrstvwxyzQ])");
    for (const auto& ita : sentences)
    {
        std::wstring tmpStr;
        getSPhoneme(tmpStr, ita);
        while (std::regex_search(tmpStr, blankPos))
            tmpStr = std::regex_replace(tmpStr, blankPos, L"$1 $2");
        getIpaStr1(tmpStr);
        *globalStrW += tmpStr;
        if (i < marks.size())
            *globalStrW += marks[i++];
    }
    return globalStrW->c_str();
}

const wchar_t* getIpa2WithBlank(const wchar_t* input)
{
    if (!ojtins)
        return nullptr;
    if (!globalStrW)
        globalStrW = new std::wstring;
    globalStrW->clear();

    const std::wregex _marks(L"[^A-Za-z\\d\u3005\u3040-\u30ff\u4e00-\u9fff\uff11-\uff19\uff21-\uff3a\uff41-\uff5a\uff66-\uff9d]+");
    const std::wregex _sentence(L"[A-Za-z\\d\u3005\u3040-\u30ff\u4e00-\u9fff\uff11-\uff19\uff21-\uff3a\uff41-\uff5a\uff66-\uff9d]+");
    const std::wstring inputTxt = input;
    std::vector<std::wstring> sentences;
    std::vector<std::wstring> marks;
    divide(inputTxt, sentences, _sentence);
    divide(inputTxt, marks, _marks);
    size_t i = 0;
    const std::wregex blankPos(L"([aiueo↓↑AIUEOQN])([AIUEOaiueoʦʃʧbcdfghjklmnpqrstvwxyzQ])");
    for (const auto& ita : sentences)
    {
        std::wstring tmpStr;
        getSPhoneme(tmpStr, ita);
        while (std::regex_search(tmpStr, blankPos))
            tmpStr = std::regex_replace(tmpStr, blankPos, L"$1 $2");
        getIpaStr2(tmpStr);
        *globalStrW += tmpStr;
        if (i < marks.size())
            *globalStrW += marks[i++];
    }
    return globalStrW->c_str();
}

const wchar_t* getPhonemeWithBlank(const wchar_t* input)
{
    if (!ojtins)
        return nullptr;
    if (!globalStrW)
        globalStrW = new std::wstring;
    globalStrW->clear();

    const std::wregex _marks(L"[^A-Za-z\\d\u3005\u3040-\u30ff\u4e00-\u9fff\uff11-\uff19\uff21-\uff3a\uff41-\uff5a\uff66-\uff9d]+");
    const std::wregex _sentence(L"[A-Za-z\\d\u3005\u3040-\u30ff\u4e00-\u9fff\uff11-\uff19\uff21-\uff3a\uff41-\uff5a\uff66-\uff9d]+");
    const std::wregex ph(L"\\-([^\\+]*)\\+");

    const std::wstring inputTxt = input;
    std::vector<std::wstring> sentences;
    std::vector<std::wstring> marks;
    divide(inputTxt, sentences, _sentence);
    divide(inputTxt, marks, _marks);
    size_t i = 0;
    const std::wregex blankPos(L"([aiueoAIUEOQN])([AIUEOaiueoʦʃʧbcdfghjklmnpqrstvwxyzQ])");
    for (const auto& ita : sentences)
    {
        std::wstring tmpStr;
        const auto labels = extract_fullcontext(*ojtins, to_byte_string(ita).c_str());
        for (const auto& it : labels)
        {
            std::wsmatch mResult;
            std::regex_search(it, mResult, ph);
            std::wstring phoneme = mResult[1].str();
            if (phoneme == L"sil" || phoneme == L"pau")
                continue;
            else
            {
                phoneme = std::regex_replace(phoneme, std::wregex(L"ch"), L"ʧ");
                phoneme = std::regex_replace(phoneme, std::wregex(L"sh"), L"ʃ");
                phoneme = std::regex_replace(phoneme, std::wregex(L"cl"), L"Q");
                phoneme = std::regex_replace(phoneme, std::wregex(L"ts"), L"ʦ");
                tmpStr += phoneme;
            }
        }
        while (std::regex_search(tmpStr, blankPos))
            tmpStr = std::regex_replace(tmpStr, blankPos, L"$1 $2");
        *globalStrW += tmpStr;
        if (i < marks.size())
            *globalStrW += marks[i++];
    }
    return globalStrW->c_str();
}

const wchar_t* getRomajiWithBlank(const wchar_t* input)
{
    if (!ojtins)
        return nullptr;
    if (!globalStrW)
        globalStrW = new std::wstring;
    globalStrW->clear();

    const std::wregex _marks(L"[^A-Za-z\\d\u3005\u3040-\u30ff\u4e00-\u9fff\uff11-\uff19\uff21-\uff3a\uff41-\uff5a\uff66-\uff9d]+");
    const std::wregex _sentence(L"[A-Za-z\\d\u3005\u3040-\u30ff\u4e00-\u9fff\uff11-\uff19\uff21-\uff3a\uff41-\uff5a\uff66-\uff9d]+");
    const std::wregex ph(L"\\-([^\\+]*)\\+");

    const std::wstring inputTxt = input;
    std::vector<std::wstring> sentences;
    std::vector<std::wstring> marks;
    divide(inputTxt, sentences, _sentence);
    divide(inputTxt, marks, _marks);
    size_t i = 0;
    const std::wregex blankPos(L"([aiueoAIUEOQN])([AIUEOaiueoʦʃʧbcdfghjklmnpqrstvwxyzQ])");
    for (const auto& ita : sentences)
    {
        std::wstring tmpStr;
        const auto labels = extract_fullcontext(*ojtins, to_byte_string(ita).c_str());
        for (const auto& it : labels)
        {
            std::wsmatch mResult;
            std::regex_search(it, mResult, ph);
            std::wstring phoneme = mResult[1].str();
            if (phoneme == L"sil" || phoneme == L"pau")
                continue;
            else
            {
                phoneme = std::regex_replace(phoneme, std::wregex(L"cl"), L"Q");
                tmpStr += phoneme;
            }
        }
        while (std::regex_search(tmpStr, blankPos))
            tmpStr = std::regex_replace(tmpStr, blankPos, L"$1 $2");
        *globalStrW += tmpStr;
        if (i < marks.size())
            *globalStrW += marks[i++];
    }
    return globalStrW->c_str();
}

std::wregex numReg(L"[0-9\\.]+");
std::wregex tokenReg(L"[A-Za-z]+");

const wchar_t* ChineseToJapanese(const wchar_t* input)
{
    globalStrW->clear();
    std::wstring text = input;
    std::wsmatch amatch_results;
    std::vector<std::wstring> Tokens;
    uint64_t PHSEQOff = text.find(L"<<<<DURATION>>>>");
    std::wstring phstr = text.substr(PHSEQOff + 16);
    text = text.substr(0, PHSEQOff + 1);
    while (std::regex_search(text, amatch_results, tokenReg))
    {
        Tokens.push_back(amatch_results[0].str());
        text = amatch_results.suffix();
    }
    std::vector<double> ph_dur;
    ph_dur.reserve(Tokens.size());

    while (std::regex_search(phstr, amatch_results, numReg))
    {
        ph_dur.push_back(_wtof(amatch_results[0].str().c_str()));
        phstr = amatch_results.suffix();
    }
    std::wstring ph_dur_str;
    std::wstring ph_seq_str;
    for (size_t i = 0; i < Tokens.size(); ++i)
    {
        if (Tokens[i] == L"ai")
        {
            ph_seq_str += L"e ";
            ph_dur_str += std::to_wstring(ph_dur[i]) + L' ';
        }
        else if (Tokens[i] == L"E")
        {
            ph_seq_str += L"e ";
            ph_dur_str += std::to_wstring(ph_dur[i]) + L' ';
        }
        else if (Tokens[i] == L"EN")
        {
            ph_seq_str += L"e N ";
            ph_dur_str += std::to_wstring(ph_dur[i] / 2) + L' ';
            ph_dur_str += std::to_wstring(ph_dur[i] / 2) + L' ';
        }
        else if (Tokens[i] == L"an")
        {
            ph_seq_str += L"a N ";
            ph_dur_str += std::to_wstring(ph_dur[i] / 2) + L' ';
            ph_dur_str += std::to_wstring(ph_dur[i] / 2) + L' ';
        }
        else if (Tokens[i] == L"ang")
        {
            ph_seq_str += L"a N ";
            ph_dur_str += std::to_wstring(ph_dur[i] / 2) + L' ';
            ph_dur_str += std::to_wstring(ph_dur[i] / 2) + L' ';
        }
        else if (Tokens[i] == L"ao")
        {
            ph_seq_str += L"a o ";
            ph_dur_str += std::to_wstring(ph_dur[i] / 2) + L' ';
            ph_dur_str += std::to_wstring(ph_dur[i] / 2) + L' ';
        }
        else if (Tokens[i] == L"c")
        {
            ph_seq_str += L"ts ";
            ph_dur_str += std::to_wstring(ph_dur[i]) + L' ';
        }
        else if (Tokens[i] == L"en")
        {
            ph_seq_str += L"e N ";
            ph_dur_str += std::to_wstring(ph_dur[i] / 2) + L' ';
            ph_dur_str += std::to_wstring(ph_dur[i] / 2) + L' ';
        }
        else if (Tokens[i] == L"eng")
        {
            ph_seq_str += L"e N ";
            ph_dur_str += std::to_wstring(ph_dur[i] / 2) + L' ';
            ph_dur_str += std::to_wstring(ph_dur[i] / 2) + L' ';
        }
        else if (Tokens[i] == L"ei")
        {
            ph_seq_str += L"e i ";
            ph_dur_str += std::to_wstring(ph_dur[i] / 2) + L' ';
            ph_dur_str += std::to_wstring(ph_dur[i] / 2) + L' ';
        }
        else if (Tokens[i] == L"er")
        {
            ph_seq_str += L"e ";
            ph_dur_str += std::to_wstring(ph_dur[i]) + L' ';
        }
        else if (Tokens[i] == L"i0")
        {
            ph_seq_str += L"i ";
            ph_dur_str += std::to_wstring(ph_dur[i]) + L' ';
        }
        else if (Tokens[i] == L"ia")
        {
            ph_seq_str += L"i a ";
            ph_dur_str += std::to_wstring(ph_dur[i] / 2) + L' ';
            ph_dur_str += std::to_wstring(ph_dur[i] / 2) + L' ';
        }
        else if (Tokens[i] == L"ian")
        {
            ph_seq_str += L"i a N ";
            ph_dur_str += std::to_wstring(ph_dur[i] / 3) + L' ';
            ph_dur_str += std::to_wstring(ph_dur[i] / 3) + L' ';
            ph_dur_str += std::to_wstring(ph_dur[i] / 3) + L' ';
        }
        else if (Tokens[i] == L"iang")
        {
            ph_seq_str += L"i a N ";
            ph_dur_str += std::to_wstring(ph_dur[i] / 3) + L' ';
            ph_dur_str += std::to_wstring(ph_dur[i] / 3) + L' ';
            ph_dur_str += std::to_wstring(ph_dur[i] / 3) + L' ';
        }
        else if (Tokens[i] == L"iao")
        {
            ph_seq_str += L"i a o ";
            ph_dur_str += std::to_wstring(ph_dur[i] / 3) + L' ';
            ph_dur_str += std::to_wstring(ph_dur[i] / 3) + L' ';
            ph_dur_str += std::to_wstring(ph_dur[i] / 3) + L' ';
        }
        else if (Tokens[i] == L"ie")
        {
            ph_seq_str += L"i e ";
            ph_dur_str += std::to_wstring(ph_dur[i] / 2) + L' ';
            ph_dur_str += std::to_wstring(ph_dur[i] / 2) + L' ';
        }
        else if (Tokens[i] == L"in")
        {
            ph_seq_str += L"i N ";
            ph_dur_str += std::to_wstring(ph_dur[i] / 2) + L' ';
            ph_dur_str += std::to_wstring(ph_dur[i] / 2) + L' ';
        }
        else if (Tokens[i] == L"ing")
        {
            ph_seq_str += L"i N ";
            ph_dur_str += std::to_wstring(ph_dur[i] / 2) + L' ';
            ph_dur_str += std::to_wstring(ph_dur[i] / 2) + L' ';
        }
        else if (Tokens[i] == L"iong")
        {
            ph_seq_str += L"i o N ";
            ph_dur_str += std::to_wstring(ph_dur[i] / 3) + L' ';
            ph_dur_str += std::to_wstring(ph_dur[i] / 3) + L' ';
            ph_dur_str += std::to_wstring(ph_dur[i] / 3) + L' ';
        }
        else if (Tokens[i] == L"iu")
        {
            ph_seq_str += L"i u ";
            ph_dur_str += std::to_wstring(ph_dur[i] / 2) + L' ';
            ph_dur_str += std::to_wstring(ph_dur[i] / 2) + L' ';
        }
        else if (Tokens[i] == L"ir")
        {
            ph_seq_str += L"i ";
            ph_dur_str += std::to_wstring(ph_dur[i]) + L' ';
        }
        else if (Tokens[i] == L"l")
        {
            ph_seq_str += L"r ";
            ph_dur_str += std::to_wstring(ph_dur[i]) + L' ';
        }
        else if (Tokens[i] == L"ong")
        {
            ph_seq_str += L"o N ";
            ph_dur_str += std::to_wstring(ph_dur[i] / 2) + L' ';
            ph_dur_str += std::to_wstring(ph_dur[i] / 2) + L' ';
        }
        else if (Tokens[i] == L"ou")
        {
            ph_seq_str += L"o u ";
            ph_dur_str += std::to_wstring(ph_dur[i] / 2) + L' ';
            ph_dur_str += std::to_wstring(ph_dur[i] / 2) + L' ';
        }
        else if (Tokens[i] == L"q")
        {
            ph_seq_str += L"ch ";
            ph_dur_str += std::to_wstring(ph_dur[i]) + L' ';
        }
        else if (Tokens[i] == L"ua")
        {
            ph_seq_str += L"u a ";
            ph_dur_str += std::to_wstring(ph_dur[i] / 2) + L' ';
            ph_dur_str += std::to_wstring(ph_dur[i] / 2) + L' ';
        }
        else if (Tokens[i] == L"uai")
        {
            ph_seq_str += L"u a i ";
            ph_dur_str += std::to_wstring(ph_dur[i] / 3) + L' ';
            ph_dur_str += std::to_wstring(ph_dur[i] / 3) + L' ';
            ph_dur_str += std::to_wstring(ph_dur[i] / 3) + L' ';
        }
        else if (Tokens[i] == L"uan")
        {
            ph_seq_str += L"u a N ";
            ph_dur_str += std::to_wstring(ph_dur[i] / 3) + L' ';
            ph_dur_str += std::to_wstring(ph_dur[i] / 3) + L' ';
            ph_dur_str += std::to_wstring(ph_dur[i] / 3) + L' ';
        }
        else if (Tokens[i] == L"uang")
        {
            ph_seq_str += L"u a N ";
            ph_dur_str += std::to_wstring(ph_dur[i] / 3) + L' ';
            ph_dur_str += std::to_wstring(ph_dur[i] / 3) + L' ';
            ph_dur_str += std::to_wstring(ph_dur[i] / 3) + L' ';
        }
        else if (Tokens[i] == L"ui")
        {
            ph_seq_str += L"u i ";
            ph_dur_str += std::to_wstring(ph_dur[i] / 2) + L' ';
            ph_dur_str += std::to_wstring(ph_dur[i] / 2) + L' ';
        }
        else if (Tokens[i] == L"un")
        {
            ph_seq_str += L"u N ";
            ph_dur_str += std::to_wstring(ph_dur[i] / 2) + L' ';
            ph_dur_str += std::to_wstring(ph_dur[i] / 2) + L' ';
        }
        else if (Tokens[i] == L"uo")
        {
            ph_seq_str += L"u o ";
            ph_dur_str += std::to_wstring(ph_dur[i] / 2) + L' ';
            ph_dur_str += std::to_wstring(ph_dur[i] / 2) + L' ';
        }
        else if (Tokens[i] == L"v")
        {
            ph_seq_str += L"i y u ";
            ph_dur_str += std::to_wstring(ph_dur[i] / 3) + L' ';
            ph_dur_str += std::to_wstring(ph_dur[i] / 3) + L' ';
            ph_dur_str += std::to_wstring(ph_dur[i] / 3) + L' ';
        }
        else if (Tokens[i] == L"van")
        {
            ph_seq_str += L"i y u a N ";
            ph_dur_str += std::to_wstring(ph_dur[i] / 5) + L' ';
            ph_dur_str += std::to_wstring(ph_dur[i] / 5) + L' ';
            ph_dur_str += std::to_wstring(ph_dur[i] / 5) + L' ';
            ph_dur_str += std::to_wstring(ph_dur[i] / 5) + L' ';
            ph_dur_str += std::to_wstring(ph_dur[i] / 5) + L' ';
        }
        else if (Tokens[i] == L"ve")
        {
            ph_seq_str += L"i y u e ";
            ph_dur_str += std::to_wstring(ph_dur[i] / 4) + L' ';
            ph_dur_str += std::to_wstring(ph_dur[i] / 4) + L' ';
            ph_dur_str += std::to_wstring(ph_dur[i] / 4) + L' ';
            ph_dur_str += std::to_wstring(ph_dur[i] / 4) + L' ';
        }
        else if (Tokens[i] == L"vn")
        {
            ph_seq_str += L"i y u N ";
            ph_dur_str += std::to_wstring(ph_dur[i] / 4) + L' ';
            ph_dur_str += std::to_wstring(ph_dur[i] / 4) + L' ';
            ph_dur_str += std::to_wstring(ph_dur[i] / 4) + L' ';
            ph_dur_str += std::to_wstring(ph_dur[i] / 4) + L' ';
        }
        else if (Tokens[i] == L"x")
        {
            ph_seq_str += L"sh ";
            ph_dur_str += std::to_wstring(ph_dur[i]) + L' ';
        }
        else if (Tokens[i] == L"zh")
        {
            ph_seq_str += L"z ";
            ph_dur_str += std::to_wstring(ph_dur[i]) + L' ';
        }
        else
        {
            ph_seq_str += Tokens[i] + L' ';
            ph_dur_str += std::to_wstring(ph_dur[i]) + L' ';
        }
    }
    *globalStrW = ph_seq_str + L"<<<<DURATION>>>>" + ph_dur_str;
    return globalStrW->c_str();
}

const wchar_t* JapaneseToChinese(const wchar_t* input)
{
    globalStrW->clear();
    std::wstring text = input;
    std::wsmatch amatch_results;
    std::vector<std::wstring> Tokens;
    uint64_t PHSEQOff = text.find(L"<<<<DURATION>>>>");
    std::wstring phstr = text.substr(PHSEQOff + 16);
    text = text.substr(0, PHSEQOff + 1);
    text = std::regex_replace(text, std::wregex(L"([kthgdbpnmr])y u"), L"$1 v");
    text = std::regex_replace(text, std::wregex(L"([kthgdbpnmr])y ([ae])"), L"$1 i$2");
    text = std::regex_replace(text, std::wregex(L"([kthgdbpnmr])y ([io])"), L"$1 $2");
    while (std::regex_search(text, amatch_results, tokenReg))
    {
        Tokens.push_back(amatch_results[0].str());
        text = amatch_results.suffix();
    }
    std::vector<double> ph_dur;
    ph_dur.reserve(Tokens.size());
    while (std::regex_search(phstr, amatch_results, numReg))
    {
        ph_dur.push_back(_wtof(amatch_results[0].str().c_str()));
        phstr = amatch_results.suffix();
    }
    std::wstring ph_dur_str;
    std::wstring ph_seq_str;
    for (size_t i = 0; i < Tokens.size(); ++i)
    {
        if (i < Tokens.size() - 1 && Tokens[i + 1] == L"N")
        {
            if (Tokens[i] == L"e")
                ph_seq_str += L"an ";
            else if (Tokens[i] == L"ie")
                ph_seq_str += L"en ";
            else if (Tokens[i] == L"o")
                ph_seq_str += L"ong ";
            else
                ph_seq_str += Tokens[i] + L"n ";
            ph_dur_str += std::to_wstring(ph_dur[i] + ph_dur[i + 1]) + L' ';
            ++i;
        }
        else if (Tokens[i] == L"I")
        {
            ph_seq_str += L"i ";
            ph_dur_str += std::to_wstring(ph_dur[i]) + L' ';
        }
        else if (Tokens[i] == L"U")
        {
            ph_seq_str += L"u ";
            ph_dur_str += std::to_wstring(ph_dur[i]) + L' ';
        }
        else if (Tokens[i] == L"br")
        {
            continue;
        }
        else if (Tokens[i] == L"cl")
        {
            continue;
        }
        else if (Tokens[i] == L"U")
        {
            ph_seq_str += L"u ";
            ph_dur_str += std::to_wstring(ph_dur[i]) + L' ';
        }
        else if (Tokens[i] == L"v")
        {
            ph_seq_str += L"w ";
            ph_dur_str += std::to_wstring(ph_dur[i]) + L' ';
        }
        else if (Tokens[i] == L"e")
        {
            ph_seq_str += L"ai ";
            ph_dur_str += std::to_wstring(ph_dur[i]) + L' ';
        }
        else if (Tokens[i].length() == 2)
        {
            if (Tokens[i] == L"ts")
            {
                ph_seq_str += L"c ";
                ph_dur_str += std::to_wstring(ph_dur[i]) + L' ';
            }
            else if (Tokens[i] == L"sh" && Tokens[i + 1] == L"i")
            {
                ph_seq_str += L"x ";
                ph_dur_str += std::to_wstring(ph_dur[i]) + L' ';
            }
            else if (Tokens[i] == L"ch" && Tokens[i + 1] == L"i")
            {
                ph_seq_str += L"q ";
                ph_dur_str += std::to_wstring(ph_dur[i]) + L' ';
            }
            else
            {
                ph_seq_str += Tokens[i] + L' ';
                ph_dur_str += std::to_wstring(ph_dur[i]) + L' ';
            }
        }
        else if (Tokens[i] == L"r")
        {
            ph_seq_str += L"l ";
            ph_dur_str += std::to_wstring(ph_dur[i]) + L' ';
        }
        else
        {
            ph_seq_str += Tokens[i] + L' ';
            ph_dur_str += std::to_wstring(ph_dur[i]) + L' ';
        }
    }
    Tokens.clear();
    text = ph_seq_str;
    while (std::regex_search(text, amatch_results, tokenReg))
    {
        Tokens.push_back(amatch_results[0]);
        text = amatch_results.suffix();
    }
    ph_dur.clear();
    ph_dur.reserve(Tokens.size());
    phstr = ph_dur_str;
    while (std::regex_search(phstr, amatch_results, numReg))
    {
        ph_dur.push_back(_wtof(amatch_results[0].str().c_str()));
        phstr = amatch_results.suffix();
    }
    ph_seq_str.clear();
    ph_dur_str.clear();
    for (size_t i = 0; i < Tokens.size(); ++i)
    {
        if (i < Tokens.size() - 1)
        {
            if (Tokens[i] == Tokens[i + 1])
            {
                ph_seq_str += Tokens[i] + L' ';
                ph_dur_str += std::to_wstring(ph_dur[i] + ph_dur[i + 1]) + L' ';
                ++i;
            }
            else if (Tokens[i].length() == 2 && Tokens[i][1] == Tokens[i + 1][0])
            {
                ph_seq_str += Tokens[i] + L' ';
                ph_dur_str += std::to_wstring(ph_dur[i] + ph_dur[i + 1]) + L' ';
                ++i;
            }
            else if (Tokens[i] == L"i" && (Tokens[i + 1] == L"a" || Tokens[i + 1] == L"e" || Tokens[i + 1] == L"u"))
            {
                ph_seq_str += Tokens[i] + L' ';
                ph_dur_str += std::to_wstring(ph_dur[i] + ph_dur[i + 1]) + L' ';
                ++i;
            }
            else
            {
                ph_seq_str += Tokens[i] + L' ';
                ph_dur_str += std::to_wstring(ph_dur[i]) + L' ';
            }
        }
        else
        {
            ph_seq_str += Tokens[i] + L' ';
            ph_dur_str += std::to_wstring(ph_dur[i]) + L' ';
        }
    }
    *globalStrW = ph_seq_str + L"<<<<DURATION>>>>" + ph_dur_str;
    return globalStrW->c_str();
}
 */

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        break;
    }
    case DLL_THREAD_ATTACH:
    {
        break;
    }
    case DLL_THREAD_DETACH:
    {
        //_CleanedData.refresh();
        break;
    }
    case DLL_PROCESS_DETACH:
        ReleaseOjt();
        break;
    }
    return TRUE;
}

