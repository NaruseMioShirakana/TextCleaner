
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
#pragma comment(lib, "openjtalk\\pyopenjtalk-master\\lib\\open_jtalk\\openjtalk.lib")
#pragma comment(lib, "openjtalk\\pyopenjtalk-master\\lib\\hts_engine_API\\hts_engine_API.lib")
#pragma comment(lib, "openjtalk\\pyopenjtalk-master\\lib\\hts_engine_API\\hts_engine.lib")
#include <codecvt>
#include <vector>
#include <string>
#include <regex>
#include <map>

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

inline openjtalk* ojtins = nullptr;

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

NjdFeature::NjdFeature(NJDNode* node)
{
    str = NJDNode_get_string(node);
    pos = NJDNode_get_pos(node);
    pos_group1 = NJDNode_get_pos_group1(node);
    pos_group2 = NJDNode_get_pos_group2(node);
    pos_group3 = NJDNode_get_pos_group3(node);
    ctype = NJDNode_get_ctype(node);
    cform = NJDNode_get_cform(node);
    orig = NJDNode_get_orig(node);
    read = NJDNode_get_read(node);
    pron = NJDNode_get_pron(node);
    acc = NJDNode_get_acc(node);
    mora_size = NJDNode_get_mora_size(node);
    chain_rule = NJDNode_get_chain_rule(node);
    chain_flag = NJDNode_get_chain_flag(node);
}

std::vector<NjdFeature> njd2feature(const NJD* njd)
{
    NJDNode* node = njd->head;
    std::vector<NjdFeature> features;
    while (node != nullptr)
    {
        features.emplace_back(NjdFeature(node));
        node = node->next;
    }
    return features;
}

std::vector<NjdFeature> openjtalk::getfeature() const
{
    NJDNode* node = njd->head;
    std::vector<NjdFeature> features;
    while (node != nullptr)
    {
        features.emplace_back(NjdFeature(node));
        node = node->next;
    }
    return features;
}

void openjtalk::run_frontend(const char* input) const
{
    char buff[8192];
    text2mecab(buff, input);
    Mecab_analysis(mecab, buff);
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
    for (int i = 0; i < label_size; i++)
        labels.push_back(to_wide_string(label_feature[i]));
    JPCommon_refresh(jpcommon);
    NJD_refresh(njd);
    return labels;
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

void getSPhoneme(std::wstring& tmpStr, openjtalk* ojtin, const std::wstring& ita)
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

void divide(const std::wstring& s, std::vector<std::wstring>& v, const std::wregex& reg)
{
    std::wsmatch mResult;
    if (regex_search(s, mResult, reg)) {
        v.emplace_back(std::wstring(mResult[0].first, mResult[0].second));
        divide(std::wstring(mResult[0].second, s.end()), v, reg);
    }
}

void CreateOjt(const char* folder)
{
    if (!ojtins)
        ojtins = new openjtalk(folder);
    if (!globalStr)
        globalStr = new std::string;
    Folder = folder;
}

void Release()
{
    delete ojtins;
    ojtins = nullptr;
    delete globalStrW;
    delete globalStr;
    globalStr = nullptr;
    globalStrW = nullptr;
}

const wchar_t* PluginMain(const wchar_t* input)
{
    if (!globalStrW)
        globalStrW = new std::wstring;
    globalStrW->clear();
    std::vector<std::wstring> sentences;
    std::vector<std::wstring> marks;
    const std::wstring wstr(input);
    const std::wregex _characters(L"[A-Za-z\\d\u3005\u3040-\u30ff\u4e00-\u9fff\uff11-\uff19\uff21-\uff3a\uff41-\uff5a\uff66-\uff9d]");
    const std::wregex _marks(L"[^A-Za-z\\d\u3005\u3040-\u30ff\u4e00-\u9fff\uff11-\uff19\uff21-\uff3a\uff41-\uff5a\uff66-\uff9d]+");
    const std::wregex _sentence(L"[A-Za-z\\d\u3005\u3040-\u30ff\u4e00-\u9fff\uff11-\uff19\uff21-\uff3a\uff41-\uff5a\uff66-\uff9d]+");
    const std::wregex ph(L"\\-([^\\+]*)\\+");
    const std::wregex nm(L"/F:(\\d+)_");
    const std::wregex a11(L"/A:(\\-?[0-9]+)\\+");
    const std::wregex a22(L"\\+(\\d+)\\+");
    const std::wregex a33(L"\\+(\\d+)/");
    divide(wstr, sentences, _sentence);
    divide(wstr, marks, _marks);
    const auto ojt = new openjtalk();
    size_t i = 0;
    for (const auto & asentence : sentences)
    {
        auto labels = extract_fullcontext(*ojt, to_byte_string(asentence).c_str());
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
                phoneme = std::regex_replace(phoneme, std::wregex(L"ts"), L"ʦ");
                *globalStrW += phoneme;
            }
            std::regex_search(labels[it], mResult, nm);
            auto n_moras = _wtoi(mResult[1].str().c_str());
            std::regex_search(labels[it], mResult, a11);
            auto a1 = _wtoi(mResult[1].str().c_str());
            std::regex_search(labels[it], mResult, a22);
            auto a2 = _wtoi(mResult[1].str().c_str());
            std::regex_search(labels[it], mResult, a33);
            auto a3 = _wtoi(mResult[1].str().c_str());
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
                *globalStrW += L' ';
            else if (a1 == 0 && a2_next == a2 + 1 && a2 != n_moras)
                *globalStrW += L"↓";
            else if (a3 == 1 && a2_next == 1)
                *globalStrW += L"↑";
        }
        if (i < marks.size())
        {
            auto mark = std::regex_replace(marks[i++], std::wregex(L" "), L"");
            *globalStrW += mark;
        }
    }
    delete ojt;
    return globalStrW->c_str();
}

