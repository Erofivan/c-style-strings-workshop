#include "test_framework.h"

#include "my_cstring.h"

TEST(strncmp_zero_count_is_always_equal) {
    // Arrange
    const char* lhs = "abc";
    const char* rhs = "xyz";

    // Act
    int result = my_strncmp(lhs, rhs, 0);

    // Assert
    CHECK_EQ(result, 0);
}

TEST(strncmp_equal_prefix) {
    // Arrange
    const char* lhs = "abcdef";
    const char* rhs = "abcxyz";

    // Act
    int result = my_strncmp(lhs, rhs, 3);

    // Assert
    CHECK_EQ(result, 0);
}

TEST(strncmp_difference_inside_range) {
    // Arrange
    const char* lhs = "abcdef";
    const char* rhs = "abcxyz";

    // Act
    int result = my_strncmp(lhs, rhs, 4);

    // Assert
    CHECK_NEGATIVE(result);
}

TEST(strncmp_count_bigger_than_both_strings) {
    // Arrange
    const char* lhs = "ab";
    const char* rhs = "ab";

    // Act
    int result = my_strncmp(lhs, rhs, 100);

    // Assert
    CHECK_EQ(result, 0);
}

TEST(strncmp_stops_at_nul_of_shorter_string) {
    // Arrange
    const char* shorter = "ab";
    const char* longer = "abc";

    // Act
    int result = my_strncmp(shorter, longer, 100);

    // Assert
    CHECK_NEGATIVE(result);
}

TEST(strncmp_empty_against_non_empty) {
    // Arrange
    const char* empty = "";
    const char* other = "a";

    // Act
    int result = my_strncmp(empty, other, 5);

    // Assert
    CHECK_NEGATIVE(result);
}

TEST(strncmp_compares_bytes_as_unsigned) {
    // Arrange
    const char high_byte[] = {static_cast<char>(200), '\0'};
    const char* letter = "a";

    // Act
    int result = my_strncmp(high_byte, letter, 1);

    // Assert
    CHECK_POSITIVE(result);
}
