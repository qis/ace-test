#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>
#include <error.hpp>
#include <filesystem>
#include <string>

#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#include <cstdlib>
#endif

namespace ace {

// http://www.tech.theplayhub.com/finding_current_executables_path_without_procselfexe-7
// =====================================================================================
// Mac OS X: _NSGetExecutablePath() (man 3 dyld)
// Linux: readlink /proc/self/exe
// Solaris: getexecname()
// FreeBSD: sysctl CTL_KERN KERN_PROC KERN_PROC_PATHNAME -1
// FreeBSD if it has procfs: readlink /proc/curproc/file (FreeBSD doesn't have procfs by default)
// NetBSD: readlink /proc/curproc/exe
// DragonFly BSD: readlink /proc/curproc/file
// Windows: GetModuleFileName() with hModule = NULL
std::filesystem::path base()
{
  static const auto path = []() {
    // Get executable file.
    std::string file;
#ifdef _WIN32
    DWORD size = 0;
    const auto instance = GetModuleHandle(nullptr);
    do {
      file.resize(file.size() + MAX_PATH);
      size = GetModuleFileNameA(instance, file.data(), static_cast<DWORD>(file.size()));
    } while (GetLastError() == ERROR_INSUFFICIENT_BUFFER);
    file.resize(size);
#elifdef __linux__
    if (const auto s = realpath("/proc/self/exe", nullptr)) {
      file.assign(s);
      free(s);  // NOLINT(cppcoreguidelines-no-malloc)
    }
#else
#error Unsupported platform
#endif
    // Get executable path.
    std::error_code ec;
    auto path = std::filesystem::canonical(file, ec);
    if (ec) {
      path.assign(file);
    }
    return path.parent_path();
  }();
  return path;
}

void test(const std::string& name)
{
#ifdef _WIN32
  const auto library = base() / ("libace-" + name + ".dll");
  const auto handle = LoadLibraryA(library.string().data());
  if (!handle) {
    throw error{ "Could not open library: {}\n0x{:X}", library.string(), GetLastError() };
  }
  const auto proc = GetProcAddress(handle, "test");
  if (!proc) {
    throw error{ "Could not find test in library: {}\n0x{:X}", library.string(), GetLastError() };
  }
#elifdef __linux__
  const auto library = base() / ("libace-" + name + ".so");
  const auto handle = dlopen(library.string().data(), RTLD_LAZY);
  if (!handle) {
    throw error{ "Could not open library: {}\n{}", library.string(), dlerror() };
  }
  const auto proc = dlsym(handle, "test");
  if (!proc) {
    throw error{ "Could not find test in library: {}\n{}", library.string(), dlerror() };
  }
#else
#error Unsupported platform
#endif
  reinterpret_cast<void (*)()>(proc)();
}

}  // namespace ace

#define ACE_TEST(name) TEST_CASE(name) { ace::test(name); }

ACE_TEST("xml2")
ACE_TEST("pugixml")
ACE_TEST("zlib")
ACE_TEST("bzip2")
ACE_TEST("lzma")
ACE_TEST("lz4")
ACE_TEST("brotli")
ACE_TEST("zstd")
ACE_TEST("deflate")
ACE_TEST("miniz")
ACE_TEST("jpeg")
ACE_TEST("jpeg-turbo")
ACE_TEST("png")
ACE_TEST("avif")
ACE_TEST("svg")
ACE_TEST("font")
ACE_TEST("glm")
ACE_TEST("glm-avx2")
ACE_TEST("vulkan")
ACE_TEST("sqlite3")
ACE_TEST("openssl")
ACE_TEST("boost")

#ifdef __linux__
ACE_TEST("wayland")
#endif

int main(int argc, char* argv[])
{
  doctest::Context context;
  context.applyCommandLine(argc, argv);
  context.setOption("no-intro", 1);
  return context.run();
}
