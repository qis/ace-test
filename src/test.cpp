import ace;

#ifdef _WIN32
#define ACE_API extern "C" __declspec(dllexport)
#else
#define ACE_API extern "C" __attribute__((__visibility__("default")))
#endif

ACE_API void test()
{
  ace::test();
}
