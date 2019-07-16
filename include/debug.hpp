/*
 * This source file is part of Modem
 *
 * Copyright 2019 Javier Lancha Vázquez
 *
*/

#ifndef _MODEM_INCLUDE_DEBUG_HPP_
#define _MODEM_INCLUDE_DEBUG_HPP_

#include <cstdio>

namespace Debug
{
    enum DebugLevel : int {
        NONE    = -1,
        INFO    = 0,
        WARNING = 1,
        ERROR   = 2,
        DEBUG   = 3,
        VERBOSE = 4,
    };

    static const char* level_tags[] {
        [DebugLevel::INFO]      = "I",
        [DebugLevel::WARNING]   = "W",
        [DebugLevel::ERROR]     = "E",
        [DebugLevel::DEBUG]     = "D",
        [DebugLevel::VERBOSE]   = "V"
    };

    const static int DEFAULT_LEVEL = INFO;

#ifdef NDEBUG
    static int defined_level = NONE;
#else
    #ifdef DEBUG_LEVEL
        static int defined_level = DEBUG_LEVEL;
    #else
        static int defined_level = DEFAULT_LEVEL;
    #endif

#endif

    template <typename... Args>
    static void log(const int level, const char* tag, const char* str) {
        if (level <= defined_level) {
            printf("[%s] %s: ", level_tags[level], tag);
            printf("%s", str);
            printf("\n");
        }
    }

    template <typename... Args>
    static void log(const int level, const char* tag, const char* fmt, Args... args) {
        if (level <= defined_level) {
            printf("[%s] %s: ", level_tags[level], tag);
            printf(fmt, args...);
            printf("\n");
        }
    }

    // Visible debug functions
    class Log {
    public:
        template <typename... Args>
        static void i(const char* tag, Args... args) {
            log(INFO, tag, args...);
        }

        template <typename... Args>
        static void w(const char* tag, Args... args) {
            log(WARNING, tag, args...);
        }

        template <typename... Args>
        static void e(const char* tag, Args... args) {
            log(ERROR, tag, args...);
        }

        template <typename... Args>
        static void d(const char* tag, Args... args) {
            log(DEBUG, tag, args...);
        }

        template <typename... Arg>
        static void v(const char* tag, Arg... args) {
            log(VERBOSE, tag, args...);
        }

    };
}

#endif // _MODEM_INCLUDE_DEBUG_HPP_
