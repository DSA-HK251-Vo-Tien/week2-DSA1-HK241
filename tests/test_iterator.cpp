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

    TEST_CASE("Reverse iteration using Iterator")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(10);
        list.insertAtTail(20);
        list.insertAtTail(30);

        int expected[] = {10, 20, 30}; // it should be {10, 20, 30}

        SUBCASE("Reverse iteration using Iterator")
        {
            int idx = 2; // Start from last element

            // list.end() is not correct
            for (auto it = list.end(); it != list.begin(); )
            {
                --it; // Move to previous element
                CHECK(*it == expected[idx--]);
            }
            CHECK(idx == -1); // All elements should be checked
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

        CHECK(it1 == it2); // Same position
        CHECK(it1 != it3); // Different positions
    }

    //TODO add test case
}