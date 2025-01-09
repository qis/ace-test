#include <glm/glm.hpp>

#ifdef __AVX2__
#error Unexpected compiler option: -mavx2
#endif

#if GLM_ARCH != GLM_ARCH_UNKNOWN
#error GLM_FORCE_PURE not defined
#endif

#if !(GLM_LANG & GLM_LANG_CXX20_FLAG)
#error GLM_FORCE_CXX20 not defined
#endif

#ifndef GLM_FORCE_SINGLE_ONLY
#error GLM_FORCE_SINGLE_ONLY not defined
#endif

#if !defined(GLM_FORCE_LEFT_HANDED) || !(GLM_CONFIG_CLIP_CONTROL & GLM_CLIP_CONTROL_LH_BIT)
#error GLM_FORCE_LEFT_HANDED not defined
#endif

#if !defined(GLM_FORCE_DEPTH_ZERO_TO_ONE) || !(GLM_CONFIG_CLIP_CONTROL & GLM_CLIP_CONTROL_ZO_BIT)
#error GLM_FORCE_DEPTH_ZERO_TO_ONE not defined
#endif

#if defined(GLM_FORCE_DEFAULT_ALIGNED_GENTYPES) || GLM_CONFIG_ALIGNED_GENTYPES == GLM_ENABLE
#error GLM_FORCE_DEFAULT_ALIGNED_GENTYPES defined
#endif

#if defined(GLM_FORCE_ALIGNED_GENTYPES) || GLM_CONFIG_ALIGNED_GENTYPES == GLM_ENABLE
#error GLM_FORCE_ALIGNED_GENTYPES defined
#endif

#if !(GLM_COMPILER & GLM_COMPILER_CLANG)
#error Clang compiler not detected
#endif

#if GLM_MODEL != GLM_MODEL_64
#error 64-bit instruction set not detected
#endif

#if defined(_WIN32)
#if !(GLM_PLATFORM & GLM_PLATFORM_WINDOWS)
#error Windows platform not detected
#endif
#else
#if !(GLM_PLATFORM & GLM_PLATFORM_LINUX)
#error Linux platform not detected
#endif
#endif

#ifdef GLM_FORCE_XYZW_ONLY
#error GLM_FORCE_XYZW_ONLY defined
#endif

#if GLM_CONFIG_SWIZZLE != GLM_SWIZZLE_DISABLED
#error GLM_CONFIG_SWIZZLE not disabled
#endif

#if GLM_CONFIG_LENGTH_TYPE != GLM_LENGTH_INT
#error GLM_CONFIG_LENGTH_TYPE not set to GLM_LENGTH_INT
#endif

#if GLM_CONFIG_UNRESTRICTED_GENTYPE != GLM_DISABLE
#error GLM_CONFIG_UNRESTRICTED_GENTYPE not disabled
#endif
