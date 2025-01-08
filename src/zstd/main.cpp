module;
#include "zstd.h"
#include <common.hpp>
module ace.zstd;

namespace ace::zstd {

void test()
{
  const auto src = read_file<char>("test.xml");

  std::vector<char> tmp;
  tmp.resize(ZSTD_compressBound(src.size()));
  auto size = ZSTD_compress(tmp.data(), tmp.size(), src.data(), src.size(), ZSTD_maxCLevel());
  if (ZSTD_isError(size)) {
    throw error{ "Could not compress data." };
  }
  tmp.resize(size);

  std::vector<char> dst;
  dst.resize(src.size());
  size = ZSTD_decompress(dst.data(), dst.size(), tmp.data(), tmp.size());
  if (ZSTD_isError(size)) {
    throw error{ "Could not decompress data." };
  }
  dst.resize(size);

  if (src != dst) {
    throw error{ "Roundtrip failed." };
  }
}

}  // namespace ace::zstd
