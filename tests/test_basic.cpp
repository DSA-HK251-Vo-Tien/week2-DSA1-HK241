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
TEST_SUITE("them 16 test case") {
    TEST_CASE("testcase1")
    {
        DoublyLinkedList<int> list;

        list.insertAtHead(1987);
        list.insertAtHead(1789);
        CHECK(list.size() == 2);
        CHECK(list.get(0) == 1789);
        CHECK(list.get(1) == 1987);
    }

    TEST_CASE("testcase2")
    {
        DoublyLinkedList<int> list;

        list.insertAtTail(1879);
        list.insertAtTail(9871);
        CHECK(list.size() == 2);
        CHECK(list.get(0) == 1879);
        CHECK(list.get(1) == 9871);
    }

    TEST_CASE("testcase3")
    {
        DoublyLinkedList<int> list;

        list.insertAt(0,1879);
        CHECK(list.get(0) == 1879);
    }
    TEST_CASE("testcase4")
    {
        DoublyLinkedList<int> list;

        list.insertAt(0,1879);
        CHECK(list.get(0) == 1879);
        list.deleteAt(0);
        CHECK(list.size() == 0);
    }

    TEST_CASE("testcase5") {
        DoublyLinkedList<int> list;

        list.insertAt(0,8791);
        CHECK(list.indexOf(8791) == 0);
    }

    TEST_CASE("testcase6") {
        DoublyLinkedList<int> list;

        list.insertAt(0,9871);
        CHECK(list.contains(9871) == true);
    }

    TEST_CASE("testcase7") {
        DoublyLinkedList<int> list;

        list.insertAtHead(1);
        list.insertAtHead(9);
        list.insertAtHead(8);
        list.insertAtHead(7);
        list.reverse();
        CHECK(list.get(0) == 1);
    }

    TEST_CASE("testcase8") {
        DoublyLinkedList<int> list;

        list.insertAtHead(7);
        list.insertAtHead(8);
        list.insertAtHead(9);
        list.insertAtHead(1);
        CHECK(list.toString() == "[1, 9, 8, 7]");
    }

    TEST_CASE("testcase9") {
        DoublyLinkedList<int> list;

        list.insertAtHead(1);
        list.insertAtTail(2);
        list.insertAtTail(3);
        list.insertAtTail(4); 

        list.deleteAt(2);
        CHECK(list.size() == 3);
        CHECK(list.get(0) == 1);
        CHECK(list.get(1) == 2);
        CHECK(list.get(2) == 4);
    }

    TEST_CASE("testcase10") {
        DoublyLinkedList<int> list;

        list.insertAtHead(10);
        list.insertAtHead(20);

        CHECK(list.indexOf(30) == -1); 
    }

    TEST_CASE("testcase12") {
        DoublyLinkedList<int> list;

        CHECK(list.contains(1) == false);
    }

    TEST_CASE("testcase13_gpt") {
        DoublyLinkedList<int> list;
        list.insertAt(0, 100);
        list.insertAt(1, 200);
        CHECK(list.size() == 2);
        CHECK(list.get(0) == 100);
        CHECK(list.get(1) == 200);
    }

    TEST_CASE("testcase14_gpt") {
        DoublyLinkedList<int> list;
        list.insertAtHead(1);
        list.insertAtTail(2);
        list.deleteAt(0);
        CHECK(list.size() == 1);
        CHECK(list.get(0) == 2);
    }

    TEST_CASE("testcase15_gpt") {
        DoublyLinkedList<int> list;
        list.insertAtHead(1);
        list.insertAtTail(3);
        list.insertAt(1, 2);  // chèn vào giữa
        CHECK(list.size() == 3);
        CHECK(list.get(0) == 1);
        CHECK(list.get(1) == 2);
        CHECK(list.get(2) == 3);
    }

    TEST_CASE("testcase16_gpt") {
        DoublyLinkedList<int> list;
        list.insertAtHead(1);
        list.insertAtTail(2);
        list.insertAtTail(3);
        list.deleteAt(1); // xóa phần tử ở giữa
        CHECK(list.size() == 2);
        CHECK(list.get(0) == 1);
        CHECK(list.get(1) == 3);
    }
}