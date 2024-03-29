# ArxStringUtils

Arduino `String` utilities


## APIs

```C++
// for integral
template <typename T> inline String to_string(const T& value);
template <typename T> inline String to_string(const T& value, size_t width);
// for floating points
template <typename T> String to_string(const T& value, size_t precision);
template <typename T> String to_string(const T& value, size_t precision, size_t width);

template <typename T> String to_hex(const T& value);
int from_hex_to_int(const String&);
char from_hex_to_char(const String&);
float from_hex_to_float(const String&);
double from_hex_to_double(const String&);

template <typename T> inline size_t string_length(const T& value);

// only for STL enabled platforms
std::vector<String> split_string(const String& str, const String& delim);
```

## Dependent Libraries

- [ArxContainer](https://github.com/hideakitai/ArxContainer)
- [ArxTypeTraits](https://github.com/hideakitai/ArxTypeTraits)

## Used Inside of

- [ES920](https://github.com/hideakitai/ES920)


## License

MIT
