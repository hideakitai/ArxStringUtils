#include <Convert.h>

void setup()
{
    Serial.begin(115200);
    delay(2000);

    String hex = Convert::to_hex(12345);
    String hex_no_zero = Convert::to_hex(12345, false);
    Serial.println(hex);
    Serial.println(hex_no_zero);
    Serial.println(Convert::from_hex_to_int(hex));

    String hex_s = "49"; // 0x49
    Serial.println((int)Convert::from_hex_to_char(hex_s)); // 73
    Serial.println((int)Convert::from_hex_to_char(hex_s), HEX); // 0x49

    // TODO: FIXME:
    String hex_f = Convert::to_hex(12.345);
    Serial.println(hex_f);
    Serial.println(Convert::from_hex_to_float(hex_f));
    Serial.println(Convert::from_hex_to_double(hex_f));

    // TODO: FIXME:
    String text = "one,two,three,four\n";
    auto strs1 = Convert::split_string(text, ",");
    for (auto& s : strs1) Serial.println(s);

    // auto strs2 = Convert::split_string(text, " ");
    // for (auto& s : strs2) Serial.println(s);
}

void loop()
{
}
