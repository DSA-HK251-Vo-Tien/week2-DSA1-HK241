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

    // TODO add test case
    TEST_CASE("Char"){
        DoublyLinkedList<char> list;
        list.insertAtTail('a');
        list.insertAtTail('b');
        list.insertAtTail('c');
        int idx = 0;
        stringstream ss;
        for(auto x : list){
            idx++;
            ss << x;
        }
        CHECK(idx == 3);
        CHECK(ss.str() == "abc");
    }

    TEST_CASE("Double"){
        DoublyLinkedList<double> list;
        list.insertAtTail(1.1);
        list.insertAtTail(2.2);
        list.insertAtTail(3.3);
        int idx = 0;
        stringstream ss;
        for(auto x : list){
            idx++;
            ss << x;
        }
        CHECK(idx == 3);
        CHECK(list.size() == 3);
        CHECK(ss.str() == "1.12.23.3");
        list.reverse();
        CHECK(list.size() == 3);
        stringstream ss2;
        for(auto x : list){
            idx++;
            ss2 << x;
        }
        CHECK(ss2.str() == "3.32.21.1");
    }
    TEST_CASE("Backward iteration using Iterator"){
        DoublyLinkedList<int> list;
        list.insertAtTail(10);
        list.insertAtTail(20);
        list.insertAtTail(30);

        int expected[] = {10, 20, 30};
        int idx = 2;
        auto it = list.end();
        --it;
        for (; it != list.begin(); --it)
        {
            CHECK(*it == expected[idx--]);
        }
        CHECK(idx == 0);
        CHECK(list.size() == 3);
    }

    TEST_CASE("Unequality"){
        DoublyLinkedList<int> list;
        list.insertAtTail(10);
        list.insertAtTail(20);
        list.insertAtTail(30);

        typename DoublyLinkedList<int>::Iterator i1 = list.begin();
        typename DoublyLinkedList<int>::Iterator i2 = list.end();
        // Changeale: auto i1 = list.begin();
        CHECK(i1 != i2);
    }

    TEST_CASE("Equality"){
        DoublyLinkedList<int> list;
        list.insertAtTail(10);
        list.insertAtTail(20);
        typename DoublyLinkedList<int>::Iterator i1 = list.begin();
        typename DoublyLinkedList<int>::Iterator i2 = list.end();
        list.deleteAt(1);
        i2 = list.end();
        --i2;
        CHECK(i1 == i2);
    }
}