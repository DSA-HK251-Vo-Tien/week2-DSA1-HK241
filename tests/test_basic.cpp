#include "doctest/doctest.h"
#include "src/DoublyLinkedList.h"

TEST_SUITE("DoublyLinkedList Core Tests") {

    TEST_CASE("New list is empty") {
        DoublyLinkedList<int> list;
        CHECK(list.size() == 0);
        CHECK(list.toString() == "[]");
    }

    TEST_CASE("Insert at head") {
        DoublyLinkedList<int> list;
        list.insertAtHead(2);
        list.insertAtHead(1); // [1,2]
        CHECK(list.size() == 2);
        CHECK(list.get(0) == 1);
        CHECK(list.get(1) == 2);
    }

    TEST_CASE("Insert at tail") {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2); // [1,2]
        CHECK(list.size() == 2);
        CHECK(list.get(0) == 1);
        CHECK(list.get(1) == 2);
    }

    TEST_CASE("Insert at index") {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(3);
        list.insertAt(1, 2); // [1,2,3]
        CHECK(list.get(1) == 2);
    }

    TEST_CASE("InsertAt invalid index throws") {
        DoublyLinkedList<int> list;
        CHECK_THROWS_AS(list.insertAt(-1, 5), std::out_of_range);
        CHECK_THROWS_AS(list.insertAt(1, 5), std::out_of_range);
    }

    TEST_CASE("Delete element at index") {
        DoublyLinkedList<int> list;
        for(int i=0;i<3;i++) list.insertAtTail(i); // [0,1,2]
        list.deleteAt(1); // [0,2]
        CHECK(list.size() == 2);
        CHECK(list.get(1) == 2);
    }

    TEST_CASE("Delete invalid index throws") {
        DoublyLinkedList<int> list;
        CHECK_THROWS_AS(list.deleteAt(0), std::out_of_range);
    }

    TEST_CASE("Reverse list") {
        DoublyLinkedList<int> list;
        for(int i=1;i<=3;i++) list.insertAtTail(i); // [1,2,3]
        list.reverse(); // [3,2,1]
        CHECK(list.get(0) == 3);
        CHECK(list.get(2) == 1);
    }

    TEST_CASE("IndexOf and contains") {
        DoublyLinkedList<int> list;
        list.insertAtTail(5);
        list.insertAtTail(7);
        CHECK(list.indexOf(7) == 1);
        CHECK(list.contains(5));
        CHECK_FALSE(list.contains(9));
    }

    TEST_CASE("Mutation through get reference") {
        DoublyLinkedList<int> list;
        list.insertAtTail(10);
        int &ref = list.get(0);
        ref = 99;
        CHECK(list.get(0) == 99);
    }

    TEST_CASE("Iterator traverses correctly") {
        DoublyLinkedList<int> list;
        for(int i=0;i<3;i++) list.insertAtTail(i);
        int expected = 0;
        for(auto it = list.begin(); it != list.end(); ++it) {
            CHECK(*it == expected++);
        }
    }

    TEST_CASE("Point toString with converter") {
        DoublyLinkedList<Point> list;
        list.insertAtTail(Point(3,4));
        auto conv = [](Point &p){ 
            return "(" + std::to_string(int(p.getX())) + "," + std::to_string(int(p.getY())) + ")"; 
        };
        CHECK(list.toString(conv) == "[(3,4)]");
    }

}


// TODO add test case