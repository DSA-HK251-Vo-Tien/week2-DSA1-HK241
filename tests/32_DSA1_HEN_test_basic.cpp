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

    TEST_CASE("Insert at middle") {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(3); // [1, 3]

        SUBCASE("Insert at index 1")
        {
            list.insertAt(1, 2); // should become [1, 2, 3]
            CHECK(list.size() == 3);
            CHECK(list.get(0) == 1);
            CHECK(list.get(1) == 2);
            CHECK(list.get(2) == 3);
        }

        SUBCASE("Insert at index 0")
        {
            list.insertAt(0, 0); // should become [0, 1, 3]
            CHECK(list.size() == 3);
            CHECK(list.get(0) == 0);
            CHECK(list.get(1) == 1);
            CHECK(list.get(2) == 3);
        }

        SUBCASE("Insert at last index")
        {
            list.insertAt(2, 4); // should become [1, 3, 4]
            CHECK(list.size() == 3);
            CHECK(list.get(0) == 1);
            CHECK(list.get(1) == 3);
            CHECK(list.get(2) == 4);
        }
    }

    TEST_CASE("Insert at begining") {
        DoublyLinkedList<int> list;
        list.insertAtTail(2);
        list.insertAtTail(3);
        list.insertAt(0, 1); // insert at beginning
        CHECK(list.size() == 3);
        CHECK(list.get(0) == 1);
        CHECK(list.get(1) == 2);
        CHECK(list.get(2) == 3);
    }

    TEST_CASE("Insert at end") {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.insertAt(2, 3); // insert at end
        CHECK(list.size() == 3);
        CHECK(list.get(0) == 1);
        CHECK(list.get(1) == 2);
        CHECK(list.get(2) == 3);
    }

    TEST_CASE("Combined insert") {
        DoublyLinkedList<int> list;
        list.insertAtHead(1); // [1]
        list.insertAtTail(3); // [1, 3]
        list.insertAt(1, 2); // [1, 2, 3]
        list.insertAt(0, 0); // [0, 1, 2, 3]
        list.insertAt(4, 4); // [0, 1, 2, 3, 4]

        CHECK(list.size() == 5);
        CHECK(list.get(0) == 0);
        CHECK(list.get(1) == 1);
        CHECK(list.get(2) == 2);
        CHECK(list.get(3) == 3);
        CHECK(list.get(4) == 4);
    }

    TEST_CASE("Insert at negative index") {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        try {
            list.insertAt(-1, 0); // should throw exception
            CHECK(false); // should not reach here
        } catch (const std::out_of_range &e) {
            CHECK(std::string(e.what()) == "Index is invalid!");
        }
    }

    TEST_CASE("Inserat at too large index") {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        try {
            list.insertAt(3, 0); // should throw exception
            CHECK(false); // should not reach here
        } catch (const std::out_of_range &e) {
            CHECK(std::string(e.what()) == "Index is invalid!");
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

    TEST_CASE("Delete at multiple deletes") {
        DoublyLinkedList<int> list;
        for (int i = 0; i < 5; ++i)
            list.insertAtTail(i + 1); // 1 2 3 4 5
        list.deleteAt(0);             // 2 3 4 5
        list.deleteAt(1);             // 2 4 5
        list.deleteAt(2);            // 2 4
        CHECK(list.size() == 2);
        CHECK(list.get(0) == 2);
        CHECK(list.get(1) == 4);           
    }

    TEST_CASE("Delete negative index") {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        try {
            list.deleteAt(-1); // should throw exception
            CHECK(false); // should not reach here
        } catch (const std::out_of_range &e) {
            CHECK(std::string(e.what()) == "Index is invalid!");
        }
    }

    TEST_CASE("Delete full sequence") {
        DoublyLinkedList<int> list;
        for (int i = 0; i < 5; ++i)
            list.insertAtTail(i + 1); // 1 2 3 4 5

        for (int i = 0; i < 5; ++i) {
            list.deleteAt(0); // delete head repeatedly
        }
        CHECK(list.size() == 0);
    }

    TEST_CASE("Get value") {
        SUBCASE("Get at valid index")
        {
            DoublyLinkedList<int> list;
            list.insertAtTail(1);
            list.insertAtTail(2);
            list.insertAtTail(3);
            CHECK(list.get(0) == 1);
            CHECK(list.get(1) == 2);
            CHECK(list.get(2) == 3);
        }

        SUBCASE("Get at first and last index")
        {
            DoublyLinkedList<int> list;
            list.insertAtTail(1);
            list.insertAtTail(2);
            list.insertAtTail(3);
            CHECK(list.get(0) == 1); // first element
            CHECK(list.get(2) == 3); // last element
        }

        SUBCASE("Get at invalid index")
        {
            DoublyLinkedList<int> list;
            list.insertAtTail(1);
            list.insertAtTail(2);
            try {
                list.get(2); // should throw exception
                CHECK(false); // should not reach here
            } catch (const std::out_of_range &e) {
                CHECK(std::string(e.what()) == "Index is invalid!");
            }
        }
    }

    TEST_CASE("Index of and contains")
    {
        SUBCASE("Index of existing item")
        {
            DoublyLinkedList<int> list;
            list.insertAtTail(1);
            list.insertAtTail(2);
            list.insertAtTail(3);
            CHECK(list.indexOf(2) == 1);
        }

        SUBCASE("Index of non-existing item")
        {
            DoublyLinkedList<int> list;
            list.insertAtTail(1);
            list.insertAtTail(2);
            CHECK(list.indexOf(3) == -1); // not found
        }

        SUBCASE("Contains existing item")
        {
            DoublyLinkedList<int> list;
            list.insertAtTail(1);
            list.insertAtTail(2);
            CHECK(list.contains(2) == true);
        }

        SUBCASE("Contains non-existing item")
        {
            DoublyLinkedList<int> list;
            list.insertAtTail(1);
            list.insertAtTail(2);
            CHECK(list.contains(3) == false); // not found
        }
    }

    TEST_CASE("toString of list") {
        SUBCASE("toString with converter") {
            DoublyLinkedList<int> list;
            list.insertAtTail(1);
            list.insertAtTail(2);
            list.insertAtTail(3);

            std::string str = list.toString([](int &item) {
                return std::to_string(item);
            });
            CHECK(str == "[1, 2, 3]");
        }
        SUBCASE("toString with empty list") {
            DoublyLinkedList<int> list;
            std::string str = list.toString([](int &item) {
                return std::to_string(item);
            });
            CHECK(str == "[]"); // should return empty string
        }
    }

    TEST_CASE("Reverse list") {
        SUBCASE("Reverse single element") {
            DoublyLinkedList<int> list;
            list.insertAtTail(1);
            list.reverse();
            CHECK(list.size() == 1);
            CHECK(list.get(0) == 1); // should remain the same
        }
        SUBCASE("Reverse multiple elements") {
            DoublyLinkedList<int> list;
            list.insertAtTail(1);
            list.insertAtTail(2);
            list.insertAtTail(3);
            list.reverse(); // should become [3, 2, 1]
            CHECK(list.size() == 3);
            CHECK(list.get(0) == 3);
            CHECK(list.get(1) == 2);
            CHECK(list.get(2) == 1);
        }
        SUBCASE("Reverse empty list") {
            DoublyLinkedList<int> list;
            list.reverse(); // should remain empty
            CHECK(list.size() == 0);
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
    TEST_CASE("To string of empty list<Point>")
    {
        DoublyLinkedList<Point> list;
        std::string str = list.toString(pointToString);
        CHECK(str == "[]"); // should return empty string
    }
    TEST_CASE("Insert at middle Point")
    {
        DoublyLinkedList<Point> list;
        list.insertAtTail(Point(1, 2));
        list.insertAtTail(Point(3, 4)); // [(1,2), (3,4)]

        SUBCASE("Insert at index 1")
        {
            list.insertAt(1, Point(2, 3)); // should become [(1,2), (2,3), (3,4)]
            CHECK(list.size() == 3);
            CHECK(list.get(0) == Point(1, 2));
            CHECK(list.get(1) == Point(2, 3));
            CHECK(list.get(2) == Point(3, 4));
        }

        SUBCASE("Insert at index 0")
        {
            list.insertAt(0, Point(0, 1)); // should become [(0,1), (1,2), (3,4)]
            CHECK(list.size() == 3);
            CHECK(list.get(0) == Point(0, 1));
            CHECK(list.get(1) == Point(1, 2));
            CHECK(list.get(2) == Point(3, 4));
        }

        SUBCASE("Insert at last index")
        {
            list.insertAt(2, Point(4, 5)); // should become [(1,2), (3,4), (4,5)]
            CHECK(list.size() == 3);
            CHECK(list.get(0) == Point(1, 2));
            CHECK(list.get(1) == Point(3, 4));
            CHECK(list.get(2) == Point(4, 5));
        }
    }
    TEST_CASE("Delete Point at middle")
    {
        DoublyLinkedList<Point> list;
        list.insertAtTail(Point(1, 2));
        list.insertAtTail(Point(3, 4));
        list.insertAtTail(Point(5, 6)); // [(1,2), (3,4), (5,6)]

        SUBCASE("Delete middle element")
        {
            list.deleteAt(1); // remove (3,4)
            CHECK(list.size() == 2);
            CHECK(list.get(0) == Point(1, 2));
            CHECK(list.get(1) == Point(5, 6));
        }
    }
}

// TODO add test case