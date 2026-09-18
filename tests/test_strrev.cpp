#include "test_framework.h"

#include "my_cstring.h"

TEST(strrev_reverses_even_length_string) {
    // Arrange
    char buffer[] = "abcd";

    // Act
    my_strrev(buffer);

    // Assert
    CHECK_STREQ(buffer, "dcba");
}

TEST(strrev_reverses_odd_length_string) {
    // Arrange
    char buffer[] = "abcde";

    // Act
    my_strrev(buffer);

    // Assert
    CHECK_STREQ(buffer, "edcba");
}

TEST(strrev_returns_same_pointer) {
    // Arrange
    char buffer[] = "abc";

    // Act
    char* result = my_strrev(buffer);

    // Assert
    CHECK_EQ(result, buffer);
}

TEST(strrev_single_char) {
    // Arrange
    char buffer[] = "a";

    // Act
    my_strrev(buffer);

    // Assert
    CHECK_STREQ(buffer, "a");
}

TEST(strrev_empty_string) {
    // Arrange
    char buffer[] = "";

    // Act
    my_strrev(buffer);

    // Assert
    CHECK_STREQ(buffer, "");
}

TEST(strrev_keeps_terminator_in_place) {
    // Arrange
    char buffer[6] = "abcd";
    buffer[5] = 'X';

    // Act
    my_strrev(buffer);

    // Assert
    CHECK_EQ(buffer[4], '\0');
    CHECK_EQ(buffer[5], 'X');
}

TEST(strrev_twice_gives_original_string) {
    // Arrange
    char buffer[] = "workshop";

    // Act
    my_strrev(buffer);
    my_strrev(buffer);

    // Assert
    CHECK_STREQ(buffer, "workshop");
}
