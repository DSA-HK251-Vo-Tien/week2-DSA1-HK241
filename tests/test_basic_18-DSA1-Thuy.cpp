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
    TEST_CASE("Insertion")
    {
        DoublyLinkedList<int> list;
        list.insertAtHead(0);
        list.insertAtTail(1);
        list.insertAtTail(2);
        CHECK(list.get(0) == 0);
        CHECK(list.get(2) == 2);
    }
    TEST_CASE("Empty list size")
    {
        DoublyLinkedList<int> list;
        CHECK(list.size() == 0);
    }
    TEST_CASE("Insertion at detailed index")
    {
        DoublyLinkedList<int> list;
        list.insertAtHead(1);
        list.insertAtTail(2);
        list.insertAt(1, 3);
        CHECK(list.size() == 3);
        CHECK(list.get(1) == 3);
    }
    TEST_CASE("Deletion")
    {
        DoublyLinkedList<int> list;
        list.insertAtHead(1);
        list.insertAtTail(2);
        list.insertAtTail(3);

        list.deleteAt(0);
        CHECK(list.size() == 2);
        CHECK(list.get(0) == 2);
    }
    TEST_CASE("Reverse linked list")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(0);
        list.insertAtTail(3);
        list.reverse();
        CHECK(list.get(0) == 3);
        CHECK(list.get(2) == 1);
    }
    TEST_CASE("check status")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.insertAtTail(3);
        CHECK(list.contains(1) == true);
        CHECK(list.contains(4) == false);
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
    TEST_CASE("Deletion point")
    {
        DoublyLinkedList<Point> list;
        list.insertAtHead(Point(0, 1));
        list.insertAtHead(Point(2, 3));
        list.insertAtTail(Point(0, 3));
        list.deleteAt(0);
        CHECK(list.size() == 2);
        CHECK(list.get(0) == Point(0, 1));
    }
    TEST_CASE("Index of point")
    {
        DoublyLinkedList<Point> list;
        list.insertAtHead(Point(0, 1));
        list.insertAtTail(Point(0, 2));
        list.insertAtHead(Point(0, 4));
        CHECK(list.size() == 3);
        CHECK(list.indexOf(Point(0, 1)) == 1);
    }

    TEST_CASE("To string of list<Point>")
    {
        DoublyLinkedList<Point> list;
        list.insertAtTail(Point(9, 0));
        list.insertAtTail(Point(8, 1));
        std::string str = list.toString(pointToString);
        CHECK(str == "[(9,0), (8,1)]");
    }
    TEST_CASE("To string of reversed list<Point>")
    {
        DoublyLinkedList<Point> list;
        list.insertAtTail(Point(0, 1));
        list.insertAtTail(Point(1, 2));
        list.insertAtTail(Point(2, 3));
        list.reverse();
        string str = list.toString(pointToString);
        CHECK(str == "[(2,3), (1,2), (0,1)]");
    }
    TEST_CASE("Get element")
    {
        DoublyLinkedList<Point> list;
        list.insertAtTail(Point(0, 9));
        list.insertAtTail(Point(3, 4));
        list.insertAt(1, Point(5, 6));
        CHECK(list.get(1) == Point(5, 6));
    }
}
