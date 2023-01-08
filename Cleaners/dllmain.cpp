
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

std::vector<char*> extract_fullcontext(openjtalk& ojt, const char* text, bool run_marine = false)
{
    ojt.run_frontend(text);
    return ojt.make_label();
}

std::vector<char*> openjtalk::make_label() const
{
    //feature2njd(njd, njd_features);
    njd2jpcommon(jpcommon, njd);
    JPCommon_make_label(jpcommon);
    const int label_size = JPCommon_get_label_size(jpcommon);
    char** label_feature = JPCommon_get_label_feature(jpcommon);
    std::vector<char*> labels;
    for (int i = 0; i < label_size; i++)
        labels.push_back(label_feature[i]);
    JPCommon_refresh(jpcommon);
    NJD_refresh(njd);
    return labels;
}

void divide(const std::wstring& s, std::vector<std::wstring>& v, const std::wregex& reg)
{
    std::wsmatch mResult;
    if (regex_search(s, mResult, reg)) {
        v.emplace_back(std::wstring(mResult[0].first, mResult[0].second));
        divide(std::wstring(mResult[0].second, s.end()), v, reg);
    }
}

const wchar_t* JapaneseCleaner(const wchar_t* input)
{
    std::vector<std::wstring> sentences;
    std::vector<std::wstring> marks;
    const std::wstring wstr(input);
    const std::wregex _characters(L"[A-Za-z\\d\u3005\u3040-\u30ff\u4e00-\u9fff\uff11-\uff19\uff21-\uff3a\uff41-\uff5a\uff66-\uff9d]");
    const std::wregex _marks(L"[^A-Za-z\\d\u3005\u3040-\u30ff\u4e00-\u9fff\uff11-\uff19\uff21-\uff3a\uff41-\uff5a\uff66-\uff9d]+");
    const std::wregex _sentence(L"[A-Za-z\\d\u3005\u3040-\u30ff\u4e00-\u9fff\uff11-\uff19\uff21-\uff3a\uff41-\uff5a\uff66-\uff9d]+");
    std::regex ph("\\-([^\\+]*)\\+");
    std::regex nm("/F:(\\d+)_");
    std::regex a11("/A:(\\-?[0-9]+)\\+");
    std::regex a22("\\+(\\d+)\\+");
    std::regex a33("\\+(\\d+)/");
    divide(wstr, sentences, _sentence);
    divide(wstr, marks, _marks);
    const auto ojt = new openjtalk();
    std::string text;
    size_t i = 0;
    for (const auto & asentence : sentences)
    {
        auto labels = extract_fullcontext(*ojt, to_byte_string(asentence).c_str());
        for (size_t it = 0; it < labels.size(); ++it)
        {
            std::smatch mResult;
            std::string te(labels[it]);
            std::regex_search(te, mResult, ph);
            std::string phoneme = mResult[1].str();
            if (phoneme == "sil" || phoneme == "pau")
                continue;
            else
            {
                phoneme = std::regex_replace(phoneme, std::regex("ch"), "\xCA\xA6");
                phoneme = std::regex_replace(phoneme, std::regex("sh"), "\xCA\x83");
                phoneme = std::regex_replace(phoneme, std::regex("cl"), "Q");
                phoneme = std::regex_replace(phoneme, std::regex("ts"), "\xCA\xA6");
	            text += phoneme;
            }
            std::regex_search(te, mResult, nm);
            auto n_moras = atoi(mResult[1].str().c_str());
            std::regex_search(te, mResult, a11);
            auto a1 = atoi(mResult[1].str().c_str());
            std::regex_search(te, mResult, a22);
            auto a2 = atoi(mResult[1].str().c_str());
            std::regex_search(te, mResult, a33);
            auto a3 = atoi(mResult[1].str().c_str());
            std::string ne(labels[it + 1]);
            std::regex_search(ne, mResult, ph);
            std::string nephoneme = mResult[1].str();
            int a2_next;
            if (nephoneme == "sil" || nephoneme == "pau")
            	a2_next = -1;
            else
            {
                std::regex_search(ne, mResult, a22);
                a2_next = atoi(mResult[1].str().c_str());
            }
            if (a3 == 1 && a2_next == 1)
                text += ' ';
            else if (a1 == 0 && a2_next == a2 + 1 && a2 != n_moras)
                text += "#";
            else if (a3 == 1 && a2_next == 1)
                text += "`";
        }
        if (i < marks.size())
        {
            auto mark = std::regex_replace(to_byte_string(marks[i++]), std::regex(" "), "");
	        text += mark;
        }
    }
    delete ojt;
    return to_wide_string(text).c_str();
}

void Release()
{
    delete globalStr;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

