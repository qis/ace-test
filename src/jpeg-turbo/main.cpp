module;
// clang-format off
#include <turbojpeg.h>
// clang-format on
#include <common.hpp>
module ace.jpeg.turbo;

namespace ace::jpeg::turbo {

void test()
{
  const auto src = read_file<unsigned char>("test.jpg");

  std::shared_ptr<void> handle{
    tj3Init(TJINIT_DECOMPRESS),
    [](auto handle) {
      tj3Destroy(handle);
    }
  };
  if (!handle) {
    throw error{ "Could not initialize decompress handle." };
  }

  if (tj3DecompressHeader(handle.get(), src.data(), src.size())) {
    throw error{ "Could not decompress header." };
  }

  const auto cx = tj3Get(handle.get(), TJPARAM_JPEGWIDTH);
  const auto cy = tj3Get(handle.get(), TJPARAM_JPEGHEIGHT);
  const auto cs = tj3Get(handle.get(), TJPARAM_COLORSPACE);
  if (cx != 800 || cy != 800) {
    throw error{ "Unexpected image size: {}x{}", cx, cy };
  }
  if (cs != TJCS_YCbCr) {
    throw error{ "Unexpected image color space: {}", cs };
  }
  if (tjPixelSize[TJPF_RGB] != 3) {
    throw error{ "Unexpected image format size: {}", tjPixelSize[TJPF_RGB] };
  }

  std::vector<unsigned char> tmp(cx * cy * tjPixelSize[TJPF_RGB], 0u);
  if (tj3Decompress8(handle.get(), src.data(), src.size(), tmp.data(), 0, TJPF_RGB)) {
    throw error{ "Could not decompress image." };
  }
  handle.reset();

  for (auto x = 0u; x < 800u; x++) {
    for (auto y = 0u; y < 800u; y++) {
      const auto p = tmp.data() + y * 800 * 3 + x * 3;
      if ((static_cast<unsigned>(p[0]) << 16) + (static_cast<unsigned>(p[1]) << 8) + p[2] == 0) {
        throw error{ "Unexpected black pixel at: {}:{}", x, y };
      }
    }
  }
}

}  // namespace ace::jpeg::turbo
