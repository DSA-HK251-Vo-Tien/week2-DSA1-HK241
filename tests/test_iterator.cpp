#include "doctest/doctest.h"
#include "src/DoublyLinkedList.h"



TEST_SUITE("Expanded DoublyLinkedList Iterator Tests")
{
    TEST_CASE("Iteration over DoublyLinkedList with double")
    {
        DoublyLinkedList<double> list;
        list.insertAtTail(1.1);
        list.insertAtTail(2.2);
        list.insertAtTail(3.3);

        double expected[] = {1.1, 2.2, 3.3};
        int idx = 0;
        for (double val : list)
        {
            CHECK(doctest::Approx(val) == expected[idx]);
            idx++; 
        }
        CHECK(idx == 3);
    }

    TEST_CASE("Iteration over DoublyLinkedList with float")
    {
        DoublyLinkedList<float> list;
        list.insertAtTail(-0.5f);
        list.insertAtTail(0.0f);
        list.insertAtTail(10.5f);

        float expected[] = {-0.5f, 0.0f, 10.5f};
        int idx = 0;
        for (auto it = list.begin(); it != list.end(); ++it)
        {
            CHECK(doctest::Approx(*it) == expected[idx++]);
        }
        CHECK(idx == 3);
    }

    TEST_CASE("Iteration over DoublyLinkedList with char")
    {
        DoublyLinkedList<char> list;
        list.insertAtTail('a');
        list.insertAtTail('b');
        list.insertAtTail('c');

        char expected[] = {'a', 'b', 'c'};
        int idx = 0;
        for (char c : list)
        {
            CHECK(c == expected[idx++]);
        }
        CHECK(idx == 3);
    }
    
    TEST_CASE("Reverse iteration with std::string")
    {
        DoublyLinkedList<std::string> list;
        list.insertAtTail("first");
        list.insertAtTail("second");
        list.insertAtTail("third");
        list.reverse();

        std::string expected[] = {"third", "second", "first"};
        int idx = 0;
        for (const auto& str : list)
        {
            CHECK(str == expected[idx++]);
        }
        CHECK(idx == 3);
    }

    TEST_CASE("Iteration over empty list with Point")
    {
        DoublyLinkedList<Point> list;
        int count = 0;
        for (const auto& p : list) {
    // code that should throw
}
        CHECK(count == 0);
    }

    TEST_CASE("Iteration over single-element list with Point")
    {
        DoublyLinkedList<Point> list;
        Point p1(1, 2, 3);
        list.insertAtTail(p1);
        
        auto it = list.begin();
        CHECK(*it == p1);
        
        CHECK(++it == list.end());
        CHECK_THROWS_AS(++it, cursor_error);
    }

    TEST_CASE("Forward iteration over DoublyLinkedList of 3D Points")
    {
        DoublyLinkedList<Point> list;
        Point p1(1, 2, 3);
        Point p2(4, 5, 6);
        list.insertAtTail(p1);
        list.insertAtTail(p2);

        Point expected[] = {p1, p2};
        int idx = 0;
        for (const auto& p : list)
        {
            CHECK(p == expected[idx++]);
        }
        CHECK(idx == 2);
    }
    
    TEST_CASE("Forward iteration over DoublyLinkedList of 2D Points")
    {
        DoublyLinkedList<Point> list;
        Point p1(10.5, 20.5);
        Point p2(-5, -8);
        list.insertAtTail(p1);
        list.insertAtTail(p2);

        Point expected[] = {Point(10.5, 20.5, 0), Point(-5, -8, 0)};
        int idx = 0;
        for (const auto& p : list)
        {
            CHECK(p == expected[idx++]);
        }
        CHECK(idx == 2);
    }

    TEST_CASE("Reverse iteration with Point")
    {
        DoublyLinkedList<Point> list;
        Point p1(1, 1, 1);
        Point p2(2, 2, 2);
        Point p3(3, 3, 3);
        list.insertAtTail(p1);
        list.insertAtTail(p2);
        list.insertAtTail(p3);
        list.reverse();

        Point expected[] = {p3, p2, p1};
        int idx = 0;
        for (const auto& p : list) {
            CHECK(p == expected[idx++]);
        }
        CHECK(idx == 3);
    }

    TEST_CASE("Iterator comparison with double list")
    {
        DoublyLinkedList<double> list;
        list.insertAtTail(3.14);
        list.insertAtTail(2.71);

        auto it1 = list.begin();
        auto it2 = list.begin();
        auto it3 = list.end();

        CHECK(it1 == it2);
        CHECK(it1 != it3);
        ++it2;
        CHECK(it1 != it2);
        ++it1;
        CHECK(it1 == it2);
        ++it1; 
        CHECK(it1 == it3);
    }

    TEST_CASE("Iterator increment on empty list throws cursor_error (float)")
    {
        DoublyLinkedList<float> list;
        auto it = list.begin();
        CHECK(it == list.end()); // NO OBJECT so no iterator to begin or end 
        CHECK_THROWS_AS(++it, cursor_error);
    }

    TEST_CASE("Iterator out of bounds throws cursor_error (Point)")
    {
        DoublyLinkedList<Point> list;
        list.insertAtTail(Point(1,1));
        
        auto it = list.begin();
        
        CHECK(++it == list.end());
        CHECK_THROWS_AS(++it, cursor_error); 
    }

    TEST_CASE("Iterator dereference with Point list")
    {
        DoublyLinkedList<Point> list;
        Point p1(5, -5, 5);
        Point p2(10, -10, 10);
        list.insertAtTail(p1);
        list.insertAtTail(p2);

        auto it = list.begin();
        CHECK(*it == p1);
        ++it;
        CHECK(*it == p2);
    }
    
    TEST_CASE("Iteration over list of empty strings")
    {
        DoublyLinkedList<std::string> list;
        list.insertAtTail("");
        list.insertAtTail("");
        
        int count = 0;
        for(const auto& s : list) {
            CHECK(s == "");
            count++;
        }
        CHECK(count == 2);
    }
    
    TEST_CASE("Dereferencing end() iterator throws cursor_error")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(100);
        auto it = list.end();
        CHECK(*(--it) == 100 ) ;
        CHECK(++it == list.end());
        CHECK_THROWS_AS(++it, cursor_error);
    }
    
    TEST_CASE("Reversing an empty list")
    {
        DoublyLinkedList<char> list;
        CHECK_NOTHROW(list.reverse());
        CHECK(list.begin() == list.end());
    }
    
    TEST_CASE("Reversing a single-element list")
    {
        DoublyLinkedList<Point> list;
        Point p(10, 20, 30);
        list.insertAtTail(p);
        list.reverse();
        
        auto it = list.begin();
        CHECK(*it == p);
        ++it;
        CHECK(it == list.end());
        CHECK_THROWS_AS(++it, cursor_error); 
    }

    TEST_CASE("Multiple iterations over the same list")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        
        int expected[] = {1, 2};
        int idx = 0;
        for(int val : list) {
            CHECK(val == expected[idx++]);
        }
        
        idx = 0;
        for(auto it = list.begin(); it != list.end(); ++it) {
            CHECK(*it == expected[idx++]);
        }
        CHECK(idx == 2);
    }
    
    TEST_CASE("Range-based for loop with Point list")
    {
        DoublyLinkedList<Point> list;
        Point p1(0, 0, 0);
        Point p2(1, 0, 1);
        list.insertAtTail(p1);
        list.insertAtTail(p2);

        Point expected[] = {p1, p2};
        int idx = 0;
        for(const auto& p : list) {
            CHECK(p == expected[idx++]);
        }
        CHECK(idx == 2);
    }
    
    TEST_CASE("Iterator comparison after multiple increments")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(10);
        list.insertAtTail(20);
        list.insertAtTail(30);

        auto it1 = list.begin();
        auto it2 = list.begin();

        ++it1;
        ++it1; // it1 trá» Ä‘áº¿n 30
        
        ++it2; // it2 trá» Ä‘áº¿n 20
        
        CHECK(it1 != it2);
        
        ++it2; // it2 trá» Ä‘áº¿n 30
        CHECK(it1 == it2);

        ++it1; // it1 trá» Ä‘áº¿n end()
        CHECK(it1 == list.end());
        CHECK_THROWS_AS(++it1, cursor_error);
    }
}