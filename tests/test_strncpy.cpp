#include "test_framework.h"

#include "my_cstring.h"

TEST(strncpy_returns_dest) {
    // Arrange
    char dest[8];

    // Act
    char* result = my_strncpy(dest, "abc", 8);

    // Assert
    CHECK_EQ(result, dest);
}

TEST(strncpy_pads_short_source_with_zeros) {
    // Arrange
    char dest[8];
    for (int i = 0; i < 8; ++i) {
        dest[i] = 'X';
    }

    // Act
    my_strncpy(dest, "ab", 5);

    // Assert
    CHECK_BYTES(dest, "ab\0\0\0", 5);
}

TEST(strncpy_does_not_write_past_count) {
    // Arrange
    char dest[8];
    for (int i = 0; i < 8; ++i) {
        dest[i] = 'X';
    }

    // Act
    my_strncpy(dest, "ab", 5);

    // Assert
    CHECK_EQ(dest[5], 'X');
}

TEST(strncpy_truncates_long_source_without_terminator) {
    // Arrange
    char dest[8];
    for (int i = 0; i < 8; ++i) {
        dest[i] = 'X';
    }

    // Act
    my_strncpy(dest, "abcdef", 3);

    // Assert
    CHECK_BYTES(dest, "abc", 3);
    CHECK_EQ(dest[3], 'X');
}

TEST(strncpy_exact_length_source_has_no_terminator) {
    // Arrange
    char dest[8];
    for (int i = 0; i < 8; ++i) {
        dest[i] = 'X';
    }

    // Act
    my_strncpy(dest, "abc", 3);

    // Assert
    CHECK_BYTES(dest, "abc", 3);
    CHECK_EQ(dest[3], 'X');
}

TEST(strncpy_zero_count_changes_nothing) {
    // Arrange
    char dest[4] = "abc";

    // Act
    my_strncpy(dest, "xyz", 0);

    // Assert
    CHECK_STREQ(dest, "abc");
}

TEST(strncpy_empty_source_fills_zeros) {
    // Arrange
    char dest[4];
    for (int i = 0; i < 4; ++i) {
        dest[i] = 'X';
    }

    // Act
    my_strncpy(dest, "", 3);

    // Assert
    CHECK_BYTES(dest, "\0\0\0", 3);
}
