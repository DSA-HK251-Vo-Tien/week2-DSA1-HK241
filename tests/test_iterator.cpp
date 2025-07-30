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

    TEST_CASE("Iterator out of bounds")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);

        auto it = list.begin();
        ++it; // Move to second element
        ++it; // Move to end (should throw)

        CHECK_THROWS_AS(++it, cursor_error);
    }

    TEST_CASE("Iterator comparison")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);

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

    TEST_CASE("Iterator with empty list")
    {
        DoublyLinkedList<int> list;
        auto it = list.begin();
        CHECK(it == list.end()); // Should be equal since the list is empty
        CHECK_THROWS_AS(++it, cursor_error); // Should throw when trying to increment
    }

    TEST_CASE("Iterator with single element")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(42);
        auto it = list.begin();
        CHECK(*it == 42);
        ++it;
        CHECK(it == list.end()); // Should be equal to end after incrementing
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

    TEST_CASE("Iterator with reverse list")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.insertAtTail(3);
        list.reverse(); // Reverse the list

        int expected[] = {3, 2, 1};
        int idx = 0;

        for (auto it = list.begin(); it != list.end(); ++it)
        {
            CHECK(*it == expected[idx++]);
        }
        CHECK(idx == 3);
    }
}