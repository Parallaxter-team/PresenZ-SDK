//////////////////////////////////////////////////////////////////////////
// Copyright (C) V-Nova 2025. All rights reserved.

/// \file PzAssert.h
/// \brief Several helper macros for validating and debugging using PresenZ logging system
///
/// Assert macros are used all over the PresenZ code base. Failed conditions will trigger a debugger
/// interruption. The failed condition will be printed with a PZ_TRACE debug level. 
///
/// Some asserts can be promoted to PZ_WARNING_TEST/PZ_ERROR_TEST if they are important to the point
/// that the user explicitly needs to be made aware of something failing.
/// 
/// PZ_WARNING_TEST/PZ_ERROR_TEST do not trigger a PZ_DEBUG_BREAK

// All rights reserved.
#ifndef __PZ_ASSERT_H__
#define __PZ_ASSERT_H__

#include "PzAppLogger.h"

/// @brief Trigger an Interruption 3/Hardware debug (windows only, will invoke abort() on other systems).

#ifdef WIN32
#define PZ_BREAK() do { __debugbreak();  } while(0)
#else
#include <signal.h>
#define PZ_BREAK() raise(SIGTRAP) // GCC/Clang
#endif

#define PZ_DEBUGBREAK(...) \
    if ((__VA_ARGS__)) { \
        PZ_BREAK(); \
    }

/// @brief This one is used for invariants: condition is supposed to always be true
#define PZ_ASSERT(condition, message,...) { if(!(condition)) { PZ_ERROR(message, ##__VA_ARGS__); PZ_BREAK(); } } 

/// @brief If this condition is violated, then we need to tell the user that something is very suspicious 
#define PZ_WARNING_TEST(condition, message,...) { if(!(condition)) { PZ_WARNING(message, ##__VA_ARGS__); } } 

/// @brief Some conditions might be tested a lot (for example: once per ray traced) but you don't want to trigger the violation each time; only once is sufficient.
#define PZ_WARNING_TEST_ONLYONCE(condition, message,...) { static bool onlyOnce = false; if(!onlyOnce && !(condition)) { onlyOnce = true; PZ_WARNING(message, ##__VA_ARGS__); } } 

/// @brief If the condition is violated, we will notify the user that something definitely went wrong.
#define PZ_ERROR_TEST(condition, message,...) { if(!(condition)) { PZ_ERROR(message, ##__VA_ARGS__); } } 

#endif // __PZ_ASSERT_H__
