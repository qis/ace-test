module;
#include "brotli/decode.h"
#include "brotli/encode.h"
#include <common.hpp>
module ace.brotli;

namespace ace::brotli {

void test()
{
  const auto src = read_file<uint8_t>("test.xml");

  std::vector<uint8_t> tmp;
  tmp.resize(BrotliEncoderMaxCompressedSize(src.size()));
  auto size = tmp.size();
  auto status = BrotliEncoderCompress(
    BROTLI_MAX_QUALITY,
    BROTLI_DEFAULT_WINDOW,
    BROTLI_MODE_TEXT,
    src.size(),
    src.data(),
    &size,
    tmp.data());
  if (!status) {
    throw std::runtime_error{ "Could not compress data." };
  }
  tmp.resize(size);

  std::vector<uint8_t> dst;
  dst.resize(src.size());
  size = dst.size();
  status = BrotliDecoderDecompress(tmp.size(), tmp.data(), &size, dst.data());
  if (!status) {
    throw std::runtime_error{ "Could not decompress data." };
  }
  dst.resize(size);

  if (src != dst) {
    throw error{ "Roundtrip failed." };
  }
}

}  // namespace ace::brotli
