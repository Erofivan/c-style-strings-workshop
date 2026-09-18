// ============================================================================
//  Песочница для первой части семинара: «как вообще устроены C-строки».
//  Здесь мы не пишем библиотеку — здесь мы щупаем руками массивы,
//  указатели и нуль-терминатор.
//
//  Сборка и запуск:
//      cmake --build build --target playground && ./build/playground
// ============================================================================

#include <iostream>
#include <string>

#include "my_cstring.h"

// ---------------------------------------------------------------- Шаг 1 ----
// std::string против char[]: что вообще такое «строка».
void step1_two_kinds_of_strings() {
    std::cout << "\n=== Шаг 1: std::string и C-строка ===\n";

    std::string modern = "abc";
    char legacy[] = "abc";  // это МАССИВ из 4 символов: 'a','b','c','\0'

    std::cout << "modern         = " << modern << "\n";
    std::cout << "legacy         = " << legacy << "\n";
    std::cout << "modern.size()  = " << modern.size() << "\n";
    std::cout << "sizeof(legacy) = " << sizeof(legacy) << "  <- 4, а не 3!\n";
}

// ---------------------------------------------------------------- Шаг 2 ----
// Нуль-терминатор: строка заканчивается там, где стоит '\0'.
void step2_where_the_string_ends() {
    std::cout << "\n=== Шаг 2: нуль-терминатор ===\n";

    char buffer[] = "abcdef";
    std::cout << "было:  " << buffer << "\n";

    buffer[3] = '\0';  // ставим «конец строки» посередине
    std::cout << "стало: " << buffer << "  <- 'def' никуда не делись, ";
    std::cout << "их просто больше не печатают\n";

    std::cout << "байты массива: ";
    for (std::size_t i = 0; i < sizeof(buffer); ++i) {
        char c = buffer[i];
        std::cout << "[" << (c == '\0' ? std::string("\\0") : std::string(1, c)) << "]";
    }
    std::cout << "\n";
}

// ---------------------------------------------------------------- Шаг 3 ----
// Массив без '\0' — undefined behaviour. Тот самый пример с мусором.
void step3_missing_terminator() {
    std::cout << "\n=== Шаг 3: массив без нуль-терминатора ===\n";

    char broken[] = {'a', 'b', 'c', 'd'};  // ВНИМАНИЕ: '\0' нет
    std::cout << "печатаем массив без '\\0': ";
    std::cout << broken << "\n";  // UB: печать поедет дальше массива
    std::cout << "^ здесь может быть мусор, может не быть — это UB\n";

    char fixed[] = {'a', 'b', 'c', 'd', '\0'};
    std::cout << "а так правильно: " << fixed << "\n";
}

// ---------------------------------------------------------------- Шаг 4 ----
// Как find-the-end работает изнутри: своими руками считаем длину.
void step4_length_by_hand() {
    std::cout << "\n=== Шаг 4: длина строки вручную ===\n";

    const char* str = "workshop";

    std::size_t len = 0;
    while (str[len] != '\0') {
        ++len;
    }
    std::cout << "длина '" << str << "' = " << len << "\n";
    std::cout << "то же самое через my_strlen = " << my_strlen(str) << "\n";
}

// ---------------------------------------------------------------- Шаг 5 ----
// Указатель и массив: str[i] это то же самое, что *(str + i).
void step5_pointer_arithmetic() {
    std::cout << "\n=== Шаг 5: указатель = массив ===\n";

    const char* str = "hello";
    std::cout << "str[1]      = " << str[1] << "\n";
    std::cout << "*(str + 1)  = " << *(str + 1) << "\n";
    std::cout << "str + 1     = " << (str + 1) << "  <- это тоже строка, ";
    std::cout << "просто начинается позже\n";
}

// ---------------------------------------------------------------- Шаг 6 ----
// Передача массива в функцию: он «разваливается» в указатель (array decay).
void print_sizeof_inside(char param[]) {
    // param здесь — это уже char*, а не массив. sizeof даст размер УКАЗАТЕЛЯ.
    // Компилятор на этой строке специально ругается (-Wsizeof-array-argument):
    // предупреждение — часть демонстрации, а не ошибка в коде.
    std::cout << "внутри функции sizeof(param) = " << sizeof(param) << "\n";
}

void step6_array_decay() {
    std::cout << "\n=== Шаг 6: массив в функции превращается в указатель ===\n";

    char buffer[64] = "abc";
    std::cout << "снаружи sizeof(buffer) = " << sizeof(buffer) << "\n";
    print_sizeof_inside(buffer);
    std::cout << "^ поэтому длину строки функция обязана искать по '\\0',\n";
    std::cout << "  а размер буфера ей приходится передавать отдельным аргументом\n";
}

// ---------------------------------------------------------------- Шаг 7 ----
// Функция меняет строку вызывающего: указатель ведёт в ЧУЖУЮ память.
void shout(char* str) {
    for (std::size_t i = 0; str[i] != '\0'; ++i) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = static_cast<char>(str[i] - 'a' + 'A');
        }
    }
}

void step7_functions_modify_caller_memory() {
    std::cout << "\n=== Шаг 7: функция меняет наш буфер ===\n";

    char buffer[] = "hello";
    shout(buffer);
    std::cout << "после shout(buffer): " << buffer << "\n";
}

// ---------------------------------------------------------------- Шаг 8 ----
// Литерал только для чтения, буфер — для записи.
void step8_literals_are_read_only() {
    std::cout << "\n=== Шаг 8: литерал нельзя менять ===\n";

    const char* literal = "hello";  // лежит в read-only памяти
    char buffer[] = "hello";        // КОПИЯ литерала в нашем массиве

    // literal[0] = 'H';  // <- раскомментировать: не соберётся (и правильно)
    buffer[0] = 'H';

    std::cout << "literal = " << literal << " (только читаем)\n";
    std::cout << "buffer  = " << buffer << " (можем менять)\n";
}

int main() {
    step1_two_kinds_of_strings();
    step2_where_the_string_ends();
    step3_missing_terminator();
    step4_length_by_hand();
    step5_pointer_arithmetic();
    step6_array_decay();
    step7_functions_modify_caller_memory();
    step8_literals_are_read_only();

    std::cout << "\nГотово. Теперь открываем cstring/my_cstring.cpp и начинаем с my_strlen.\n";
    return 0;
}
