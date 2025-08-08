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
}

TEST_SUITE("them 4 test case") {
    TEST_CASE("iter1") {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.insertAtTail(3);
        int count = 0;
        for (auto x : list) count++;
        CHECK(count == 3);
    }

    TEST_CASE("iter2") {
        DoublyLinkedList<int> list;
        list.insertAtHead(10);
        list.insertAtHead(20);
        int count = 0;
        for (auto x : list) count++;
        CHECK(count == 2);
    }

    TEST_CASE("iter3") {
        DoublyLinkedList<int> list;
        int count = 0;
        for (auto x : list) count++;
        CHECK(count == 0);
    }

    TEST_CASE("iter4") {
        DoublyLinkedList<int> list;
        list.insertAtTail(42);
        int count = 0;
        for (auto x : list) count++;
        CHECK(count == 1);
    }
}