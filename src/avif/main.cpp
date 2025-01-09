module;
// clang-format off
#include <avif/avif.h>
// clang-format on
#include <common.hpp>
module ace.avif;

namespace ace::avif {

void test()
{
  // https://youtu.be/UaIOYh8srvE
  // https://docs.krita.org/en/general_concepts/colors/color_managed_workflow.html
  // https://registry.khronos.org/vulkan/specs/latest/man/html/VkColorSpaceKHR.html
  // main.kra: 16-bit (float) Rec2020-elle-V4-g10.icc
  // main.avif: 12-bit
  // * Chroma: 444
  // * Quality: Lossless
  // * Color Space: Rec 2100 PQ
  const auto src = read_file<std::uint8_t>("test.avif");

  std::unique_ptr<avifDecoder, decltype(&avifDecoderDestroy)> decoder{
    avifDecoderCreate(),
    avifDecoderDestroy,
  };
  if (!decoder) {
    throw error{ "Could not create decoder." };
  }
  if (avifDecoderSetIOMemory(decoder.get(), src.data(), src.size()) != AVIF_RESULT_OK) {
    throw error{ "Could not set decoder memory." };
  }
  if (avifDecoderParse(decoder.get()) != AVIF_RESULT_OK) {
    throw error{ "Could not decode image." };
  }
  const auto cx = decoder->image->width;
  const auto cy = decoder->image->height;
  if (cx != 800 || cy != 800) {
    throw error{ "Unexpected image size: {}x{}", cx, cy };
  }
  const auto bd = decoder->image->depth;
  if (bd != 12) {
    throw error{ "Unexpected image bit depth: {}", bd };
  }
  const auto format = decoder->image->yuvFormat;
  if (format != AVIF_PIXEL_FORMAT_YUV444) {
    throw error{ "Unexpected image YUV format: {}", static_cast<int>(format) };
  }
  const auto range = decoder->image->yuvRange;
  if (range != AVIF_RANGE_FULL) {
    throw error{ "Unexpected image YUV range: {}", static_cast<int>(range) };
  }
  const auto color = decoder->image->colorPrimaries;
  if (color != AVIF_COLOR_PRIMARIES_BT2100) {
    throw error{ "Unexpected color primaries: {}", static_cast<int>(color) };
  }
  const auto transfer = decoder->image->transferCharacteristics;
  if (transfer != AVIF_TRANSFER_CHARACTERISTICS_PQ) {
    throw error{ "Unexpected transfer characteristics: {}", static_cast<int>(transfer) };
  }
}

}  // namespace ace::avif
