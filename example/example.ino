#include <ArxStringUtils.h>

#if ARX_HAVE_LIBSTDCPLUSPLUS >= 201103L // Have libstdc++11
#include <cassert>
#else
inline void assert_impl(const bool b, const String& expression) {
    if (!b) {
        Serial.print("assertion failed: ");
        Serial.println(expression);
        while(1) ;
    }
}
#define assert(b) assert_impl((b), #b)
#endif

void setup()
{
    Serial.begin(115200);
    delay(2000);

    Serial.print("hex string of '0x123' is ");
    Serial.println(arx::str::to_hex(0x123, false)); // with no leading zeros
    assert(arx::str::to_hex((uint8_t)0x12) == "12");
    assert(arx::str::to_hex((uint16_t)0x123) == "0123");
    assert(arx::str::to_hex((uint16_t)0x1234) == "1234");
    assert(arx::str::to_hex((uint32_t)0x12345) == "00012345");
    assert(arx::str::to_hex((uint32_t)0x123456) == "00123456");
    assert(arx::str::to_hex((uint32_t)0x1234567) == "01234567");
    assert(arx::str::to_hex((uint32_t)0x12345678) == "12345678");

    assert(arx::str::to_hex((uint8_t)0x12, false) == "12");
    assert(arx::str::to_hex((uint16_t)0x123, false) == "123");
    assert(arx::str::to_hex((uint16_t)0x1234, false) == "1234");
    assert(arx::str::to_hex((uint32_t)0x12345, false) == "12345");
    assert(arx::str::to_hex((uint32_t)0x123456, false) == "123456");
    assert(arx::str::to_hex((uint32_t)0x1234567, false) == "1234567");
    assert(arx::str::to_hex((uint32_t)0x12345678, false) == "12345678");

    Serial.print("value of hex string '123' is ");
    Serial.println(arx::str::from_hex_to_int("123"), HEX);
    assert(arx::str::from_hex_to_int(arx::str::to_hex(0x12)) == 0x12);
    assert(arx::str::from_hex_to_int(arx::str::to_hex(0x1234)) == 0x1234);
    assert(arx::str::from_hex_to_int(arx::str::to_hex(0x123456)) == 0x123456);
    assert(arx::str::from_hex_to_int(arx::str::to_hex(0x12345678)) == 0x12345678);

    Serial.print("hex string of '1.2f' is ");
    Serial.println(arx::str::to_hex(1.2f, false)); // with no leading zeros
    Serial.print("value of hex string '3F99999A' is ");
    Serial.println(arx::str::from_hex_to_float("3F99999A"));
    assert(arx::str::from_hex_to_float(arx::str::to_hex(1.2f)) == 1.2f);
    assert(arx::str::from_hex_to_float(arx::str::to_hex(12.34f)) == 12.34f);
    assert(arx::str::from_hex_to_float(arx::str::to_hex(123.456f)) == 123.456f);
    assert(arx::str::from_hex_to_float(arx::str::to_hex(1234.5678f)) == 1234.5678f);
    assert(arx::str::from_hex_to_float(arx::str::to_hex(12345.67890f)) == 12345.67890f);

    // FIXME:
    // assert(arx::str::from_hex_to_double(arx::str::to_hex(1.2)) == 1.2);
    // assert(arx::str::from_hex_to_double(arx::str::to_hex(12.34)) == 12.34);
    // assert(arx::str::from_hex_to_double(arx::str::to_hex(123.456)) == 123.456);
    // assert(arx::str::from_hex_to_double(arx::str::to_hex(1234.5678)) == 1234.5678);
    // assert(arx::str::from_hex_to_double(arx::str::to_hex(12345.67890)) == 12345.67890);

    Serial.print("bcd of hex '0x12' is ");
    Serial.println(arx::str::from_dec_to_bcd(0x12), BIN);
    Serial.print("dec of bcd '12' is ");
    Serial.println(arx::str::from_bcd_to_dec(12), BIN);
    assert(arx::str::from_bcd_to_dec(arx::str::from_dec_to_bcd(0x1)) == 0x1);
    assert(arx::str::from_bcd_to_dec(arx::str::from_dec_to_bcd(0x12)) == 0x12);
    assert(arx::str::from_bcd_to_dec(arx::str::from_dec_to_bcd(0x123)) == 0x123);
    assert(arx::str::from_bcd_to_dec(arx::str::from_dec_to_bcd(0x1234)) == 0x1234);
    assert(arx::str::from_bcd_to_dec(arx::str::from_dec_to_bcd(0x12345)) == 0x12345);
    assert(arx::str::from_bcd_to_dec(arx::str::from_dec_to_bcd(0x123456)) == 0x123456);
    assert(arx::str::from_bcd_to_dec(arx::str::from_dec_to_bcd(0x1234567)) == 0x1234567);
    assert(arx::str::from_bcd_to_dec(arx::str::from_dec_to_bcd(0x12345678)) == 0x12345678);

    Serial.print("length of '1234' is ");
    Serial.println(arx::str::string_length(1234));
    assert(arx::str::string_length(1) == 1);
    assert(arx::str::string_length(12) == 2);
    assert(arx::str::string_length(123) == 3);
    assert(arx::str::string_length(1234) == 4);
    assert(arx::str::string_length(12345) == 5);
    assert(arx::str::string_length(123456) == 6);
    assert(arx::str::string_length(1234567) == 7);
    assert(arx::str::string_length(12345678) == 8);
    assert(arx::str::string_length(123456789) == 9);

    Serial.print("convert int '1234' to string: ");
    Serial.println(arx::str::to_string(1234));
    assert(arx::str::to_string(1) == "1");
    assert(arx::str::to_string(12) == "12");
    assert(arx::str::to_string(123) == "123");
    assert(arx::str::to_string(1234) == "1234");
    assert(arx::str::to_string(12345) == "12345");
    assert(arx::str::to_string(123456) == "123456");
    assert(arx::str::to_string(1234567) == "1234567");
    assert(arx::str::to_string(12345678) == "12345678");
    assert(arx::str::to_string(123456789) == "123456789");

    Serial.print("convert int '1234' to string in width 8: ");
    Serial.println(arx::str::to_string(1234, 8));
    assert(arx::str::to_string(1, 8) == "00000001");
    assert(arx::str::to_string(12, 8) == "00000012");
    assert(arx::str::to_string(123, 8) == "00000123");
    assert(arx::str::to_string(1234, 8) == "00001234");
    assert(arx::str::to_string(12345, 8) == "00012345");
    assert(arx::str::to_string(123456, 8) == "00123456");
    assert(arx::str::to_string(1234567, 8) == "01234567");
    assert(arx::str::to_string(12345678, 8) == "12345678");

    Serial.print("convert '1.2' to string with precision 2: ");
    Serial.println(arx::str::to_string(1.2, 2));
    Serial.print("convert '1.234' to string with precision 2: ");
    Serial.println(arx::str::to_string(1.234, 2));
    Serial.print("convert '123.4' to string with precision 2: ");
    Serial.println(arx::str::to_string(123.4, 2));

    Serial.print("convert '123.456789' to string with precision 2 in width 4: ");
    Serial.println(arx::str::to_string(123.456789, 2, 4));
    Serial.print("convert '123.456789' to string with precision 2 in width 8: ");
    Serial.println(arx::str::to_string(123.456789, 2, 8));

#if ARX_HAVE_LIBSTDCPLUSPLUS >= 201103L // Have libstdc++11
    auto strs1 = arx::str::split_string("one,two,three,four", ",");
    Serial.print("string 'one,two,three' is devided to : ");
    for (auto& s : strs1) { Serial.print(s); Serial.print(", "); }
    Serial.println();

    auto strs2 = arx::str::split_string("one,two,three,four\n", ",");
    Serial.print("string 'one,two,three' is devided to : ");
    for (auto& s : strs2) { Serial.print(s); Serial.print(", "); }
    Serial.println();
#endif
}

void loop()
{
}
