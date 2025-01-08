#pragma once
#include <format>
#include <stdexcept>
#include <string>

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
