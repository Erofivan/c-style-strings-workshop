#include "test_framework.h"

#include "my_cstring.h"

TEST(strpbrk_finds_char_from_set) {
    // Arrange
    const char* str = "hello, world";
    const char* accept = ",;";

    // Act
    const char* found = my_strpbrk(str, accept);

    // Assert
    REQUIRE_NOT_NULL(found);
    CHECK_EQ(found - str, std::ptrdiff_t(5));
}

TEST(strpbrk_picks_earliest_position) {
    // Arrange
    const char* str = "a=b:c";
    const char* accept = ":=";

    // Act
    const char* found = my_strpbrk(str, accept);

    // Assert
    REQUIRE_NOT_NULL(found);
    CHECK_EQ(found - str, std::ptrdiff_t(1));
}

TEST(strpbrk_first_char_matches) {
    // Arrange
    const char* str = "=value";
    const char* accept = "=";

    // Act
    const char* found = my_strpbrk(str, accept);

    // Assert
    REQUIRE_NOT_NULL(found);
    CHECK_EQ(found - str, std::ptrdiff_t(0));
}

TEST(strpbrk_no_match) {
    // Arrange
    const char* str = "abc";
    const char* accept = "xyz";

    // Act
    const char* found = my_strpbrk(str, accept);

    // Assert
    CHECK_NULL(found);
}

TEST(strpbrk_empty_accept_set) {
    // Arrange
    const char* str = "abc";
    const char* accept = "";

    // Act
    const char* found = my_strpbrk(str, accept);

    // Assert
    CHECK_NULL(found);
}

TEST(strpbrk_empty_string) {
    // Arrange
    const char* str = "";
    const char* accept = "abc";

    // Act
    const char* found = my_strpbrk(str, accept);

    // Assert
    CHECK_NULL(found);
}
