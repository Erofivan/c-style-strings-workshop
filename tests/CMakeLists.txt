# Каждой функции — свой файл тестов и свой исполняемый файл.
# Имя теста в CTest совпадает с именем функции без префикса my_.
set(WORKSHOP_TESTS
    strlen
    strcmp
    strncmp
    strcpy
    strncpy
    strcat
    strncat
    strchr
    strrchr
    strstr
    strspn
    strcspn
    strpbrk
    memset
    memcpy
    memmove
    memcmp
    strdup
    strrev
    strtok
    atoi
    itoa
)

foreach(test_name IN LISTS WORKSHOP_TESTS)
    add_executable(test_${test_name} test_${test_name}.cpp)
    target_link_libraries(test_${test_name} PRIVATE my_cstring)
    target_include_directories(test_${test_name} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
    add_test(NAME ${test_name} COMMAND test_${test_name})
endforeach()

# Запустить все тесты разом: cmake --build build --target check
add_custom_target(check
    COMMAND "${CMAKE_CTEST_COMMAND}" --output-on-failure
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
    DEPENDS ${WORKSHOP_TESTS_TARGETS}
)
foreach(test_name IN LISTS WORKSHOP_TESTS)
    add_dependencies(check test_${test_name})
endforeach()
