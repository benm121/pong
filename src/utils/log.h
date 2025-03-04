#pragma once

#include <cstdio>
#include <cstdlib>

#ifndef NDEBUG

#define LOG_INFO(fmt, ...) std::fprintf(stdout, "\033[32m[INFO]\033[0m " fmt "\n", ##__VA_ARGS__)
#define LOG_WARN(fmt, ...) std::fprintf(stderr, "\033[33m[WARN]\033[0m " fmt "\n", ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) std::fprintf(stderr, "\033[31m[ERROR]\033[0m " fmt "\n", ##__VA_ARGS__)
#define LOG_ERROR_EXIT(code, fmt, ...) LOG_ERROR(fmt, ##__VA_ARGS__); exit(code)
#define LOG_ERROR_RETURN(R, fmt, ...) LOG_ERROR(fmt, ##__VA_ARGS__); return R;

#else

#define LOG_INFO(fmt, ...) (void)0
#define LOG_WARN(fmt, ...) (void)0
#define LOG_ERROR(fmt, ...) (void)0
#define LOG_ERROR_EXIT(code, fmt, ...) (void)0
#define LOG_ERROR_RETURN(R, fmt, ...) (void)0

#endif

