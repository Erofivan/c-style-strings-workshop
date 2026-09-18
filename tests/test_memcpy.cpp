#include "test_framework.h"

#include "my_cstring.h"

TEST(memcpy_copies_bytes) {
    // Arrange
    char dest[8];

    // Act
    my_memcpy(dest, "abcdefg", 8);

    // Assert
    CHECK_STREQ(dest, "abcdefg");
}

TEST(memcpy_returns_dest) {
    // Arrange
    char dest[4];

    // Act
    void* result = my_memcpy(dest, "abc", 4);

    // Assert
    CHECK_EQ(result, static_cast<void*>(dest));
}

TEST(memcpy_copies_zeros_inside_buffer) {
    // Arrange
    const char src[6] = {'a', '\0', 'b', '\0', 'c', '\0'};
    char dest[6];

    // Act
    my_memcpy(dest, src, 6);

    // Assert
    CHECK_BYTES(dest, src, 6);
}

TEST(memcpy_zero_count_changes_nothing) {
    // Arrange
    char dest[4] = "abc";

    // Act
    my_memcpy(dest, "xyz", 0);

    // Assert
    CHECK_STREQ(dest, "abc");
}

TEST(memcpy_does_not_touch_bytes_after_count) {
    // Arrange
    char dest[5] = "XXXX";

    // Act
    my_memcpy(dest, "ab", 2);

    // Assert
    CHECK_EQ(dest[2], 'X');
}

TEST(memcpy_works_with_int_array) {
    // Arrange
    int src[3] = {10, 20, 30};
    int dest[3] = {0, 0, 0};

    // Act
    my_memcpy(dest, src, sizeof(src));

    // Assert
    CHECK_EQ(dest[0], 10);
    CHECK_EQ(dest[2], 30);
}
