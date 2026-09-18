#include "test_framework.h"

#include "my_cstring.h"

TEST(memmove_copies_when_areas_do_not_overlap) {
    // Arrange
    char dest[8];

    // Act
    my_memmove(dest, "abcdefg", 8);

    // Assert
    CHECK_STREQ(dest, "abcdefg");
}

TEST(memmove_returns_dest) {
    // Arrange
    char dest[4];

    // Act
    void* result = my_memmove(dest, "abc", 4);

    // Assert
    CHECK_EQ(result, static_cast<void*>(dest));
}

TEST(memmove_shifts_data_left) {
    // Arrange
    char buffer[8] = "abcdefg";

    // Act
    my_memmove(buffer, buffer + 2, 6);

    // Assert
    CHECK_STREQ(buffer, "cdefg");
}

TEST(memmove_shifts_data_right) {
    // Arrange
    char buffer[8] = "abcdefg";

    // Act
    my_memmove(buffer + 2, buffer, 5);
    buffer[7] = '\0';

    // Assert
    CHECK_STREQ(buffer, "ababcde");
}

TEST(memmove_same_pointer) {
    // Arrange
    char buffer[4] = "abc";

    // Act
    my_memmove(buffer, buffer, 4);

    // Assert
    CHECK_STREQ(buffer, "abc");
}

TEST(memmove_zero_count_changes_nothing) {
    // Arrange
    char buffer[4] = "abc";

    // Act
    my_memmove(buffer, buffer + 1, 0);

    // Assert
    CHECK_STREQ(buffer, "abc");
}
