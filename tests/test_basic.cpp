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

    TEST_CASE("Insert at Middle and Tail")
    {
        DoublyLinkedList<Point> list;
        list.insertAtTail(Point(0, 0));
        list.insertAtTail(Point(1, 1));
        list.insertAt(1,Point(2,2));
        CHECK(list.size() == 3);
        list.insertAt(1,Point(3,3));
        CHECK(list.size() == 4);
        CHECK(list.contains(Point(2,2)));
    }

    TEST_CASE("GetterPoint")
    {
        DoublyLinkedList<Point> list;
        list.insertAtTail(Point(1, 2));
        list.insertAtTail(Point(3, 4));
        list.insertAt(1,Point(5,6));
        CHECK(list.size() == 3);
        list.insertAt(1,Point(3,3));
        CHECK(list.size() == 4);
        CHECK(!list.contains(Point(2,2)));
        CHECK(list.contains(Point(1,2)));
        CHECK(list.contains(Point(3,4)));
        CHECK(list.contains(Point(5,6)));
        CHECK(list.indexOf(Point(1,2)) == 0);
        CHECK(list.indexOf(Point(3,3)) == 1);
        CHECK(list.indexOf(Point(5,6)) == 2);
        CHECK(list.get(0) == Point(1,2));
    }

    TEST_CASE("Reversion"){
        DoublyLinkedList<Point> list;
        list.insertAtHead(Point(3, 3));
        list.insertAtHead(Point(2, 2));
        list.insertAtHead(Point(1, 1));
        list.insertAtHead(Point(0, 0));
        CHECK(list.size() == 4);
        CHECK(list.get(0) == Point(0, 0));
        CHECK(list.get(1) == Point(1, 1));
        CHECK(list.get(2) == Point(2, 2));
        CHECK(list.get(3) == Point(3, 3));
        list.reverse();
        std::string str = list.toString(pointToString);
        CHECK(str == "[(3,3), (2,2), (1,1), (0,0)]");
    }
}

// TODO add test case
TEST_SUITE("Summary Of Operations"){
    TEST_CASE("Insertion_ver1")
    {
        DoublyLinkedList<int> list;
        list.insertAtHead(1);
        list.insertAtTail(2);
        list.insertAtHead(0);
        CHECK(list.size() == 3);
        CHECK(list.get(0) == 0);
        CHECK(list.get(1) == 1);
        CHECK(list.get(2) == 2);
    }

    TEST_CASE("Insertion_ver2")
    {
        DoublyLinkedList<int> list;
        list.insertAtHead(0);
        list.insertAtTail(4);
        list.insertAt(1,1);
        list.insertAt(2,2);
        list.insertAt(3,3);
        CHECK(list.size() == 5);
        CHECK(list.get(0) == 0);
        CHECK(list.get(1) == 1);
        CHECK(list.get(2) == 2);
        CHECK(list.get(3) == 3);
    }

    TEST_CASE("Deletion")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.insertAtTail(3); // [1, 2, 3]

        list.deleteAt(0);
        list.deleteAt(0);
        CHECK(list.size() == 1);
        CHECK(list.get(0) == 3);
        list.deleteAt(0);
        CHECK(list.size() == 0);
    }

    TEST_CASE("Getter_Value")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(0);
        list.insertAtTail(1);
        list.insertAtTail(2); 
        list.insertAtTail(3);
        list.insertAtTail(4);
        list.insertAtTail(5);
        CHECK(list.size() == 6);
        CHECK(list.get(0) == 0);
        CHECK(list.get(1) == 1);
        CHECK(list.get(2) == 2);
        CHECK(list.get(3) == 3);
        CHECK(list.get(4) == 4);
        CHECK(list.get(5) == 5);
    }

    TEST_CASE("Getter_Index")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(0);
        list.insertAtTail(1);
        list.insertAtTail(2); 
        list.insertAtTail(3);
        list.insertAtTail(4);
        CHECK(list.size() == 5);
        CHECK(list.indexOf(3) == 3);
        CHECK(list.indexOf(4) == 4);
        CHECK(list.indexOf(5) == -1);
        CHECK(list.indexOf(6) == -1);
        CHECK(list.indexOf(7) == -1);
        CHECK(list.indexOf(8) == -1);
        CHECK(list.indexOf(9) == -1);
    }

    TEST_CASE("isContain")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(0);
        list.insertAtTail(1);
        list.insertAtTail(2); 
        CHECK(list.size() == 3);
        CHECK(list.contains(0));
        CHECK(list.contains(1));
        CHECK(list.contains(2));
        CHECK(!list.contains(3));
        CHECK(!list.contains(4));
        CHECK(!list.contains(5));
    }

    TEST_CASE("Reverse")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(0);
        list.insertAtTail(1);
        list.insertAtTail(2); 
        list.insertAtTail(3);
        list.insertAtTail(4);
        list.insertAtTail(5);
        list.reverse();
        CHECK(list.size() == 6);
        CHECK(list.indexOf(3) == 2);
        CHECK(list.indexOf(4) == 1);
        CHECK(list.indexOf(5) == 0);
        CHECK(list.indexOf(1) == 4);
        CHECK(list.indexOf(2) == 3);
        CHECK(list.indexOf(0) == 5);
    }

    TEST_CASE("toString")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(0);
        list.insertAtTail(1);
        list.insertAtTail(2); 
        list.insertAtTail(3);
        list.insertAtTail(4);
        list.insertAtTail(5);
        string s = list.toString();
        CHECK(list.size() == 6);
        CHECK(s == "[0, 1, 2, 3, 4, 5]");
        list.reverse();
        CHECK(list.size() == 6);
        s = list.toString();
        CHECK(s == "[5, 4, 3, 2, 1, 0]");
    }
}