module;
#include "zlib.h"
#include <common.hpp>
module ace.zlib;

namespace ace::zlib {

void test()
{
  const auto src = read_file<Bytef>("test.xml");

  std::vector<Bytef> tmp;
  tmp.resize(static_cast<std::size_t>(compressBound(static_cast<uLong>(src.size()))));

  z_stream strm{};
  strm.avail_in = static_cast<uInt>(src.size());
  strm.next_in = const_cast<Bytef*>(src.data());
  strm.avail_out = static_cast<uInt>(tmp.size());
  strm.next_out = tmp.data();

  if (deflateInit(&strm, Z_BEST_COMPRESSION) != Z_OK) {
    throw error{ "Could not initialize deflate stream." };
  }

  auto status = deflate(&strm, Z_FINISH);
  deflateEnd(&strm);

  if (status != Z_STREAM_END) {
    throw error{ "Could not deflate data." };
  }

  tmp.resize(static_cast<std::size_t>(strm.total_out));

  std::vector<Bytef> dst;
  dst.resize(src.size());

  strm = {};
  strm.avail_in = static_cast<uInt>(tmp.size());
  strm.next_in = tmp.data();
  strm.avail_out = static_cast<uInt>(dst.size());
  strm.next_out = dst.data();

  if (inflateInit(&strm) != Z_OK) {
    throw error{ "Could not initialize inflate stream." };
  }

  status = inflate(&strm, Z_NO_FLUSH);
  inflateEnd(&strm);

  if (status != Z_STREAM_END) {
    throw error{ "Could not inflate data." };
  }

  dst.resize(static_cast<std::size_t>(strm.total_out));

  if (src != dst) {
    throw error{ "Roundtrip failed." };
  }
}

}  // namespace ace::zlib
