#include "test_framework.h"

#include "my_cstring.h"

TEST(strrchr_finds_last_occurrence) {
    // Arrange
    const char* str = "abcabc";

    // Act
    const char* found = my_strrchr(str, 'b');

    // Assert
    REQUIRE_NOT_NULL(found);
    CHECK_EQ(found - str, std::ptrdiff_t(4));
}

TEST(strrchr_single_occurrence) {
    // Arrange
    const char* str = "hello";

    // Act
    const char* found = my_strrchr(str, 'e');

    // Assert
    REQUIRE_NOT_NULL(found);
    CHECK_EQ(found - str, std::ptrdiff_t(1));
}

TEST(strrchr_cuts_file_name_from_path) {
    // Arrange
    const char* path = "path/to/file";

    // Act
    const char* found = my_strrchr(path, '/');

    // Assert
    REQUIRE_NOT_NULL(found);
    CHECK_STREQ(found, "/file");
}

TEST(strrchr_missing_character) {
    // Arrange
    const char* str = "abc";

    // Act
    const char* found = my_strrchr(str, 'z');

    // Assert
    CHECK_NULL(found);
}

TEST(strrchr_empty_string) {
    // Arrange
    const char* str = "";

    // Act
    const char* found = my_strrchr(str, 'a');

    // Assert
    CHECK_NULL(found);
}

TEST(strrchr_finds_terminator) {
    // Arrange
    const char* str = "abc";

    // Act
    const char* found = my_strrchr(str, '\0');

    // Assert
    REQUIRE_NOT_NULL(found);
    CHECK_EQ(found - str, std::ptrdiff_t(3));
}
