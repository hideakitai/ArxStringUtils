#include <Convert.h>

void setup()
{
    Serial.begin(115200);
    delay(2000);

    String hex = Convert::to_hex(12345);
    Serial.println(hex);

    Serial.println(Convert::from_hex_to_int(hex));
    Serial.println(Convert::from_hex_to_char(hex));
    Serial.println(Convert::from_hex_to_float(hex));
    Serial.println(Convert::from_hex_to_double(hex));

    // NON-AVR only
#ifndef __AVR__
    String text = "one, two, three and four\r\n five, six, seven and eight\n";
    auto strs = Convert::split_string(text, ",");
    for (auto& s : strs) Serial.println(s);
#endif
}

void loop()
{
}
