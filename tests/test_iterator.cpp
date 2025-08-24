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
    TEST_CASE("Empty list begin == end")
    {
        DoublyLinkedList<int> list;
        CHECK(list.begin() == list.end());
    }

    TEST_CASE("Single element list iteration")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(42);
        auto it = list.begin();
        CHECK(it != list.end());
        CHECK(*it == 42);
        ++it;
        CHECK(it == list.end());
    }

    TEST_CASE("Iterator prefix increment")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        auto it = list.begin();
        ++it;
        CHECK(*it == 2);
    }

    TEST_CASE("Iterator postfix increment")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(5);
        list.insertAtTail(10);
        auto it = list.begin();
        auto old = it++;
        CHECK(*old == 5);
        CHECK(*it == 10);
    }

    TEST_CASE("Iterator prefix decrement")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(7);
        list.insertAtTail(8);
        auto it = list.end();
        --it;
        CHECK(*it == 8);
    }

    TEST_CASE("Iterator postfix decrement")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(11);
        list.insertAtTail(22);
        list.insertAtTail(33);
        auto it = list.end();
        auto old = it--;
        CHECK(old == list.end()); // old giữ vị trí end
        --old; // lùi lại
        CHECK(*old == 33);
    }

    TEST_CASE("Iterators from copy are equal")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(99);
        auto it1 = list.begin();
        auto it2 = it1;
        CHECK(it1 == it2);
        CHECK(*it2 == 99);
    }

    TEST_CASE("Iterating backwards from end to begin")
    {
        DoublyLinkedList<int> list;
        for (int i = 1; i <= 3; i++) list.insertAtTail(i);
        int expected[] = {3, 2, 1};
        int idx = 0;
        for (auto it = --list.end(); ; --it)
        {
            CHECK(*it == expected[idx++]);
            if (it == list.begin()) break;
        }
        CHECK(idx == 3);
    }

    TEST_CASE("Range-based for with empty list")
    {
        DoublyLinkedList<int> list;
        int cnt = 0;
        for (int x : list) {
            (void)x;
            cnt++;
        }
        CHECK(cnt == 0);
    }

    TEST_CASE("Modify elements via iterator")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        for (auto it = list.begin(); it != list.end(); ++it)
        {
            *it = *it * 10;
        }
        int expected[] = {10, 20};
        int idx = 0;
        for (auto x : list)
        {
            CHECK(x == expected[idx++]);
        }
    }
}