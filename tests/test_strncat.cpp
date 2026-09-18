#include "test_framework.h"

#include "my_cstring.h"

TEST(strncat_appends_limited_number_of_chars) {
    // Arrange
    char dest[16] = "abc";

    // Act
    my_strncat(dest, "defgh", 2);

    // Assert
    CHECK_STREQ(dest, "abcde");
}

TEST(strncat_returns_dest) {
    // Arrange
    char dest[16] = "a";

    // Act
    char* result = my_strncat(dest, "bcd", 2);

    // Assert
    CHECK_EQ(result, dest);
}

TEST(strncat_count_bigger_than_source) {
    // Arrange
    char dest[16] = "abc";

    // Act
    my_strncat(dest, "de", 100);

    // Assert
    CHECK_STREQ(dest, "abcde");
}

TEST(strncat_zero_count_changes_nothing) {
    // Arrange
    char dest[16] = "abc";

    // Act
    my_strncat(dest, "xyz", 0);

    // Assert
    CHECK_STREQ(dest, "abc");
}

TEST(strncat_always_writes_terminator) {
    // Arrange
    char dest[16];
    for (int i = 0; i < 16; ++i) {
        dest[i] = 'X';
    }
    dest[0] = '\0';

    // Act
    my_strncat(dest, "abcdef", 3);

    // Assert
    CHECK_EQ(dest[3], '\0');
    CHECK_EQ(dest[4], 'X');
}

TEST(strncat_to_empty_dest) {
    // Arrange
    char dest[16] = "";

    // Act
    my_strncat(dest, "hello", 4);

    // Assert
    CHECK_STREQ(dest, "hell");
}
