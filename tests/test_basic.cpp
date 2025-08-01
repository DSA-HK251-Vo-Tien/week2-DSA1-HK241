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

    TEST_CASE("Insert and delete at head and tail")
    {
        DoublyLinkedList<int> list;
        list.insertAtHead(2); // [2]
        list.insertAtHead(1); // [1, 2]
        list.insertAtTail(3); // [1, 2, 3]
        list.deleteAt(0);     // [2, 3]
        list.deleteAt(list.size() - 1); // [2]

        CHECK(list.size() == 1);
        CHECK(list.get(0) == 2);
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

    TEST_CASE("Insert Point at specific index")
    {
        DoublyLinkedList<Point> list;
        list.insertAtTail(Point(1, 2));
        list.insertAtHead(Point(3, 4));
        list.insertAt(1, Point(2, 3)); // should become [(3,4), (2,3), (1,2)]
        CHECK(list.size() == 3);
        CHECK(list.get(0) == Point(3, 4));
        CHECK(list.get(1) == Point(2, 3));
        CHECK(list.get(2) == Point(1, 2));
    }

    TEST_CASE("Delete Point at specific index")
    {
        DoublyLinkedList<Point> list;
        list.insertAtTail(Point(1, 2));
        list.insertAtTail(Point(3, 4));
        list.insertAtTail(Point(5, 6));
        list.deleteAt(1); // should become [(1,2), (5,6)]
        CHECK(list.size() == 2);
        CHECK(list.get(0) == Point(1, 2));
        CHECK(list.get(1) == Point(5, 6));
    }

    TEST_CASE("Index of Point")
    {
        DoublyLinkedList<Point> list;
        list.insertAtTail(Point(1, 2));
        list.insertAtTail(Point(3, 4));
        CHECK(list.indexOf(Point(3, 4)) == 1);
        CHECK(list.indexOf(Point(5, 6)) == -1); // not found
    }

    TEST_CASE("Contains Point")
    {
        DoublyLinkedList<Point> list;
        list.insertAtTail(Point(1, 2));
        list.insertAtTail(Point(3, 4));
        CHECK(list.contains(Point(3, 4)) == true);
        CHECK(list.contains(Point(0, 0)) == false);
    }

    TEST_CASE("Reverse Point list")
    {
        DoublyLinkedList<Point> list;
        list.insertAtTail(Point(1, 2));
        list.insertAtTail(Point(3, 4));
        list.insertAtTail(Point(5, 6));
        list.reverse(); // [5,6], [3,4], [1,2]
        CHECK(list.get(0) == Point(5, 6));
        CHECK(list.get(2) == Point(1, 2));
    }

    TEST_CASE("ToString on empty list of Point")
    {
        DoublyLinkedList<Point> list;
        std::string str = list.toString(pointToString);
        CHECK(str == "[]");
    }

    TEST_CASE("Insert Point at index 0 (head)")
    {
        DoublyLinkedList<Point> list;
        list.insertAt(0, Point(7, 8)); // list = [(7,8)]
        CHECK(list.size() == 1);
        CHECK(list.get(0) == Point(7, 8));
    }

    TEST_CASE("Index out of bounds for Point")
    {
        DoublyLinkedList<Point> list;
        list.insertAtTail(Point(1, 1));
        CHECK_THROWS_AS(list.get(1), std::out_of_range);
        CHECK_THROWS_AS(list.deleteAt(2), std::out_of_range);
        CHECK_THROWS_AS(list.insertAt(-1, Point(0, 0)), std::out_of_range);
    }

    TEST_CASE("Insert multiple Points at tail")
    {
        DoublyLinkedList<Point> list;
        for (int i = 0; i < 5; ++i)
            list.insertAtTail(Point(i, i + 1));

        CHECK(list.size() == 5);
        CHECK(list.get(0) == Point(0, 1));
        CHECK(list.get(4) == Point(4, 5));
    }

    TEST_CASE("Remove last Point")
    {
        DoublyLinkedList<Point> list;
        list.insertAtTail(Point(1, 2));
        list.insertAtTail(Point(3, 4));
        list.deleteAt(1); // remove last
        CHECK(list.size() == 1);
        CHECK(list.get(0) == Point(1, 2));
    }

    TEST_CASE("Insert and remove single Point")
    {
        DoublyLinkedList<Point> list;
        list.insertAtHead(Point(9, 9));
        CHECK(list.size() == 1);
        list.deleteAt(0);
        CHECK(list.size() == 0);
    }

    TEST_CASE("Insert duplicate Points and find index")
    {
        DoublyLinkedList<Point> list;
        list.insertAtTail(Point(1, 1));
        list.insertAtTail(Point(2, 2));
        list.insertAtTail(Point(1, 1)); // duplicate
        CHECK(list.indexOf(Point(1, 1)) == 0); // should find first one
    }

    TEST_CASE("Reverse empty Point list")
    {
        DoublyLinkedList<Point> list;
        list.reverse(); // should not crash
        CHECK(list.size() == 0);
    }

}

// TODO add test case