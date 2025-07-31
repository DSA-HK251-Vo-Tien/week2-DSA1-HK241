#include "doctest/doctest.h"
#include "src/DoublyLinkedList.h"

TEST_SUITE("DoublyLinkedList Basic Operations")
{
    TEST_CASE("Constructor and initial state")
    {
        DoublyLinkedList<int> list;
        CHECK(list.size() == 0);
    }

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

        SUBCASE("Insert mixed head and tail")
        {
            list.insertAtHead(2);
            list.insertAtTail(3);
            list.insertAtHead(1);
            list.insertAtTail(4);
            CHECK(list.size() == 4);
            CHECK(list.get(0) == 1);
            CHECK(list.get(1) == 2);
            CHECK(list.get(2) == 3);
            CHECK(list.get(3) == 4);
        }
    }

    TEST_CASE("Insert at specific index")
    {
        DoublyLinkedList<int> list;

        SUBCASE("Insert at index 0 (empty list)")
        {
            list.insertAt(0, 5);
            CHECK(list.size() == 1);
            CHECK(list.get(0) == 5);
        }

        SUBCASE("Insert at middle")
        {
            list.insertAtTail(1);
            list.insertAtTail(3);
            list.insertAt(1, 2);
            CHECK(list.size() == 3);
            CHECK(list.get(0) == 1);
            CHECK(list.get(1) == 2);
            CHECK(list.get(2) == 3);
        }

        SUBCASE("Insert at end using insertAt")
        {
            list.insertAtTail(1);
            list.insertAtTail(2);
            list.insertAt(2, 3);
            CHECK(list.size() == 3);
            CHECK(list.get(2) == 3);
        }

        SUBCASE("Insert at invalid index throws exception")
        {
            CHECK_THROWS_AS(list.insertAt(-1, 5), std::out_of_range);
            CHECK_THROWS_AS(list.insertAt(1, 5), std::out_of_range);
            list.insertAtTail(1);
            CHECK_THROWS_AS(list.insertAt(2, 5), std::out_of_range);
        }
    }

    TEST_CASE("Delete operations")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.insertAtTail(3);
        list.insertAtTail(4);

        SUBCASE("Delete first element")
        {
            list.deleteAt(0);
            CHECK(list.size() == 3);
            CHECK(list.get(0) == 2);
        }

        SUBCASE("Delete middle element")
        {
            list.deleteAt(1);
            CHECK(list.size() == 3);
            CHECK(list.get(0) == 1);
            CHECK(list.get(1) == 3);
            CHECK(list.get(2) == 4);
        }

        SUBCASE("Delete last element")
        {
            list.deleteAt(3);
            CHECK(list.size() == 3);
            CHECK(list.get(2) == 3);
        }

        SUBCASE("Delete invalid index throws exception")
        {
            CHECK_THROWS_AS(list.deleteAt(-1), std::out_of_range);
            CHECK_THROWS_AS(list.deleteAt(4), std::out_of_range);
        }

        SUBCASE("Delete from single element list")
        {
            DoublyLinkedList<int> singleList;
            singleList.insertAtTail(42);
            singleList.deleteAt(0);
            CHECK(singleList.size() == 0);
        }
    }

    TEST_CASE("Get operations")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(10);
        list.insertAtTail(20);
        list.insertAtTail(30);

        SUBCASE("Get valid indices")
        {
            CHECK(list.get(0) == 10);
            CHECK(list.get(1) == 20);
            CHECK(list.get(2) == 30);
        }

        SUBCASE("Get invalid indices throws exception")
        {
            CHECK_THROWS_AS(list.get(-1), std::out_of_range);
            CHECK_THROWS_AS(list.get(3), std::out_of_range);
        }

        SUBCASE("Modify through get reference")
        {
            list.get(1) = 25;
            CHECK(list.get(1) == 25);
        }
    }

    TEST_CASE("Search operations")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(10);
        list.insertAtTail(20);
        list.insertAtTail(30);
        list.insertAtTail(20); // duplicate

        SUBCASE("indexOf existing elements")
        {
            CHECK(list.indexOf(10) == 0);
            CHECK(list.indexOf(20) == 1); // returns first occurrence
            CHECK(list.indexOf(30) == 2);
        }

        SUBCASE("indexOf non-existing element")
        {
            CHECK(list.indexOf(40) == -1);
        }

        SUBCASE("contains existing elements")
        {
            CHECK(list.contains(10) == true);
            CHECK(list.contains(20) == true);
            CHECK(list.contains(30) == true);
        }

        SUBCASE("contains non-existing element")
        {
            CHECK(list.contains(40) == false);
        }
    }

    TEST_CASE("Reverse operations")
    {
        SUBCASE("Reverse empty list")
        {
            DoublyLinkedList<int> list;
            list.reverse();
            CHECK(list.size() == 0);
        }

        SUBCASE("Reverse single element list")
        {
            DoublyLinkedList<int> list;
            list.insertAtTail(42);
            list.reverse();
            CHECK(list.size() == 1);
            CHECK(list.get(0) == 42);
        }

        SUBCASE("Reverse multiple elements")
        {
            DoublyLinkedList<int> list;
            list.insertAtTail(1);
            list.insertAtTail(2);
            list.insertAtTail(3);
            list.insertAtTail(4);
            
            list.reverse();
            CHECK(list.get(0) == 4);
            CHECK(list.get(1) == 3);
            CHECK(list.get(2) == 2);
            CHECK(list.get(3) == 1);
        }

        SUBCASE("Double reverse returns to original")
        {
            DoublyLinkedList<int> list;
            list.insertAtTail(1);
            list.insertAtTail(2);
            list.insertAtTail(3);
            
            list.reverse();
            list.reverse();
            CHECK(list.get(0) == 1);
            CHECK(list.get(1) == 2);
            CHECK(list.get(2) == 3);
        }
    }

    TEST_CASE("toString operations")
    {
        SUBCASE("Empty list toString")
        {
            DoublyLinkedList<int> list;
            CHECK(list.toString() == "[]");
        }

        SUBCASE("Single element toString")
        {
            DoublyLinkedList<int> list;
            list.insertAtTail(42);
            CHECK(list.toString() == "[42]");
        }

        SUBCASE("Multiple elements toString")
        {
            DoublyLinkedList<int> list;
            list.insertAtTail(1);
            list.insertAtTail(2);
            list.insertAtTail(3);
            CHECK(list.toString() == "[1, 2, 3]");
        }
    }
}

