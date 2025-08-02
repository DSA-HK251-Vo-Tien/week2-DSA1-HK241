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


    TEST_CASE("Empty list iterator")
    {
        DoublyLinkedList<int> list;
        int count = 0;
        for (auto it = list.begin(); it != list.end(); ++it) ++count;
        CHECK(count == 0);
    }

    TEST_CASE("Single element iteration")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(99);
        int sum = 0;
        for (auto it = list.begin(); it != list.end(); ++it) sum += *it;
        CHECK(sum == 99);
    }

    TEST_CASE("Iterator equality and inequality")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        auto it1 = list.begin();
        auto it2 = list.begin();
        auto it3 = list.end();
        CHECK(it1 == it2);
        ++it2;
        CHECK(it2 == it3);
        CHECK(it1 != it3);
    }

    TEST_CASE("Iterator with custom type")
    {
        DoublyLinkedList<Point> list;
        list.insertAtTail(Point(1,2));
        list.insertAtTail(Point(3,4));
        double sumX = 0;
        for (auto it = list.begin(); it != list.end(); ++it) sumX += it->getX();
        CHECK(sumX == 4);
    }

    TEST_CASE("Range-based for with empty list")
    {
        DoublyLinkedList<int> list;
        int count = 0;
        for (int x : list) (void)x, ++count;
        CHECK(count == 0);
    }

    TEST_CASE("Range-based for with one element")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(7);
        int count = 0;
        for (int x : list) { CHECK(x == 7); ++count; }
        CHECK(count == 1);
    }

    TEST_CASE("Iterator after reverse")
    {
        DoublyLinkedList<int> list;
        for (int i = 1; i <= 3; ++i) list.insertAtTail(i); // [1,2,3]
        list.reverse();
        int expected[] = {3,2,1};
        int idx = 0;
        for (int x : list) CHECK(x == expected[idx++]);
        CHECK(idx == 3);
    }

    TEST_CASE("Iterator with insertAtHead")
    {
        DoublyLinkedList<int> list;
        for (int i = 0; i < 5; ++i) list.insertAtHead(i);
        int expected[] = {4,3,2,1,0};
        int idx = 0;
        for (int x : list) CHECK(x == expected[idx++]);
        CHECK(idx == 5);
    }

    TEST_CASE("Iterator with insertAt")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(3);
        list.insertAt(1,2);
        int expected[] = {1,2,3};
        int idx = 0;
        for (int x : list) CHECK(x == expected[idx++]);
        CHECK(idx == 3);
    }

    TEST_CASE("Iterator after deleteAt")
    {
        DoublyLinkedList<int> list;
        for (int i = 0; i < 4; ++i) list.insertAtTail(i);
        list.deleteAt(2);
        int expected[] = {0,1,3};
        int idx = 0;
        for (int x : list) CHECK(x == expected[idx++]);
        CHECK(idx == 3);
    }

    TEST_CASE("Iterator with all elements deleted")
    {
        DoublyLinkedList<int> list;
        for (int i = 0; i < 3; ++i) list.insertAtTail(i);
        for (int i = 0; i < 3; ++i) list.deleteAt(0);
        int count = 0;
        for (int x : list) (void)x, ++count;
        CHECK(count == 0);
    }

    TEST_CASE("Iterator with duplicate values")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(1);
        list.insertAtTail(2);
        int expected[] = {1,1,2};
        int idx = 0;
        for (int x : list) CHECK(x == expected[idx++]);
        CHECK(idx == 3);
    }

    TEST_CASE("Iterator with Point type and reverse")
    {
        DoublyLinkedList<Point> list;
        list.insertAtTail(Point(1,2));
        list.insertAtTail(Point(3,4));
        list.reverse();
        double sumY = 0;
        for (auto it = list.begin(); it != list.end(); ++it) sumY += it->getY();
        CHECK(sumY == 6);
    }

    TEST_CASE("Iterator with only one Point")
    {
        DoublyLinkedList<Point> list;
        list.insertAtTail(Point(7,8));
        int count = 0;
        for (auto it = list.begin(); it != list.end(); ++it) {
            CHECK(it->getX() == 7);
            CHECK(it->getY() == 8);
            ++count;
        }
        CHECK(count == 1);
    }

    TEST_CASE("Iterator with empty Point list")
    {
        DoublyLinkedList<Point> list;
        int count = 0;
        for (auto it = list.begin(); it != list.end(); ++it) ++count;
        CHECK(count == 0);
    }

    TEST_CASE("Iterator with alternating insertAtHead and insertAtTail")
    {
        DoublyLinkedList<int> list;
        list.insertAtHead(1);
        list.insertAtTail(2);
        list.insertAtHead(0);
        list.insertAtTail(3);
        int expected[] = {0,1,2,3};
        int idx = 0;
        for (int x : list) CHECK(x == expected[idx++]);
        CHECK(idx == 4);
    }
}