#include "doctest/doctest.h"
#include "src/DoublyLinkedList.h"

TEST_SUITE("DoublyLinkedList Basic Operations")
{
    TEST_CASE("Insert at head and tail")
    {
        DoublyLinkedList<int> list;
        list.insertAtHead(2);
        list.insertAtHead(1);
        list.insertAtTail(3);
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
        list.deleteAt(1);
        CHECK(list.get(0) == 1);
        CHECK(list.get(1) == 3);
        CHECK(list.size() == 2);
    }

    TEST_CASE("Reverse list")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.insertAtTail(3);
        list.reverse();
        CHECK(list.get(0) == 3);
        CHECK(list.get(1) == 2);
        CHECK(list.get(2) == 1);
    }
}

TEST_SUITE("DoublyLinkedList<Point> Operations")
{
    std::string pointToString(Point &p)
    {
        return "(" + std::to_string(int(p.getX())) + "," + std::to_string(int(p.getY())) + ")";
    }

    TEST_CASE("Insert Point and check order")
    {
        DoublyLinkedList<Point> list;
        list.insertAtHead(Point(1, 2));
        list.insertAtHead(Point(3, 4));
        CHECK(list.get(0) == Point(3, 4));
        CHECK(list.get(1) == Point(1, 2));
    }

    TEST_CASE("To string for Point list")
    {
        DoublyLinkedList<Point> list;
        list.insertAtTail(Point(9, 0));
        list.insertAtTail(Point(8, 1));
        CHECK(list.toString(pointToString) == "[(9,0), (8,1)]");
    }

    TEST_CASE("Contains and indexOf with Point")
    {
        DoublyLinkedList<Point> list;
        list.insertAtTail(Point(1, 2));
        list.insertAtTail(Point(3, 4));
        CHECK(list.contains(Point(1, 2)));
        CHECK(list.indexOf(Point(3, 4)) == 1);
        CHECK_FALSE(list.contains(Point(5, 6)));
    }
}

TEST_SUITE("DoublyLinkedList Iterator")
{
    TEST_CASE("Forward iteration using Iterator")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(10);
        list.insertAtTail(20);
        list.insertAtTail(30);

        int expected[] = {10, 20, 30};
        int idx = 0;
        for (auto it = list.begin(); it != list.end(); ++it)
        {
            CHECK(*it == expected[idx++]);
        }
    }

    TEST_CASE("Range-based for loop")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.insertAtTail(3);
        int sum = 0;
        for (int val : list)
            sum += val;
        CHECK(sum == 6);
    }

    TEST_CASE("Iterator independence")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(100);
        list.insertAtTail(200);
        auto it1 = list.begin();
        auto it2 = list.begin();
        ++it2;
        CHECK(*it1 == 100);
        CHECK(*it2 == 200);
    }
}

TEST_SUITE("DoublyLinkedList Edge Cases")
{
    TEST_CASE("Empty list toString and size")
    {
        DoublyLinkedList<int> list;
        CHECK(list.size() == 0);
        CHECK(list.toString([](int &v) { return std::to_string(v); }) == "[]");
    }

    TEST_CASE("Out of bounds access throws")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        CHECK_THROWS_AS(list.get(1), std::out_of_range);
        CHECK_THROWS_AS(list.deleteAt(2), std::out_of_range);
    }
}
