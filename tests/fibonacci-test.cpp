#include <gtest/gtest.h>
#include <vector>
#include <stdexcept>
#include <limits>
#include "fibonacci.h"

class FibonacciTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Настройка перед каждым тестом
    }
    
    void TearDown() override {
        // Очистка после каждого теста
    }
};

// Тест проверяет вызов с некорректным аргументом (n = 0)
TEST_F(FibonacciTest, ZeroInput) {
    EXPECT_THROW(FibonacciGenerator::generateFibonacci(0), std::invalid_argument);
}

// Тест проверяет вызов для одного элемента
TEST_F(FibonacciTest, SingleElement) {
    auto result = FibonacciGenerator::generateFibonacci(1);
    ASSERT_EQ(1, result.size());
    EXPECT_EQ(0, result[0]);
}

// Тест проверяет вызов для двух элементов
TEST_F(FibonacciTest, TwoElements) {
    auto result = FibonacciGenerator::generateFibonacci(2);
    ASSERT_EQ(2, result.size());
    EXPECT_EQ(0, result[0]);
    EXPECT_EQ(1, result[1]);
}

// Тест для проверки первых 10 чисел Фибоначчи
TEST_F(FibonacciTest, FirstTenElements) {
    auto result = FibonacciGenerator::generateFibonacci(10);
    
    ASSERT_EQ(10, result.size());
    
    // Проверяем каждый элемент
    std::vector<unsigned long long> expected = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34};
    for (size_t i = 0; i < expected.size(); ++i) {
        EXPECT_EQ(expected[i], result[i]) << "Несоответствие на позиции " << i;
    }
}

// Тест для проверки генерации средних последовательностей
TEST_F(FibonacciTest, MediumSequence) {
    auto result = FibonacciGenerator::generateFibonacci(20);
    
    ASSERT_EQ(20, result.size());
    
    // Проверяем несколько характерных значений из последовательности
    EXPECT_EQ(0, result[0]);
    EXPECT_EQ(1, result[1]);
    EXPECT_EQ(55, result[10]);
    EXPECT_EQ(6765, result[19]);
}

// Тест для больших чисел (но не вызывающих переполнение)
TEST_F(FibonacciTest, LargeValidNumbers) {
    // 92 - максимальный индекс, который помещается в unsigned long long
    auto result = FibonacciGenerator::generateFibonacci(92);
    
    ASSERT_EQ(92, result.size());
    
    // Проверяем последний элемент, который должен быть максимальным числом, 
    // которое помещается в unsigned long long
    EXPECT_EQ(7540113804746346429ULL, result[91]);
}

// Тест проверяет обработку переполнения
TEST_F(FibonacciTest, OverflowHandling) {
    // 93-е число Фибоначчи вызывает переполнение для unsigned long long
    EXPECT_THROW(FibonacciGenerator::generateFibonacci(93), std::overflow_error);
}

// Тест производительности для больших значений n
TEST_F(FibonacciTest, Performance) {
    // Засекаем время
    auto start = std::chrono::high_resolution_clock::now();
    
    auto result = FibonacciGenerator::generateFibonacci(50);
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    
    // Проверяем, что вычисление выполняется быстро (< 10 мс)
    EXPECT_LT(duration, 10);
    
    // Проверяем правильность конечного результата
    EXPECT_EQ(12586269025ULL, result[49]);
}

// Функция main является необязательной, если вы используете gtest_main
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
