#include "test_framework.h"

#include "my_cstring.h"

TEST(strcpy_copies_content) {
    // Arrange
    char dest[16];

    // Act
    my_strcpy(dest, "hello");

    // Assert
    CHECK_STREQ(dest, "hello");
}

TEST(strcpy_returns_dest) {
    // Arrange
    char dest[16];

    // Act
    char* result = my_strcpy(dest, "abc");

    // Assert
    CHECK_EQ(result, dest);
}

TEST(strcpy_writes_terminator) {
    // Arrange
    char dest[8];
    for (int i = 0; i < 8; ++i) {
        dest[i] = 'X';
    }

    // Act
    my_strcpy(dest, "abc");

    // Assert
    CHECK_EQ(dest[3], '\0');
}

TEST(strcpy_does_not_touch_bytes_after_terminator) {
    // Arrange
    char dest[8];
    for (int i = 0; i < 8; ++i) {
        dest[i] = 'X';
    }

    // Act
    my_strcpy(dest, "abc");

    // Assert
    CHECK_EQ(dest[4], 'X');
}

TEST(strcpy_empty_source) {
    // Arrange
    char dest[8] = "garbage";

    // Act
    my_strcpy(dest, "");

    // Assert
    CHECK_EQ(dest[0], '\0');
}

TEST(strcpy_overwrites_longer_content) {
    // Arrange
    char dest[16] = "very long text";

    // Act
    my_strcpy(dest, "short");

    // Assert
    CHECK_STREQ(dest, "short");
}

TEST(strcpy_does_not_modify_source) {
    // Arrange
    char dest[16];
    char src[] = "source";

    // Act
    my_strcpy(dest, src);

    // Assert
    CHECK_STREQ(src, "source");
}
