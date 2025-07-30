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

    TEST_CASE("Insert Point at specific index")
    {
        DoublyLinkedList<Point> list;
        list.insertAtTail(Point(1, 2));
        list.insertAtTail(Point(3, 4));
        list.insertAt(1, Point(2, 3)); // should become [(1,2), (2,3), (3,4)]
        CHECK(list.size() == 3);
        CHECK(list.get(0) == Point(1, 2));
        CHECK(list.get(1) == Point(2, 3));
        CHECK(list.get(2) == Point(3, 4));
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
        CHECK(list.indexOf(Point(5, 6)) == -1); // Not in the list
    }

    TEST_CASE("Contains Point")
    {
        DoublyLinkedList<Point> list;
        list.insertAtTail(Point(1, 2));
        list.insertAtTail(Point(3, 4));
        CHECK(list.contains(Point(1, 2)) == true);
        CHECK(list.contains(Point(5, 6)) == false); // Not in the list
    }

    TEST_CASE("Size of Point list")
    {
        DoublyLinkedList<Point> list;
        list.insertAtTail(Point(1, 2));
        list.insertAtTail(Point(3, 4));
        CHECK(list.size() == 2);
    }

    TEST_CASE("Reverse Point list")
    {
        DoublyLinkedList<Point> list;
        list.insertAtTail(Point(1, 2));
        list.insertAtTail(Point(3, 4));
        list.reverse(); // should become [(3,4), (1,2)]
        CHECK(list.get(0) == Point(3, 4));
        CHECK(list.get(1) == Point(1, 2));
    }
}

TEST_SUITE("DoublyLinkedList Operations")
{
    TEST_CASE("Insert at specific index")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(3);
        list.insertAt(1, 2); // should become [1, 2, 3]
        CHECK(list.size() == 3);
        CHECK(list.get(0) == 1);
        CHECK(list.get(1) == 2);
        CHECK(list.get(2) == 3);
    }

    TEST_CASE("Delete at specific index")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.insertAtTail(3);
        list.deleteAt(1); // should become [1, 3]
        CHECK(list.size() == 2);
        CHECK(list.get(0) == 1);
        CHECK(list.get(1) == 3);
    }

    TEST_CASE("Index of and contains")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.insertAtTail(3);
        CHECK(list.indexOf(2) == 1);
        CHECK(list.contains(3) == true);
        CHECK(list.contains(4) == false);
    }

    TEST_CASE("Reverse with 1 element")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.reverse(); // should still be [1]
        CHECK(list.size() == 1);
        CHECK(list.get(0) == 1);
    }

    TEST_CASE("Insert at 0")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(2);
        list.insertAt(0, 1); // should become [1, 2]
        CHECK(list.size() == 2);
        CHECK(list.get(0) == 1);
        CHECK(list.get(1) == 2);
    }

    TEST_CASE("To String with custom function")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        std::string str = list.toString([](int &value) { return std::to_string(value); });
        CHECK(str == "[1, 2]");
    }

    TEST_CASE("Index out of bounds")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        CHECK_THROWS_AS(list.get(2), std::out_of_range);
        CHECK_THROWS_AS(list.deleteAt(2), std::out_of_range);
        CHECK_THROWS_AS(list.insertAt(-1, 0), std::out_of_range);
    }

    TEST_CASE("Iterator basic functionality")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.insertAtTail(3);

        int sum = 0;
        for (const auto &item : list)
        {
            sum += item;
        }
        CHECK(sum == 6); // 1 + 2 + 3
    }

    TEST_CASE("Empty list")
    {
        DoublyLinkedList<int> list;
        std::string str = list.toString([](int &value) { return std::to_string(value); });
        CHECK(str == "[]"); // Should handle empty list correctly
    }
}