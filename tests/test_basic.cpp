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
std::string intToStr(int &x) {
    return std::to_string(x);
}

TEST_SUITE("DoublyLinkedList TO-DO TESTCASES") {

    TEST_CASE("Insert duplicate values") {
        DoublyLinkedList<int> list;
        list.insertAtTail(5);
        list.insertAtTail(5);
        list.insertAtTail(5);
        CHECK(list.size() == 3);
        CHECK(list.indexOf(5) == 0);
    }

    TEST_CASE("Remove all and reinsert") {
        DoublyLinkedList<int> list;
        for (int i = 0; i < 5; ++i) list.insertAtTail(i);
        for (int i = 0; i < 5; ++i) list.deleteAt(0);
        CHECK(list.size() == 0);
        list.insertAtHead(10);
        CHECK(list.get(0) == 10);
    }

    TEST_CASE("Insert at head and reverse") {
        DoublyLinkedList<int> list;
        list.insertAtHead(3);
        list.insertAtHead(2);
        list.insertAtHead(1);
        list.reverse();
        CHECK(list.get(0) == 3);
        CHECK(list.get(2) == 1);
    }

    TEST_CASE("Reverse multiple times") {
        DoublyLinkedList<int> list;
        for (int i = 1; i <= 4; ++i) list.insertAtTail(i);
        list.reverse();
        list.reverse();
        CHECK(list.get(0) == 1);
        CHECK(list.get(3) == 4);
    }

    TEST_CASE("Insert at invalid index") {
        DoublyLinkedList<int> list;
        CHECK_THROWS_AS(list.insertAt(1, 5), std::out_of_range);
        list.insertAtHead(1);
        CHECK_THROWS_AS(list.insertAt(3, 2), std::out_of_range);
    }

    TEST_CASE("To string with custom converter") {
        DoublyLinkedList<int> list;
        for (int i = 0; i < 3; ++i) list.insertAtTail(i);
        std::string s = list.toString([](int &val) {
            return "#" + std::to_string(val);
        });
        CHECK(s == "[#0, #1, #2]");
    }
    TEST_CASE("Index of non-existing element") {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        CHECK(list.indexOf(3) == -1);
    }
    TEST_CASE("Contains method") {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        CHECK(list.contains(1) == true);
        CHECK(list.contains(3) == false);
    }
    TEST_CASE("Iterator sum of squares") {
        DoublyLinkedList<int> list;
        for (int i = 1; i <= 3; ++i) list.insertAtTail(i); // [1,2,3]
        int sum = 0;
        for (auto &v : list) sum += v * v;
        CHECK(sum == 14); // 1² + 2² + 3²
    }

    TEST_CASE("List after reverse and delete") {
        DoublyLinkedList<int> list;
        for (int i = 1; i <= 5; ++i) list.insertAtTail(i);
        list.reverse();
        list.deleteAt(2);
        CHECK(list.size() == 4);
        CHECK(list.get(2) == 2);
    }
} 
