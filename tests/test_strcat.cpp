#include "test_framework.h"

#include "my_cstring.h"

TEST(strcat_appends_to_the_end) {
    // Arrange
    char dest[16] = "hello";

    // Act
    my_strcat(dest, ", world");

    // Assert
    CHECK_STREQ(dest, "hello, world");
}

TEST(strcat_returns_dest) {
    // Arrange
    char dest[16] = "a";

    // Act
    char* result = my_strcat(dest, "b");

    // Assert
    CHECK_EQ(result, dest);
}

TEST(strcat_to_empty_dest) {
    // Arrange
    char dest[16] = "";

    // Act
    my_strcat(dest, "abc");

    // Assert
    CHECK_STREQ(dest, "abc");
}

TEST(strcat_empty_source) {
    // Arrange
    char dest[16] = "abc";

    // Act
    my_strcat(dest, "");

    // Assert
    CHECK_STREQ(dest, "abc");
}

TEST(strcat_can_be_called_twice) {
    // Arrange
    char dest[16] = "a";

    // Act
    my_strcat(dest, "b");
    my_strcat(dest, "c");

    // Assert
    CHECK_STREQ(dest, "abc");
}

TEST(strcat_writes_terminator_and_nothing_more) {
    // Arrange
    char dest[10];
    for (int i = 0; i < 10; ++i) {
        dest[i] = 'X';
    }
    dest[0] = 'a';
    dest[1] = '\0';

    // Act
    my_strcat(dest, "bc");

    // Assert
    CHECK_EQ(dest[3], '\0');
    CHECK_EQ(dest[4], 'X');
}

TEST(strcat_does_not_modify_source) {
    // Arrange
    char dest[16] = "abc";
    char src[] = "def";

    // Act
    my_strcat(dest, src);

    // Assert
    CHECK_STREQ(src, "def");
}
