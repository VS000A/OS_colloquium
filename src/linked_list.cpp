// linked_list.h
#pragma once

#include <memory>
#include <stdexcept>
#include <iostream>
#include <vector>

template <typename T>
class LinkedList {
public:
    struct Node {
        T data;
        std::shared_ptr<Node> next;
        
        explicit Node(T value) : data(std::move(value)), next(nullptr) {}
    };
    
private:
    std::shared_ptr<Node> head_;
    size_t size_;
    
public:
    LinkedList() : head_(nullptr), size_(0) {}
    
    /**
     * Создание списка из вектора значений
     */
    explicit LinkedList(const std::vector<T>& values) : head_(nullptr), size_(0) {
        for (const auto& value : values) {
            pushBack(value);
        }
    }
    
    /**
     * Добавление элемента в конец списка
     */
    void pushBack(T value) {
        auto newNode = std::make_shared<Node>(std::move(value));
        
        if (!head_) {
            head_ = newNode;
        } else {
            auto current = head_;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
        
        ++size_;
    }
    
    /**
     * Добавление элемента в начало списка
     */
    void pushFront(T value) {
        auto newNode = std::make_shared<Node>(std::move(value));
        newNode->next = head_;
        head_ = newNode;
        ++size_;
    }
    
    /**
     * Получение размера списка
     */
    [[nodiscard]] size_t size() const {
        return size_;
    }
    
    /**
     * Проверка пустой ли список
     */
    [[nodiscard]] bool isEmpty() const {
        return size_ == 0;
    }
    
    /**
     * Получение указателя на голову списка
     */
    [[nodiscard]] std::shared_ptr<Node> getHead() const {
        return head_;
    }
    
    /**
     * Очистка списка
     */
    void clear() {
        head_ = nullptr;
        size_ = 0;
    }
    
    /**
     * Преобразование списка в вектор
     */
    [[nodiscard]] std::vector<T> toVector() const {
        std::vector<T> result;
        result.reserve(size_);
        
        auto current = head_;
        while (current) {
            result.push_back(current->data);
            current = current->next;
        }
        
        return result;
    }
    
    /**
     * Разворот связного списка (итеративный подход)
     * Меняет текущий список и возвращает указатель на новую голову
     */
    std::shared_ptr<Node> reverse() {
        if (!head_ || !head_->next) {
            return head_; // Пустой список или список из одного элемента не требует разворота
        }
        
        std::shared_ptr<Node> prev = nullptr;
        std::shared_ptr<Node> current = head_;
        std::shared_ptr<Node> next = nullptr;
        
        while (current) {
            // Сохраняем следующий узел
            next = current->next;
            
            // Меняем указатель текущего узла на предыдущий
            current->next = prev;
            
            // Переходим к следующей итерации
            prev = current;
            current = next;
        }
        
        // Обновляем голову списка
        head_ = prev;
        
        return head_;
    }
    
    /**
     * Статический метод для разворота списка без изменения оригинального списка
     * Возвращает новый развернутый список
     */
    static LinkedList<T> reverseCopy(const LinkedList<T>& list) {
        LinkedList<T> result;
        auto current = list.getHead();
        
        // Для каждого элемента в исходном списке добавляем его в начало нового списка
        while (current) {
            result.pushFront(current->data);
            current = current->next;
        }
        
        return result;
    }
};

// linked_list_test.cpp
#include <gtest/gtest.h>
#include "linked_list.h"

class LinkedListTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(LinkedListTest, EmptyList) {
    LinkedList<int> list;
    EXPECT_TRUE(list.isEmpty());
    EXPECT_EQ(0, list.size());
    
