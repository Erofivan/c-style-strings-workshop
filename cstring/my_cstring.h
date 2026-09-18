#pragma once

#include <cstddef>

std::size_t my_strlen(const char* str);
int my_strcmp(const char* lhs, const char* rhs);
int my_strncmp(const char* lhs, const char* rhs, std::size_t count);

char* my_strcpy(char* dest, const char* src);
char* my_strncpy(char* dest, const char* src, std::size_t count);
char* my_strcat(char* dest, const char* src);
char* my_strncat(char* dest, const char* src, std::size_t count);

const char* my_strchr(const char* str, int ch);
const char* my_strrchr(const char* str, int ch);
const char* my_strstr(const char* haystack, const char* needle);
std::size_t my_strspn(const char* str, const char* accept);
std::size_t my_strcspn(const char* str, const char* reject);
const char* my_strpbrk(const char* str, const char* accept);

void* my_memset(void* dest, int value, std::size_t count);
void* my_memcpy(void* dest, const void* src, std::size_t count);
void* my_memmove(void* dest, const void* src, std::size_t count);
int my_memcmp(const void* lhs, const void* rhs, std::size_t count);

char* my_strdup(const char* str);
char* my_strrev(char* str);
char* my_strtok(char* str, const char* delims);

int my_atoi(const char* str);
char* my_itoa(int value, char* buffer);
