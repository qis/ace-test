module;
#include "libxml/parser.h"
#include <error.hpp>
#include <memory>
module ace.xml2;

namespace ace::xml2 {

void test()
{
  const auto filename = "test.xml";
  std::unique_ptr<xmlDoc, decltype(&xmlFreeDoc)> doc{
    xmlReadFile(filename, nullptr, XML_PARSE_NONET),
    xmlFreeDoc,
  };
  if (!doc) {
    throw error{ "Could not parse XML file: {}", filename };
  }
}

}  // namespace ace::xml2