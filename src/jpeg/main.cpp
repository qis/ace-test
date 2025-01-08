module;
// clang-format off
#include <stdio.h>
#include <jpeglib.h>
// clang-format on
#include <common.hpp>
module ace.jpeg;

namespace ace::jpeg {

void test()
{
  const auto file = open("test.jpg");

  jpeg_error_mgr jerr{};
  jpeg_decompress_struct cinfo{};
  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_decompress(&cinfo);
  jpeg_stdio_src(&cinfo, file.get());
  jpeg_read_header(&cinfo, TRUE);
  jpeg_start_decompress(&cinfo);

  const auto se = on_scope_exit([&]() {
    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
  });

  const auto cx = cinfo.output_width;
  const auto cy = cinfo.output_height;
  if (cx != 800 || cy != 800) {
    throw error{ "Unexpected image size: {}x{}", cx, cy };
  }
  if (cinfo.output_components != 3) {
    throw error{ "Unexpected number of color components: {}", cinfo.output_components };
  }

  const auto stride = cinfo.output_width * cinfo.output_components;
  JSAMPARRAY buffer =
    (*cinfo.mem->alloc_sarray)(reinterpret_cast<j_common_ptr>(&cinfo), JPOOL_IMAGE, stride, 1);

  auto y = 0u;
  while (cinfo.output_scanline < cinfo.output_height) {
    std::memset(buffer[0], 0, stride);
    jpeg_read_scanlines(&cinfo, buffer, 1);
    for (auto x = 0u; x < cx; x++) {
      const auto p = buffer[0] + x * 3;
      if ((static_cast<unsigned>(p[0]) << 16) + (static_cast<unsigned>(p[1]) << 8) + p[2] == 0) {
        throw error{ "Unexpected black pixel at: {}:{}", x, y };
      }
    }
    y++;
  }
}

}  // namespace ace::jpeg
