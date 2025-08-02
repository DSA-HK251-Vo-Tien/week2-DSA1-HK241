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
TEST_SUITE("DDL Test"){
    TEST_CASE("contain"){
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.insertAtTail(3);
        CHECK(list.contains(4)==false);
        CHECK(list.contains(3)==true);
    };
    TEST_CASE("get index"){
        DoublyLinkedList<char> list;
        list.insertAtHead('a');
        list.insertAtHead('z');
        list.insertAtHead('c');
        CHECK(list.indexOf('x')==-1);
        CHECK(list.indexOf('a')==2);
    }
    TEST_CASE("tostring"){
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.insertAtTail(3);
        CHECK(list.toString()=="[1, 2, 3]");
    }
    TEST_CASE("invalid input"){
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.insertAtTail(3);
        list.insertAt(2,4);
        CHECK(list.get(2)==4);
    }
    TEST_CASE("Khởi tạo danh sách rỗng") {
    DoublyLinkedList<int> list;
    CHECK(list.size() == 0);
    CHECK(list.toString() == "[]");
    }
    TEST_CASE("Chèn với index không hợp lệ") {
    DoublyLinkedList<int> list;
    CHECK_THROWS_AS(list.insertAt(1, 100), std::out_of_range);
    }
    TEST_CASE("Chèn với index không hợp lệ") {
    DoublyLinkedList<int> list;
    CHECK_THROWS_AS(list.deleteAt(1), std::out_of_range);
    CHECK_THROWS_AS(list.deleteAt(-100), std::out_of_range);
    }
    TEST_CASE("Iterator remains valid after insertAtTail") {
    DoublyLinkedList<int> list;
    list.insertAtTail(1);
    list.insertAtTail(2);
    
    auto it = list.begin(); // trỏ đến phần tử 1
    list.insertAtTail(3);   // chèn thêm phần tử cuối

    CHECK(*it == 1);
    ++it;
    CHECK(*it == 2);
    ++it;
    CHECK(*it == 3);
    }
    TEST_CASE("Iterator on empty list") {
    DoublyLinkedList<int> list;
    auto it = list.begin();
    auto et = list.end();

    CHECK(it == et);
    }
}