#include "test_framework.h"

#include "my_cstring.h"

TEST(strcmp_equal_strings) {
    // Arrange
    const char* lhs = "hello";
    const char* rhs = "hello";

    // Act
    int result = my_strcmp(lhs, rhs);

    // Assert
    CHECK_EQ(result, 0);
}

TEST(strcmp_two_empty_strings) {
    // Arrange
    const char* lhs = "";
    const char* rhs = "";

    // Act
    int result = my_strcmp(lhs, rhs);

    // Assert
    CHECK_EQ(result, 0);
}

TEST(strcmp_first_is_smaller) {
    // Arrange
    const char* lhs = "abc";
    const char* rhs = "abd";

    // Act
    int result = my_strcmp(lhs, rhs);

    // Assert
    CHECK_NEGATIVE(result);
}

TEST(strcmp_first_is_bigger) {
    // Arrange
    const char* lhs = "abd";
    const char* rhs = "abc";

    // Act
    int result = my_strcmp(lhs, rhs);

    // Assert
    CHECK_POSITIVE(result);
}

TEST(strcmp_empty_string_is_smaller) {
    // Arrange
    const char* lhs = "";
    const char* rhs = "a";

    // Act
    int result = my_strcmp(lhs, rhs);

    // Assert
    CHECK_NEGATIVE(result);
}

TEST(strcmp_prefix_is_smaller_than_whole_string) {
    // Arrange
    const char* prefix = "abc";
    const char* whole = "abcd";

    // Act
    int result = my_strcmp(prefix, whole);

    // Assert
    CHECK_NEGATIVE(result);
}

TEST(strcmp_uppercase_is_smaller_than_lowercase) {
    // Arrange
    const char* upper = "Apple";
    const char* lower = "apple";

    // Act
    int result = my_strcmp(upper, lower);

    // Assert
    CHECK_NEGATIVE(result);
}

TEST(strcmp_compares_bytes_as_unsigned) {
    // Arrange
    const char high_byte[] = {static_cast<char>(200), '\0'};
    const char* letter = "a";

    // Act
    int result = my_strcmp(high_byte, letter);

    // Assert
    CHECK_POSITIVE(result);
}

TEST(strcmp_does_not_modify_arguments) {
    // Arrange
    char lhs[] = "abc";
    char rhs[] = "abd";

    // Act
    my_strcmp(lhs, rhs);

    // Assert
    CHECK_STREQ(lhs, "abc");
    CHECK_STREQ(rhs, "abd");
}