const char* extractFullContext(const char* input)
{
    if (!ojtins)
	    return nullptr;
    if (!globalStrW)
        globalStrW = new std::wstring;
    if (!globalStr)
        globalStr = new std::string;
    globalStrW->clear();
    const auto out = extract_fullcontext(*ojtins, input);
    for (const auto& ph : out)
    {
	    *globalStrW += ph;
        *globalStrW += L"\n";
    }
    *globalStr = to_byte_string(*globalStrW);
    return globalStr->c_str();
}

const char* getKana(const char* input)
{
    if (!ojtins)
        return nullptr;
    if (!globalStr)
        globalStr = new std::string;
    globalStr->clear();
    const std::wregex _marks(L"[^A-Za-z\\d\u3005\u3040-\u30ff\u4e00-\u9fff\uff11-\uff19\uff21-\uff3a\uff41-\uff5a\uff66-\uff9d]+");
    const std::wregex _sentence(L"[A-Za-z\\d\u3005\u3040-\u30ff\u4e00-\u9fff\uff11-\uff19\uff21-\uff3a\uff41-\uff5a\uff66-\uff9d]+");
    const auto inputTxt = to_wide_string(input);
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
                *globalStr += std::regex_replace(it.str, std::regex("’"), "");
            }
            else
            {
                *globalStr += std::regex_replace(it.pron, std::regex("’"), "");
            }
        }
        ojtins->refresh();
        if (i < marks.size())
        {
            *globalStr += to_byte_string(marks[i++]);
        }
    }
    return globalStr->c_str();
}

const char* getPhoneme(const char* input)
{
    if (!ojtins)
        return nullptr;
    if (!globalStrW)
        globalStrW = new std::wstring;
    if (!globalStr)
        globalStr = new std::string;
    globalStrW->clear();

    const std::wregex _marks(L"[^A-Za-z\\d\u3005\u3040-\u30ff\u4e00-\u9fff\uff11-\uff19\uff21-\uff3a\uff41-\uff5a\uff66-\uff9d]+");
    const std::wregex _sentence(L"[A-Za-z\\d\u3005\u3040-\u30ff\u4e00-\u9fff\uff11-\uff19\uff21-\uff3a\uff41-\uff5a\uff66-\uff9d]+");
    const std::wregex ph(L"\\-([^\\+]*)\\+");

    const auto inputTxt = to_wide_string(input);
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
    *globalStr = to_byte_string(*globalStrW);
    return globalStr->c_str();
}

