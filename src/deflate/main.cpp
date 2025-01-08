module;
#include "libdeflate.h"
#include <common.hpp>
#include <memory>
module ace.deflate;

namespace ace::deflate {

void test()
{
  const auto src = read_file<char>("test.xml");

  std::unique_ptr<libdeflate_compressor, decltype(&libdeflate_free_compressor)> compressor{
    libdeflate_alloc_compressor(9),
    libdeflate_free_compressor,
  };
  if (!compressor) {
    throw error{ "Could not create compressor." };
  }

  std::vector<char> tmp;
  tmp.resize(libdeflate_deflate_compress_bound(compressor.get(), src.size()));
  auto size =
    libdeflate_deflate_compress(compressor.get(), src.data(), src.size(), tmp.data(), tmp.size());
  if (!size) {
    throw error{ "Could not compress data." };
  }
  tmp.resize(size);

  std::unique_ptr<libdeflate_decompressor, decltype(&libdeflate_free_decompressor)> decompressor{
    libdeflate_alloc_decompressor(),
    libdeflate_free_decompressor,
  };
  if (!decompressor) {
    throw error{ "Could not create decompressor." };
  }

  std::vector<char> dst;
  dst.resize(src.size());
  const auto result = libdeflate_deflate_decompress(
    decompressor.get(), tmp.data(), tmp.size(), dst.data(), dst.size(), &size);
  if (result != LIBDEFLATE_SUCCESS) {
    throw error{ "Could not decompress data." };
  }
  dst.resize(size);

  if (src != dst) {
    throw error{ "Roundtrip failed." };
  }
}

}  // namespace ace::deflate