    auto reversed = list.reverse();
    EXPECT_EQ(nullptr, reversed);
    EXPECT_TRUE(list.isEmpty());
}

TEST_F(LinkedListTest, SingleElementList) {
    LinkedList<int> list;
    list.pushBack(42);
    
    EXPECT_FALSE(list.isEmpty());
    EXPECT_EQ(1, list.size());
    
    auto head = list.getHead();
    EXPECT_EQ(42, head->data);
    EXPECT_EQ(nullptr, head->next);
    
    auto reversed = list.reverse();
    EXPECT_EQ(42, reversed->data);
    EXPECT_EQ(nullptr, reversed->next);
    EXPECT_EQ(1, list.size());
}

TEST_F(LinkedListTest, MultiElementList) {
    LinkedList<int> list;
    list.pushBack(1);
    list.pushBack(2);
    list.pushBack(3);
    list.pushBack(4);
    list.pushBack(5);
    
    EXPECT_EQ(5, list.size());
    
    auto vec = list.toVector();
    ASSERT_EQ(5, vec.size());
    EXPECT_EQ(1, vec[0]);
    EXPECT_EQ(2, vec[1]);
    EXPECT_EQ(3, vec[2]);
    EXPECT_EQ(4, vec[3]);
    EXPECT_EQ(5, vec[4]);
    
    // Разворачиваем список
    auto reversed = list.reverse();
    
    // Проверяем развернутый список
    EXPECT_EQ(5, reversed->data);
    EXPECT_EQ(4, reversed->next->data);
    EXPECT_EQ(3, reversed->next->next->data);
    EXPECT_EQ(2, reversed->next->next->next->data);
    EXPECT_EQ(1, reversed->next->next->next->next->data);
    EXPECT_EQ(nullptr, reversed->next->next->next->next->next);
    
    auto reversedVec = list.toVector();
    ASSERT_EQ(5, reversedVec.size());
    EXPECT_EQ(5, reversedVec[0]);
    EXPECT_EQ(4, reversedVec[1]);
    EXPECT_EQ(3, reversedVec[2]);
    EXPECT_EQ(2, reversedVec[3]);
    EXPECT_EQ(1, reversedVec[4]);
}

TEST_F(LinkedListTest, ReverseTwice) {
    LinkedList<int> list;
    list.pushBack(1);
    list.pushBack(2);
    list.pushBack(3);
    
    // Разворачиваем список дважды должно вернуть исходный порядок
    list.reverse();
    list.reverse();
    
    auto vec = list.toVector();
    ASSERT_EQ(3, vec.size());
    EXPECT_EQ(1, vec[0]);
    EXPECT_EQ(2, vec[1]);
    EXPECT_EQ(3, vec[2]);
}

TEST_F(LinkedListTest, CreateFromVector) {
    std::vector<int> values = {10, 20, 30, 40, 50};
    LinkedList<int> list(values);
    
    EXPECT_EQ(5, list.size());
    
    auto vec = list.toVector();
    EXPECT_EQ(values, vec);
}

TEST_F(LinkedListTest, ReverseCopy) {
    LinkedList<int> original;
    original.pushBack(1);
    original.pushBack(2);
    original.pushBack(3);
    
    LinkedList<int> reversed = LinkedList<int>::reverseCopy(original);
    
    // Проверяем, что оригинальный список не изменился
    auto origVec = original.toVector();
    ASSERT_EQ(3, origVec.size());
    EXPECT_EQ(1, origVec[0]);
    EXPECT_EQ(2, origVec[1]);
    EXPECT_EQ(3, origVec[2]);
    
    // Проверяем, что новый список развернут
    auto revVec = reversed.toVector();
    ASSERT_EQ(3, revVec.size());
    EXPECT_EQ(3, revVec[0]);
    EXPECT_EQ(2, revVec[1]);
    EXPECT_EQ(1, revVec[2]);
}

TEST_F(LinkedListTest, ClearList) {
    LinkedList<int> list;
    list.pushBack(1);
    list.pushBack(2);
    
    EXPECT_EQ(2, list.size());
    
    list.clear();
    EXPECT_TRUE(list.isEmpty());
    EXPECT_EQ(0, list.size());
    EXPECT_EQ(nullptr, list.getHead());
}

TEST_F(LinkedListTest, PushFront) {
    LinkedList<int> list;
    list.pushFront(3);
    list.pushFront(2);
    list.pushFront(1);
    
    auto vec = list.toVector();
    ASSERT_EQ(3, vec.size());
    EXPECT_EQ(1, vec[0]);
    EXPECT_EQ(2, vec[1]);
    EXPECT_EQ(3, vec[2]);
}

// Пример использования
#include <iostream>
#include "linked_list.h"

template <typename T>
void printList(const LinkedList<T>& list) {
    auto vec = list.toVector();
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i];
        if (i < vec.size() - 1) {
            std::cout << " -> ";
        }
    }
    std::cout << std::endl;
}

int main() {
    try {
        LinkedList<int> list;
        
        // Заполняем список
        for (int i = 1; i <= 5; ++i) {
            list.pushBack(i);
        }
        
        std::cout << "Исходный список: ";
        printList(list);
        
        // Разворачиваем список
        list.reverse();
        
        std::cout << "Развернутый список: ";
        printList(list);
        
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }
}
