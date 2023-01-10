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

ccdllexport void CreateOjt(const char* folder);
ccdllexport const char* extractFullContext(const char* text);
ccdllexport void ReleaseOjt();

class openjtalk
{
public:
    openjtalk();
    openjtalk(const char*);
    ~openjtalk()
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
    void run_frontend(const char*) const;
    openjtalk(const openjtalk&) = delete;
    openjtalk(openjtalk&&) = delete;
    openjtalk operator=(const openjtalk&) = delete;
    openjtalk operator = (openjtalk&&) = delete;
    std::vector<char*> make_label() const;
private:
    Mecab* mecab = nullptr;
    NJD* njd = nullptr;
    JPCommon* jpcommon = nullptr;
};