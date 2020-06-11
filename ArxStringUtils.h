#pragma once
#ifndef ARX_STRINGUTILS_H
#define ARX_STRINGUTILS_H

#include <Arduino.h>
#include "util/ArxTypeTraits/ArxTypeTraits.h"
#include <type_traits>

namespace arx {
namespace str {

    namespace detail
    {
        template <size_t size>
        struct same_size_int;

        template <size_t size>
        using same_size_int_t = typename same_size_int<size>::type;

        template <> struct same_size_int<1> { using type = int8_t; };
        template <> struct same_size_int<2> { using type = int16_t; };
        template <> struct same_size_int<4> { using type = int32_t; };
        template <> struct same_size_int<8> { using type = int64_t; };

        template <typename T, typename std::enable_if<std::is_floating_point<T>::value>::type* = nullptr>
        struct IntFloatUnion_impl {
            using type = union {
                same_size_int_t<sizeof(T)> x;
                T f;
            };
        };

        template <typename T>
        using IntFloatUnion = typename IntFloatUnion_impl<T>::type;

        template <typename T>
        inline auto to_int(const String &intString)
        -> typename std::enable_if<std::is_integral<T>::value, T>::type
        {
            return (T)intString.toInt();
        }
    }

    template <typename T, size_t length = sizeof(T) * 2>
    inline auto to_hex(const T& value, bool b_leading_zeros = true)
    -> typename std::enable_if<std::is_integral<T>::value, String>::type
    {
        String format;
        if (b_leading_zeros) format = "%0" + String(length) + "X";
        else                 format = "%X";
        char hex[length + 1];
        sprintf(hex, format.c_str(), value);
        return String(hex);
    }

    template <typename T, size_t length = sizeof(T) * 2>
    inline auto to_hex(const T& value, bool b_leading_zeros = true)
    -> typename std::enable_if<std::is_floating_point<T>::value, String>::type
    {
        detail::IntFloatUnion<T> myUnion;
        myUnion.f = value;
        return to_hex(myUnion.x, b_leading_zeros);
    }

    inline int from_hex_to_int(const String& intHexString)
    {
        return (int)strtol(intHexString.c_str(), NULL, 16);
    }

    inline char from_hex_to_char(const String& charHexString)
    {
        return (char)strtol(charHexString.c_str(), NULL, 16);
    }

    inline float from_hex_to_float(const String& floatHexString)
    {
        detail::IntFloatUnion<float> myUnion;
        myUnion.x = from_hex_to_int(floatHexString);
        return myUnion.f;
    }

    inline double from_hex_to_double(const String& doubleHexString)
    {
        detail::IntFloatUnion<double> myUnion;
        myUnion.x = from_hex_to_int(doubleHexString);
        return myUnion.f;
    }

    template <typename T>
    inline auto from_dec_to_bcd(const T& n)
    -> typename std::enable_if<std::is_integral<T>::value, size_t>::type
    {
        return n + 6 * (n / 10);
    }

    template <typename T>
    inline auto from_bcd_to_dec(const T& n)
    -> typename std::enable_if<std::is_integral<T>::value, size_t>::type
    {
        return n - 6 * (n >> 4);
    }

    template <typename T>
    inline auto string_length(const T& value)
    -> typename std::enable_if<std::is_integral<T>::value, size_t>::type
    {
        return floor(log10(value) + 1);
    }

    template <typename T>
    inline auto to_string(const T& value, size_t width)
    -> typename std::enable_if<std::is_integral<T>::value, String>::type
    {
        String format;
        format = "%0" + String(width) + "d";
        const size_t str_len = string_length(value);
        const size_t len = (width > str_len) ? width : str_len;
        char dec[len + 1];
        sprintf(dec, format.c_str(), value);
        return String(dec);
    }

    template <typename T>
    inline auto to_string(const T& value)
    -> typename std::enable_if<std::is_integral<T>::value, String>::type
    {
        return to_string(value, 0);
    }

    template <typename T>
    inline auto to_string(const T& value, size_t precision, size_t width)
    -> typename std::enable_if<std::is_floating_point<T>::value, String>::type
    {
        String format;
        format = "%0" + String(width) + "." + String(precision) + "f";
        const size_t str_len = String(value).length();
        const size_t len = (width > str_len) ? width : str_len;
        char dec[len + 1];
        sprintf(dec, format.c_str(), value);
        return String(dec);
    }

    template <typename T>
    inline auto to_string(const T& value, size_t precision)
    -> typename std::enable_if<std::is_floating_point<T>::value, String>::type
    {
        return to_string(value, precision, 0);
    }


#ifndef __AVR__

    #include <vector>

    inline std::vector<String> split_string(const String& s, const String& delim)
    {
        std::vector<String> result;
        std::vector<size_t> pos;
        // std::vector<size_t> length;
        pos.emplace_back(0);
        for (size_t i = 0; i < s.length(); ++i)
        {
            if (s.charAt(i) == *(delim.c_str()))
            {
                pos.emplace_back(i + 1);
            }
            else if (s.charAt(i) == '\r')
            {
                pos.emplace_back(i + 1);
                break;
            }
            else if (s.charAt(i) == '\n')
            {
                pos.emplace_back(i + 1);
                break;
            }
        }
        for (size_t i = 0; i < pos.size() - 1; ++i)
        {
            result.push_back(s.substring(pos[i], pos[i + 1] - 1));
        }
        if (!s.endsWith(String('\n')))
        {
            result.push_back(s.substring(pos[pos.size() - 1], s.length()));
        }
        return result; // local value will be moved
    }

#endif

//    String to_bin(const String& value)
//    {
//        String out("");
//        size_t numBytes = value.length();
//        for(size_t i = 0; i < numBytes; i++) {
//            std::bitset<8> bitBuffer(value.c_str()[i]);
//            out += String(bitBuffer.to_ulong(), BIN);
//        }
//        return out;
//    }
//
//    String to_bin(const char* value) { return toBinary(String(value)); }
//
//    int from_bin_to_int(const String& value)
//    {
//        const size_t intSize = sizeof(int) * 8;
//        std::bitset<intSize> binaryString(value.c_str()[0]);
//        return (int)binaryString.to_ulong();
//    }
//
//    char from_bin_to_char(const String& value)
//    {
//        const size_t charSize = sizeof(char) * 8;
//        std::bitset<charSize> binaryString(value.c_str()[0]);
//        return (char) binaryString.to_ulong();
//    }
//
//    float from_bin_to_float(const String& value)
//    {
//        const size_t floatSize = sizeof(float) * 8;
//        std::bitset<floatSize> binaryString(value.c_str()[0]);
//        union ulongFloatUnion {
//                unsigned long result;
//                float f;
//        } myUFUnion;
//        myUFUnion.result = binaryString.to_ulong();
//        return myUFUnion.f;
//    }
//
//    template <class T>
//    String to_bin(const T& value) {
//        return std::bitset<8 * sizeof(T)>(*reinterpret_cast<const uint64_t*>(&value)).to_string();
//    }

} // namespace str
} // namespace arx


#endif // EMBEDDEDUTILS_CALCULUS_H
