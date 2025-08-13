#include "doctest/doctest.h"
#include "src/DoublyLinkedList.h"

TEST_SUITE("DoublyLinkedList Iterator")
{
    TEST_CASE("Iteration over DoublyLinkedList")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(10);
        list.insertAtTail(20);
        list.insertAtTail(30);

        int expected[] = {10, 20, 30};

        SUBCASE("Forward iteration using Iterator")
        {
            int idx = 0;
            for (auto it = list.begin(); it != list.end(); ++it)
            {
                CHECK(*it == expected[idx++]);
            }
            CHECK(idx == 3);
        }

        SUBCASE("Range-based for iteration")
        {
            int idx = 0;
            for (int x : list)
            {
                CHECK(x == expected[idx++]);
            }
            CHECK(idx == 3);
        }
    }

    TEST_CASE("Iterator functionality")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.insertAtTail(3);

        int sum = 0;
        for (int i = 0; i < list.size(); i++) {
            sum += list.get(i);
        }
        CHECK(sum == 6);
    }

TEST_CASE("Reverse iteration using Iterator")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(10);
        list.insertAtTail(20);
        list.insertAtTail(30);

        int expected[] = {10, 20, 30};

        SUBCASE("Reverse iteration using Iterator")
        {
            int idx = 2;

            for (auto it = list.end(); it != list.begin(); )
            {
                --it;
                CHECK(*it == expected[idx--]);
            }
            CHECK(idx == -1);
        }
    }

    TEST_CASE("Iterator equality and inequality")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);

        auto it1 = list.begin();
        auto it2 = list.begin();
        auto it3 = list.end();

        CHECK(it1 == it2);
        CHECK(it1 != it3);
    }

    TEST_CASE("Iterator comparison")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(4);

        auto it1 = list.begin();
        auto it2 = list.begin();
        auto it3 = list.end();

        CHECK(it1 != it3);
        CHECK(it1 == it2);
        ++it1;
        CHECK(it1 != it2);
    }

    TEST_CASE("Iterator dereference")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(5);
        list.insertAtTail(10);

        auto it = list.begin();
        CHECK(*it == 5);
        ++it;
        CHECK(*it == 10);
    }

    TEST_CASE("Iterator with single element")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(42);
        auto it = list.begin();
        CHECK(*it == 42);
        ++it;
        CHECK(it == list.end());
    }

    TEST_CASE("Iterator with custom data type")
    {
        DoublyLinkedList<std::string> list;
        list.insertAtTail("Hello");
        list.insertAtTail("World");

        std::string expected[] = {"Hello", "World"};
        int idx = 0;

        for (const auto &str : list)
        {
            CHECK(str == expected[idx++]);
        }
        CHECK(idx == 2);
    }

    TEST_CASE("Iterator with empty list")
    {
        DoublyLinkedList<int> list;
        auto it = list.begin();
        CHECK(it == list.end());
    
        SUBCASE("Empty list iteration")
        {
            int count = 0;
            for (auto &item : list)
            {
                count++;
            }
            CHECK(count == 0);
        }
    }

    TEST_CASE("Iterator with multiple elements")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.insertAtTail(3);

        int count = 0;
        for (auto &item : list)
        {
            count++;
        }
        CHECK(count == 3);
    }

    TEST_CASE("Iterator with mixed operations")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.insertAtTail(3);

        auto it = list.begin();
        CHECK(*it == 1);
        ++it;
        CHECK(*it == 2);
        --it;
        CHECK(*it == 1);
        ++it;
        ++it;
        CHECK(*it == 3);
    }

}