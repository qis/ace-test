import ace;

#ifdef _WIN32
#define ACE_API __declspec(dllexport)
#else
#define ACE_API __attribute__((__visibility__("default")))
#endif

extern "C" ACE_API void test()
{
  ace::test();
}
