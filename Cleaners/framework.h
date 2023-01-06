#pragma once
#include <list>
#include <string>
#include <vector>

#include "openjtalk/open_jtalk-1.11/src/mecab/src/mecab.h"
#include "openjtalk/open_jtalk-1.11/src/njd/njd.h"
#include "openjtalk\\open_jtalk-1.11\\src\\jpcommon\\jpcommon.h"
#define ccdllexport extern "C" __declspec(dllexport)
inline std::wstring* globalStr;

ccdllexport const wchar_t* JapaneseCleaner(const wchar_t* input);
ccdllexport void Release();

struct node2feature
{
    const char* str;
    const char* pos;
    const char* pos_group1;
    const char* pos_group2;
    const char* pos_group3;
    const char* ctype;
    const char* cform;
    const char* orig;
    const char* read;
    const char* pron;
    int acc;
    int mora_size;
    const char* chain_rule;
    int chain_flag;
    node2feature(NJDNode* node);
};

class openjtalk
{
public:
    openjtalk();
    ~openjtalk()
    {
        Mecab_clear(mecab);
        NJD_clear(njd);
        JPCommon_clear(jpcommon);
        delete mecab;
        delete njd;
        delete jpcommon;
        delete[] data;
        jpcommon = nullptr;
        mecab = nullptr;
        data = nullptr;
        njd = nullptr;
    }
    std::list<node2feature> run_frontend(const char*);
    openjtalk(const openjtalk&) = delete;
    openjtalk(openjtalk&&) = delete;
    openjtalk operator=(const openjtalk&) = delete;
    openjtalk operator = (openjtalk&&) = delete;
    std::vector<char*> make_label(const std::list<node2feature>& njd_features) const;
private:
    Mecab* mecab = nullptr;
    NJD* njd = nullptr;
    JPCommon* jpcommon = nullptr;
    char* data = nullptr;
};