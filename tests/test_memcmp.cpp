#include "test_framework.h"

#include "my_cstring.h"

TEST(memcmp_equal_buffers) {
    // Arrange
    const char* lhs = "abc";
    const char* rhs = "abc";

    // Act
    int result = my_memcmp(lhs, rhs, 3);

    // Assert
    CHECK_EQ(result, 0);
}

TEST(memcmp_compares_only_first_count_bytes) {
    // Arrange
    const char* lhs = "abc";
    const char* rhs = "abd";

    // Act
    int result = my_memcmp(lhs, rhs, 2);

    // Assert
    CHECK_EQ(result, 0);
}

TEST(memcmp_first_buffer_is_smaller) {
    // Arrange
    const char* lhs = "abc";
    const char* rhs = "abd";

    // Act
    int result = my_memcmp(lhs, rhs, 3);

    // Assert
    CHECK_NEGATIVE(result);
}

TEST(memcmp_first_buffer_is_bigger) {
    // Arrange
    const char* lhs = "abd";
    const char* rhs = "abc";

    // Act
    int result = my_memcmp(lhs, rhs, 3);

    // Assert
    CHECK_POSITIVE(result);
}

TEST(memcmp_zero_count_is_always_equal) {
    // Arrange
    const char* lhs = "abc";
    const char* rhs = "xyz";

    // Act
    int result = my_memcmp(lhs, rhs, 0);

    // Assert
    CHECK_EQ(result, 0);
}

TEST(memcmp_does_not_stop_at_nul) {
    // Arrange
    const char lhs[4] = {'a', '\0', 'b', '\0'};
    const char rhs[4] = {'a', '\0', 'c', '\0'};

    // Act
    int result = my_memcmp(lhs, rhs, 4);

    // Assert
    CHECK_NEGATIVE(result);
}

TEST(memcmp_compares_bytes_as_unsigned) {
    // Arrange
    const unsigned char lhs[1] = {200};
    const unsigned char rhs[1] = {10};

    // Act
    int result = my_memcmp(lhs, rhs, 1);

    // Assert
    CHECK_POSITIVE(result);
}

TEST(memcmp_works_with_int_arrays) {
    // Arrange
    int lhs[2] = {1, 2};
    int rhs[2] = {1, 3};

    // Act
    int result = my_memcmp(lhs, rhs, sizeof(lhs));

    // Assert
    CHECK(result != 0);
}
