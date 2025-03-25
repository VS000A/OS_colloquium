#include <iostream>
#include <string>
#include <vector>
#include <limits>

#include "fibonacci.h"
#include "palindrome.h"
#include "linked_list.h"

// Функция для вывода меню
void printMenu() {
    std::cout << "\n===== АЛГОРИТМИЧЕСКИЕ ЗАДАЧИ =====\n";
    std::cout << "1. Генерация чисел Фибоначчи\n";
    std::cout << "2. Проверка палиндрома\n";
    std::cout << "3. Разворот связного списка\n";
    std::cout << "0. Выход\n";
    std::cout << "Выберите задачу (0-3): ";
}

// Функция для обработки задачи с числами Фибоначчи
void fibonacciTask() {
    std::cout << "\n--- ГЕНЕРАЦИЯ ЧИСЕЛ ФИБОНАЧЧИ ---\n";
    
    unsigned int n;
    std::cout << "Введите количество чисел Фибоначчи для генерации: ";
    std::cin >> n;
    
    try {
        auto fibonacci = FibonacciGenerator::generateFibonacci(n);
        
        std::cout << "Первые " << n << " чисел Фибоначчи:\n";
        for (size_t i = 0; i < fibonacci.size(); ++i) {
            std::cout << fibonacci[i];
            if (i < fibonacci.size() - 1) {
                std::cout << ", ";
            }
            // Добавляем перенос строки каждые 10 чисел для удобства чтения
            if ((i + 1) % 10 == 0) {
                std::cout << "\n";
            }
        }
        std::cout << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
    }
}

// Функция для обработки задачи с проверкой палиндрома
void palindromeTask() {
    std::cout << "\n--- ПРОВЕРКА ПАЛИНДРОМА ---\n";
    
    long long number;
    std::cout << "Введите число для проверки: ";
    std::cin >> number;
    
    try {
        bool isPalindrome = PalindromeChecker::isPalindrome(number);
        bool isPalindromeNumeric = PalindromeChecker::isPalindromeNumeric(number);
        
        if (isPalindrome) {
            std::cout << "Число " << number << " является палиндромом.\n";
        } else {
            std::cout << "Число " << number << " не является палиндромом.\n";
        }
        
        // Проверяем, что оба метода дают одинаковый результат
        if (isPalindrome != isPalindromeNumeric) {
            std::cout << "Внимание: методы строкового и числового определения палиндрома дали разные результаты!\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
    }
}

// Функция для вывода списка
template <typename T>
void printList(const LinkedList<T>& list) {
    auto vec = list.toVector();
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
        if (i < vec.size() - 1) {
            std::cout << " -> ";
        }
    }
    std::cout << "\n";
}

// Функция для обработки задачи с разворотом связного списка
void linkedListTask() {
    std::cout << "\n--- РАЗВОРОТ СВЯЗНОГО СПИСКА ---\n";
    
    LinkedList<int> list;
    
    // Создаем список из введенных пользователем чисел
    std::cout << "Введите элементы списка (введите нечисловое значение для завершения):\n";
    
    int value;
    while (std::cin >> value) {
        list.pushBack(value);
    }
    
    // Сбрасываем состояние ввода
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    if (list.isEmpty()) {
        std::cout << "Список пуст.\n";
        return;
    }
    
    std::cout << "Исходный список: ";
    printList(list);
    
    // Создаем копию для демонстрации метода reverseCopy
    auto copyList = LinkedList<int>::reverseCopy(list);
    
    // Разворачиваем оригинальный список
    list.reverse();
    
    std::cout << "Развернутый список (методом reverse): ";
    printList(list);
    
    std::cout << "Развернутый список (методом reverseCopy): ";
    printList(copyList);
}

int main() {
    // Устанавливаем локаль для корректного отображения русских символов
    setlocale(LC_ALL, "");
    
    int choice;
    
    do {
        printMenu();
        std::cin >> choice;
        
        // Проверка корректности ввода
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка ввода. Пожалуйста, введите число от 0 до 3.\n";
            continue;
        }
        
        switch (choice) {
            case 1:
                fibonacciTask();
                break;
            case 2:
                palindromeTask();
                break;
            case 3:
                linkedListTask();
                break;
            case 0:
                std::cout << "Выход из программы.\n";
                break;
            default:
                std::cout << "Неверный выбор. Пожалуйста, введите число от 0 до 3.\n";
        }
    } while (choice != 0);
    
    return 0;
}
