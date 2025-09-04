#include "doctest/doctest.h"
#include "src/DoublyLinkedList.h"

TEST_SUITE("DoublyLinkedList Iterator")
{
    TEST_CASE("Iteration over DoublyLinkedList")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(10);
        list.insertAtTail(20);
        list.insertAtTail(30);

        int expected[] = {10, 20, 30};

        SUBCASE("Forward iteration using Iterator")
        {
            int idx = 0;
            for (auto it = list.begin(); it != list.end(); ++it)
            {
                CHECK(*it == expected[idx++]);
            }
            CHECK(idx == 3);
        }

        SUBCASE("Range-based for iteration")
        {
            int idx = 0;
            for (int x : list)
            {
                CHECK(x == expected[idx++]);
            }
            CHECK(idx == 3);
        }
    }
    TEST_CASE("check list after remove"){
        DoublyLinkedList<int> list;
        list.insertAtTail(10);
        list.insertAtTail(20);
        list.insertAtTail(30);
        list.deleteAt(1);
        int expected[] = {10,30};
        int idx = 0;
        for (int x : list){
            CHECK(x == expected[idx++]);
        } CHECK(idx == 2);
    }
    TEST_CASE("Iterator on an empty list")
    {
        DoublyLinkedList<int> list;
        bool loop_entered = false;
        for (int x : list)
        {
            loop_entered = true;
        }
        CHECK(loop_entered == false);
    }
    TEST_CASE("Iterator on a single-element list")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(100);
        int count = 0;
        int value = 0;
        for (int x : list)
        {
            count++;
            value = x;
        }
        CHECK(count == 1);
        CHECK(value == 100);
    }
     TEST_CASE("Iterator comparison operators")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(5);
        list.insertAtTail(10);

        auto it1 = list.begin();
        auto it2 = list.begin();
        auto end_it = list.end();

        CHECK(it1 == it2); 
        CHECK(it1 != end_it); 
        ++it1; 
        CHECK(it1 != it2); 
    }
    TEST_CASE("Modifying data through an iterator")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.insertAtTail(3);
        for (int& x : list)
        {
            x *= 2;
        }
        int expected[] = {2, 4, 6};
        int idx = 0;
        for (int x : list)
        {
            CHECK(x == expected[idx++]);
        }
    }
     TEST_CASE("Post-increment and post-decrement operators")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(10);
        list.insertAtTail(20);
        list.insertAtTail(30);

        auto it = list.begin();
        CHECK(*(it++) == 10); 
        CHECK(*it == 20);    

        CHECK(*(it++) == 20);
        CHECK(*it == 30);     
    }
    TEST_CASE("Arrow operator with Point objects")
    {
        DoublyLinkedList<Point> list;
        list.insertAtTail(Point(1, 2));
        list.insertAtTail(Point(3, 4));

        auto it = list.begin();
        CHECK(it->getX() == 1);
        CHECK(it->getY() == 2);
        
        ++it;
        CHECK(it->getX() == 3);
        CHECK(it->getY() == 4);
    }
    // TODO add test case
}