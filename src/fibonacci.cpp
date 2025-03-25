// fibonacci.h
#pragma once

#include <vector>
#include <stdexcept>
#include <limits>

class FibonacciGenerator {
public:
    /**
     * Генерирует контейнер с первыми n чисел Фибоначчи
     * 
     * @param n Количество чисел Фибоначчи для генерации
     * @return Вектор с первыми n числами Фибоначчи
     * @throws std::invalid_argument если n равно 0
     * @throws std::overflow_error если вычисление приводит к переполнению
     */
    static std::vector<unsigned long long> generateFibonacci(unsigned int n) {
        if (n == 0) {
            throw std::invalid_argument("Количество чисел должно быть больше 0");
        }
        
        std::vector<unsigned long long> fibonacci;
        fibonacci.reserve(n); // Резервируем память для оптимизации
        
        // Первые два числа Фибоначчи
        fibonacci.push_back(0);
        if (n > 1) {
            fibonacci.push_back(1);
        }
        
        // Генерируем остальные числа
        for (unsigned int i = 2; i < n; ++i) {
            // Проверка на переполнение перед вычислением
            if (fibonacci[i-1] > std::numeric_limits<unsigned long long>::max() - fibonacci[i-2]) {
                throw std::overflow_error("Переполнение при вычислении числа Фибоначчи");
            }
            
            fibonacci.push_back(fibonacci[i-1] + fibonacci[i-2]);
        }
        
        return fibonacci;
    }
};

// fibonacci_test.cpp
#include <gtest/gtest.h>
#include "fibonacci.h"

class FibonacciTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(FibonacciTest, EmptyInput) {
    EXPECT_THROW(FibonacciGenerator::generateFibonacci(0), std::invalid_argument);
}

TEST_F(FibonacciTest, SingleElement) {
    auto result = FibonacciGenerator::generateFibonacci(1);
    ASSERT_EQ(1, result.size());
    EXPECT_EQ(0, result[0]);
}

TEST_F(FibonacciTest, TwoElements) {
    auto result = FibonacciGenerator::generateFibonacci(2);
    ASSERT_EQ(2, result.size());
    EXPECT_EQ(0, result[0]);
    EXPECT_EQ(1, result[1]);
}

TEST_F(FibonacciTest, TenElements) {
    auto result = FibonacciGenerator::generateFibonacci(10);
    ASSERT_EQ(10, result.size());
    
    // Первые 10 чисел Фибоначчи: 0, 1, 1, 2, 3, 5, 8, 13, 21, 34
    EXPECT_EQ(0, result[0]);
    EXPECT_EQ(1, result[1]);
    EXPECT_EQ(1, result[2]);
    EXPECT_EQ(2, result[3]);
    EXPECT_EQ(3, result[4]);
    EXPECT_EQ(5, result[5]);
    EXPECT_EQ(8, result[6]);
    EXPECT_EQ(13, result[7]);
    EXPECT_EQ(21, result[8]);
    EXPECT_EQ(34, result[9]);
}

// Тест на большие числа (может привести к переполнению на некоторых системах)
TEST_F(FibonacciTest, LargeNumbers) {
    // Выбираем значение, которое не должно приводить к переполнению для unsigned long long
    auto result = FibonacciGenerator::generateFibonacci(93);
    ASSERT_EQ(93, result.size());
    
    // Проверяем последние несколько чисел для подтверждения правильности
    EXPECT_EQ(7540113804746346429ULL, result[92]);
}

// Тест на проверку переполнения
TEST_F(FibonacciTest, Overflow) {
    // 94-е число Фибоначчи вызывает переполнение для unsigned long long
    EXPECT_THROW(FibonacciGenerator::generateFibonacci(94), std::overflow_error);
}

// Пример использования
#include <iostream>
#include "fibonacci.h"

int main(int argc, char* argv[]) {
    try {
        int n;
        std::cout << "Введите количество чисел Фибоначчи: ";
        std::cin >> n;
        
        auto fibonacci = FibonacciGenerator::generateFibonacci(n);
        
        std::cout << "Первые " << n << " чисел Фибоначчи:" << std::endl;
        for (size_t i = 0; i < fibonacci.size(); ++i) {
            std::cout << fibonacci[i];
            if (i < fibonacci.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << std::endl;
        
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }
}
