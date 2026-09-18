#include "test_framework.h"

#include "my_cstring.h"

TEST(memset_fills_part_of_buffer) {
    // Arrange
    char buffer[6] = "abcde";

    // Act
    my_memset(buffer, 'x', 3);

    // Assert
    CHECK_STREQ(buffer, "xxxde");
}

TEST(memset_returns_dest) {
    // Arrange
    char buffer[4];

    // Act
    void* result = my_memset(buffer, 0, 4);

    // Assert
    CHECK_EQ(result, static_cast<void*>(buffer));
}

TEST(memset_zeroes_buffer) {
    // Arrange
    char buffer[4] = "abc";

    // Act
    my_memset(buffer, 0, 4);

    // Assert
    CHECK_BYTES(buffer, "\0\0\0\0", 4);
}

TEST(memset_zero_count_changes_nothing) {
    // Arrange
    char buffer[4] = "abc";

    // Act
    my_memset(buffer, 'z', 0);

    // Assert
    CHECK_STREQ(buffer, "abc");
}

TEST(memset_does_not_touch_bytes_after_count) {
    // Arrange
    unsigned char buffer[5] = {1, 2, 3, 4, 5};

    // Act
    my_memset(buffer, 9, 2);

    // Assert
    CHECK_EQ(int(buffer[1]), 9);
    CHECK_EQ(int(buffer[2]), 3);
}

TEST(memset_works_with_int_array) {
    // Arrange
    int numbers[3] = {1, 2, 3};

    // Act
    my_memset(numbers, 0, sizeof(numbers));

    // Assert
    CHECK_EQ(numbers[0], 0);
    CHECK_EQ(numbers[2], 0);
}

TEST(memset_truncates_value_to_one_byte) {
    // Arrange
    char buffer[3];

    // Act
    my_memset(buffer, 0x141, 2);
    buffer[2] = '\0';

    // Assert
    CHECK_STREQ(buffer, "AA");
}
