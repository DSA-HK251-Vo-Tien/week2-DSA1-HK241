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
        list.insertAtTail(3);

        SUBCASE("Delete middle element")
        {
            list.deleteAt(1);
            CHECK(list.size() == 2);
            CHECK(list.get(0) == 1);
            CHECK(list.get(1) == 3);
        }

        SUBCASE("Reverse list")
        {
            list.reverse();
            CHECK(list.get(0) == 3);
            CHECK(list.get(2) == 1);
        }
    }

    TEST_CASE("Insert at head and tail")
    {
        DoublyLinkedList<int> list;
        SUBCASE("Insert at head")
        {
            list.insertAtHead(5);
            list.insertAtHead(10);
            list.insertAtHead(15);
            CHECK(list.size() == 3);
            CHECK(list.get(0) == 15);
            CHECK(list.get(2) == 5);
        }

        SUBCASE("Insert at tail")
        {
            list.insertAtTail(100);
            list.insertAtTail(200);
            CHECK(list.size() == 2);
            CHECK(list.get(0) == 100);
            CHECK(list.get(1) == 200);
        }
    }

    TEST_CASE("Delete and reverse")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(10);
        list.insertAtTail(20);
        list.insertAtTail(30);
        list.insertAtTail(40);

        SUBCASE("Delete middle element")
        {
            list.deleteAt(1); 
            CHECK(list.size() == 3);
            CHECK(list.get(0) == 10);
            CHECK(list.get(1) == 30);
        }

        SUBCASE("Reverse list")
        {
            list.reverse(); 
            CHECK(list.get(0) == 40);
            CHECK(list.get(2) == 20);
        }
    }

    TEST_CASE("Large number operations") 
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1000);
        list.insertAtTail(2000);
        list.insertAtTail(3000);
    
        CHECK(list.size() == 3);
        CHECK(list.get(1) == 2000);
    
        list.reverse();
        CHECK(list.get(0) == 3000);
    }

    TEST_CASE("Negative number operations")
    {
        DoublyLinkedList<int> list;
        list.insertAtHead(-5);
        list.insertAtHead(-10);
    
        CHECK(list.indexOf(-5) == 1);
        CHECK(list.contains(-10));
    }

    TEST_CASE("Mixed insert operations")
    {
        DoublyLinkedList<int> list;
        list.insertAtHead(50);
        list.insertAtTail(60);
        list.insertAt(1, 55);
    
        CHECK(list.toString() == "[50, 55, 60]");
        list.deleteAt(0);
        CHECK(list.toString() == "[55, 60]");
    }

    TEST_CASE("String list operations")
    {
        DoublyLinkedList<string> list;
        list.insertAtTail("apple");
        list.insertAtTail("banana");
    
        CHECK(list.get(1) == "banana");
        CHECK(list.indexOf("apple") == 0);
    }

    TEST_CASE("Edge case operations") 
    {
        DoublyLinkedList<int> list;
        CHECK(list.size() == 0);
        
        list.insertAt(0, 100);
        CHECK(list.get(0) == 100);
    
        list.deleteAt(0);
        CHECK(list.size() == 0);
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
    
    TEST_CASE("Point list edge cases")
    {
        DoublyLinkedList<Point> list;
    
        SUBCASE("Empty list toString")
        {
            CHECK(list.toString(pointToString) == "[]");
            CHECK(list.size() == 0);
        }
    
        SUBCASE("Single point operations")
        {
            list.insertAtTail(Point(99, 99));
            CHECK(list.toString(pointToString) == "[(99,99)]");
            list.deleteAt(0);
            CHECK(list.toString(pointToString) == "[]");
        }
    
        SUBCASE("Floating point truncation")
        {
            list.insertAtTail(Point(1.9, 2.1));
            list.insertAtTail(Point(3.5, 4.9));  // Truncated to [(1,2), (3,4)]
            CHECK(list.toString(pointToString) == "[(1,2), (3,4)]");
        }
    }
}

// TODO add test case