#include "doctest/doctest.h"
#include "src/DoublyLinkedList.h"

TEST_SUITE("DoublyLinkedList Basic Operations")
{

    TEST_CASE("Insert at head and tail")
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

    TEST_CASE("Delete and reverse")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.insertAtTail(3); // [1, 2, 3]

        SUBCASE("Delete middle element")
        {
            list.deleteAt(1); // remove 2
            CHECK(list.size() == 2);
            CHECK(list.get(0) == 1);
            CHECK(list.get(1) == 3);
        }

        SUBCASE("Reverse list")
        {
            list.reverse(); // should become [3, 2, 1]
            CHECK(list.get(0) == 3);
            CHECK(list.get(2) == 1);
        }
    }
}

TEST_SUITE("DoublyLinkedList<Point> Operations")
{
    std::string pointToString(Point & p)
    {
        return "(" + std::to_string(int(p.getX())) + "," + std::to_string(int(p.getY())) + ")";
    }

    TEST_CASE("Insert and get Point")
    {
        DoublyLinkedList<Point> list;

        SUBCASE("Insert at head")
        {
            list.insertAtHead(Point(1, 2));
            list.insertAtHead(Point(3, 4));
            CHECK(list.size() == 2);
            CHECK(list.get(0) == Point(3, 4));
            CHECK(list.get(1) == Point(1, 2));
        }
    }

    TEST_CASE("To string of list<Point>")
    {
        DoublyLinkedList<Point> list;
        list.insertAtTail(Point(9, 0));
        list.insertAtTail(Point(8, 1));
        std::string str = list.toString(pointToString);
        CHECK(str == "[(9,0), (8,1)]");
    }
}

// TODO add test case
TEST_SUITE("DoublyLinkedList Additional Tests")
{
    TEST_CASE("Insert at arbitrary positions")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(3);
        list.insertAt(1, 2); // [1,2,3]
        CHECK(list.size() == 3);
        CHECK(list.get(0) == 1);
        CHECK(list.get(1) == 2);
        CHECK(list.get(2) == 3);
    }

    TEST_CASE("Delete head element")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(10);
        list.insertAtTail(20);
        list.deleteAt(0); // remove 10
        CHECK(list.size() == 1);
        CHECK(list.get(0) == 20);
    }

    TEST_CASE("Delete tail element")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(10);
        list.insertAtTail(20);
        list.deleteAt(1); // remove 20
        CHECK(list.size() == 1);
        CHECK(list.get(0) == 10);
    }

    TEST_CASE("IndexOf and contains")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(5);
        list.insertAtTail(6);
        list.insertAtTail(7);
        CHECK(list.indexOf(6) == 1);
        CHECK(list.contains(7));
        CHECK_FALSE(list.contains(10));
    }

    TEST_CASE("Reverse empty list")
    {
        DoublyLinkedList<int> list;
        list.reverse();
        CHECK(list.size() == 0);
    }

    TEST_CASE("Reverse single element list")
    {
        DoublyLinkedList<int> list;
        list.insertAtHead(42);
        list.reverse();
        CHECK(list.size() == 1);
        CHECK(list.get(0) == 42);
    }

    TEST_CASE("Iterator traverses list")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.insertAtTail(3);

        int values[3];
        int idx = 0;

        for (auto it = list.begin(); it != list.end(); ++it) {
            values[idx++] = *it;
        }

        CHECK(idx == 3);
        CHECK(values[0] == 1);
        CHECK(values[1] == 2);
        CHECK(values[2] == 3);
    }


    TEST_CASE("Iterator allows modification")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        for (auto it = list.begin(); it != list.end(); ++it) {
            *it = *it + 10;
        }
        CHECK(list.get(0) == 11);
        CHECK(list.get(1) == 12);
    }

    TEST_CASE("ToString with default convert2str")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        std::string s = list.toString();
        CHECK(s == "[1, 2]");
    }

    TEST_CASE("Exception when index out of range")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(99);
        CHECK_THROWS(list.get(5));
        CHECK_THROWS(list.deleteAt(2));
        CHECK_THROWS(list.insertAt(3, 100));
    }
}
