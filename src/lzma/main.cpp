module;
#include "lzma.h"
#include <common.hpp>
module ace.lzma;

namespace ace::lzma {

void test()
{
  const auto src = read_file<uint8_t>("test.xml");

  lzma_stream strm = LZMA_STREAM_INIT;
  if (lzma_easy_encoder(&strm, 9, LZMA_CHECK_CRC64) != LZMA_OK) {
    throw error{ "Could not initialize encoder." };
  }

  strm.next_in = src.data();
  strm.avail_in = src.size();

  std::vector<uint8_t> tmp;
  tmp.resize(lzma_stream_buffer_bound(src.size()));

  strm.next_out = tmp.data();
  strm.avail_out = tmp.size();

  auto status = lzma_code(&strm, LZMA_FINISH);
  lzma_end(&strm);
  if (status != LZMA_STREAM_END) {
    throw error{ "Could not encode data." };
  }
  tmp.resize(strm.total_out);

  strm = LZMA_STREAM_INIT;
  if (lzma_auto_decoder(&strm, UINT64_MAX, LZMA_FAIL_FAST) != LZMA_OK) {
    throw error{ "Could not initialize decoder." };
  }

  strm.next_in = tmp.data();
  strm.avail_in = tmp.size();

  std::vector<uint8_t> dst;
  dst.resize(src.size());

  strm.next_out = dst.data();
  strm.avail_out = dst.size();

  status = lzma_code(&strm, LZMA_FINISH);
  lzma_end(&strm);
  if (status != LZMA_STREAM_END) {
    throw std::runtime_error{ "Could not decode data." };
  }
  dst.resize(strm.total_out);

  if (src != dst) {
    throw error{ "Roundtrip failed." };
  }
}

}  // namespace ace::lzma
