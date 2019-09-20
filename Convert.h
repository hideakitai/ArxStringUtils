#pragma once
#ifndef EMBEDDEDUTILS_CONVERT_H
#define EMBEDDEDUTILS_CONVERT_H

#ifdef __AVR__
#error AVR Boards are NOT supported
#endif

#include <Arduino.h>
#include <type_traits>
#include <vector>

namespace Convert
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
    auto to_int(const String &intString)
    -> typename std::enable_if<std::is_integral<T>::value, T>::type
    {
        return (T)intString.toInt();
    }

    template <typename T>
    using IntFloatUnion = typename IntFloatUnion_impl<T>::type;


    template <typename T, size_t length = sizeof(T) * 2>
    auto to_hex(const T& value, bool b_leading_zeros = true)
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
    auto to_hex(const T& value, bool b_leading_zeros = true)
    -> typename std::enable_if<std::is_floating_point<T>::value, String>::type
    {
        IntFloatUnion<T> myUnion;
        myUnion.f = value;
        return to_hex(myUnion.x, b_leading_zeros);
    }

    int from_hex_to_int(const String& intHexString) { return (int)strtol(intHexString.c_str(), NULL, 16); }
    char from_hex_to_char(const String& charHexString) { return (char)strtol(charHexString.c_str(), NULL, 16); }
    float from_hex_to_float(const String& floatHexString)
    {
        IntFloatUnion<float> myUnion;
        myUnion.x = to_int<decltype(myUnion.x)>(floatHexString);
        return myUnion.f;
    }
    double from_hex_to_double(const String& doubleHexString)
    {
        IntFloatUnion<double> myUnion;
        myUnion.x = to_int<decltype(myUnion.x)>(doubleHexString);
        return myUnion.f;
    }

    uint8_t from_dec_to_bcd(uint8_t n)
    {
        return n + 6 * (n / 10);
    }

    uint8_t from_bcd_to_dec(uint8_t n)
    {
        return n - 6 * (n >> 4);
    }

#ifndef __AVR__

    std::vector<String> split_string(const String& s, const String& delim)
    {
        std::vector<String> result;
        std::vector<size_t> pos;
        std::vector<size_t> length;
        pos.emplace_back(0);
        for (size_t i = 0; i < s.length(); ++i)
        {
            if (s.charAt(i) == *(delim.c_str()))
            {
                pos.emplace_back(i + 1);
                length.emplace_back(pos[pos.size() - 1] - pos[pos.size() - 2]);
            }
            else if (s.charAt(i) == '\r')
            {
                pos.emplace_back(i + 1);
                length.emplace_back(pos[pos.size() - 1] - pos[pos.size() - 2]);
                break;
            }
            else if (s.charAt(i) == '\n')
            {
                pos.emplace_back(i);
                length.emplace_back(pos[pos.size() - 1] - pos[pos.size() - 2]);
                break;
            }
        }
        for (size_t i = 0; i < pos.size() - 1; ++i)
        {
            result.push_back(s.substring(pos[i], pos[i + 1] - 1));
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
}

#endif // EMBEDDEDUTILS_CALCULUS_H
