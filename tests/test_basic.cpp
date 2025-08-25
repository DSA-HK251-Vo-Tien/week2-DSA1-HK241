#include "doctest/doctest.h"
#include "src/DoublyLinkedList.h"


TEST_CASE("Insert at head") {
    DoublyLinkedList<int> list;
    list.insertAtHead(2);
    list.insertAtHead(1);
    CHECK(list.size() == 2);
    CHECK(list.get(0) == 1);
    CHECK(list.get(1) == 2);
}

TEST_CASE("Insert at tail") {
    DoublyLinkedList<int> list;
    list.insertAtTail(1);
    list.insertAtTail(2);
    CHECK(list.size() == 2);
    CHECK(list.get(0) == 1);
    CHECK(list.get(1) == 2);
}

TEST_CASE("Insert at arbitrary position") {
    DoublyLinkedList<int> list;
    list.insertAtTail(1);
    list.insertAtTail(3);
    list.insertAt(1, 2);
    CHECK(list.size() == 3);
    CHECK(list.get(1) == 2);
}

TEST_CASE("Delete at head and tail") {
    DoublyLinkedList<int> list;
    list.insertAtTail(1);
    list.insertAtTail(2);
    list.insertAtTail(3);
    list.deleteAt(0);
    CHECK(list.get(0) == 2);
    list.deleteAt(list.size()-1);
    CHECK(list.get(0) == 2);
    CHECK(list.size() == 1);
}

TEST_CASE("Delete middle element") {
    DoublyLinkedList<int> list;
    list.insertAtTail(1);
    list.insertAtTail(2);
    list.insertAtTail(3);
    list.deleteAt(1);
    CHECK(list.size() == 2);
    CHECK(list.get(0) == 1);
    CHECK(list.get(1) == 3);
}

TEST_CASE("Reverse list") {
    DoublyLinkedList<int> list;
    list.insertAtTail(1);
    list.insertAtTail(2);
    list.insertAtTail(3);
    list.reverse();
    CHECK(list.get(0) == 3);
    CHECK(list.get(2) == 1);
}

TEST_CASE("IndexOf and Contains") {
    DoublyLinkedList<int> list;
    list.insertAtTail(5);
    list.insertAtTail(10);
    list.insertAtTail(15);
    CHECK(list.indexOf(10) == 1);
    CHECK(list.contains(15));
    CHECK(!list.contains(100));
}

TEST_CASE("Empty list operations") {
    DoublyLinkedList<int> list;
    CHECK(list.size() == 0);
    CHECK_THROWS(list.get(0));
    CHECK_THROWS(list.deleteAt(0));
}

TEST_CASE("Insert and delete all") {
    DoublyLinkedList<int> list;
    for (int i = 0; i < 5; ++i) list.insertAtTail(i);
    for (int i = 0; i < 5; ++i) list.deleteAt(0);
    CHECK(list.size() == 0);
}

TEST_CASE("Reverse twice returns original") {
    DoublyLinkedList<int> list;
    for (int i = 1; i <= 4; ++i) list.insertAtTail(i);
    list.reverse();
    list.reverse();
    for (int i = 0; i < 4; ++i) CHECK(list.get(i) == i+1);
}

TEST_CASE("Insert at invalid index throws") {
    DoublyLinkedList<int> list;
    CHECK_THROWS(list.insertAt(1, 10));
    list.insertAtTail(1);
    CHECK_THROWS(list.insertAt(-1, 2));
    CHECK_THROWS(list.insertAt(3, 3));
}

TEST_CASE("Delete at invalid index throws") {
    DoublyLinkedList<int> list;
    CHECK_THROWS(list.deleteAt(0));
    list.insertAtTail(1);
    CHECK_THROWS(list.deleteAt(1));
    CHECK_THROWS(list.deleteAt(-1));
}

TEST_CASE("Get at invalid index throws") {
    DoublyLinkedList<int> list;
    CHECK_THROWS(list.get(0));
    list.insertAtTail(1);
    CHECK_THROWS(list.get(1));
    CHECK_THROWS(list.get(-1));
}

TEST_CASE("ToString with empty list") {
    DoublyLinkedList<int> list;
    auto toStr = [](int &x) { return std::to_string(x); };
    CHECK(list.toString(toStr) == "[]");
}

TEST_CASE("ToString with one element") {
    DoublyLinkedList<int> list;
    auto toStr = [](int &x) { return std::to_string(x); };
    list.insertAtTail(42);
    CHECK(list.toString(toStr) == "[42]");
}

TEST_CASE("Insert many and check order") {
    DoublyLinkedList<int> list;
    for (int i = 0; i < 10; ++i) list.insertAtTail(i);
    for (int i = 0; i < 10; ++i) CHECK(list.get(i) == i);
}

TEST_CASE("Insert at head many times") {
    DoublyLinkedList<int> list;
    for (int i = 0; i < 5; ++i) list.insertAtHead(i);
    for (int i = 0; i < 5; ++i) CHECK(list.get(i) == 4-i);
}

TEST_CASE("Point: insert, delete, contains") {
    DoublyLinkedList<Point> list;
    Point p1(1,2), p2(3,4);
    list.insertAtTail(p1);
    list.insertAtTail(p2);
    CHECK(list.contains(p1));
    list.deleteAt(0);
    CHECK(!list.contains(p1));
    CHECK(list.contains(p2));
}

TEST_CASE("Point: indexOf and get") {
    DoublyLinkedList<Point> list;
    Point p1(1,2), p2(3,4);
    list.insertAtTail(p1);
    list.insertAtTail(p2);
    CHECK(list.indexOf(p2) == 1);
    CHECK(list.get(0) == p1);
    CHECK(list.get(1) == p2);
}