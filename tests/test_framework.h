#pragma once

// Мини-фреймворк тестов. TEST(имя) { ... }, внутри — CHECK_*/REQUIRE_*.
// main() определён в конце файла: каждый файл тестов — отдельная программа.

#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace mini_test {

struct TestCase {
    const char* name;
    void (*fn)();
};

inline std::vector<TestCase>& registry() {
    static std::vector<TestCase> tests;
    return tests;
}

inline int& failures_in_current_test() {
    static int count = 0;
    return count;
}

struct Registrar {
    Registrar(const char* name, void (*fn)()) { registry().push_back({name, fn}); }
};

// Экранирует невидимые символы, чтобы '\0' было видно в отчёте.
inline std::string quote(const char* str, std::size_t len) {
    std::ostringstream out;
    out << '"';
    for (std::size_t i = 0; i < len; ++i) {
        unsigned char c = static_cast<unsigned char>(str[i]);
        switch (c) {
            case '\0': out << "\\0"; break;
            case '\n': out << "\\n"; break;
            case '\t': out << "\\t"; break;
            case '\\': out << "\\\\"; break;
            case '"':  out << "\\\""; break;
            default:
                if (c < 32 || c > 126) {
                    out << "\\x" << std::hex << static_cast<int>(c) << std::dec;
                } else {
                    out << static_cast<char>(c);
                }
        }
    }
    out << '"';
    return out.str();
}

inline std::string quote(const char* str) {
    if (str == nullptr) {
        return "nullptr";
    }
    return quote(str, std::strlen(str));
}

inline void report(const char* file, int line, const std::string& message) {
    ++failures_in_current_test();
    std::cout << "    [FAIL] " << file << ":" << line << "\n           " << message << "\n";
}

template <typename T>
std::string show(const T& value) {
    std::ostringstream out;
    out << value;
    return out.str();
}

inline std::string show(const char* value) { return quote(value); }
inline std::string show(char* value) { return quote(value); }
inline std::string show(std::nullptr_t) { return "nullptr"; }

}  // namespace mini_test

#define TEST(name)                                                        \
    static void name();                                                   \
    static ::mini_test::Registrar mini_test_registrar_##name(#name, name); \
    static void name()

#define CHECK(condition)                                                        \
    do {                                                                        \
        if (!(condition)) {                                                     \
            ::mini_test::report(__FILE__, __LINE__, "условие ложно: " #condition); \
        }                                                                       \
    } while (false)

#define CHECK_EQ(actual, expected)                                                    \
    do {                                                                              \
        auto mini_test_a = (actual);                                                  \
        auto mini_test_b = (expected);                                                \
        if (!(mini_test_a == mini_test_b)) {                                          \
            ::mini_test::report(__FILE__, __LINE__,                                   \
                                std::string(#actual) + " -> " +                       \
                                    ::mini_test::show(mini_test_a) + ", ожидалось " + \
                                    ::mini_test::show(mini_test_b));                  \
        }                                                                             \
    } while (false)

#define CHECK_STREQ(actual, expected)                                               \
    do {                                                                            \
        const char* mini_test_a = (actual);                                         \
        const char* mini_test_b = (expected);                                       \
        if (mini_test_a == nullptr || std::strcmp(mini_test_a, mini_test_b) != 0) {  \
            ::mini_test::report(__FILE__, __LINE__,                                 \
                                std::string(#actual) + " -> " +                     \
                                    ::mini_test::quote(mini_test_a) +               \
                                    ", ожидалось " + ::mini_test::quote(mini_test_b)); \
        }                                                                           \
    } while (false)

#define CHECK_BYTES(actual, expected, count)                                         \
    do {                                                                             \
        const char* mini_test_a = reinterpret_cast<const char*>(actual);             \
        const char* mini_test_b = reinterpret_cast<const char*>(expected);           \
        std::size_t mini_test_n = (count);                                           \
        if (std::memcmp(mini_test_a, mini_test_b, mini_test_n) != 0) {               \
            ::mini_test::report(__FILE__, __LINE__,                                  \
                                std::string(#actual) + " -> " +                      \
                                    ::mini_test::quote(mini_test_a, mini_test_n) +   \
                                    ", ожидалось " +                                 \
                                    ::mini_test::quote(mini_test_b, mini_test_n));   \
        }                                                                            \
    } while (false)

#define CHECK_NEGATIVE(expr)                                                          \
    do {                                                                              \
        auto mini_test_v = (expr);                                                    \
        if (!(mini_test_v < 0)) {                                                      \
            ::mini_test::report(__FILE__, __LINE__,                                   \
                                std::string(#expr) + " -> " +                         \
                                    ::mini_test::show(mini_test_v) +                  \
                                    ", ожидалось отрицательное число");               \
        }                                                                             \
    } while (false)

#define CHECK_POSITIVE(expr)                                                          \
    do {                                                                              \
        auto mini_test_v = (expr);                                                    \
        if (!(mini_test_v > 0)) {                                                      \
            ::mini_test::report(__FILE__, __LINE__,                                   \
                                std::string(#expr) + " -> " +                         \
                                    ::mini_test::show(mini_test_v) +                  \
                                    ", ожидалось положительное число");               \
        }                                                                             \
    } while (false)

#define CHECK_NULL(expr)                                                              \
    do {                                                                              \
        const void* mini_test_p = (expr);                                             \
        if (mini_test_p != nullptr) {                                                 \
            ::mini_test::report(__FILE__, __LINE__,                                   \
                                std::string(#expr) + " -> не nullptr, а ожидался nullptr"); \
        }                                                                             \
    } while (false)

// Прерывает тест: дальше указатель разыменовывается.
#define REQUIRE_NOT_NULL(expr)                                                        \
    do {                                                                              \
        const void* mini_test_p = (expr);                                             \
        if (mini_test_p == nullptr) {                                                 \
            ::mini_test::report(__FILE__, __LINE__,                                   \
                                std::string(#expr) + " -> nullptr (функция не реализована?)"); \
            return;                                                                   \
        }                                                                             \
    } while (false)

// Аргумент командной строки — фильтр по имени теста (подстрока).
int main(int argc, char** argv) {
    const char* filter = argc > 1 ? argv[1] : nullptr;

    int total = 0;
    int failed_tests = 0;

    for (const ::mini_test::TestCase& test : ::mini_test::registry()) {
        if (filter != nullptr && std::strstr(test.name, filter) == nullptr) {
            continue;
        }

        ++total;
        ::mini_test::failures_in_current_test() = 0;
        std::cout << "  * " << test.name << "\n";
        test.fn();
        if (::mini_test::failures_in_current_test() != 0) {
            ++failed_tests;
        }
    }

    if (total == 0) {
        std::cout << "Ни один тест не подошёл под фильтр\n";
        return 1;
    }
    if (failed_tests == 0) {
        std::cout << "OK: пройдено " << total << " тест(ов)\n";
        return 0;
    }
    std::cout << "ПРОВАЛЕНО: " << failed_tests << " из " << total << " тест(ов)\n";
    return 1;
}
