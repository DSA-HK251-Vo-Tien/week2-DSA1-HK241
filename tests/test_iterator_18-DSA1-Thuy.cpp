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
    TEST_CASE("Multiple iterators ")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.insertAtTail(3);

        auto it1 = list.begin();
        auto it2 = list.begin();

        ++it1;
        CHECK(*it1 == 2);
        CHECK(*it2 == 1);
    }
    TEST_CASE("Iterator operator* returns reference")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(5);

        for (auto it = list.begin(); it != list.end(); ++it)
        {
            *it = 100;
        }

        CHECK(list.get(0) == 100);
    }
    TEST_CASE("Check value")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(0);
        list.insertAtTail(1);
        auto it1 = list.begin();
        ++it1;
        auto it2 = list.begin();
        CHECK(*it1 != *it2);
    }
    TEST_CASE("Iterator allows modifying elements via reference")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(10);
        list.insertAtTail(20);

        for (auto it = list.begin(); it != list.end(); ++it)
        {
            *it *= 2;
        }

        CHECK(list.get(0) == 20);
        CHECK(list.get(1) == 40);
    }
    TEST_CASE("Iterator allows modifying elements via reference v2")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(10);
        list.insertAtTail(20);

        for (auto it = list.begin(); it != list.end(); ++it)
        {
            *it *= 2;
            ++it;
        }

        CHECK(list.get(0) == 20);
        CHECK(list.get(1) == 20);
    }
}