#include "doctest/doctest.h"
#include "src/DoublyLinkedList.h"

TEST_SUITE("DoublyLinkedList Iterator") {

    TEST_CASE("Empty list begin equals end and no iteration") {
        DoublyLinkedList<int> list;
        CHECK(list.begin() == list.end());
        int count = 0;
        for (auto it = list.begin(); it != list.end(); ++it) ++count;
        CHECK(count == 0);
    }

    TEST_CASE("Single element iteration yields once") {
        DoublyLinkedList<int> list;
        list.insertAtHead(5);
        int count = 0;
        for (auto it = list.begin(); it != list.end(); ++it) { CHECK(*it == 5); ++count; }
        CHECK(count == 1);
    }

    TEST_CASE("Pre-increment traverses forward correctly") {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.insertAtTail(3);
        auto it = list.begin();
        CHECK(*it == 1);
        ++it; CHECK(*it == 2);
        ++it; CHECK(*it == 3);
        ++it; CHECK(it == list.end());
    }

    TEST_CASE("Pre-decrement from end goes to last element") {
        DoublyLinkedList<int> list;
        list.insertAtTail(10);
        list.insertAtTail(20);
        auto it = list.end();
        --it; CHECK(*it == 20);
        --it; CHECK(*it == 10);
        CHECK(it == list.begin());
    }

    TEST_CASE("Modify elements via iterator dereference") {
        DoublyLinkedList<int> list;
        for (int i=0;i<3;++i) list.insertAtTail(i);
        for (auto it = list.begin(); it != list.end(); ++it) { *it += 10; }
        int expected[] = {10,11,12};
        int idx=0;
        for (auto it = list.begin(); it != list.end(); ++it) { CHECK(*it == expected[idx++]); }
    }

    TEST_CASE("Range-based for iteration") {
        DoublyLinkedList<int> list;
        for (int i=1;i<=3;i++) list.insertAtTail(i);
        int expected[] = {1,2,3};
        int idx=0;
        for (int x : list) CHECK(x == expected[idx++]);
        CHECK(idx==3);
    }

    TEST_CASE("Iterator equality and inequality") {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        auto a = list.begin();
        auto b = list.begin();
        CHECK(a == b);
        ++b;
        CHECK(a != b);
    }

    TEST_CASE("Iteration after insertion in middle") {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(3);
        list.insertAt(1,2); // [1,2,3]
        int expected[] = {1,2,3};
        int idx=0;
        for (auto it = list.begin(); it != list.end(); ++it) CHECK(*it == expected[idx++]);
    }

    TEST_CASE("Iteration after deletions") {
        DoublyLinkedList<int> list;
        for (int i=1;i<=5;++i) list.insertAtTail(i); // [1,2,3,4,5]
        list.deleteAt(0); // remove 1
        list.deleteAt(2); // remove 4 -> [2,3,5]
        int expected[] = {2,3,5};
        int idx=0;
        for (auto it = list.begin(); it != list.end(); ++it) CHECK(*it == expected[idx++]);
    }

    TEST_CASE("Multiple independent iterators") {
        DoublyLinkedList<int> list;
        for (int i=0;i<3;++i) list.insertAtTail(i);
        auto it1 = list.begin();
        auto it2 = list.begin();
        ++it1; CHECK(*it1 == 1);
        CHECK(*it2 == 0);
    }

    TEST_CASE("Iterator with Point objects") {
        DoublyLinkedList<Point> list;
        list.insertAtTail(Point(1,1));
        list.insertAtTail(Point(2,2));
        int sum=0;
        for (auto &p : list) sum += int(p.getX()+p.getY());
        CHECK(sum == 6);
    }

    TEST_CASE("Iterator dereference yields lvalue reference") {
        DoublyLinkedList<int> list;
        list.insertAtTail(50);
        auto it=list.begin();
        (*it)++;
        CHECK(*it==51);
    }

    TEST_CASE("Iterator over large list counts correctly") {
        DoublyLinkedList<int> list;
        for (int i=0;i<100;i++) list.insertAtTail(i);
        int count=0;
        for (auto it=list.begin(); it!=list.end(); ++it) ++count;
        CHECK(count==100);
    }

}
