#pragma once

//Config checks
#ifndef CLV_DEBUG
	#define CLV_DEBUG 0
#endif

#ifndef CLV_DEVELOPMENT
	#define CLV_DEVELOPMENT 0
#endif

#ifndef CLV_PROFILING
	#define CLV_PROFILING 0
#endif

#ifndef CLV_RELEASE
	#define CLV_RELEASE 0
#endif

#if (CLV_DEBUG + CLV_DEVELOPMENT + CLV_PROFILING + CLV_RELEASE) != 1
	#error Invalid configuration!
#endif

//Platform checks
#ifndef CLV_PLATFORM_WINDOWS
	#define CLV_PLATFORM_WINDOWS 0
#endif

#ifndef CLV_PLATFORM_LINUX
	#define CLV_PLATFORM_LINUX 0
#endif

#if (CLV_PLATFORM_WINDOWS + CLV_PLATFORM_LINUX) != 1
	#error Invalid platform!
#endif

//Misc checks
#ifndef CLV_ENGINE
	#define CLV_ENGINE 0
#endif

//Utility defines
#if CLV_PLATFORM_WINDOWS
	#define CLV_DEBUG_BREAK __debugbreak()
#elif CLV_PLATFORM_LINUX
	#define CLV_DEBUG_BREAK __builtin_trap()
#else
	#define CLV_DEBUG_BREAK
#endif

#if CLV_DEBUG || CLV_DEVELOPMENT
	#define CLV_ENABLE_ASSERTS 1
#else
	#define CLV_ENABLE_ASSERTS 0
#endif

#if CLV_PROFILING
	#define CLV_ENABLE_PROFILING 1
#else
	#define CLV_ENABLE_PROFILING 0
#endif

#if CLV_ENABLE_ASSERTS
	#define CLV_ASSERT(x, ...) { if(!(x)){ CLV_LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); CLV_DEBUG_BREAK; } }
#else
	#define CLV_ASSERT(x, ...) (x)
#endif

#define BIT(x) (1 << x)

#if CLV_PLATFORM_WINDOWS
	#define CLV_APIENTRY APIENTRY
#else
	#define CLV_APIENTRY
#endif
