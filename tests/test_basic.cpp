#include "doctest/doctest.h"
#include "src/DoublyLinkedList.h"


#include <iomanip> 

TEST_SUITE("Expanded DoublyLinkedList Basic Operations")
{
    TEST_CASE("Basic operations with double")
    {
        DoublyLinkedList<double> list;
        list.insertAtHead(20.5);
        list.insertAtTail(30.5);
        list.insertAtHead(10.5); 

        CHECK(list.size() == 3);
        CHECK(doctest::Approx(list.get(0)) == 10.5);
        CHECK(doctest::Approx(list.get(1)) == 20.5);
        CHECK(doctest::Approx(list.get(2)) == 30.5);
    }

    TEST_CASE("Delete and reverse with float")
    {
        DoublyLinkedList<float> list;
        list.insertAtTail(1.1f);
        list.insertAtTail(2.2f);
        list.insertAtTail(3.3f);
        list.insertAtTail(4.4f); 

        list.deleteAt(2); 
        CHECK(list.size() == 3);
        CHECK(doctest::Approx(list.get(2)) == 4.4f);

        list.reverse(); 
        CHECK(doctest::Approx(list.get(0)) == 4.4f);
        CHECK(doctest::Approx(list.get(2)) == 1.1f);
    }
    
    TEST_CASE("indexOf and contains with char")
    {
        DoublyLinkedList<char> list;
        list.insertAtTail('X');
        list.insertAtTail('Y');
        list.insertAtTail('Z');

        CHECK(list.indexOf('Y') == 1);
        CHECK(list.indexOf('A') == -1);
        CHECK(list.contains('Z') == true);
        CHECK(list.contains('B') == false);
    }
    
    TEST_CASE("Insert and delete with std::string")
    {
        DoublyLinkedList<std::string> list;
        list.insertAtHead("World");
        list.insertAtHead("Hello"); 
        list.insertAt(1, ", ");   
        CHECK(list.size() == 3);
        CHECK(list.get(0) == "Hello");
        CHECK(list.get(1) == ", ");
        
        list.deleteAt(0);
        CHECK(list.get(0) == ", ");
    }
    
    TEST_CASE("Deleting first and last elements")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(10);
        list.insertAtTail(20);
        list.insertAtTail(30);

        SUBCASE("Delete head")
        {
            list.deleteAt(0); 
            CHECK(list.size() == 2);
            CHECK(list.get(0) == 20);
        }

        SUBCASE("Delete tail")
        {
            list.deleteAt(list.size() - 1);
            CHECK(list.size() == 2);
            CHECK(list.get(1) == 20);
        }
    }
    
    TEST_CASE("Insert at end index is equivalent to insertAtTail")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.insertAt(2, 3);
        CHECK(list.size() == 3);
        CHECK((list.get(2) == 3));
    }

    TEST_CASE("Operations on an empty list")
    {
        DoublyLinkedList<char> list;
        CHECK(list.size() == 0);
        CHECK(list.indexOf('a') == -1);
        CHECK(list.contains('a') == false);
        CHECK_THROWS_AS(list.get(0), std::out_of_range);
        CHECK_THROWS_AS(list.deleteAt(0), std::out_of_range);
        CHECK_NOTHROW(list.reverse()); 
        CHECK(list.size() == 0);
    }
    
    TEST_CASE("Reversing a list twice returns to original state")
    {
        DoublyLinkedList<Point> list;
        Point p1(1,1), p2(2,2), p3(3,3);
        list.insertAtTail(p1);
        list.insertAtTail(p2);
        list.insertAtTail(p3);

        list.reverse(); 
        CHECK(list.get(0) == p3);

        list.reverse(); 
        CHECK(list.get(0) == p1);
        CHECK(list.get(1) == p2);
        CHECK(list.get(2) == p3);
    }
    
    TEST_CASE("toString with double and custom formatting")
    {
        DoublyLinkedList<double> list;
        list.insertAtTail(1.25);
        list.insertAtTail(2.5);
        
        auto formatter = [](double& val) {
            std::stringstream ss;
            ss << std::fixed << std::setprecision(1) << val;
            return ss.str();
        };
        
        std::string str = list.toString(formatter);
        CHECK(str == "[1.2, 2.5]");
    }
    
    TEST_CASE("Operations with 3D Point objects")
    {
        DoublyLinkedList<Point> list;
        Point p1(1, 2, 3);
        Point p2(4, 5, 6);
        list.insertAtHead(p2);
        list.insertAtTail(p1); 
        
        CHECK(list.size() == 2);
        CHECK(list.get(0) == Point(4, 5, 6));
        CHECK(list.get(1) == Point(1, 2, 3));
        CHECK(list.contains(Point(4, 5, 6)) == true);
    }
    
    TEST_CASE("Clearing the list by deleting elements")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(5);
        list.insertAtTail(10);
        list.insertAtTail(15);
        
        while(list.size() > 0) {
            list.deleteAt(0);
        }
        
        CHECK(list.size() == 0);
        CHECK_THROWS_AS(list.get(0), std::out_of_range);
    }

    TEST_CASE("Inserting at invalid indices throws exception")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(10);
        CHECK_THROWS_AS(list.insertAt(-1, 99), std::out_of_range);
        CHECK_THROWS_AS(list.insertAt(2, 99), std::out_of_range); 
    }
    
    TEST_CASE("Deleting at invalid indices throws exception")
    {
        DoublyLinkedList<std::string> list;
        list.insertAtTail("test");
        CHECK_THROWS_AS(list.deleteAt(-1), std::out_of_range);
        CHECK_THROWS_AS(list.deleteAt(1), std::out_of_range); 
    }
    
    TEST_CASE("Getting from invalid indices throws exception")
    {
        DoublyLinkedList<Point> list;
        list.insertAtTail(Point(0,0));
        CHECK_THROWS_AS(list.get(-1), std::out_of_range);
        CHECK_THROWS_AS(list.get(1), std::out_of_range);
    }
    
    TEST_CASE("toString of list<Point> with negative coordinates")
    {
        auto pointToString = [](Point & p)
        {
            return "(" + std::to_string(int(p.getX())) + "," + std::to_string(int(p.getY())) + ")";
        };

        DoublyLinkedList<Point> list;
        list.insertAtTail(Point(-1, -5));
        list.insertAtTail(Point(0, -9));
        std::string str = list.toString(pointToString);
        CHECK(str == "[(-1,-5), (0,-9)]");
    }
    
    TEST_CASE("indexOf with duplicate elements")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(10);
        list.insertAtTail(20);
        list.insertAtTail(10);
        list.insertAtTail(30);
        
        CHECK(list.indexOf(10) == 0);
        CHECK(list.indexOf(20) == 1);
    }
    
    TEST_CASE("Contains after deletion")
    {
        DoublyLinkedList<char> list;
        list.insertAtTail('a');
        list.insertAtTail('b');
        CHECK(list.contains('b') == true);
        
        list.deleteAt(1);
        CHECK(list.contains('b') == false);
        CHECK(list.size() == 1);
    }

    TEST_CASE("Operations on a single-element list")
    {
        DoublyLinkedList<std::string> list;
        list.insertAtTail("lonely");

        CHECK(list.size() == 1);
        CHECK(list.get(0) == "lonely");
        CHECK(list.contains("lonely") == true);
        CHECK(list.indexOf("lonely") == 0);
        
        list.deleteAt(0);
        CHECK(list.size() == 0);
    }
    
    TEST_CASE("toString of an empty list")
    {
        DoublyLinkedList<int> list;
        auto formatter = [](int& val) { return std::to_string(val); };
        CHECK(list.toString(formatter) == "[]");
    }
    
    TEST_CASE("toString with std::string elements")
    {
        DoublyLinkedList<std::string> list;
        list.insertAtTail("alpha");
        list.insertAtTail("beta");
        auto formatter = [](std::string& s) { return s; };
        CHECK(list.toString(formatter) == "[alpha, beta]");
    }
}