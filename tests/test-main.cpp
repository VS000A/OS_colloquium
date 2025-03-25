#include <gtest/gtest.h>
#include <iostream>

// Функция main для запуска всех тестов
int main(int argc, char **argv) {
    std::cout << "Запуск тестов для всех задач..." << std::endl;
    
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
