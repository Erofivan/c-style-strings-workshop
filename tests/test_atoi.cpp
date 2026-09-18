#include "test_framework.h"

#include "my_cstring.h"

TEST(atoi_single_digit) {
    // Arrange
    const char* str = "7";

    // Act
    int value = my_atoi(str);

    // Assert
    CHECK_EQ(value, 7);
}

TEST(atoi_several_digits) {
    // Arrange
    const char* str = "1234567";

    // Act
    int value = my_atoi(str);

    // Assert
    CHECK_EQ(value, 1234567);
}

TEST(atoi_zero) {
    // Arrange
    const char* str = "0";

    // Act
    int value = my_atoi(str);

    // Assert
    CHECK_EQ(value, 0);
}

TEST(atoi_negative_number) {
    // Arrange
    const char* str = "-42";

    // Act
    int value = my_atoi(str);

    // Assert
    CHECK_EQ(value, -42);
}

TEST(atoi_explicit_plus_sign) {
    // Arrange
    const char* str = "+42";

    // Act
    int value = my_atoi(str);

    // Assert
    CHECK_EQ(value, 42);
}

TEST(atoi_skips_leading_whitespace) {
    // Arrange
    const char* str = "\t\n  -7";

    // Act
    int value = my_atoi(str);

    // Assert
    CHECK_EQ(value, -7);
}

TEST(atoi_stops_at_first_non_digit) {
    // Arrange
    const char* str = "42abc";

    // Act
    int value = my_atoi(str);

    // Assert
    CHECK_EQ(value, 42);
}

TEST(atoi_reads_only_integer_part) {
    // Arrange
    const char* str = "3.14";

    // Act
    int value = my_atoi(str);

    // Assert
    CHECK_EQ(value, 3);
}

TEST(atoi_string_without_digits) {
    // Arrange
    const char* str = "abc";

    // Act
    int value = my_atoi(str);

    // Assert
    CHECK_EQ(value, 0);
}

TEST(atoi_empty_string) {
    // Arrange
    const char* str = "";

    // Act
    int value = my_atoi(str);

    // Assert
    CHECK_EQ(value, 0);
}

TEST(atoi_sign_without_digits) {
    // Arrange
    const char* str = "-abc";

    // Act
    int value = my_atoi(str);

    // Assert
    CHECK_EQ(value, 0);
}

TEST(atoi_leading_zeros) {
    // Arrange
    const char* str = "-0042";

    // Act
    int value = my_atoi(str);

    // Assert
    CHECK_EQ(value, -42);
}

TEST(atoi_does_not_modify_string) {
    // Arrange
    char buffer[] = "42";

    // Act
    my_atoi(buffer);

    // Assert
    CHECK_STREQ(buffer, "42");
}
