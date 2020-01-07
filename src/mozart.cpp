/**
 * Mozart++ Template Library
 * Licensed under MIT License
 * Copyright (c) 2020 Covariant Institute
 * Website: https://covariant.cn/
 * Github:  https://github.com/covariant-institute/
 */

#include <mozart++/mozart>

mpp::byte_t *mpp::uninitialized_copy(byte_t *dest, byte_t *src, size_t count) noexcept {
    return reinterpret_cast<byte_t *>(
            memcpy(reinterpret_cast<void *>(dest), reinterpret_cast<void *>(src), count));
}

std::chrono::time_point<std::chrono::high_resolution_clock>
mpp::timer::m_timer(std::chrono::high_resolution_clock::now());

template <typename T>
mpp::any::default_allocator<mpp::any::stor_impl<T>> mpp::any::stor_impl<T>::allocator;

std::wstring_convert<std::codecvt_utf8<wchar_t>> mpp::codecvt::conv;

#ifdef MOZART_PLATFORM_WIN32

#include <shlobj.h>

#pragma comment(lib, "shell32.lib")
#endif

#ifdef _MSC_VER
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif
#include <windows.h>
#include <Dbghelp.h>
#pragma comment(lib, "DbgHelp")
namespace mpp {
    std::string cxx_demangle(const char* name)
    {
        char buffer[1024];
        DWORD length = UnDecorateSymbolName(name, buffer, sizeof(buffer), 0);
        if (length > 0)
            return std::string(buffer, length);
        else
            return name;
    }
}
#elif defined __GNUC__

#include <cxxabi.h>

namespace mpp {
    std::string cxx_demangle(const char *name) {
        char buffer[1024] = {0};
        size_t size = sizeof(buffer);
        int status;
        char *ret = abi::__cxa_demangle(name, buffer, &size, &status);
        if (ret != nullptr)
            return std::string(ret);
        else
            return name;
    }
}
#endif
