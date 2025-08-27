#include "doctest/doctest.h"
#include "src/DoublyLinkedList.h"

TEST_SUITE("DoublyLinkedList Iterator") {
  TEST_CASE("Iteration over DoublyLinkedList") {
    DoublyLinkedList<int> list;
    list.insertAtTail(10);
    list.insertAtTail(20);
    list.insertAtTail(30);

    int expected[] = {10, 20, 30};

    SUBCASE("Forward iteration using Iterator") {
      int idx = 0;
      for (auto it = list.begin(); it != list.end(); ++it) {
        CHECK(*it == expected[idx++]);
      }
      CHECK(idx == 3);
    }

    SUBCASE("Range-based for iteration") {
      int idx = 0;
      for (int x : list) {
        CHECK(x == expected[idx++]);
      }
      CHECK(idx == 3);
    }
  }

  // TODO add test case
  TEST_CASE("Iterator on empty and single-element lists") {
    DoublyLinkedList<int> list;

    SUBCASE("Iteration over an empty list") {
      int count = 0;
      for (int x : list) {
        count++;  // Vòng lặp này sẽ không bao giờ chạy
      }
      CHECK(count == 0);
      // Trong danh sách rỗng, begin() và end() phải trỏ cùng một nơi
      CHECK(list.begin() == list.end());  // <-- Bạn sẽ cần thêm operator==
    }

    SUBCASE("Iteration over a single-element list") {
      list.insertAtHead(42);
      int count = 0;
      for (int x : list) {
        count++;
        CHECK(x == 42);
      }
      CHECK(count == 1);
    }
  }

  TEST_CASE("Modifying list through Iterator") {
    DoublyLinkedList<int> list;
    list.insertAtTail(1);
    list.insertAtTail(2);
    list.insertAtTail(3);

    // Dùng iterator để tăng mỗi phần tử lên 10
    for (auto it = list.begin(); it != list.end(); ++it) {
      *it += 10;
    }

    CHECK(list.get(0) == 11);
    CHECK(list.get(1) == 12);
    CHECK(list.get(2) == 13);
  }
}