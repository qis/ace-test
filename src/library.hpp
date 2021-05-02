#pragma once
#include <string_view>

#ifdef _WIN32
#  define LIBRARY_EXPORT __declspec(dllexport)
#  define LIBRARY_IMPORT __declspec(dllimport)
#else
#  define LIBRARY_EXPORT __attribute__((__visibility__("default")))
#  define LIBRARY_IMPORT
#endif

#ifdef LIBRARY_SHARED
#  ifdef LIBRARY_EXPORTS
#    define LIBRARY_API LIBRARY_EXPORT
#  else
#    define LIBRARY_API LIBRARY_IMPORT
#  endif
#else
#  define LIBRARY_API
#endif

#if !defined(__clang__) || defined(__cpp_exceptions)
#  define LIBRARY_EXCEPTIONS 1
#else
#  define LIBRARY_EXCEPTIONS 0
#endif

namespace library {

LIBRARY_API std::string_view test() noexcept;

}  // namespace library
