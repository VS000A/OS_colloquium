#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "linked_list.h"

class LinkedListTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Настройка перед каждым тестом
        // Проверяем размер
    EXPECT_EQ(5, list.size());
    
    // Проверяем содержимое
    auto vec = list.toVector();
    ASSERT_EQ(5, vec.size());
    EXPECT_EQ(10, vec[0]);
    EXPECT_EQ(20, vec[1]);
    EXPECT_EQ(30, vec[2]);
    EXPECT_EQ(40, vec[3]);
    EXPECT_EQ(50, vec[4]);
}

// Тест для проверки метода reverseCopy
TEST_F(LinkedListTest, ReverseCopy) {
    LinkedList<int> original;
    original.pushBack(1);
    original.pushBack(2);
    original.pushBack(3);
    
    // Создаем копию с развернутым порядком
    LinkedList<int> reversed = LinkedList<int>::reverseCopy(original);
    
    // Проверяем, что исходный список не изменился
    auto origVec = original.toVector();
    ASSERT_EQ(3, origVec.size());
    EXPECT_EQ(1, origVec[0]);
    EXPECT_EQ(2, origVec[1]);
    EXPECT_EQ(3, origVec[2]);
    
    // Проверяем, что копия содержит элементы в обратном порядке
    auto revVec = reversed.toVector();
    ASSERT_EQ(3, revVec.size());
    EXPECT_EQ(3, revVec[0]);
    EXPECT_EQ(2, revVec[1]);
    EXPECT_EQ(1, revVec[2]);
}

// Тест для проверки очистки списка
TEST_F(LinkedListTest, ClearList) {
    LinkedList<int> list;
    list.pushBack(1);
    list.pushBack(2);
    list.pushBack(3);
    
    EXPECT_EQ(3, list.size());
    
    list.clear();
    
    EXPECT_TRUE(list.isEmpty());
    EXPECT_EQ(0, list.size());
    EXPECT_EQ(nullptr, list.getHead());
}

// Тест для проверки работы с другими типами данных
TEST_F(LinkedListTest, StringList) {
    LinkedList<std::string> list;
    list.pushBack("Hello");
    list.pushBack("World");
    list.pushBack("C++");
    
    EXPECT_EQ(3, list.size());
    
    auto head = list.getHead();
    ASSERT_NE(nullptr, head);
    EXPECT_EQ("Hello", head->data);
    
    // Разворачиваем список
    auto reversed = list.reverse();
    
    // Проверяем развернутый список
    ASSERT_NE(nullptr, reversed);
    EXPECT_EQ("C++", reversed->data);
    
    ASSERT_NE(nullptr, reversed->next);
    EXPECT_EQ("World", reversed->next->data);
    
    ASSERT_NE(nullptr, reversed->next->next);
    EXPECT_EQ("Hello", reversed->next->next->data);
    
    EXPECT_EQ(nullptr, reversed->next->next->next);
}

// Тест для проверки производительности
TEST_F(LinkedListTest, Performance) {
    // Создаем большой список для тестирования производительности
    LinkedList<int> list;
    const int SIZE = 10000;
    
    // Замеряем время добавления элементов
    auto startPush = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < SIZE; ++i) {
        list.pushBack(i);
    }
    auto endPush = std::chrono::high_resolution_clock::now();
    auto durationPush = std::chrono::duration_cast<std::chrono::milliseconds>(endPush - startPush).count();
    
    // Проверяем, что все элементы добавлены корректно
    EXPECT_EQ(SIZE, list.size());
    
    // Замеряем время разворота списка
    auto startReverse = std::chrono::high_resolution_clock::now();
    list.reverse();
    auto endReverse = std::chrono::high_resolution_clock::now();
    auto durationReverse = std::chrono::duration_cast<std::chrono::milliseconds>(endReverse - startReverse).count();
    
    // Проверяем, что размер не изменился
    EXPECT_EQ(SIZE, list.size());
    
    // Выводим информацию о времени выполнения (для информации)
    std::cout << "Время добавления " << SIZE << " элементов: " << durationPush << " мс\n";
    std::cout << "Время разворота списка из " << SIZE << " элементов: " << durationReverse << " мс\n";
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

// Тест для проверки создания пустого списка
TEST_F(LinkedListTest, EmptyList) {
    LinkedList<int> list;
    
    EXPECT_TRUE(list.isEmpty());
    EXPECT_EQ(0, list.size());
    EXPECT_EQ(nullptr, list.getHead());
}

// Тест для проверки добавления одного элемента
TEST_F(LinkedListTest, PushBackSingleElement) {
    LinkedList<int> list;
    list.pushBack(42);
    
    EXPECT_FALSE(list.isEmpty());
    EXPECT_EQ(1, list.size());
    
    auto head = list.getHead();
    ASSERT_NE(nullptr, head);
    EXPECT_EQ(42, head->data);
    EXPECT_EQ(nullptr, head->next);
}

