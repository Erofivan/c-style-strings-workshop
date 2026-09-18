#include "test_framework.h"

#include "my_cstring.h"

TEST(strtok_returns_first_token) {
    // Arrange
    char buffer[] = "a,b,c";

    // Act
    char* token = my_strtok(buffer, ",");

    // Assert
    REQUIRE_NOT_NULL(token);
    CHECK_STREQ(token, "a");
}

TEST(strtok_returns_next_tokens_for_nullptr) {
    // Arrange
    char buffer[] = "a,b,c";
    my_strtok(buffer, ",");

    // Act
    char* second = my_strtok(nullptr, ",");
    char* third = my_strtok(nullptr, ",");

    // Assert
    REQUIRE_NOT_NULL(second);
    CHECK_STREQ(second, "b");
    REQUIRE_NOT_NULL(third);
    CHECK_STREQ(third, "c");
}

TEST(strtok_returns_nullptr_after_last_token) {
    // Arrange
    char buffer[] = "a,b";
    my_strtok(buffer, ",");
    my_strtok(nullptr, ",");

    // Act
    char* token = my_strtok(nullptr, ",");

    // Assert
    CHECK_NULL(token);
}

TEST(strtok_skips_repeated_delimiters) {
    // Arrange
    char buffer[] = ",,a,,,b,,";

    // Act
    char* first = my_strtok(buffer, ",");
    char* second = my_strtok(nullptr, ",");
    char* third = my_strtok(nullptr, ",");

    // Assert
    REQUIRE_NOT_NULL(first);
    CHECK_STREQ(first, "a");
    REQUIRE_NOT_NULL(second);
    CHECK_STREQ(second, "b");
    CHECK_NULL(third);
}

TEST(strtok_supports_several_delimiters) {
    // Arrange
    char buffer[] = "one two\tthree\nfour";
    const char* delims = " \t\n";
    const char* expected[] = {"one", "two", "three", "four"};

    // Act & Assert
    char* token = my_strtok(buffer, delims);
    for (int i = 0; i < 4; ++i) {
        REQUIRE_NOT_NULL(token);
        CHECK_STREQ(token, expected[i]);
        token = my_strtok(nullptr, delims);
    }
    CHECK_NULL(token);
}

TEST(strtok_string_without_delimiters) {
    // Arrange
    char buffer[] = "single";

    // Act
    char* token = my_strtok(buffer, ",");

    // Assert
    REQUIRE_NOT_NULL(token);
    CHECK_STREQ(token, "single");
}

TEST(strtok_string_of_delimiters_only) {
    // Arrange
    char buffer[] = ",,,";

    // Act
    char* token = my_strtok(buffer, ",");

    // Assert
    CHECK_NULL(token);
}

TEST(strtok_empty_string) {
    // Arrange
    char buffer[] = "";

    // Act
    char* token = my_strtok(buffer, ",");

    // Assert
    CHECK_NULL(token);
}

TEST(strtok_replaces_delimiter_with_terminator) {
    // Arrange
    char buffer[] = "ab,cd";

    // Act
    my_strtok(buffer, ",");

    // Assert
    CHECK_EQ(buffer[2], '\0');
}

TEST(strtok_restarts_on_new_string) {
    // Arrange
    char first_buffer[] = "a,b";
    char second_buffer[] = "x,y";
    my_strtok(first_buffer, ",");

    // Act
    char* first = my_strtok(second_buffer, ",");
    char* second = my_strtok(nullptr, ",");

    // Assert
    REQUIRE_NOT_NULL(first);
    CHECK_STREQ(first, "x");
    REQUIRE_NOT_NULL(second);
    CHECK_STREQ(second, "y");
}
