#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>
import ace.xml2;
import ace.pugixml;
import ace.zlib;
import ace.bzip2;
import ace.lzma;
import ace.lz4;
import ace.brotli;
import ace.zstd;
import std;

TEST_CASE("xml2")
{
  ace::xml2::test();
}

TEST_CASE("pugixml")
{
  ace::pugixml::test();
}

TEST_CASE("zlib")
{
  ace::zlib::test();
}

TEST_CASE("bzip2")
{
  ace::bzip2::test();
}

TEST_CASE("lzma")
{
  ace::lzma::test();
}

TEST_CASE("lz4")
{
  ace::lz4::test();
}

TEST_CASE("brotli")
{
  ace::brotli::test();
}

TEST_CASE("zstd")
{
  ace::zstd::test();
}

int main(int argc, char* argv[])
{
  doctest::Context context;
  context.applyCommandLine(argc, argv);
  context.setOption("no-intro", 1);
  return context.run();
}
