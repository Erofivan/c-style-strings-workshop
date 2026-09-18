#include "test_framework.h"

#include "my_cstring.h"

TEST(itoa_single_digit) {
    // Arrange
    char buffer[16];

    // Act
    my_itoa(7, buffer);

    // Assert
    CHECK_STREQ(buffer, "7");
}

TEST(itoa_several_digits) {
    // Arrange
    char buffer[16];

    // Act
    my_itoa(1234567, buffer);

    // Assert
    CHECK_STREQ(buffer, "1234567");
}

TEST(itoa_zero) {
    // Arrange
    char buffer[16];

    // Act
    my_itoa(0, buffer);

    // Assert
    CHECK_STREQ(buffer, "0");
}

TEST(itoa_negative_number) {
    // Arrange
    char buffer[16];

    // Act
    my_itoa(-1234, buffer);

    // Assert
    CHECK_STREQ(buffer, "-1234");
}

TEST(itoa_returns_buffer) {
    // Arrange
    char buffer[16];

    // Act
    char* result = my_itoa(123, buffer);

    // Assert
    CHECK_EQ(result, buffer);
}

TEST(itoa_writes_terminator_and_nothing_more) {
    // Arrange
    char buffer[16];
    for (int i = 0; i < 16; ++i) {
        buffer[i] = 'X';
    }

    // Act
    my_itoa(123, buffer);

    // Assert
    CHECK_EQ(buffer[3], '\0');
    CHECK_EQ(buffer[4], 'X');
}

TEST(itoa_int_max) {
    // Arrange
    char buffer[16];

    // Act
    my_itoa(2147483647, buffer);

    // Assert
    CHECK_STREQ(buffer, "2147483647");
}

TEST(itoa_int_min) {
    // Arrange
    char buffer[16];

    // Act
    my_itoa(-2147483647 - 1, buffer);

    // Assert
    CHECK_STREQ(buffer, "-2147483648");
}

TEST(itoa_and_atoi_are_inverse) {
    // Arrange
    char buffer[16];
    const int values[] = {0, 1, -1, 99, -99, 100000, -100000};

    // Act & Assert
    for (int value : values) {
        CHECK_EQ(my_atoi(my_itoa(value, buffer)), value);
    }
}
