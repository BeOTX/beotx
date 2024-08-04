#pragma once
#ifndef PRINTF_CONFIG_H_
#define PRINTF_CONFIG_H_

#define PRINTF_SUPPORT_DECIMAL_SPECIFIERS       0
#define PRINTF_SUPPORT_EXPONENTIAL_SPECIFIERS   0
#define PRINTF_SUPPORT_WRITEBACK_SPECIFIER      0
#define PRINTF_SUPPORT_MSVC_STYLE_INTEGER_SPECIFIERS 0
#define PRINTF_SUPPORT_LONG_LONG                0
#define PRINTF_USE_DOUBLE_INTERNALLY            0
#define PRINTF_ALIAS_STANDARD_FUNCTION_NAMES_SOFT    0
#define PRINTF_ALIAS_STANDARD_FUNCTION_NAMES_HARD    1

#define PRINTF_INTEGER_BUFFER_SIZE              32
#define PRINTF_DECIMAL_BUFFER_SIZE              32
#define PRINTF_DEFAULT_FLOAT_PRECISION          6
#define PRINTF_MAX_INTEGRAL_DIGITS_FOR_DECIMAL  9
#define PRINTF_LOG10_TAYLOR_TERMS               4
#define PRINTF_CHECK_FOR_NUL_IN_FORMAT_SPECIFIER 0

#endif // PRINTF_CONFIG_H_