TEST_SUITE("DoublyLinkedList Iterator")
{
    TEST_CASE("Forward iteration")
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

        SUBCASE("Post-increment iteration")
        {
            int idx = 0;
            for (auto it = list.begin(); it != list.end(); it++)
            {
                CHECK(*it == expected[idx++]);
            }
            CHECK(idx == 3);
        }
    }

    TEST_CASE("Iterator on empty list")
    {
        DoublyLinkedList<int> list;
        
        SUBCASE("begin equals end for empty list")
        {
            CHECK(list.begin() == list.end());
        }

        SUBCASE("No iteration on empty list")
        {
            int count = 0;
            for (auto it = list.begin(); it != list.end(); ++it)
            {
                count++;
            }
            CHECK(count == 0);
        }
    }

    TEST_CASE("Iterator modification")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.insertAtTail(3);

        SUBCASE("Modify elements through iterator")
        {
            for (auto it = list.begin(); it != list.end(); ++it)
            {
                *it = *it * 2;
            }
            CHECK(list.get(0) == 2);
            CHECK(list.get(1) == 4);
            CHECK(list.get(2) == 6);
        }
    }

    TEST_CASE("Iterator equality and inequality")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);

        SUBCASE("Iterator equality")
        {
            auto it1 = list.begin();
            auto it2 = list.begin();
            CHECK(it1 == it2);
            
            ++it1;
            CHECK(it1 != it2);
            
            ++it2;
            CHECK(it1 == it2);
        }
    }
}

