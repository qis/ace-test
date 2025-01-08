#pragma once
#include "error.hpp"
#include <fstream>
#include <string>
#include <vector>

namespace ace {

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

}  // namespace ace