const char* getRomaji(const char* input)
{
    if (!ojtins)
        return nullptr;
    if (!globalStrW)
        globalStrW = new std::wstring;
    if (!globalStr)
        globalStr = new std::string;
    globalStrW->clear();

    const std::wregex _marks(L"[^A-Za-z\\d\u3005\u3040-\u30ff\u4e00-\u9fff\uff11-\uff19\uff21-\uff3a\uff41-\uff5a\uff66-\uff9d]+");
    const std::wregex _sentence(L"[A-Za-z\\d\u3005\u3040-\u30ff\u4e00-\u9fff\uff11-\uff19\uff21-\uff3a\uff41-\uff5a\uff66-\uff9d]+");
    const std::wregex ph(L"\\-([^\\+]*)\\+");

    const auto inputTxt = to_wide_string(input);
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
    *globalStr = to_byte_string(*globalStrW);
    return globalStr->c_str();
}

const char* getIpa1(const char* input)
{
    if (!ojtins)
        return nullptr;
    if (!globalStrW)
        globalStrW = new std::wstring;
    if (!globalStr)
        globalStr = new std::string;
    globalStrW->clear();

    const std::wregex _marks(L"[^A-Za-z\\d\u3005\u3040-\u30ff\u4e00-\u9fff\uff11-\uff19\uff21-\uff3a\uff41-\uff5a\uff66-\uff9d]+");
    const std::wregex _sentence(L"[A-Za-z\\d\u3005\u3040-\u30ff\u4e00-\u9fff\uff11-\uff19\uff21-\uff3a\uff41-\uff5a\uff66-\uff9d]+");
    const auto inputTxt = to_wide_string(input);
    std::vector<std::wstring> sentences;
    std::vector<std::wstring> marks;
    divide(inputTxt, sentences, _sentence);
    divide(inputTxt, marks, _marks);
    size_t i = 0;
    for (const auto& ita : sentences)
    {
        std::wstring tmpStr;
        getSPhoneme(tmpStr, ojtins, ita);
        getIpaStr1(tmpStr);
        *globalStrW += tmpStr;
        if (i < marks.size())
            *globalStrW += marks[i++];
    }
    *globalStr = to_byte_string(*globalStrW);
    return globalStr->c_str();
}

const char* getIpa2(const char* input)
{
    if (!ojtins)
        return nullptr;
    if (!globalStrW)
        globalStrW = new std::wstring;
    if (!globalStr)
        globalStr = new std::string;
    globalStrW->clear();

    const std::wregex _marks(L"[^A-Za-z\\d\u3005\u3040-\u30ff\u4e00-\u9fff\uff11-\uff19\uff21-\uff3a\uff41-\uff5a\uff66-\uff9d]+");
    const std::wregex _sentence(L"[A-Za-z\\d\u3005\u3040-\u30ff\u4e00-\u9fff\uff11-\uff19\uff21-\uff3a\uff41-\uff5a\uff66-\uff9d]+");
    const auto inputTxt = to_wide_string(input);
    std::vector<std::wstring> sentences;
    std::vector<std::wstring> marks;
    divide(inputTxt, sentences, _sentence);
    divide(inputTxt, marks, _marks);
    size_t i = 0;
    for (const auto& ita : sentences)
    {
        std::wstring tmpStr;
        getSPhoneme(tmpStr, ojtins, ita);
        getIpaStr2(tmpStr);
        *globalStrW += tmpStr;
        if (i < marks.size())
            *globalStrW += marks[i++];
    }
    *globalStr = to_byte_string(*globalStrW);
    return globalStr->c_str();
}

const char* getIpa1WithBlank(const char* input)
{
    if (!ojtins)
        return nullptr;
    if (!globalStrW)
        globalStrW = new std::wstring;
    if (!globalStr)
        globalStr = new std::string;
    globalStrW->clear();

    const std::wregex _marks(L"[^A-Za-z\\d\u3005\u3040-\u30ff\u4e00-\u9fff\uff11-\uff19\uff21-\uff3a\uff41-\uff5a\uff66-\uff9d]+");
    const std::wregex _sentence(L"[A-Za-z\\d\u3005\u3040-\u30ff\u4e00-\u9fff\uff11-\uff19\uff21-\uff3a\uff41-\uff5a\uff66-\uff9d]+");
    const auto inputTxt = to_wide_string(input);
    std::vector<std::wstring> sentences;
    std::vector<std::wstring> marks;
    divide(inputTxt, sentences, _sentence);
    divide(inputTxt, marks, _marks);
    size_t i = 0;
    const std::wregex blankPos(L"([aiueo↓↑AIUEOQN])([AIUEOaiueoʦʃʧbcdfghjklmnpqrstvwxyzQ])");
    for (const auto& ita : sentences)
    {
        std::wstring tmpStr;
        getSPhoneme(tmpStr, ojtins, ita);
        while (std::regex_search(tmpStr, blankPos))
            tmpStr = std::regex_replace(tmpStr, blankPos, L"$1 $2");
        getIpaStr1(tmpStr);
        *globalStrW += tmpStr;
        if (i < marks.size())
            *globalStrW += marks[i++];
    }
    *globalStr = to_byte_string(*globalStrW);
    return globalStr->c_str();
}

