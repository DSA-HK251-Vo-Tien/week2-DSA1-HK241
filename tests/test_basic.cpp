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
TEST_SUITE("DoublyLinkedList Other Operations")
{
    TEST_CASE("Index of and contains")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.insertAtTail(3); // [1, 2, 3]

        SUBCASE("Index of existing element")
        {
            CHECK(list.indexOf(2) == 1);
        }

        SUBCASE("Index of non-existing element")
        {
            CHECK(list.indexOf(4) == -1);
        }

        SUBCASE("Contains existing element")
        {
            CHECK(list.contains(3) == true);
        }

        SUBCASE("Contains non-existing element")
        {
            CHECK(list.contains(5) == false);
        }
    }

    TEST_CASE("Insert middle")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(3); // [1, 3]

        SUBCASE("Insert at valid middle index")
        {
            list.insertAt(1, 2); // [1, 2, 3]
            CHECK(list.size() == 3);
            CHECK(list.get(1) == 2);
        }

        SUBCASE("Insert at invalid index")
        {
            CHECK_THROWS_AS(list.insertAt(5, 4), std::out_of_range);
        }
    }

    TEST_CASE("Different data")
    {
        DoublyLinkedList<std::string> strList;
        strList.insertAtTail("hello");
        strList.insertAtTail("world");
        CHECK(strList.size() == 2);
        CHECK(strList.get(0) == "hello");
        CHECK(strList.get(1) == "world");

        DoublyLinkedList<double> doubleList;
        doubleList.insertAtTail(1.1);
        doubleList.insertAtTail(2.2);
        CHECK(doubleList.size() == 2);
        CHECK(doubleList.get(0) == doctest::Approx(1.1));
        CHECK(doubleList.get(1) == doctest::Approx(2.2));
    }

    TEST_CASE("Empty list behavior") 
    {
        DoublyLinkedList<int> list;

        CHECK(list.size() == 0);
        CHECK_THROWS_AS(list.get(0), std::out_of_range);
        CHECK_THROWS_AS(list.deleteAt(0), std::out_of_range);

        list.reverse();
        CHECK(list.size() == 0);
    }

    TEST_CASE("Single element behavior") {
        DoublyLinkedList<int> list;
        list.insertAtHead(42);

        CHECK(list.size() == 1);
        list.reverse();
        CHECK(list.get(0) == 42);

        list.deleteAt(0);
        CHECK(list.size() == 0);
    }
}