module;
// clang-format off
#include <lunasvg.h>
// clang-format on
#include <common.hpp>
module ace.svg;

namespace ace::svg {

void test()
{
  auto document = lunasvg::Document::loadFromFile("test.svg");
  if (!document) {
    throw error{ "Could not load file: test.svg" };
  }
  auto bitmap = document->renderToBitmap(400, 400, 0x00000000);
  if (!bitmap.valid()) {
    throw error{ "Could not render vector graphic." };
  }
  if (bitmap.stride() != 400 * 4) {
    throw error{ "Unexpected stride." };
  }
  bitmap.convertToRGBA();
  const auto get = [&bitmap](std::size_t x, std::size_t y) -> std::uint32_t {
    return *reinterpret_cast<const std::uint32_t*>(bitmap.data() + y * 400 * 4 + x * 4);
  };
  if (get(0, 0)) {
    throw error{ "Unexpected color pixel at: 0:0" };
  }
  if (!get(200, 200)) {
    throw error{ "Unexpected transparent pixel at: 200:200" };
  }
}

}  // namespace ace::svg
