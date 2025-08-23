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
}

// TODO add test case
TEST_SUITE("DoublyLinkedList Additional Test Cases")
{
    TEST_CASE("Insert at specific index")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(3);
        list.insertAt(1, 2); // Insert 2 at index 1
        CHECK(list.size() == 3);
        CHECK(list.get(0) == 1);
        CHECK(list.get(1) == 2);
        CHECK(list.get(2) == 3);
    }

    TEST_CASE("Delete first element")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.deleteAt(0); // Remove the first element
        CHECK(list.size() == 1);
        CHECK(list.get(0) == 2);
    }

    TEST_CASE("Delete last element")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.deleteAt(1); // Remove the last element
        CHECK(list.size() == 1);
        CHECK(list.get(0) == 1);
    }

    TEST_CASE("Insert at head and tail alternately")
{
    DoublyLinkedList<int> list;

    // Insert elements alternately at head and tail
    list.insertAtHead(1); // [1]
    list.insertAtTail(2); // [1, 2]
    list.insertAtHead(0); // [0, 1, 2]
    list.insertAtTail(3); // [0, 1, 2, 3]

    // Verify the size and order of elements
    CHECK(list.size() == 4);
    CHECK(list.get(0) == 0);
    CHECK(list.get(1) == 1);
    CHECK(list.get(2) == 2);
    CHECK(list.get(3) == 3);
}

    TEST_CASE("Reverse empty list")
    {
        DoublyLinkedList<int> list;
        list.reverse();
        CHECK(list.size() == 0);
    }

    TEST_CASE("Reverse single element list")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.reverse();
        CHECK(list.size() == 1);
        CHECK(list.get(0) == 1);
    }

    TEST_CASE("Insert at out-of-bounds index")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        CHECK_THROWS_AS(list.insertAt(5, 2), std::out_of_range);
    }

    TEST_CASE("Delete at out-of-bounds index")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        CHECK_THROWS_AS(list.deleteAt(5), std::out_of_range);
    }

    TEST_CASE("Access out-of-bounds index")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        CHECK_THROWS_AS(list.get(5), std::out_of_range);
    }

    TEST_CASE("Insert multiple elements at head")
    {
        DoublyLinkedList<int> list;
        list.insertAtHead(3);
        list.insertAtHead(2);
        list.insertAtHead(1);
        CHECK(list.size() == 3);
        CHECK(list.get(0) == 1);
        CHECK(list.get(1) == 2);
        CHECK(list.get(2) == 3);
    }

    TEST_CASE("Insert multiple elements at tail")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.insertAtTail(3);
        CHECK(list.size() == 3);
        CHECK(list.get(0) == 1);
        CHECK(list.get(1) == 2);
        CHECK(list.get(2) == 3);
    }

    TEST_CASE("Insert and delete in a large list")
{
    DoublyLinkedList<int> list;

    // Insert 100 elements at the tail
    for (int i = 0; i < 100; ++i) {
        list.insertAtTail(i);
    }

    // Verify the size and contents
    CHECK(list.size() == 100);
    for (int i = 0; i < 100; ++i) {
        CHECK(list.get(i) == i);
    }

    // Delete every 10th element
    for (int i = 9; i < list.size(); i -= 1) {
        list.deleteAt(i);
    }

    // Verify the size after deletion
    CHECK(list.size() == 90);

    // Verify the remaining elements
    for (int i = 0, j = 0; i < 100; ++i) {
        if (i % 10 != 9) {
            CHECK(list.get(j++) == i);
        }
    }
}

    TEST_CASE("Get first element")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        CHECK(list.get(0) == 1);
    }

    TEST_CASE("Get last element")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        CHECK(list.get(list.size() - 1) == 2);
    }

    TEST_CASE("Insert and delete repeatedly")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.deleteAt(0);
        list.insertAtTail(3);
        CHECK(list.size() == 2);
        CHECK(list.get(0) == 2);
        CHECK(list.get(1) == 3);
    }

    TEST_CASE("Insert at head and reverse")
    {
        DoublyLinkedList<int> list;
        list.insertAtHead(3);
        list.insertAtHead(2);
        list.insertAtHead(1);
        list.reverse();
        CHECK(list.get(0) == 3);
        CHECK(list.get(1) == 2);
        CHECK(list.get(2) == 1);
    }

    TEST_CASE("Insert at tail and reverse")
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

    TEST_CASE("Insert duplicate elements")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(1);
        list.insertAtTail(2);
        CHECK(list.size() == 3);
        CHECK(list.get(0) == 1);
        CHECK(list.get(1) == 1);
        CHECK(list.get(2) == 2);
    }

    TEST_CASE("Insert and delete all elements")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.deleteAt(0);
        list.deleteAt(0);
        CHECK(list.size() == 0);
        CHECK_THROWS_AS(list.get(0), std::out_of_range);
    }

    TEST_CASE("To string with custom objects")
    {
        struct Custom
        {
            int value;
            Custom(int v) : value(v) {}
            bool operator==(const Custom &other) const { return value == other.value; }
        };

        auto customToString = [](Custom &c) { return std::to_string(c.value); };

        DoublyLinkedList<Custom> list;
        list.insertAtTail(Custom(1));
        list.insertAtTail(Custom(2));
        std::string str = list.toString(customToString);
        CHECK(str == "[1, 2]");
    }
}