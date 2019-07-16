/*
 * This source file is part of Modem
 * Copyright (C) 2019  Javier Lancha Vázquez
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
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

#if defined(NDEBUG) && NDEBUG !=0
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
