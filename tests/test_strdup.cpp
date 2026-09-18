#include "test_framework.h"

#include "my_cstring.h"

TEST(strdup_copies_content) {
    // Arrange
    const char* original = "hello";

    // Act
    char* copy = my_strdup(original);

    // Assert
    REQUIRE_NOT_NULL(copy);
    CHECK_STREQ(copy, "hello");
    delete[] copy;
}

TEST(strdup_returns_new_memory) {
    // Arrange
    const char* original = "abc";

    // Act
    char* copy = my_strdup(original);

    // Assert
    REQUIRE_NOT_NULL(copy);
    CHECK(copy != original);
    delete[] copy;
}

TEST(strdup_copy_is_independent_from_original) {
    // Arrange
    char original[] = "abc";
    char* copy = my_strdup(original);
    REQUIRE_NOT_NULL(copy);

    // Act
    original[0] = 'z';

    // Assert
    CHECK_STREQ(copy, "abc");
    delete[] copy;
}

TEST(strdup_empty_string) {
    // Arrange
    const char* original = "";

    // Act
    char* copy = my_strdup(original);

    // Assert
    REQUIRE_NOT_NULL(copy);
    CHECK_EQ(copy[0], '\0');
    delete[] copy;
}

TEST(strdup_allocates_room_for_terminator) {
    // Arrange
    const char* original = "abcdef";

    // Act
    char* copy = my_strdup(original);

    // Assert
    REQUIRE_NOT_NULL(copy);
    CHECK_EQ(copy[6], '\0');
    delete[] copy;
}
