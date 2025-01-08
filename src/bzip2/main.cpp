module;
#include "bzlib.h"
#include <common.hpp>
module ace.bzip2;

namespace ace::bzip2 {

void test()
{
  const auto src = read_file<char>("test.xml");

  std::vector<char> tmp;
  tmp.resize(std::max(src.size(), std::size_t{ 900 * 1'024 }));

  auto size = static_cast<unsigned int>(tmp.size());
  auto status = BZ2_bzBuffToBuffCompress(
    tmp.data(), &size, const_cast<char*>(src.data()), static_cast<unsigned int>(src.size()), 9, 0, 0);
  if (status != BZ_OK) {
    throw error{ "Could not compress data." };
  }
  tmp.resize(size);

  std::vector<char> dst;
  dst.resize(src.size());
  size = static_cast<unsigned int>(dst.size());
  status = BZ2_bzBuffToBuffDecompress(
    dst.data(), &size, tmp.data(), static_cast<unsigned int>(tmp.size()), 0, 0);
  if (status != BZ_OK) {
    throw error{ "Could not decompress data." };
  }
  dst.resize(size);

  if (src != dst) {
    throw error{ "Roundtrip failed." };
  }
}

}  // namespace ace::bzip2
