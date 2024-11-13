#pragma once

#define _DLLEXPORT extern "C" __declspec(dllexport)

class Interface;

_DLLEXPORT void* CreateInstance(const wchar_t* /* const void* */ UserParameter);
_DLLEXPORT void DestoryInstance(void* _Instance);

// Return: [Pointer of struct { wchar_t Phoneme[8]; int64_t Tone; }] (Array Of<Phoneme, Tone>), Dll Should Keep The Memory
_DLLEXPORT void* Convert(void* _Instance, const wchar_t* InputText, const char* LanguageID, const void* UserParameter);

// Optional
_DLLEXPORT void* GetExtraInfo(void* _Instance);