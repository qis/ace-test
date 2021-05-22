#include <library.hpp>
#include <exception>
#include <stdexcept>
#include <string>

#if !defined(__clang__) || defined(__cpp_exceptions)
#  define LLVM_EXCEPTIONS_ENABLED 1
#else
#  define LLVM_EXCEPTIONS_ENABLED 0
#endif


int main(int argc, char* argv[])
{
#if LLVM_EXCEPTIONS_ENABLED
  try {
    throw std::runtime_error(std::to_string(argc));
  }
  catch (const std::exception& e) {
    std::puts(e.what());
  }
#endif
  std::puts(library::test().data());
}