// Тест для проверки добавления нескольких элементов
TEST_F(LinkedListTest, PushBackMultipleElements) {
    LinkedList<int> list;
    list.pushBack(1);
    list.pushBack(2);
    list.pushBack(3);
    
    EXPECT_EQ(3, list.size());
    
    auto head = list.getHead();
    ASSERT_NE(nullptr, head);
    EXPECT_EQ(1, head->data);
    
    ASSERT_NE(nullptr, head->next);
    EXPECT_EQ(2, head->next->data);
    
    ASSERT_NE(nullptr, head->next->next);
    EXPECT_EQ(3, head->next->next->data);
    
    EXPECT_EQ(nullptr, head->next->next->next);
}

// Тест для проверки добавления элементов в начало списка
TEST_F(LinkedListTest, PushFrontElements) {
    LinkedList<int> list;
    list.pushFront(3);
    list.pushFront(2);
    list.pushFront(1);
    
    EXPECT_EQ(3, list.size());
    
    auto head = list.getHead();
    ASSERT_NE(nullptr, head);
    EXPECT_EQ(1, head->data);
    
    ASSERT_NE(nullptr, head->next);
    EXPECT_EQ(2, head->next->data);
    
    ASSERT_NE(nullptr, head->next->next);
    EXPECT_EQ(3, head->next->next->data);
    
    EXPECT_EQ(nullptr, head->next->next->next);
}

// Тест для проверки функции toVector
TEST_F(LinkedListTest, ToVector) {
    LinkedList<int> list;
    list.pushBack(1);
    list.pushBack(2);
    list.pushBack(3);
    
    auto vec = list.toVector();
    
    ASSERT_EQ(3, vec.size());
    EXPECT_EQ(1, vec[0]);
    EXPECT_EQ(2, vec[1]);
    EXPECT_EQ(3, vec[2]);
}

// Тест для проверки разворота пустого списка
TEST_F(LinkedListTest, ReverseEmptyList) {
    LinkedList<int> list;
    
    auto reversed = list.reverse();
    
    EXPECT_EQ(nullptr, reversed);
    EXPECT_TRUE(list.isEmpty());
}

// Тест для проверки разворота списка с одним элементом
TEST_F(LinkedListTest, ReverseSingleElementList) {
    LinkedList<int> list;
    list.pushBack(42);
    
    auto reversed = list.reverse();
    
    ASSERT_NE(nullptr, reversed);
    EXPECT_EQ(42, reversed->data);
    EXPECT_EQ(nullptr, reversed->next);
    EXPECT_EQ(1, list.size());
}

// Тест для проверки разворота списка с несколькими элементами
TEST_F(LinkedListTest, ReverseMultiElementList) {
    LinkedList<int> list;
    list.pushBack(1);
    list.pushBack(2);
    list.pushBack(3);
    list.pushBack(4);
    list.pushBack(5);
    
    auto reversed = list.reverse();
    
    // Проверяем, что указатель на голову корректен
    ASSERT_NE(nullptr, reversed);
    EXPECT_EQ(5, reversed->data);
    
    // Проверяем, что все элементы в списке изменили свой порядок
    ASSERT_NE(nullptr, reversed->next);
    EXPECT_EQ(4, reversed->next->data);
    
    ASSERT_NE(nullptr, reversed->next->next);
    EXPECT_EQ(3, reversed->next->next->data);
    
    ASSERT_NE(nullptr, reversed->next->next->next);
    EXPECT_EQ(2, reversed->next->next->next->data);
    
    ASSERT_NE(nullptr, reversed->next->next->next->next);
    EXPECT_EQ(1, reversed->next->next->next->next->data);
    
    EXPECT_EQ(nullptr, reversed->next->next->next->next->next);
    
    // Проверяем, что size не изменился
    EXPECT_EQ(5, list.size());
}

// Тест для проверки разворота списка дважды
TEST_F(LinkedListTest, ReverseTwice) {
    LinkedList<int> list;
    list.pushBack(1);
    list.pushBack(2);
    list.pushBack(3);
    
    // Разворачиваем список дважды, должны получить исходный порядок
    list.reverse();
    auto finalHead = list.reverse();
    
    // Проверяем, что порядок элементов соответствует исходному
    ASSERT_NE(nullptr, finalHead);
    EXPECT_EQ(1, finalHead->data);
    
    ASSERT_NE(nullptr, finalHead->next);
    EXPECT_EQ(2, finalHead->next->data);
    
    ASSERT_NE(nullptr, finalHead->next->next);
    EXPECT_EQ(3, finalHead->next->next->data);
    
    EXPECT_EQ(nullptr, finalHead->next->next->next);
}

// Тест для проверки создания списка из вектора
TEST_F(LinkedListTest, CreateFromVector) {
    std::vector<int> values = {10, 20, 30, 40, 50};
    LinkedList<int> list(values);