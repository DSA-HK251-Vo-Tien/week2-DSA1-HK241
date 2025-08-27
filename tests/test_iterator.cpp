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

        SUBCASE("Begin should equal end")
        {
            auto it = list.begin();
            auto endIt = list.end();
            CHECK(it == endIt);
        }

        SUBCASE("Range-based for loop should not execute")
        {
            int count = 0;
            for (int x : list)
            {
                count++;
            }
            CHECK(count == 0);
        }
    }

    TEST_CASE("Iterator after modifications")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.insertAtTail(3);

        auto it = list.begin();
        CHECK(*it == 1);
        ++it;
        CHECK(*it == 2);

        list.insertAtHead(0); // List is now 0, 1, 2, 3
        it = list.begin();
        CHECK(*it == 0);
        ++it;
        CHECK(*it == 1);

        list.deleteAt(1); // Remove '1', List is now 0, 2, 3
        it = list.begin();
        CHECK(*it == 0);
        ++it;
        CHECK(*it == 2);
    }
}