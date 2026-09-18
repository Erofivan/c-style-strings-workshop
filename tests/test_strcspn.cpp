#include "test_framework.h"

#include "my_cstring.h"

TEST(strcspn_finds_prefix_before_rejected_char) {
    // Arrange
    const char* str = "hello, world";
    const char* reject = ",";

    // Act
    std::size_t count = my_strcspn(str, reject);

    // Assert
    CHECK_EQ(count, std::size_t(5));
}

TEST(strcspn_several_rejected_chars) {
    // Arrange
    const char* str = "key=value";
    const char* reject = "=:";

    // Act
    std::size_t count = my_strcspn(str, reject);

    // Assert
    CHECK_EQ(count, std::size_t(3));
}

TEST(strcspn_first_char_is_rejected) {
    // Arrange
    const char* str = ",abc";
    const char* reject = ",";

    // Act
    std::size_t count = my_strcspn(str, reject);

    // Assert
    CHECK_EQ(count, std::size_t(0));
}

TEST(strcspn_no_rejected_chars_in_string) {
    // Arrange
    const char* str = "abc";
    const char* reject = "xyz";

    // Act
    std::size_t count = my_strcspn(str, reject);

    // Assert
    CHECK_EQ(count, std::size_t(3));
}

TEST(strcspn_empty_reject_set) {
    // Arrange
    const char* str = "abc";
    const char* reject = "";

    // Act
    std::size_t count = my_strcspn(str, reject);

    // Assert
    CHECK_EQ(count, std::size_t(3));
}

TEST(strcspn_empty_string) {
    // Arrange
    const char* str = "";
    const char* reject = "abc";

    // Act
    std::size_t count = my_strcspn(str, reject);

    // Assert
    CHECK_EQ(count, std::size_t(0));
}
