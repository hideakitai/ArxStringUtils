# Convert
String from/to value conversion in Arduino (port a part of ofUtils (openFrameworks))

## Note

AVR Boards (like Uno, Mega etc.) are not supported

## APIs

```C++
    String to_hex(const T& value)
    int from_hex_to_int(const String&)
    char from_hex_to_char(const String&)
    float from_hex_to_float(const String&)
    double from_hex_to_double(const String&)

    std::vector<String> split_string(const String& str, const String& delim)

//    String to_bin(const T& value)
//    int from_bin_to_int(const String& value)
//    char from_bin_to_char(const String& value)
//    float from_bin_to_float(const String& value)
//    double from_bin_to_double(const String& value)
```

## License

MIT
