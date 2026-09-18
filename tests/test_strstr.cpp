#include "test_framework.h"

#include "my_cstring.h"

TEST(strstr_finds_substring) {
    // Arrange
    const char* haystack = "hello, world";

    // Act
    const char* found = my_strstr(haystack, "world");

    // Assert
    REQUIRE_NOT_NULL(found);
    CHECK_EQ(found - haystack, std::ptrdiff_t(7));
}

TEST(strstr_finds_first_of_several_matches) {
    // Arrange
    const char* haystack = "abababa";

    // Act
    const char* found = my_strstr(haystack, "aba");

    // Assert
    REQUIRE_NOT_NULL(found);
    CHECK_EQ(found - haystack, std::ptrdiff_t(0));
}

TEST(strstr_finds_match_at_the_end) {
    // Arrange
    const char* haystack = "abcdef";

    // Act
    const char* found = my_strstr(haystack, "def");

    // Assert
    REQUIRE_NOT_NULL(found);
    CHECK_EQ(found - haystack, std::ptrdiff_t(3));
}

TEST(strstr_empty_needle_returns_haystack) {
    // Arrange
    const char* haystack = "abc";

    // Act
    const char* found = my_strstr(haystack, "");

    // Assert
    REQUIRE_NOT_NULL(found);
    CHECK_EQ(found - haystack, std::ptrdiff_t(0));
}

TEST(strstr_needle_longer_than_haystack) {
    // Arrange
    const char* haystack = "abc";

    // Act
    const char* found = my_strstr(haystack, "abcd");

    // Assert
    CHECK_NULL(found);
}

TEST(strstr_missing_needle) {
    // Arrange
    const char* haystack = "aaab";

    // Act
    const char* found = my_strstr(haystack, "aac");

    // Assert
    CHECK_NULL(found);
}

TEST(strstr_search_continues_after_partial_match) {
    // Arrange
    const char* haystack = "aaaaab";

    // Act
    const char* found = my_strstr(haystack, "aab");

    // Assert
    REQUIRE_NOT_NULL(found);
    CHECK_EQ(found - haystack, std::ptrdiff_t(3));
}

TEST(strstr_single_char_needle) {
    // Arrange
    const char* haystack = "abc";

    // Act
    const char* found = my_strstr(haystack, "c");

    // Assert
    REQUIRE_NOT_NULL(found);
    CHECK_EQ(found - haystack, std::ptrdiff_t(2));
}
