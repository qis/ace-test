module;
#include "pugixml.hpp"
#include <common.hpp>
#include <string_view>
module ace.pugixml;

namespace ace::pugixml {

void test()
{
  pugi::xml_document doc;
  const auto filename = "test.xml";
  if (const auto result = doc.load_file(filename); !result) {
    throw error{ "Could not parse XML file: {}\nError: {}", filename, result.description() };
  }
  if (const auto value = doc.child("main").attribute("type").value(); !value) {
    throw error{ "Missing XML main > type property value." };
  } else if (std::string_view{ value } != "success") {
    throw error{ "Unexpected XML main > type property value: {}", value };
  }
}

}  // namespace ace::pugixml
