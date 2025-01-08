#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>
import ace.libxml2;
import ace.pugixml;
import ace.zlib;
import std;

TEST_CASE("libxml2")
{
  ace::libxml2::test();
}

TEST_CASE("pugixml")
{
  ace::pugixml::test();
}

TEST_CASE("zlib")
{
  ace::zlib::test();
}

int main(int argc, char* argv[])
{
  doctest::Context context;
  context.applyCommandLine(argc, argv);
  context.setOption("no-intro", 1);
  return context.run();
}
