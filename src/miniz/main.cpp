module;
// clang-format off
#include <miniz.h>
// clang-format on
#include <common.hpp>
module ace.miniz;

namespace ace::miniz {

void test()
{
  const auto src = read_file<unsigned char>("test.xml");

  auto size = compressBound(src.size());

  std::vector<unsigned char> tmp;
  tmp.resize(size);
  if (compress(tmp.data(), &size, src.data(), src.size()) != Z_OK) {
    throw error{ "Could not compress data." };
  }
  tmp.resize(size);

  std::vector<unsigned char> dst;
  dst.resize(src.size());
  size = static_cast<decltype(size)>(dst.size());
  if (uncompress(dst.data(), &size, tmp.data(), tmp.size()) != Z_OK) {
    throw error{ "Could not uncompress data." };
  }
  dst.resize(size);

  if (src != dst) {
    throw error{ "Roundtrip failed." };
  }
}

}  // namespace ace::miniz
