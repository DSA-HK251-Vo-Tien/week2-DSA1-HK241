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

    TEST_CASE("Iteration over single-element list")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(99); 

        int expected[] = {99};

        SUBCASE("Forward iteration using Iterator")
        {
            int idx = 0;
            for (auto it = list.begin(); it != list.end(); ++it)
            {
                CHECK(*it == expected[idx++]);
            }
            CHECK(idx == 1);
        }

        SUBCASE("Range-based for iteration")
        {
            int idx = 0;
            for (int x : list)
            {
                CHECK(x == expected[idx++]);
            }
            CHECK(idx == 1);
        }
    }

    TEST_CASE("Iteration over five-element list")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(5);
        list.insertAtTail(10);
        list.insertAtTail(15);
        list.insertAtTail(20);
        list.insertAtTail(25);

        int expected[] = {5, 10, 15, 20, 25};

        SUBCASE("Forward iteration using Iterator")
        {
            int idx = 0;
            for (auto it = list.begin(); it != list.end(); ++it)
            {
                CHECK(*it == expected[idx++]);
            }
            CHECK(idx == 5);
        }

        SUBCASE("Range-based for iteration")
        {
            int idx = 0;
            for (int x : list)
            {
                CHECK(x == expected[idx++]);
            }
            CHECK(idx == 5);
        }
    }

    TEST_CASE("Iteration with negative numbers")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(-10);
        list.insertAtTail(-20);
        list.insertAtTail(-30);

        int expected[] = {-10, -20, -30};

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
    // TODO add test case
    TEST_CASE("Iteration over DoublyLinkedList")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.insertAtTail(3);
        list.insertAtTail(4);

        int expected[] = {1, 2, 3, 4};

        SUBCASE("Forward iteration using Iterator")
        {
            int idx = 0;
            for (auto it = list.begin(); it != list.end(); ++it)
            {
                CHECK(*it == expected[idx++]);
            }
            CHECK(idx == 4);
        }

        SUBCASE("Range-based for iteration")
        {
            int idx = 0;
            for (int x : list)
            {
                CHECK(x == expected[idx++]);
            }
            CHECK(idx == 4);
        }
    }

    TEST_CASE("Prefix == manual iteration") {
        DoublyLinkedList<int> list;
        for (int i = 100; i <= 500; i += 100) list.insertAtTail(i);
        for (int i = 500; i >= 100; i -= 100) list.insertAtHead(i);

        for(int io = 0; io < list.size(); io++){
            auto it = list.begin();
            int total = 0;
            for(int j = 0; j < list.size();j++){
                if(list.get(j) == *list.begin()) total++;
            }
            CHECK(total == 2);
        }
    }
    
    TEST_CASE("Iterator equality with while loop") {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.insertAtTail(3);
        list.insertAtHead(3);
        list.insertAtHead(2);
        list.insertAtHead(1);

        auto it = list.begin();
        int count = 0;
        int target = *list.begin();
        while(it != list.end()) {
            if(*it == target) {
                count++;
            }
            ++it;
        }
        CHECK(count == 2);
    }

    TEST_CASE("Count specific value occurrences") {
        DoublyLinkedList<int> list;
        list.insertAtTail(5);
        list.insertAtTail(10);
        list.insertAtHead(5);
        list.insertAtTail(15);
        list.insertAt(2, 5);

        int five_count = 0;
        for(auto it = list.begin(); it != list.end(); ++it) {
            if(*it == 5) {
                five_count++;
            }
        }
        CHECK(five_count == 3);
    }

    TEST_CASE("Count unequal elements using iterators") {
        DoublyLinkedList<int> list;
        list.insertAtTail(10);
        list.insertAtTail(20);
        list.insertAtTail(10);
        list.insertAtTail(20);
        list.insertAtTail(10);

        int first_val = *list.begin();
        int unequal_count = 0;
    
        for (auto it = list.begin(); it != list.end(); ++it) {
            if (*it != first_val) {
                unequal_count++;
            }
        }
        CHECK(unequal_count == 2);
    }

    TEST_CASE("Inequality check with early exit") {
        DoublyLinkedList<int> list;
        list.insertAtTail(5);
        list.insertAtTail(5);
        list.insertAtTail(3);
        list.insertAtTail(5);
        list.insertAtTail(5);

        int first_val = list.get(0);
        bool found_unequal = false;
        int unequal_pos = -1;
    
        int index = 0;
        for (int val : list) {
            if (val != first_val) {
                found_unequal = true;
                unequal_pos = index;
                break;
            }
            index++;
        }
    
        CHECK(found_unequal);
        CHECK(unequal_pos == 2);
        CHECK(list.get(unequal_pos) == 3);
    }

    TEST_CASE("Dereference operator with consecutive numbers") {
        DoublyLinkedList<int> list;
        for (int i = 1; i <= 5; i++) list.insertAtTail(i);
        for (int i = 5; i >= 1; i--) list.insertAtHead(i);

        int j = 0;
        for (auto it = list.begin(); it != list.end(); ++it) {
            CHECK(*it == list.get(j++)); 
        }
        CHECK(j == list.size());
    }   

    TEST_CASE("Dereference operator with mixed signs") {
        DoublyLinkedList<int> list;
        list.insertAtTail(-10);
        list.insertAtTail(-20);
        list.insertAtHead(10);
        list.insertAtHead(20);

        int j = 0;
        for (auto it = list.begin(); it != list.end(); ++it) {
            CHECK(*it == list.get(j++));
        }
    }

    TEST_CASE("Dereference operator with equal values") {
        DoublyLinkedList<int> list;
        for (int i = 0; i < 5; i++) {
            list.insertAtTail(7);
            list.insertAtHead(7);
        }

        int j = 0;
        for (auto it = list.begin(); it != list.end(); ++it) {
            CHECK(*it == list.get(j++));
            CHECK(*it == 7);
        }
    }
}