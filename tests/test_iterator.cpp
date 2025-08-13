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
    TEST_SUITE("DoublyLinkedList Iterator - Full Tests")
    {

        TEST_CASE("Empty list iterator")
        {
            DoublyLinkedList<int> list;
            int count = 0;
            for (int x : list)
                count++;
            CHECK(count == 0);
        }

        TEST_CASE("Single element iteration")
        {
            DoublyLinkedList<int> list;
            list.insertAtTail(5);
            for (int x : list)
            {
                CHECK(x == 5);
            }
        }

        TEST_CASE("Multiple elements forward iteration")
        {
            DoublyLinkedList<int> list;
            list.insertAtTail(1);
            list.insertAtTail(2);
            list.insertAtTail(3);
            int expected[] = {1, 2, 3};
            int i = 0;
            for (auto x : list)
                CHECK(x == expected[i++]);
            CHECK(i == 3);
        }

        TEST_CASE("Begin equals end on empty list")
        {
            DoublyLinkedList<int> list;
            CHECK(list.begin() == list.end());
        }

        TEST_CASE("Begin not equal to end when non-empty")
        {
            DoublyLinkedList<int> list;
            list.insertAtTail(42);
            CHECK(list.begin() != list.end());
        }

        TEST_CASE("Post-increment iterator")
        {
            DoublyLinkedList<int> list;
            list.insertAtTail(10);
            list.insertAtTail(20);
            auto it = list.begin();
            CHECK(*it == 10);
            it++;
            CHECK(*it == 20);
        }

        TEST_CASE("Iterator after deletion")
        {
            DoublyLinkedList<int> list;
            list.insertAtTail(1);
            list.insertAtTail(2);
            list.deleteAt(0);
            auto it = list.begin();
            CHECK(*it == 2);
        }

        TEST_CASE("Iterator stability after insert")
        {
            DoublyLinkedList<int> list;
            list.insertAtTail(5);
            auto it = list.begin();
            list.insertAtTail(10);
            CHECK(*it == 5);
        }

        TEST_CASE("Range-based for loop correctness")
        {
            DoublyLinkedList<int> list;
            list.insertAtTail(7);
            list.insertAtTail(8);
            list.insertAtTail(9);
            int expected[] = {7, 8, 9};
            int i = 0;
            for (int x : list)
                CHECK(x == expected[i++]);
        }

        TEST_CASE("Iterator over reversed list")
        {
            DoublyLinkedList<int> list;
            list.insertAtTail(3);
            list.insertAtTail(2);
            list.insertAtTail(1);
            list.reverse();
            int expected[] = {1, 2, 3};
            int i = 0;
            for (int x : list)
                CHECK(x == expected[i++]);
        }

        TEST_CASE("Iterator multiple cycles")
        {
            DoublyLinkedList<int> list;
            for (int i = 0; i < 3; ++i)
                list.insertAtTail(i);
            int cycle = 0;
            for (int x : list)
            {
                (void)x;
                cycle++;
            }
            CHECK(cycle == 3);
            cycle = 0;
            for (int x : list)
                cycle++;
            CHECK(cycle == 3);
        }

        TEST_CASE("Iterator comparison consistency")
        {
            DoublyLinkedList<int> list;
            list.insertAtTail(100);
            auto it1 = list.begin();
            auto it2 = list.begin();
            CHECK(it1 == it2);
            ++it1;
            CHECK(it1 != it2);
        }

        TEST_CASE("Modify values through iterator (if allowed)")
        {
            DoublyLinkedList<int> list;
            list.insertAtTail(1);
            list.insertAtTail(2);
            for (auto it = list.begin(); it != list.end(); ++it)
            {
                *it *= 2;
            }
            CHECK(list.get(0) == 2);
            CHECK(list.get(1) == 4);
        }

        TEST_CASE("Iterator on list with duplicate values")
        {
            DoublyLinkedList<int> list;
            list.insertAtTail(7);
            list.insertAtTail(7);
            list.insertAtTail(8);
            int sum = 0;
            for (int x : list)
                sum += x;
            CHECK(sum == 22);
        }

        TEST_CASE("Iterator not affected by reverse after creation")
        {
            DoublyLinkedList<int> list;
            list.insertAtTail(1);
            list.insertAtTail(2);
            auto it = list.begin();
            list.reverse();
            CHECK(*it == 1); // depends on implementation details
        }

        TEST_CASE("Empty list doesn't enter loop")
        {
            DoublyLinkedList<int> list;
            bool entered = false;
            for (int x : list)
                entered = true;
            CHECK(entered == false);
        }

        TEST_CASE("List with 100 elements")
        {
            DoublyLinkedList<int> list;
            for (int i = 0; i < 100; i++)
                list.insertAtTail(i);
            int count = 0;
            for (int x : list)
                CHECK(x == count++);
            CHECK(count == 100);
        }

        TEST_CASE("Iterator dereference and increment in same line")
        {
            DoublyLinkedList<int> list;
            list.insertAtTail(5);
            list.insertAtTail(10);
            auto it = list.begin();
            CHECK(*it++ == 5);
            CHECK(*it == 10);
        }

        TEST_CASE("Iterator over toString result")
        {
            DoublyLinkedList<int> list;
            list.insertAtTail(3);
            list.insertAtTail(6);
            list.insertAtTail(9);
            std::string str = list.toString();
            CHECK(str == "[3, 6, 9]");
        }
    }
}