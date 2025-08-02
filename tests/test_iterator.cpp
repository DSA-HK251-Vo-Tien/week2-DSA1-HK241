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
    TEST_CASE("Iterator - Duyệt ngược danh sách bằng operator--") {
    DoublyLinkedList<int> list;
    list.insertAtTail(1); list.insertAtTail(2); list.insertAtTail(3);

    auto it = list.end();
    --it; CHECK(*it == 3);
    --it; CHECK(*it == 2);
    --it; CHECK(*it == 1);
    };
    TEST_CASE("Iterator - So sánh == và !=") {
    DoublyLinkedList<int> list;
    list.insertAtHead(100); list.insertAtHead(200);

    auto it1 = list.begin();
    auto it2 = list.begin();
    auto it3 = list.end();

    CHECK(it1 == it2);
    CHECK(it1 != it3);
    };

    TEST_CASE("Iterator - Dereference phần tử đầu tiên") {
    DoublyLinkedList<std::string> list;
    list.insertAtHead("Hello");
    CHECK(*list.begin() == "Hello");
    }

    TEST_CASE("Iterator - Duyệt danh sách rỗng") {
    DoublyLinkedList<char> list;

    auto it = list.begin();
    auto end = list.end();

    CHECK(it == end);  // vì không có phần tử nào
    }
    TEST_CASE("Iterator - Duyệt 1 phần tử") {
    DoublyLinkedList<int> list;
    list.insertAtTail(42);

    auto it = list.begin();
    CHECK(*it == 42);
    ++it;
    CHECK(it == list.end());
    }

    TEST_CASE("Iterator - Nhiều iterator không ảnh hưởng nhau") {
    DoublyLinkedList<int> list;
    list.insertAtTail(1); list.insertAtTail(2); list.insertAtTail(3);

    auto it1 = list.begin();
    auto it2 = list.begin();
    ++it2; // it2 đến 2
    CHECK(*it1 == 1);
    CHECK(*it2 == 2);
    }
   

TEST_CASE("Iterator - Trỏ tới phần tử cuối bằng --end()") {
    DoublyLinkedList<int> list;
    list.insertAtTail(7); list.insertAtTail(8); list.insertAtTail(9);

    auto it = list.end();
    --it;
    CHECK(*it == 9);
}
}