const char* getIpa2WithBlank(const char* input)
{
    if (!ojtins)
        return nullptr;
    if (!globalStrW)
        globalStrW = new std::wstring;
    if (!globalStr)
        globalStr = new std::string;
    globalStrW->clear();

    const std::wregex _marks(L"[^A-Za-z\\d\u3005\u3040-\u30ff\u4e00-\u9fff\uff11-\uff19\uff21-\uff3a\uff41-\uff5a\uff66-\uff9d]+");
    const std::wregex _sentence(L"[A-Za-z\\d\u3005\u3040-\u30ff\u4e00-\u9fff\uff11-\uff19\uff21-\uff3a\uff41-\uff5a\uff66-\uff9d]+");
    const auto inputTxt = to_wide_string(input);
    std::vector<std::wstring> sentences;
    std::vector<std::wstring> marks;
    divide(inputTxt, sentences, _sentence);
    divide(inputTxt, marks, _marks);
    size_t i = 0;
    const std::wregex blankPos(L"([aiueo↓↑AIUEOQN])([AIUEOaiueoʦʃʧbcdfghjklmnpqrstvwxyzQ])");
    for (const auto& ita : sentences)
    {
        std::wstring tmpStr;
        getSPhoneme(tmpStr, ojtins, ita);
        while (std::regex_search(tmpStr, blankPos))
            tmpStr = std::regex_replace(tmpStr, blankPos, L"$1 $2");
        getIpaStr2(tmpStr);
        *globalStrW += tmpStr;
        if (i < marks.size())
            *globalStrW += marks[i++];
    }
    *globalStr = to_byte_string(*globalStrW);
    return globalStr->c_str();
}

const char* getPhonemeWithBlank(const char* input)
{
    if (!ojtins)
        return nullptr;
    if (!globalStrW)
        globalStrW = new std::wstring;
    if (!globalStr)
        globalStr = new std::string;
    globalStrW->clear();

    const std::wregex _marks(L"[^A-Za-z\\d\u3005\u3040-\u30ff\u4e00-\u9fff\uff11-\uff19\uff21-\uff3a\uff41-\uff5a\uff66-\uff9d]+");
    const std::wregex _sentence(L"[A-Za-z\\d\u3005\u3040-\u30ff\u4e00-\u9fff\uff11-\uff19\uff21-\uff3a\uff41-\uff5a\uff66-\uff9d]+");
    const std::wregex ph(L"\\-([^\\+]*)\\+");

    const auto inputTxt = to_wide_string(input);
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
    *globalStr = to_byte_string(*globalStrW);
    return globalStr->c_str();
}

const char* getRomajiWithBlank(const char* input)
{
    if (!ojtins)
        return nullptr;
    if (!globalStrW)
        globalStrW = new std::wstring;
    if (!globalStr)
        globalStr = new std::string;
    globalStrW->clear();

    const std::wregex _marks(L"[^A-Za-z\\d\u3005\u3040-\u30ff\u4e00-\u9fff\uff11-\uff19\uff21-\uff3a\uff41-\uff5a\uff66-\uff9d]+");
    const std::wregex _sentence(L"[A-Za-z\\d\u3005\u3040-\u30ff\u4e00-\u9fff\uff11-\uff19\uff21-\uff3a\uff41-\uff5a\uff66-\uff9d]+");
    const std::wregex ph(L"\\-([^\\+]*)\\+");

    const auto inputTxt = to_wide_string(input);
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
    *globalStr = to_byte_string(*globalStrW);
    return globalStr->c_str();
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        globalStr = new std::string;
        globalStrW = new std::wstring;
        break;
    case DLL_THREAD_ATTACH:
        if (!globalStr)
            globalStr = new std::string;
        if (!globalStrW)
            globalStrW = new std::wstring;
        break;
    case DLL_THREAD_DETACH:
        Release();
        break;
    case DLL_PROCESS_DETACH:
        if (lpReserved != nullptr)
            break;
        Release();
        break;
    }
    return TRUE;
}

