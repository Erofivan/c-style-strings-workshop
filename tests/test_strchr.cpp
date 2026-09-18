#include "test_framework.h"

#include "my_cstring.h"

TEST(strchr_finds_first_occurrence) {
    // Arrange
    const char* str = "abcabc";

    // Act
    const char* found = my_strchr(str, 'b');

    // Assert
    REQUIRE_NOT_NULL(found);
    CHECK_EQ(found - str, std::ptrdiff_t(1));
}

TEST(strchr_returns_pointer_into_original_string) {
    // Arrange
    const char* str = "hello";

    // Act
    const char* found = my_strchr(str, 'l');

    // Assert
    REQUIRE_NOT_NULL(found);
    CHECK_STREQ(found, "llo");
}

TEST(strchr_finds_first_character) {
    // Arrange
    const char* str = "abc";

    // Act
    const char* found = my_strchr(str, 'a');

    // Assert
    REQUIRE_NOT_NULL(found);
    CHECK_EQ(found - str, std::ptrdiff_t(0));
}

TEST(strchr_missing_character) {
    // Arrange
    const char* str = "abc";

    // Act
    const char* found = my_strchr(str, 'z');

    // Assert
    CHECK_NULL(found);
}

TEST(strchr_empty_string) {
    // Arrange
    const char* str = "";

    // Act
    const char* found = my_strchr(str, 'a');

    // Assert
    CHECK_NULL(found);
}

TEST(strchr_finds_terminator) {
    // Arrange
    const char* str = "abc";

    // Act
    const char* found = my_strchr(str, '\0');

    // Assert
    REQUIRE_NOT_NULL(found);
    CHECK_EQ(found - str, std::ptrdiff_t(3));
}

TEST(strchr_finds_terminator_of_empty_string) {
    // Arrange
    const char* str = "";

    // Act
    const char* found = my_strchr(str, '\0');

    // Assert
    REQUIRE_NOT_NULL(found);
    CHECK_EQ(found - str, std::ptrdiff_t(0));
}
