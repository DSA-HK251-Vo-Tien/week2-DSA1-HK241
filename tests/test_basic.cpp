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
TEST_SUITE("DoublyLinkedList - Full Tests")
{

    TEST_CASE("Insert at specific index")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(3);
        list.insertAt(1, 2); // [1,2,3]
        CHECK(list.get(0) == 1);
        CHECK(list.get(1) == 2);
        CHECK(list.get(2) == 3);
        CHECK(list.size() == 3);
    }

    TEST_CASE("Insert at index 0")
    {
        DoublyLinkedList<int> list;
        list.insertAt(0, 42);
        CHECK(list.get(0) == 42);
        CHECK(list.size() == 1);
    }

    TEST_CASE("Insert at end (index == length)")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(10);
        list.insertAtTail(20);
        list.insertAt(2, 30);
        CHECK(list.toString() == "[10, 20, 30]");
    }

    TEST_CASE("Insert at invalid index throws")
    {
        DoublyLinkedList<int> list;
        CHECK_THROWS_AS(list.insertAt(-1, 1), std::out_of_range);
        CHECK_THROWS_AS(list.insertAt(1, 1), std::out_of_range);
    }

    TEST_CASE("Delete at head, tail, middle")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.insertAtTail(3); // [1,2,3]

        list.deleteAt(0); // delete head
        CHECK(list.toString() == "[2, 3]");
        list.deleteAt(1); // delete tail
        CHECK(list.toString() == "[2]");
    }

    TEST_CASE("Delete at invalid index throws")
    {
        DoublyLinkedList<int> list;
        CHECK_THROWS_AS(list.deleteAt(0), std::out_of_range);
        list.insertAtTail(10);
        CHECK_THROWS_AS(list.deleteAt(1), std::out_of_range);
    }

    TEST_CASE("IndexOf and Contains")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(5);
        list.insertAtTail(10);
        list.insertAtTail(15);

        CHECK(list.indexOf(5) == 0);
        CHECK(list.indexOf(15) == 2);
        CHECK(list.indexOf(99) == -1);
        CHECK(list.contains(10));
        CHECK(!list.contains(100));
    }

    TEST_CASE("toString formatting")
    {
        DoublyLinkedList<int> list;
        CHECK(list.toString() == "[]");

        list.insertAtTail(1);
        list.insertAtTail(2);
        list.insertAtTail(3);
        CHECK(list.toString() == "[1, 2, 3]");
    }

    TEST_CASE("reverse empty and single element")
    {
        DoublyLinkedList<int> list;
        list.reverse();
        CHECK(list.toString() == "[]");

        list.insertAtTail(99);
        list.reverse();
        CHECK(list.toString() == "[99]");
    }

    TEST_CASE("reverse 3 elements")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.insertAtTail(3);
        list.reverse();
        CHECK(list.toString() == "[3, 2, 1]");
    }
}
// TODO add test case