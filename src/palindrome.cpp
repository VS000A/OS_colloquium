// palindrome.h
#pragma once

#include <string>
#include <algorithm>
#include <cctype>

class PalindromeChecker {
public:
    /**
     * Проверяет, является ли число палиндромом
     * 
     * @param number Число для проверки
     * @return true если число является палиндромом, false в противном случае
     */
    static bool isPalindrome(long long number) {
        // Преобразуем число в строку для упрощения сравнения
        std::string str = std::to_string(number);
        
        // Для отрицательных чисел удаляем знак минус (опционально)
        if (number < 0) {
            str = str.substr(1);
        }
        
        // Сравниваем строку с ее обратной версией
        std::string reversedStr = str;
        std::reverse(reversedStr.begin(), reversedStr.end());
        
        return str == reversedStr;
    }
    
    /**
     * Альтернативный метод проверки палиндрома без преобразования числа в строку
     * 
     * @param number Число для проверки
     * @return true если число является палиндромом, false в противном случае
     */
    static bool isPalindromeNumeric(long long number) {
        // Обрабатываем отрицательные числа (опционально)
        if (number < 0) {
            number = -number;
        }
        
        // Обработка краевого случая для 0
        if (number == 0) {
            return true;
        }
        
        // Если число заканчивается на 0, но не равно 0, то оно не может быть палиндромом
        if (number % 10 == 0) {
            return false;
        }
        
        long long reversed = 0;
        long long original = number;
        
        // Разворачиваем число
        while (number > 0) {
            // Добавляем последнюю цифру к развернутому числу
            long long digit = number % 10;
            
            // Проверка на переполнение перед умножением
            if (reversed > LLONG_MAX / 10) {
                throw std::overflow_error("Переполнение при вычислении перевернутого числа");
            }
            reversed = reversed * 10 + digit;
            
            // Удаляем последнюю цифру из исходного числа
            number /= 10;
        }
        
        return original == reversed;
    }
};

// palindrome_test.cpp
#include <gtest/gtest.h>
#include "palindrome.h"

class PalindromeTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Тесты для метода, использующего строковое представление
TEST_F(PalindromeTest, ZeroIsStringPalindrome) {
    EXPECT_TRUE(PalindromeChecker::isPalindrome(0));
}

TEST_F(PalindromeTest, SingleDigitIsStringPalindrome) {
    for (int i = 1; i <= 9; ++i) {
        EXPECT_TRUE(PalindromeChecker::isPalindrome(i));
    }
}

TEST_F(PalindromeTest, MultiDigitStringPalindromes) {
    EXPECT_TRUE(PalindromeChecker::isPalindrome(11));
    EXPECT_TRUE(PalindromeChecker::isPalindrome(121));
    EXPECT_TRUE(PalindromeChecker::isPalindrome(12321));
    EXPECT_TRUE(PalindromeChecker::isPalindrome(1234321));
}

TEST_F(PalindromeTest, StringNonPalindromes) {
    EXPECT_FALSE(PalindromeChecker::isPalindrome(12));
    EXPECT_FALSE(PalindromeChecker::isPalindrome(123));
    EXPECT_FALSE(PalindromeChecker::isPalindrome(12345));
}

TEST_F(PalindromeTest, NegativeStringPalindromes) {
    // Для отрицательных чисел удаляем знак минус
    EXPECT_TRUE(PalindromeChecker::isPalindrome(-121));
    EXPECT_TRUE(PalindromeChecker::isPalindrome(-12321));
}

TEST_F(PalindromeTest, LargeStringPalindrome) {
    EXPECT_TRUE(PalindromeChecker::isPalindrome(123456787654321LL));
}

// Тесты для числового метода
TEST_F(PalindromeTest, ZeroIsNumericPalindrome) {
    EXPECT_TRUE(PalindromeChecker::isPalindromeNumeric(0));
}

TEST_F(PalindromeTest, SingleDigitIsNumericPalindrome) {
    for (int i = 1; i <= 9; ++i) {
        EXPECT_TRUE(PalindromeChecker::isPalindromeNumeric(i));
    }
}

TEST_F(PalindromeTest, MultiDigitNumericPalindromes) {
    EXPECT_TRUE(PalindromeChecker::isPalindromeNumeric(11));
    EXPECT_TRUE(PalindromeChecker::isPalindromeNumeric(121));
    EXPECT_TRUE(PalindromeChecker::isPalindromeNumeric(12321));
    EXPECT_TRUE(PalindromeChecker::isPalindromeNumeric(1234321));
}

TEST_F(PalindromeTest, NumericNonPalindromes) {
    EXPECT_FALSE(PalindromeChecker::isPalindromeNumeric(12));
    EXPECT_FALSE(PalindromeChecker::isPalindromeNumeric(123));
    EXPECT_FALSE(PalindromeChecker::isPalindromeNumeric(12345));
}

TEST_F(PalindromeTest, ZeroEndingNumericNonPalindrome) {
    EXPECT_FALSE(PalindromeChecker::isPalindromeNumeric(10));
    EXPECT_FALSE(PalindromeChecker::isPalindromeNumeric(100));
}

TEST_F(PalindromeTest, NegativeNumericPalindromes) {
    EXPECT_TRUE(PalindromeChecker::isPalindromeNumeric(-121));
    EXPECT_TRUE(PalindromeChecker::isPalindromeNumeric(-12321));
}

TEST_F(PalindromeTest, CompareStringAndNumericMethods) {
    // Оба метода должны давать одинаковый результат
    for (long long num : {0LL, 1LL, 11LL, 121LL, 12321LL, 123LL, 456LL}) {
        EXPECT_EQ(PalindromeChecker::isPalindrome(num), 
                  PalindromeChecker::isPalindromeNumeric(num));
    }
}

// Пример использования
#include <iostream>
#include "palindrome.h"

int main(int argc, char* argv[]) {
    try {
        long long number;
        std::cout << "Введите число для проверки палиндрома: ";
        std::cin >> number;
        
        bool isPalindrome = PalindromeChecker::isPalindrome(number);
        
        if (isPalindrome) {
            std::cout << "Число " << number << " является палиндромом." << std::endl;
        } else {
            std::cout << "Число " << number << " не является палиндромом." << std::endl;
        }
        
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }
}