TEST_SUITE("DoublyLinkedList<Point> Operations")
{
    std::string pointToString(Point & p)
    {
        return "(" + std::to_string(int(p.getX())) + "," + std::to_string(int(p.getY())) + ")";
    }

    TEST_CASE("Point insertion and retrieval")
    {
        DoublyLinkedList<Point> list;

        SUBCASE("Insert Point at head")
        {
            list.insertAtHead(Point(1, 2));
            list.insertAtHead(Point(3, 4));
            CHECK(list.size() == 2);
            CHECK(list.get(0) == Point(3, 4));
            CHECK(list.get(1) == Point(1, 2));
        }

        SUBCASE("Insert Point at tail")
        {
            list.insertAtTail(Point(1, 2));
            list.insertAtTail(Point(3, 4));
            CHECK(list.size() == 2);
            CHECK(list.get(0) == Point(1, 2));
            CHECK(list.get(1) == Point(3, 4));
        }
    }

    TEST_CASE("Point search operations")
    {
        DoublyLinkedList<Point> list;
        list.insertAtTail(Point(1, 1));
        list.insertAtTail(Point(2, 2));
        list.insertAtTail(Point(3, 3));

        SUBCASE("indexOf Point")
        {
            CHECK(list.indexOf(Point(2, 2)) == 1);
            CHECK(list.indexOf(Point(4, 4)) == -1);
        }

        SUBCASE("contains Point")
        {
            CHECK(list.contains(Point(1, 1)) == true);
            CHECK(list.contains(Point(5, 5)) == false);
        }
    }

    TEST_CASE("Point toString")
    {
        DoublyLinkedList<Point> list;
        
        SUBCASE("Empty Point list toString")
        {
            CHECK(list.toString(pointToString) == "[]");
        }

        SUBCASE("Single Point toString")
        {
            list.insertAtTail(Point(5, 7));
            CHECK(list.toString(pointToString) == "[(5,7)]");
        }

        SUBCASE("Multiple Points toString")
        {
            list.insertAtTail(Point(9, 0));
            list.insertAtTail(Point(8, 1));
            std::string str = list.toString(pointToString);
            CHECK(str == "[(9,0), (8,1)]");
        }
    }

    TEST_CASE("Point reverse operation")
    {
        DoublyLinkedList<Point> list;
        list.insertAtTail(Point(1, 1));
        list.insertAtTail(Point(2, 2));
        list.insertAtTail(Point(3, 3));
        
        list.reverse();
        CHECK(list.get(0) == Point(3, 3));
        CHECK(list.get(1) == Point(2, 2));
        CHECK(list.get(2) == Point(1, 1));
    }
}

TEST_SUITE("DoublyLinkedList String Operations")
{
    TEST_CASE("String list operations")
    {
        DoublyLinkedList<std::string> list;

        SUBCASE("String insertion")
        {
            list.insertAtTail("hello");
            list.insertAtTail("world");
            CHECK(list.size() == 2);
            CHECK(list.get(0) == "hello");
            CHECK(list.get(1) == "world");
        }

        SUBCASE("String search")
        {
            list.insertAtTail("apple");
            list.insertAtTail("banana");
            list.insertAtTail("cherry");
            
            CHECK(list.indexOf("banana") == 1);
            CHECK(list.contains("cherry") == true);
            CHECK(list.contains("grape") == false);
        }

        SUBCASE("String toString")
        {
            list.insertAtTail("first");
            list.insertAtTail("second");
            CHECK(list.toString() == "[first, second]");
        }
    }
}

TEST_SUITE("DoublyLinkedList Edge Cases")
{
    TEST_CASE("Large list operations")
    {
        DoublyLinkedList<int> list;
        
        SUBCASE("Insert many elements")
        {
            for (int i = 0; i < 1000; ++i)
            {
                list.insertAtTail(i);
            }
            CHECK(list.size() == 1000);
            CHECK(list.get(0) == 0);
            CHECK(list.get(999) == 999);
        }

        SUBCASE("Delete many elements")
        {
            for (int i = 0; i < 100; ++i)
            {
                list.insertAtTail(i);
            }
            
            // Delete every other element
            for (int i = 99; i >= 0; i -= 2)
            {
                list.deleteAt(i);
            }
            
            CHECK(list.size() == 50);
        }
    }

    TEST_CASE("Mixed operations")
    {
        DoublyLinkedList<int> list;
        
        SUBCASE("Insert, delete, reverse sequence")
        {
            list.insertAtTail(1);
            list.insertAtHead(0);
            list.insertAt(1, 2);
            // List: [0, 2, 1]
            
            list.deleteAt(1);
            // List: [0, 1]
            
            list.reverse();
            // List: [1, 0]
            
            CHECK(list.size() == 2);
            CHECK(list.get(0) == 1);
            CHECK(list.get(1) == 0);
        }
    }

    TEST_CASE("Memory and performance")
    {
        SUBCASE("Repeated insert and delete")
        {
            DoublyLinkedList<int> list;
            
            // Insert and delete many times
            for (int cycle = 0; cycle < 10; ++cycle)
            {
                for (int i = 0; i < 100; ++i)
                {
                    list.insertAtTail(i);
                }
                
                while (list.size() > 0)
                {
                    list.deleteAt(0);
                }
            }
            
            CHECK(list.size() == 0);
        }
    }
}