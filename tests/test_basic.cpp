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
    TEST_CASE("Insert Point at specific index")
    {
        DoublyLinkedList<Point> list;
        list.insertAtTail(Point(1, 2));
        list.insertAtTail(Point(3, 4));
        list.insertAt(1, Point(2, 3)); // should become [(1,2), (2,3), (3,4)]
        CHECK(list.size() == 3);
        CHECK(list.get(0) == Point(1, 2));
        CHECK(list.get(1) == Point(2, 3));
        CHECK(list.get(2) == Point(3, 4));
    }

    TEST_CASE("Delete Point at specific index")
    {
        DoublyLinkedList<Point> list;
        list.insertAtTail(Point(1, 2));
        list.insertAtTail(Point(3, 4));
        list.insertAtTail(Point(5, 6));
        list.deleteAt(1); // should become [(1,2), (5,6)]
        CHECK(list.size() == 2);
        CHECK(list.get(0) == Point(1, 2));
        CHECK(list.get(1) == Point(5, 6));
    }

    TEST_CASE("Index of Point")
    {
        DoublyLinkedList<Point> list;
        list.insertAtTail(Point(1, 2));
        list.insertAtTail(Point(3, 4));
        CHECK(list.indexOf(Point(3, 4)) == 1);
        CHECK(list.indexOf(Point(5, 6)) == -1); // Not in the list
    }

    TEST_CASE("Contains Point")
    {
        DoublyLinkedList<Point> list;
        list.insertAtTail(Point(1, 2));
        list.insertAtTail(Point(3, 4));
        CHECK(list.contains(Point(1, 2)) == true);
        CHECK(list.contains(Point(5, 6)) == false); // Not in the list
    }

    TEST_CASE("Size of Point list")
    {
        DoublyLinkedList<Point> list;
        list.insertAtTail(Point(1, 2));
        list.insertAtTail(Point(3, 4));
        CHECK(list.size() == 2);
    }

    TEST_CASE("Reverse Point list")
    {
        DoublyLinkedList<Point> list;
        list.insertAtTail(Point(1, 2));
        list.insertAtTail(Point(3, 4));
        list.reverse(); // should become [(3,4), (1,2)]
        CHECK(list.get(0) == Point(3, 4));
        CHECK(list.get(1) == Point(1, 2));
    }
}

// TODO add test case
TEST_SUITE("DoublyLinkedList Operations")
{
    TEST_CASE("Insert at specific index")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(3);
        list.insertAt(1, 2); // should become [1, 2, 3]
        CHECK(list.size() == 3);
        CHECK(list.get(0) == 1);
        CHECK(list.get(1) == 2);
        CHECK(list.get(2) == 3);
    }

    TEST_CASE("Delete at specific index")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.insertAtTail(3);
        list.deleteAt(1); // should become [1, 3]
        CHECK(list.size() == 2);
        CHECK(list.get(0) == 1);
        CHECK(list.get(1) == 3);
    }

    TEST_CASE("Index of and contains")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.insertAtTail(3);
        CHECK(list.indexOf(2) == 1);
        CHECK(list.contains(3) == true);
        CHECK(list.contains(4) == false);
    }
    TEST_CASE("Iterator basic functionality")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.insertAtTail(3);

        int sum = 0;
        for (const auto &item : list)
        {
            sum += item;
        }
        CHECK(sum == 6); // 1 + 2 + 3
    }
    TEST_CASE("Insert at 1")
    {
        DoublyLinkedList<int> list;
        list.insertAtHead(3);
        list.insertAtTail(2);

        list.insertAt(1, 1); // should become [1, 2]
        CHECK(list.size() == 3);
        CHECK(list.get(0) == 3);
        CHECK(list.get(1) == 1);
    }

}
TEST_SUITE("DoublyLinkedList Additional Tests")
{
    TEST_CASE("Insert at head multiple times")
    {
        DoublyLinkedList<int> list;
        list.insertAtHead(3);
        list.insertAtHead(2);
        list.insertAtHead(1); // should become [1, 2, 3]

        CHECK(list.size() == 3);
        CHECK(list.get(0) == 1);
        CHECK(list.get(1) == 2);
        CHECK(list.get(2) == 3);
    }

    TEST_CASE("Delete head and tail")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(10);
        list.insertAtTail(20);
        list.insertAtTail(30);
        list.deleteAt(0); // delete head, list = [20, 30]
        list.deleteAt(1); // delete tail, list = [20]

        CHECK(list.size() == 1);
        CHECK(list.get(0) == 20);
    }

    TEST_CASE("Insert at out-of-range index")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(5);
        list.insertAtTail(10);
        CHECK_THROWS_AS(list.insertAt(5, 99), std::out_of_range);
        CHECK(list.size() == 2);
    }

    TEST_CASE("Delete at out-of-range index")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        CHECK_THROWS_AS(list.deleteAt(2), std::out_of_range);
        CHECK(list.size() == 1);
    }

    TEST_CASE("Get at out-of-range index")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        CHECK_THROWS_AS(list.get(3), std::out_of_range);
    }

    TEST_CASE("Iterator with empty list")
    {
        DoublyLinkedList<int> list;
        int count = 0;
        for (auto it : list)
        {
            (void)it;
            count++;
        }
        CHECK(count == 0);
    }

    TEST_CASE("Insert at tail repeatedly")
    {
        DoublyLinkedList<int> list;
        for (int i = 1; i <= 5; ++i)
            list.insertAtTail(i); // [1, 2, 3, 4, 5]

        CHECK(list.size() == 5);
        CHECK(list.get(4) == 5);
    }

    TEST_CASE("IndexOf returns -1 for non-existent element")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.insertAtTail(3);
        CHECK(list.indexOf(99) == -1);
    }
}
