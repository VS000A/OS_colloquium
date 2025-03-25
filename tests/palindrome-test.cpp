#include <gtest/gtest.h>
#include <limits>
#include "palindrome.h"

class PalindromeTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Настройка перед каждым тестом
    // Тест для проверки отрицательных чисел
TEST_F(PalindromeTest, NegativeStringPalindromes) {
    long long numbers[] = {-121, -12321, -1234321};
    for (long long num : numbers) {
        // Определение, являются ли отрицательные числа палиндромами, зависит от реализации
        // Наша реализация отбрасывает знак минус и проверяет только цифры
        EXPECT_TRUE(PalindromeChecker::isPalindrome(num)) << "Ошибка для числа " << num;
    }
}

// Тест для проверки очень больших палиндромов
TEST_F(PalindromeTest, VeryLargeStringPalindromes) {
    // Большие палиндромы
    EXPECT_TRUE(PalindromeChecker::isPalindrome(12345678987654321LL));
    EXPECT_TRUE(PalindromeChecker::isPalindrome(9876543210123456789LL));
}

// Тесты для числового метода проверки палиндрома

// Тест для проверки числа 0
TEST_F(PalindromeTest, ZeroIsNumericPalindrome) {
    EXPECT_TRUE(PalindromeChecker::isPalindromeNumeric(0));
}

// Тест для проверки однозначных чисел числовым методом
TEST_F(PalindromeTest, SingleDigitsAreNumericPalindromes) {
    for (int i = 1; i <= 9; ++i) {
        EXPECT_TRUE(PalindromeChecker::isPalindromeNumeric(i)) << "Ошибка для числа " << i;
    }
}

// Тест для проверки двузначных палиндромов числовым методом
TEST_F(PalindromeTest, TwoDigitNumericPalindromes) {
    int palindromes[] = {11, 22, 33, 44, 55, 66, 77, 88, 99};
    for (int num : palindromes) {
        EXPECT_TRUE(PalindromeChecker::isPalindromeNumeric(num)) << "Ошибка для числа " << num;
    }
}

// Тест для проверки двузначных не-палиндромов числовым методом
TEST_F(PalindromeTest, TwoDigitNumericNonPalindromes) {
    int nonPalindromes[] = {10, 12, 23, 34, 45, 56, 67, 78, 89};
    for (int num : nonPalindromes) {
        EXPECT_FALSE(PalindromeChecker::isPalindromeNumeric(num)) << "Ошибка для числа " << num;
    }
}

// Тест для проверки многозначных палиндромов числовым методом
TEST_F(PalindromeTest, MultiDigitNumericPalindromes) {
    long long palindromes[] = {121, 12321, 123321, 1234321, 12344321};
    for (long long num : palindromes) {
        EXPECT_TRUE(PalindromeChecker::isPalindromeNumeric(num)) << "Ошибка для числа " << num;
    }
}

// Тест для проверки чисел, заканчивающихся на 0
TEST_F(PalindromeTest, TrailingZeroesNumeric) {
    // Числа с 0 на конце (кроме 0) не могут быть палиндромами
    long long numbers[] = {10, 100, 1000, 1230, 5670};
    for (long long num : numbers) {
        EXPECT_FALSE(PalindromeChecker::isPalindromeNumeric(num)) << "Ошибка для числа " << num;
    }
}

// Тест для проверки согласованности результатов обоих методов
TEST_F(PalindromeTest, ConsistencyOfMethods) {
    // Проверяем, что оба метода дают одинаковый результат
    long long testNumbers[] = {
        0, 1, 9, 11, 12, 121, 123, 12321, 12345, 
        1234321, 1234567, 12345678987654321LL
    };
    
    for (long long num : testNumbers) {
        bool stringResult = PalindromeChecker::isPalindrome(num);
        bool numericResult = PalindromeChecker::isPalindromeNumeric(num);
        
        EXPECT_EQ(stringResult, numericResult) 
            << "Результаты методов не совпадают для числа " << num;
    }
}

// Тест производительности
TEST_F(PalindromeTest, Performance) {
    // Тестируем производительность обоих методов на большом числе
    long long largeNumber = 1234567890987654321LL;
    
    // Замеряем время для строкового метода
    auto stringStart = std::chrono::high_resolution_clock::now();
    bool stringResult = PalindromeChecker::isPalindrome(largeNumber);
    auto stringEnd = std::chrono::high_resolution_clock::now();
    auto stringDuration = std::chrono::duration_cast<std::chrono::microseconds>(stringEnd - stringStart).count();
    
    // Замеряем время для числового метода
    auto numericStart = std::chrono::high_resolution_clock::now();
    bool numericResult = PalindromeChecker::isPalindromeNumeric(largeNumber);
    auto numericEnd = std::chrono::high_resolution_clock::now();
    auto numericDuration = std::chrono::duration_cast<std::chrono::microseconds>(numericEnd - numericStart).count();
    
    // Проверяем, что оба метода дают одинаковый результат
    EXPECT_EQ(stringResult, numericResult);
    
    // Выводим информацию о времени выполнения (для информации)
    std::cout << "Время выполнения строкового метода: " << stringDuration << " микросекунд\n";
    std::cout << "Время выполнения числового метода: " << numericDuration << " микросекунд\n";
}

// Функция main является необязательной, если вы используете gtest_main
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
    
    void TearDown() override {
        // Очистка после каждого теста
    }
};

// Тесты для строкового метода проверки палиндрома

// Тест для проверки числа 0
TEST_F(PalindromeTest, ZeroIsStringPalindrome) {
    EXPECT_TRUE(PalindromeChecker::isPalindrome(0));
}

// Тест для проверки однозначных чисел
TEST_F(PalindromeTest, SingleDigitsAreStringPalindromes) {
    for (int i = 1; i <= 9; ++i) {
        EXPECT_TRUE(PalindromeChecker::isPalindrome(i)) << "Ошибка для числа " << i;
    }
}

// Тест для проверки двузначных палиндромов
TEST_F(PalindromeTest, TwoDigitStringPalindromes) {
    int palindromes[] = {11, 22, 33, 44, 55, 66, 77, 88, 99};
    for (int num : palindromes) {
        EXPECT_TRUE(PalindromeChecker::isPalindrome(num)) << "Ошибка для числа " << num;
    }
}

// Тест для проверки двузначных не-палиндромов
TEST_F(PalindromeTest, TwoDigitStringNonPalindromes) {
    int nonPalindromes[] = {10, 12, 23, 34, 45, 56, 67, 78, 89};
    for (int num : nonPalindromes) {
        EXPECT_FALSE(PalindromeChecker::isPalindrome(num)) << "Ошибка для числа " << num;
    }
}

// Тест для проверки многозначных палиндромов
TEST_F(PalindromeTest, MultiDigitStringPalindromes) {
    long long palindromes[] = {121, 12321, 123321, 1234321, 12344321};
    for (long long num : palindromes) {
        EXPECT_TRUE(PalindromeChecker::isPalindrome(num)) << "Ошибка для числа " << num;
    }
}

// Тест для проверки многозначных не-палиндромов
TEST_F(PalindromeTest, MultiDigitStringNonPalindromes) {
    long long nonPalindromes[] = {123, 1232, 12345, 123456, 1234567};
    for (long long num : nonPalindromes) {
        EXPECT_FALSE(PalindromeChecker::isPalindrome(num)) << "Ошибка для числа " << num;
    }
}