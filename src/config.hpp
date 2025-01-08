#pragma once
#ifdef ACE_EXPORT
#ifdef _WIN32
#define ACE_API __declspec(dllexport)
#else
#define ACE_API __attribute__((__visibility__("default")))
#endif
#else
#ifdef _WIN32
#define ACE_API __declspec(dllimport)
#else
#define ACE_API
#endif
#endif
