#pragma once
#include <format>
#include <stdexcept>
#include <string>

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

namespace ace {

class error : public std::runtime_error {
public:
  error(const std::string& message) :
    std::runtime_error(message)
  {}

  template <class Arg, class... Args>
  error(const std::format_string<Arg, Args...> fmt, Arg&& arg, Args&&... args) :
    std::runtime_error(std::vformat(fmt.get(), std::make_format_args(arg, args...)))
  {}
};

}  // namespace ace
