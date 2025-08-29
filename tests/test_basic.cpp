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

// ==================== Bổ sung test mới ====================

TEST_SUITE("DoublyLinkedList Extended")
{
    TEST_CASE("Insert at index middle")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(3);
        list.insertAt(1, 2); // [1,2,3]
        CHECK(list.toString() == "[1, 2, 3]");
    }

    TEST_CASE("Insert at index 0 behaves like head")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(2);
        list.insertAt(0, 1);
        CHECK(list.get(0) == 1);
    }

    TEST_CASE("Insert at index=size behaves like tail")
    {
        DoublyLinkedList<int> list;
        list.insertAtHead(1);
        list.insertAt(1, 2);
        CHECK(list.get(1) == 2);
    }

    TEST_CASE("Insert invalid index throws")
    {
        DoublyLinkedList<int> list;
        CHECK_THROWS(list.insertAt(-1, 5));
        CHECK_THROWS(list.insertAt(2, 5));
    }

    TEST_CASE("Delete at head")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.deleteAt(0);
        CHECK(list.get(0) == 2);
    }

    TEST_CASE("Delete at tail")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.deleteAt(1);
        CHECK(list.size() == 1);
        CHECK(list.get(0) == 1);
    }

    TEST_CASE("Delete invalid index throws")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        CHECK_THROWS(list.deleteAt(5));
    }

    TEST_CASE("Get invalid index throws")
    {
        DoublyLinkedList<int> list;
        CHECK_THROWS(list.get(0));
    }

    TEST_CASE("IndexOf finds element")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(10);
        list.insertAtTail(20);
        CHECK(list.indexOf(20) == 1);
        CHECK(list.indexOf(99) == -1);
    }

    TEST_CASE("Contains works")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(5);
        CHECK(list.contains(5));
        CHECK_FALSE(list.contains(10));
    }

    TEST_CASE("Size updates after operations")
    {
        DoublyLinkedList<int> list;
        CHECK(list.size() == 0);
        list.insertAtTail(1);
        list.insertAtTail(2);
        CHECK(list.size() == 2);
        list.deleteAt(1);
        CHECK(list.size() == 1);
    }

    TEST_CASE("Reverse empty list safe")
    {
        DoublyLinkedList<int> list;
        list.reverse();
        CHECK(list.size() == 0);
    }

    TEST_CASE("Reverse single element safe")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(42);
        list.reverse();
        CHECK(list.get(0) == 42);
    }

    TEST_CASE("ToString with custom convert function")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(7);
        auto conv = [](int &x)
        {
            return string("val=") + to_string(x);
        };
        CHECK(list.toString(conv) == "[val=7]");
    }
}
