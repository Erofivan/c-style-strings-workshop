#include "test_framework.h"

#include "my_cstring.h"

TEST(strspn_whole_string_matches) {
    // Arrange
    const char* str = "abcabc";
    const char* accept = "cba";

    // Act
    std::size_t count = my_strspn(str, accept);

    // Assert
    CHECK_EQ(count, std::size_t(6));
}

TEST(strspn_stops_at_first_foreign_char) {
    // Arrange
    const char* str = "129abc";
    const char* accept = "0123456789";

    // Act
    std::size_t count = my_strspn(str, accept);

    // Assert
    CHECK_EQ(count, std::size_t(3));
}

TEST(strspn_counts_leading_spaces) {
    // Arrange
    const char* str = "   text";
    const char* accept = " ";

    // Act
    std::size_t count = my_strspn(str, accept);

    // Assert
    CHECK_EQ(count, std::size_t(3));
}

TEST(strspn_first_char_is_foreign) {
    // Arrange
    const char* str = "xabc";
    const char* accept = "abc";

    // Act
    std::size_t count = my_strspn(str, accept);

    // Assert
    CHECK_EQ(count, std::size_t(0));
}

TEST(strspn_empty_string) {
    // Arrange
    const char* str = "";
    const char* accept = "abc";

    // Act
    std::size_t count = my_strspn(str, accept);

    // Assert
    CHECK_EQ(count, std::size_t(0));
}

TEST(strspn_empty_accept_set) {
    // Arrange
    const char* str = "abc";
    const char* accept = "";

    // Act
    std::size_t count = my_strspn(str, accept);

    // Assert
    CHECK_EQ(count, std::size_t(0));
}

TEST(strspn_duplicate_chars_in_accept_set) {
    // Arrange
    const char* str = "aabbcc";
    const char* accept = "aabb";

    // Act
    std::size_t count = my_strspn(str, accept);

    // Assert
    CHECK_EQ(count, std::size_t(4));
}
