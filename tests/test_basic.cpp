#include "doctest/doctest.h"
#include "src/DoublyLinkedList.h"

TEST_SUITE("DoublyLinkedList Basic Operations")
{

        TEST_CASE("Insert at index 0 into empty list")
        {
            DoublyLinkedList<int> list;
            list.insertAt(0, 42);
            CHECK(list.size() == 1);
            CHECK(list.get(0) == 42);
        }

        TEST_CASE("Insert at index size (append)")
        {
            DoublyLinkedList<int> list;
            list.insertAtTail(1);
            list.insertAtTail(2);
            list.insertAt(2, 3);
            CHECK(list.size() == 3);
            CHECK(list.get(0) == 1);
            CHECK(list.get(1) == 2);
            CHECK(list.get(2) == 3);
        }

        TEST_CASE("Insert at middle index")
        {
            DoublyLinkedList<int> list;
            list.insertAtTail(1);
            list.insertAtTail(3);
            list.insertAt(1, 2);
            CHECK(list.size() == 3);
            CHECK(list.get(0) == 1);
            CHECK(list.get(1) == 2);
            CHECK(list.get(2) == 3);
        }

        TEST_CASE("Delete only element makes list empty")
        {
            DoublyLinkedList<int> list;
            list.insertAtTail(9);
            list.deleteAt(0);
            CHECK(list.size() == 0);
            CHECK(list.begin() == list.end());
        }

        TEST_CASE("Delete at head from multi-element list")
        {
            DoublyLinkedList<int> list;
            list.insertAtTail(1);
            list.insertAtTail(2);
            list.insertAtTail(3);
            list.deleteAt(0);
            CHECK(list.size() == 2);
            CHECK(list.get(0) == 2);
            CHECK(list.get(1) == 3);
        }

        TEST_CASE("Delete at tail from multi-element list")
        {
            DoublyLinkedList<int> list;
            list.insertAtTail(1);
            list.insertAtTail(2);
            list.insertAtTail(3);
            list.deleteAt(2);
            CHECK(list.size() == 2);
            CHECK(list.get(0) == 1);
            CHECK(list.get(1) == 2);
        }

        TEST_CASE("Delete at middle index")
        {
            DoublyLinkedList<int> list;
            list.insertAtTail(10);
            list.insertAtTail(20);
            list.insertAtTail(30);
            list.deleteAt(1);
            CHECK(list.size() == 2);
            CHECK(list.get(0) == 10);
            CHECK(list.get(1) == 30);
        }

        TEST_CASE("Get out of range throws")
        {
            DoublyLinkedList<int> list;
            list.insertAtTail(1);
            CHECK_THROWS_AS(list.get(-1), std::out_of_range);
            CHECK_THROWS_AS(list.get(1), std::out_of_range);
        }

        TEST_CASE("Delete out of range throws")
        {
            DoublyLinkedList<int> list;
            CHECK_THROWS_AS(list.deleteAt(0), std::out_of_range);
            list.insertAtTail(5);
            CHECK_THROWS_AS(list.deleteAt(1), std::out_of_range);
            CHECK_THROWS_AS(list.deleteAt(-1), std::out_of_range);
        }

        TEST_CASE("Insert out of range throws")
        {
            DoublyLinkedList<int> list;
            CHECK_THROWS_AS(list.insertAt(1, 7), std::out_of_range);
            CHECK_THROWS_AS(list.insertAt(-1, 7), std::out_of_range);
        }

        TEST_CASE("indexOf returns -1 for missing element")
        {
            DoublyLinkedList<int> list;
            list.insertAtTail(1);
            list.insertAtTail(2);
            CHECK(list.indexOf(3) == -1);
        }

        TEST_CASE("contains on empty and non-empty")
        {
            DoublyLinkedList<int> list;
            CHECK_FALSE(list.contains(1));
            list.insertAtTail(1);
            CHECK(list.contains(1));
            CHECK_FALSE(list.contains(2));
        }

        TEST_CASE("reverse on empty list no-op")
        {
            DoublyLinkedList<int> list;
            list.reverse();
            CHECK(list.size() == 0);
            CHECK(list.begin() == list.end());
        }

        TEST_CASE("reverse single element unchanged")
        {
            DoublyLinkedList<int> list;
            list.insertAtTail(99);
            list.reverse();
            CHECK(list.size() == 1);
            CHECK(list.get(0) == 99);
        }

        TEST_CASE("reverse even number of elements")
        {
            DoublyLinkedList<int> list;
            list.insertAtTail(1);
            list.insertAtTail(2);
            list.insertAtTail(3);
            list.insertAtTail(4);
            list.reverse();
            CHECK(list.get(0) == 4);
            CHECK(list.get(1) == 3);
            CHECK(list.get(2) == 2);
            CHECK(list.get(3) == 1);
        }

        TEST_CASE("reverse odd number of elements")
        {
            DoublyLinkedList<int> list;
            for (int i = 1; i <= 5; ++i) list.insertAtTail(i); // 1 2 3 4 5
            list.reverse(); // 5 4 3 2 1
            CHECK(list.get(0) == 5);
            CHECK(list.get(1) == 4);
            CHECK(list.get(2) == 3);
            CHECK(list.get(3) == 2);
            CHECK(list.get(4) == 1);
        }

        TEST_CASE("toString with char list")
        {
            DoublyLinkedList<char> list;
            list.insertAtTail('a');
            list.insertAtTail('b');
            list.insertAtTail('c');
            CHECK(list.toString() == std::string("abc"));
        }

        TEST_CASE("size reflects insertions and deletions")
        {
            DoublyLinkedList<int> list;
            CHECK(list.size() == 0);
            list.insertAtTail(1);
            list.insertAtTail(2);
            CHECK(list.size() == 2);
            list.deleteAt(1);
            CHECK(list.size() == 1);
            list.deleteAt(0);
            CHECK(list.size() == 0);
        }

        TEST_CASE("indexOf returns first occurrence with duplicates")
        {
            DoublyLinkedList<int> list;
            list.insertAtTail(7);
            list.insertAtTail(8);
            list.insertAtTail(7);
            CHECK(list.indexOf(7) == 0);
            CHECK(list.indexOf(8) == 1);
        }
        TEST_CASE("Insert at head/tail")
        {
            DoublyLinkedList<int> list;

            SUBCASE("Insert at head")
            {
                list.insertAtHead(2);
                list.insertAtHead(1);
                CHECK(list.size() == 2);
                CHECK(list.get(0) == 1);
                CHECK(list.get(1) == 2);
            }

            SUBCASE("Insert at tail")
            {
                list.insertAtTail(1);
                list.insertAtTail(2);
                CHECK(list.size() == 2);
                CHECK(list.get(0) == 1);
                CHECK(list.get(1) == 2);
            }
        }
}