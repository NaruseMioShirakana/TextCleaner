#pragma once
#include <string>
#include <thread>
#include <vector>
#include "openjtalk/open_jtalk-1.11/src/mecab/src/mecab.h"
#include "openjtalk/open_jtalk-1.11/src/njd/njd.h"
#include "openjtalk/open_jtalk-1.11/src/jpcommon/jpcommon.h"
#define ccdllexport extern "C" __declspec(dllexport)

class ThreadBoundData
{
public:
    ThreadBoundData() = default;
    ~ThreadBoundData() = default;

    //获取当前调用线程绑定的string
    std::wstring& get() {
        //确定当前线程是否已存在新的string绑定：
        bool isExisted = false;
        for (auto& item : _data) {
            //若存在新绑定赋给curStr：
            if (item.tid == std::this_thread::get_id()) {
                curStr = &(item.data);
                isExisted = true;
                break;
            }
        }
        //如当前线程未存在新绑定，则绑定：
        if (!isExisted) {
            Data temp;
            temp.tid = std::this_thread::get_id();
            temp.data = L"";
            _data.push_back(temp);
            curStr = &(_data.back().data);
        }
        return *curStr;
    }

    void refresh() {
        for (size_t i = 0; i < _data.size(); ++i)
            if (std::this_thread::get_id() == _data[i].tid)
                _data.erase(_data.begin() + int64_t(i));
    }

private:
    struct Data {
        std::wstring data;
        std::thread::id tid;
    };
    std::vector<Data> _data;
    std::wstring* curStr = nullptr;
};

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

ccdllexport const wchar_t* PluginMain(const wchar_t*);

ccdllexport void CreateOjt(const wchar_t*);

ccdllexport void Release();

/*
ccdllexport const wchar_t* extractFullContext(const wchar_t*);

ccdllexport const wchar_t* getKana(const wchar_t*);

ccdllexport const wchar_t* getPhoneme(const wchar_t*);

ccdllexport const wchar_t* getRomaji(const wchar_t*);

ccdllexport const wchar_t* getIpa1(const wchar_t*);

ccdllexport const wchar_t* getIpa2(const wchar_t*);

ccdllexport const wchar_t* getPhonemeWithBlank(const wchar_t*);

ccdllexport const wchar_t* getRomajiWithBlank(const wchar_t*);

ccdllexport const wchar_t* getIpa1WithBlank(const wchar_t*);

ccdllexport const wchar_t* getIpa2WithBlank(const wchar_t*);

ccdllexport const wchar_t* ChineseToJapanese(const wchar_t* input);

ccdllexport const wchar_t* JapaneseToChinese(const wchar_t* input);
 */
