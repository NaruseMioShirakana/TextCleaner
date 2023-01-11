#pragma once
#include <string>
#include <vector>
#include "openjtalk/open_jtalk-1.11/src/mecab/src/mecab.h"
#include "openjtalk/open_jtalk-1.11/src/njd/njd.h"
#include "openjtalk/open_jtalk-1.11/src/jpcommon/jpcommon.h"
#define ccdllexport extern "C" __declspec(dllexport)
inline std::wstring* globalStrW = nullptr;
inline std::string* globalStr = nullptr;
inline std::string Folder;

struct NjdFeature
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
    NjdFeature(NJDNode* node);
};

ccdllexport const wchar_t* PluginMain(const wchar_t*);

ccdllexport void CreateOjt(const char*);

ccdllexport const char* extractFullContext(const char*);

ccdllexport const char* getKana(const char*);

ccdllexport const char* getPhoneme(const char*);

ccdllexport const char* getRomaji(const char*);

ccdllexport const char* getIpa1(const char*);

ccdllexport const char* getIpa2(const char*);

ccdllexport const char* getPhonemeWithBlank(const char*);

ccdllexport const char* getRomajiWithBlank(const char*);

ccdllexport const char* getIpa1WithBlank(const char*);

ccdllexport const char* getIpa2WithBlank(const char*);

ccdllexport void Release();

class openjtalk
{
public:
    openjtalk();
    openjtalk(const char*);
    ~openjtalk();
    void run_frontend(const char*) const;
    openjtalk(const openjtalk&) = delete;
    openjtalk(openjtalk&&) = delete;
    openjtalk operator=(const openjtalk&) = delete;
    openjtalk operator = (openjtalk&&) = delete;
    [[nodiscard]] std::vector<std::wstring> make_label() const;
    [[nodiscard]] std::vector<NjdFeature> getfeature() const;
    void refresh() const
    {
        NJD_refresh(njd);
        Mecab_refresh(mecab);
        JPCommon_refresh(jpcommon);
    }
private:
    Mecab* mecab = nullptr;
    NJD* njd = nullptr;
    JPCommon* jpcommon = nullptr;
};