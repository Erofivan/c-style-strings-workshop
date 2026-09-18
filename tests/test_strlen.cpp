#include "test_framework.h"

#include "my_cstring.h"

TEST(strlen_empty_string) {
    // Arrange
    const char* str = "";

    // Act
    std::size_t length = my_strlen(str);

    // Assert
    CHECK_EQ(length, std::size_t(0));
}

TEST(strlen_single_char) {
    // Arrange
    const char* str = "a";

    // Act
    std::size_t length = my_strlen(str);

    // Assert
    CHECK_EQ(length, std::size_t(1));
}

TEST(strlen_several_words) {
    // Arrange
    const char* str = "hello, world";

    // Act
    std::size_t length = my_strlen(str);

    // Assert
    CHECK_EQ(length, std::size_t(12));
}

TEST(strlen_counts_whitespace) {
    // Arrange
    const char* str = "a\tb\nc ";

    // Act
    std::size_t length = my_strlen(str);

    // Assert
    CHECK_EQ(length, std::size_t(6));
}

TEST(strlen_stops_at_first_nul) {
    // Arrange
    char buffer[6] = {'a', 'b', '\0', 'c', 'd', '\0'};

    // Act
    std::size_t length = my_strlen(buffer);

    // Assert
    CHECK_EQ(length, std::size_t(2));
}

TEST(strlen_does_not_modify_string) {
    // Arrange
    char buffer[] = "abc";

    // Act
    my_strlen(buffer);

    // Assert
    CHECK_STREQ(buffer, "abc");
}

TEST(strlen_long_string) {
    // Arrange
    char buffer[101];
    for (int i = 0; i < 100; ++i) {
        buffer[i] = 'x';
    }
    buffer[100] = '\0';

    // Act
    std::size_t length = my_strlen(buffer);

    // Assert
    CHECK_EQ(length, std::size_t(100));
}
