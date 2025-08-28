#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include "src/DoublyLinkedList.h"

TEST_CASE("Basic functionality of DoublyLinkedList<int>")
{
    DoublyLinkedList<int> list;
    list.insertAtTail(42);
    CHECK(list.size() == 1);
    CHECK(list.get(0) == 42);
}