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
    TEST_CASE("Invalid element"){
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtHead(3);
        CHECK_THROWS_AS(list.get(5), out_of_range);
        CHECK_THROWS_AS(list.get(-1), out_of_range);
    }
    TEST_CASE("reverse") {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.insertAtTail(3);
        list.reverse();
        CHECK(list.get(0) == 3);
        CHECK(list.get(2) == 1);
    }
    TEST_CASE("contain"){
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(3);
        list.insertAtHead(2);
        CHECK(list.contains(9) == false);
        CHECK(list.contains(1) == true);
    }
    TEST_CASE("TO_STRING with single element"){
        DoublyLinkedList<int> list;
        list.insertAtTail(5);
        string str = list.toString();
        CHECK(str == "[5]");
    }
    TEST_CASE("InsertAt with invalid index") {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(3);
        list.insertAtHead(2);
        CHECK_THROWS_AS(list.insertAt(-1,9), out_of_range);
        CHECK_THROWS_AS(list.insertAt(5,6),out_of_range);
    }
    TEST_CASE("delete At with invalid index"){
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(3);
        list.insertAtHead(2);
        CHECK_THROWS_AS(list.deleteAt(-1), out_of_range);
        CHECK_THROWS_AS(list.deleteAt(5),out_of_range);
    }
    TEST_CASE("indexOf for integers")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(10);
        list.insertAtTail(20);
        list.insertAtTail(30);
        list.insertAtTail(20); 

        CHECK(list.indexOf(20) == 1); 
        CHECK(list.indexOf(30) == 2);
        CHECK(list.indexOf(99) == -1); 
    }
    TEST_CASE("Reverse on edge-case lists")
    {
        SUBCASE("Reverse empty list")
        {
            DoublyLinkedList<int> list;
            list.reverse();
            CHECK(list.size() == 0);
            CHECK(list.toString() == "[]");
        }

        SUBCASE("Reverse single element list")
        {
            DoublyLinkedList<int> list;
            list.insertAtTail(42);
            list.reverse();
            CHECK(list.size() == 1);
            CHECK(list.get(0) == 42);
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

    TEST_CASE("Find and check existence of Point")
    {
        DoublyLinkedList<Point> list;
        Point p1(1, 1), p2(2, 2), p3(3, 3);
        list.insertAtTail(p1);
        list.insertAtTail(p2);
        list.insertAtTail(p3);

        SUBCASE("indexOf Point")
        {
            CHECK(list.indexOf(p2) == 1);
            CHECK(list.indexOf(Point(9, 9)) == -1); 
        }

        SUBCASE("contains Point")
        {
            CHECK(list.contains(p3) == true);
            CHECK(list.contains(Point(0, 0)) == false);
        }
    }

    TEST_CASE("Delete a Point")
    {
        DoublyLinkedList<Point> list;
        Point p1(1, 1), p2(2, 2), p3(3, 3);
        list.insertAtTail(p1);
        list.insertAtTail(p2);
        list.insertAtTail(p3); 

        list.deleteAt(1); 

        CHECK(list.size() == 2);
        CHECK(list.get(0) == p1);
        CHECK(list.get(1) == p3);
        CHECK(list.toString(pointToString) == "[(1,1), (3,3)]");
    }

    TEST_CASE("Insert a Point")
    {
        DoublyLinkedList<Point> list;
        Point p1(1, 1), p3(3, 3);
        list.insertAtTail(p1);
        list.insertAtTail(p3); 

        Point p2(2, 2);
        list.insertAt(1, p2); 

        CHECK(list.size() == 3);
        CHECK(list.get(0) == p1);
        CHECK(list.get(1) == p2);
        CHECK(list.get(2) == p3);
    }

    TEST_CASE("Reverse a list of Points")
    {
        DoublyLinkedList<Point> list;
        Point p1(1, 1), p2(2, 2), p3(3, 3);
        list.insertAtTail(p1);
        list.insertAtTail(p2);
        list.insertAtTail(p3); 

        list.reverse(); 

        CHECK(list.get(0) == p3);
        CHECK(list.get(2) == p1);
    }

    TEST_CASE("toString on an empty list of Points")
    {
        DoublyLinkedList<Point> list;
        CHECK(list.toString(pointToString) == "[]");
    }
   
}

// TODO add test case