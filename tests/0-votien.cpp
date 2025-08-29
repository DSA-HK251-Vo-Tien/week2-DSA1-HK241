#include "doctest/doctest.h"
#include "src/DoublyLinkedList.h"

TEST_SUITE("demo Git")
{
    TEST_CASE("demo")
    {
        DoublyLinkedList<int> list;

        list.insertAtHead(2);
        list.insertAtHead(1);
        CHECK(list.size() == 2);
        CHECK(list.get(0) == 1);
        CHECK(list.get(1) == 2);
    }

}
