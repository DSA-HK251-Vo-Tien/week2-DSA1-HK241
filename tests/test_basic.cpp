#include "doctest/doctest.h"
#include "src/DoublyLinkedList.h"

TEST_SUITE("DoublyLinkedList Basic Operations") {
  TEST_CASE("Insert at head and tail") {
    DoublyLinkedList<int> list;

    SUBCASE("Insert at head") {
      list.insertAtHead(2);
      list.insertAtHead(1);
      CHECK(list.size() == 2);
      CHECK(list.get(0) == 1);
      CHECK(list.get(1) == 2);
    }

    SUBCASE("Insert at tail") {
      list.insertAtTail(1);
      list.insertAtTail(2);
      CHECK(list.size() == 2);
      CHECK(list.get(0) == 1);
      CHECK(list.get(1) == 2);
    }
  }

  TEST_CASE("Delete and reverse") {
    DoublyLinkedList<int> list;
    list.insertAtTail(1);
    list.insertAtTail(2);
    list.insertAtTail(3);  // [1, 2, 3]

    SUBCASE("Delete middle element") {
      list.deleteAt(1);  // remove 2
      CHECK(list.size() == 2);
      CHECK(list.get(0) == 1);
      CHECK(list.get(1) == 3);
    }

    SUBCASE("Reverse list") {
      list.reverse();  // should become [3, 2, 1]
      CHECK(list.get(0) == 3);
      CHECK(list.get(2) == 1);
    }
  }
}

TEST_SUITE("DoublyLinkedList<Point> Operations") {
  std::string pointToString(Point & p) {
    return "(" + std::to_string(int(p.getX())) + "," +
           std::to_string(int(p.getY())) + ")";
  }

  TEST_CASE("Insert and get Point") {
    DoublyLinkedList<Point> list;

    SUBCASE("Insert at head") {
      list.insertAtHead(Point(1, 2));
      list.insertAtHead(Point(3, 4));
      CHECK(list.size() == 2);
      CHECK(list.get(0) == Point(3, 4));
      CHECK(list.get(1) == Point(1, 2));
    }
  }

  TEST_CASE("To string of list<Point>") {
    DoublyLinkedList<Point> list;
    list.insertAtTail(Point(9, 0));
    list.insertAtTail(Point(8, 1));
    std::string str = list.toString(pointToString);
    CHECK(str == "[(9,0), (8,1)]");
  }
}

// TODO add test case
TEST_SUITE("DoublyLinkedList Advanced Operations & Edge Cases") {
  TEST_CASE("Operations on an empty list") {
    DoublyLinkedList<int> list;
    CHECK(list.size() == 0);
    CHECK(list.toString() == "[]");

    // Kiểm tra ném ngoại lệ khi thao tác trên danh sách rỗng
    CHECK_THROWS_AS(list.get(0), std::out_of_range);
    CHECK_THROWS_AS(list.deleteAt(0), std::out_of_range);

    // indexOf và contains trên danh sách rỗng
    CHECK(list.indexOf(10) == -1);
    CHECK(list.contains(10) == false);
  }

  TEST_CASE("Insertion at a specific index (insertAt)") {
    DoublyLinkedList<int> list;
    list.insertAtTail(10);  // [10]
    list.insertAtTail(30);  // [10, 30]

    SUBCASE("Insert in the middle") {
      list.insertAt(1, 20);  // [10, 20, 30]
      CHECK(list.size() == 3);
      CHECK(list.get(1) == 20);
      CHECK(list.toString() == "[10, 20, 30]");
    }

    SUBCASE("Insert at beginning (index 0)") {
      list.insertAt(0, 5);  // [5, 10, 30]
      CHECK(list.size() == 3);
      CHECK(list.get(0) == 5);
    }

    SUBCASE("Insert at end (index size())") {
      list.insertAt(2, 40);  // [10, 30, 40]
      CHECK(list.size() == 3);
      CHECK(list.get(2) == 40);
    }

    SUBCASE("Exception for negative index") {
      CHECK_THROWS_AS(list.insertAt(-1, 99), std::out_of_range);
    }

    SUBCASE("Exception for out of bounds index") {
      // index > size() là không hợp lệ
      CHECK_THROWS_AS(list.insertAt(3, 99), std::out_of_range);
    }
  }

  TEST_CASE("Deletion edge cases (deleteAt)") {
    DoublyLinkedList<int> list;
    list.insertAtTail(10);
    list.insertAtTail(20);
    list.insertAtTail(30);  // [10, 20, 30]

    SUBCASE("Delete the first element") {
      list.deleteAt(0);  // [20, 30]
      CHECK(list.size() == 2);
      CHECK(list.get(0) == 20);
    }

    SUBCASE("Delete the last element") {
      list.deleteAt(2);  // [10, 20]
      CHECK(list.size() == 2);
      CHECK(list.get(1) == 20);
      CHECK_THROWS_AS(list.get(2), std::out_of_range);  // Phần tử cũ không còn
    }

    SUBCASE("Delete from a single-element list") {
      DoublyLinkedList<int> single_list;
      single_list.insertAtHead(100);
      single_list.deleteAt(0);
      CHECK(single_list.size() == 0);
      CHECK(single_list.toString() == "[]");
    }
  }

  TEST_CASE("Search operations (indexOf and contains)") {
    DoublyLinkedList<int> list;
    list.insertAtTail(10);
    list.insertAtTail(20);
    list.insertAtTail(30);
    list.insertAtTail(20);  // [10, 20, 30, 20]

    SUBCASE("Find first and middle element") {
      CHECK(list.indexOf(10) == 0);
      CHECK(list.contains(30) == true);
    }

    SUBCASE("Find an item that does not exist") {
      CHECK(list.indexOf(99) == -1);
      CHECK(list.contains(99) == false);
    }

    SUBCASE("Find a duplicate item") {
      // indexOf phải trả về chỉ số của phần tử đầu tiên nó tìm thấy
      CHECK(list.indexOf(20) == 1);
    }
  }

  TEST_CASE("Reverse edge cases") {
    DoublyLinkedList<int> list;

    SUBCASE("Reverse an empty list") {
      list.reverse();
      CHECK(list.size() == 0);
      CHECK(list.toString() == "[]");
    }

    SUBCASE("Reverse a single-element list") {
      list.insertAtHead(42);
      list.reverse();
      CHECK(list.size() == 1);
      CHECK(list.get(0) == 42);
    }
  }

  TEST_CASE("Complex chained operations") {
    DoublyLinkedList<int> list;
    list.insertAtHead(10);  // [10]
    list.insertAtTail(20);  // [10, 20]
    list.insertAtHead(0);   // [0, 10, 20]
    list.insertAt(3, 30);   // [0, 10, 20, 30]
    list.deleteAt(1);       // [0, 20, 30]
    CHECK(list.toString() == "[0, 20, 30]");

    list.reverse();  // [30, 20, 0]
    CHECK(list.get(0) == 30);
    CHECK(list.get(1) == 20);
    CHECK(list.get(2) == 0);
    CHECK(list.size() == 3);
  }
}