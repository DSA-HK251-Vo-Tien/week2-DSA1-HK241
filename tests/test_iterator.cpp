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

    // TODO add test case
    TEST_CASE("Iterator on empty list")
    {
        DoublyLinkedList<int> list;

        int count = 0;
        for (auto it = list.begin(); it != list.end(); ++it)
        {
            count++;
        }

        CHECK(count == 0);

        for (int x : list)
        {
            FAIL("Should not enter loop for empty list");
        }
    }
        TEST_CASE("Iterator after reverse")
    {
        DoublyLinkedList<int> list;
        for (int i = 1; i <= 5; ++i)
            list.insertAtTail(i);

        list.reverse();

        int expected[] = {5,4,3,2,1};
        int idx = 0;
        for (int x : list)
        {
            CHECK(x == expected[idx++]);
        }
        CHECK(idx == 5);
    }
    TEST_CASE("Iterator single-element list")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(42);

        SUBCASE("Loop through manually")
        {
            auto it = list.begin();
            CHECK(it != list.end());
            CHECK(*it == 42);
            ++it;
            CHECK(it == list.end());
        }

        SUBCASE("Range-based for")
        {
            int count = 0;
            for (int x : list)
            {
                CHECK(x == 42);
                count++;
            }
            CHECK(count == 1);
        }
    }
    TEST_CASE("Iterator after reverse")
    {
        DoublyLinkedList<int> list;
        for (int i = 1; i <= 4; ++i)
            list.insertAtTail(i);  // [1, 2, 3, 4]

        list.reverse(); // [4, 3, 2, 1]
        int expected[] = {4, 3, 2, 1};

        int idx = 0;
        for (int x : list)
        {
            CHECK(x == expected[idx++]);
        }
        CHECK(idx == 4);
    }
}