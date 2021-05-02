#include <doctest/doctest.h>
#include <library.hpp>

TEST_CASE("library")
{
  CHECK(library::test().size() == 4);
}
