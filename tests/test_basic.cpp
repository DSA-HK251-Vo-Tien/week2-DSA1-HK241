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
TEST_SUITE("Homework")
{
    TEST_CASE("Mixed insert at head and tail")
    {
        DoublyLinkedList<int> list;
        list.insertAtHead(2);
        list.insertAtTail(4);
        list.insertAtHead(1);
        list.insertAtTail(5);

        CHECK(list.size() == 4);
        CHECK(list.get(0) == 1);
        CHECK(list.get(1) == 2);
        CHECK(list.get(2) == 4);
        CHECK(list.get(3) == 5);
    }
    TEST_CASE("Insert Point at arbitrary index")
    {
        DoublyLinkedList<Point> list;
        list.insertAtTail(Point(1, 1));
        list.insertAtTail(Point(3, 3));
        list.insertAt(1, Point(2, 2));

        CHECK(list.get(0) == Point(1, 1));
        CHECK(list.get(1) == Point(2, 2));
        CHECK(list.get(2) == Point(3, 3));
    }
    TEST_CASE("Reverse Point list and toString")
    {
        DoublyLinkedList<Point> list;
        list.insertAtTail(Point(5, 0));
        list.insertAtTail(Point(6, 1));
        list.insertAtTail(Point(7, 2));

        list.reverse();

        auto pointToString = [](Point &p) {
            return "(" + std::to_string(int(p.getX())) + "," + std::to_string(int(p.getY())) + ")";
        };

        CHECK(list.toString(pointToString) == "[(7,2), (6,1), (5,0)]");
    }
    TEST_CASE("Insert at arbitrary index and handle invalid index")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(3);
        list.insertAt(1, 2);

        CHECK(list.size() == 3);
        CHECK(list.get(0) == 1);
        CHECK(list.get(1) == 2);
        CHECK(list.get(2) == 3);

        CHECK_THROWS_AS(list.insertAt(-1, 9), std::out_of_range);
        CHECK_THROWS_AS(list.insertAt(4, 9), std::out_of_range);
    }
    TEST_CASE("Delete with invalid index")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(10);
        CHECK_THROWS_AS(list.deleteAt(-1), std::out_of_range);
        CHECK_THROWS_AS(list.deleteAt(1), std::out_of_range);
    }
    TEST_CASE("Get elements with valid and invalid indices")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(42);

        CHECK(list.get(0) == 42);
        CHECK_THROWS_AS(list.get(-1), std::out_of_range);
        CHECK_THROWS_AS(list.get(1), std::out_of_range);
    }
    TEST_CASE("Check indexOf and contains")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(5);
        list.insertAtTail(10);
        list.insertAtTail(15);

        CHECK(list.indexOf(10) == 1);
        CHECK(list.indexOf(42) == -1);
        CHECK(list.contains(15));
        CHECK(!list.contains(99));
    }
    TEST_CASE("Reverse edge cases")
    {
        SUBCASE("Empty list")
        {
            DoublyLinkedList<int> list;
            list.reverse();
            CHECK(list.size() == 0);
        }

        SUBCASE("Single element list")
        {
            DoublyLinkedList<int> list;
            list.insertAtTail(99);
            list.reverse();
            CHECK(list.get(0) == 99);
        }
    }
    TEST_CASE("toString with integers")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.insertAtTail(3);

        auto toStr = [](int &x) -> std::string {
            return std::to_string(x);
        };

        CHECK(list.toString(toStr) == "[1, 2, 3]");
    }
    TEST_CASE("Reverse twice returns original order")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.insertAtTail(3);
        
        list.reverse();
        list.reverse();

        CHECK(list.get(0) == 1);
        CHECK(list.get(1) == 2);
        CHECK(list.get(2) == 3);
    }
        TEST_CASE("Insert and delete in loop")
    {
        DoublyLinkedList<int> list;
        for (int i = 0; i < 100; ++i)
            list.insertAtTail(i);

        CHECK(list.size() == 100);
        for (int i = 0; i < 50; ++i)
            list.deleteAt(0);

        CHECK(list.size() == 50);
        CHECK(list.get(0) == 50);
    }
    TEST_CASE("Multiple Point and string output")
    {
        DoublyLinkedList<Point> list;
        list.insertAtTail(Point(1, 1));
        list.insertAtTail(Point(2, 2));
        list.insertAtTail(Point(3, 3));

        auto pointToStr = [](Point &p) {
            return "(" + std::to_string(int(p.getX())) + "," + std::to_string(int(p.getY())) + ")";
        };

        CHECK(list.toString(pointToStr) == "[(1,1), (2,2), (3,3)]");
    }
    TEST_CASE("Delete last element")
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
    TEST_CASE("Insert at size index (append)")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);

        list.insertAt(list.size(), 3);
        CHECK(list.size() == 3);
        CHECK(list.get(2) == 3);
    }
    TEST_CASE("Insert at index 0 repeatedly")
    {
        DoublyLinkedList<int> list;
        list.insertAt(0, 3);
        list.insertAt(0, 2);
        list.insertAt(0, 1);

        CHECK(list.get(0) == 1);
        CHECK(list.get(1) == 2);
        CHECK(list.get(2) == 3);
    }
        TEST_CASE("toString with single element")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(7);

        auto toStr = [](int &x) {
            return std::to_string(x);
        };

        CHECK(list.toString(toStr) == "[7]");
    }
    TEST_CASE("Get after multiple reverse")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.insertAtTail(3);

        list.reverse();
        list.reverse();

        CHECK(list.get(0) == 1);
        CHECK(list.get(2) == 3);
    }
}