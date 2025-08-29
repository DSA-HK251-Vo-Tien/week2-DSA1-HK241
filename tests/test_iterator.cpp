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

    // ==================== Bổ sung test mới ====================
    TEST_CASE("Iteration over empty DoublyLinkedList")
    {
        DoublyLinkedList<int> list;
        CHECK(list.begin() == list.end());
    }

    TEST_CASE("Begin points to first element")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(99);
        auto it = list.begin();
        CHECK(*it == 99);
    }

    TEST_CASE("End points after last element")
    {
        DoublyLinkedList<int> list;
        auto it = list.end();
        CHECK(it == list.end());
    }

    TEST_CASE("Iterator increment and decrement")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        auto it = list.begin();
        CHECK(*it == 1);
        ++it;
        CHECK(*it == 2);
        --it;
        CHECK(*it == 1);
    }

    TEST_CASE("Iterate empty list")
    {
        DoublyLinkedList<int> list;
        int count = 0;
        for (int x : list)
        {
            count++;
        }
        CHECK(count == 0);
    }

    TEST_CASE("Iterator works after reverse")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.insertAtTail(3);
        list.reverse(); // [3,2,1]

        int expected[] = {3, 2, 1};
        int idx = 0;
        for (int x : list)
        {
            CHECK(x == expected[idx++]);
        }
    }
}
