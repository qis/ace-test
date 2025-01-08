#pragma once
#include "error.hpp"
#include <fstream>
#include <functional>
#include <memory>
#include <span>
#include <string>
#include <string_view>
#include <vector>
#include <cstdio>

namespace ace {

inline std::unique_ptr<FILE, decltype(&fclose)> open(const std::string& filename)
{
  std::unique_ptr<FILE, decltype(&fclose)> file{
    fopen(filename.data(), "rb"),
    fclose,
  };
  if (!file) {
    throw error{ "Could not open file: {}", filename };
  }
  return file;
}

template <class T>
std::vector<T> read_file(const std::string& filename)
{
  static_assert(sizeof(T) == sizeof(char));
  std::ifstream file{ filename, std::ios::ate | std::ios::binary };
  if (!file) {
    throw error{ "Could not open file: {}", filename };
  }
  std::vector<T> data;
  if (const auto size = static_cast<std::size_t>(file.tellg())) {
    data.resize(size);
    if (!file.seekg(0, std::ios::beg)) {
      throw error{ "Could not seek in file: {}", filename };
    }
    if (!file.read(reinterpret_cast<char*>(data.data()), data.size())) {
      throw error{ "Could not read file: {}", filename };
    }
  }
  return data;
}

class scope_exit {
public:
  scope_exit(std::function<void()> call) :
    call_(std::move(call))
  {}

  scope_exit(scope_exit&& other) :
    call_(std::move(other.call_))
  {
    other.call_ = {};
  }

  scope_exit(const scope_exit& other) = delete;

  scope_exit& operator=(scope_exit&& other)
  {
    call_ = std::move(other.call_);
    other.call_ = {};
    return *this;
  }

  scope_exit& operator=(const scope_exit& other) = delete;

  ~scope_exit()
  {
    if (call_) {
      call_();
    }
  }

private:
  std::function<void()> call_;
};

inline scope_exit on_scope_exit(std::function<void()> call)
{
  return { std::move(call) };
}

}  // namespace ace
