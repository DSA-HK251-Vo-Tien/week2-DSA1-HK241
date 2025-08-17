#include "doctest/doctest.h"
#include "src/DoublyLinkedList.h"

static std::string intToString(int &x) { return std::to_string(x); }

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
            list.reverse(); 
            CHECK(list.get(0) == 3);
            CHECK(list.get(2) == 1);
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
}

TEST_SUITE("DoublyLinkedList Edge Cases & Utilities")
{
    TEST_CASE("insertAt - boundaries and invalid indices")
    {
        DoublyLinkedList<int> list;
        // Danh sách rỗng: insertAt(0, x) theo implement hiện tại là invalid (index >= length)
        CHECK_THROWS_AS(list.insertAt(0, 1), std::out_of_range);

        // Chuẩn bị [10]
        list.insertAtHead(10);
        CHECK(list.size() == 1);
        // insertAt(-1, x) invalid
        CHECK_THROWS_AS(list.insertAt(-1, 99), std::out_of_range);
        // insertAt(1, x) invalid vì length == 1, index >= length
        CHECK_THROWS_AS(list.insertAt(1, 99), std::out_of_range);

        // Thêm vào đầu qua insertAt(0, x): hợp lệ vì 0 < length (length=1)
        list.insertAt(0, 5); // [5, 10]
        CHECK(list.size() == 2);
        CHECK(list.get(0) == 5);
        CHECK(list.get(1) == 10);

        // Thêm vào giữa: index=1
        list.insertAt(1, 7); // [5, 7, 10]
        CHECK(list.size() == 3);
        CHECK(list.get(0) == 5);
        CHECK(list.get(1) == 7);
        CHECK(list.get(2) == 10);
    }

    TEST_CASE("deleteAt - boundaries and invalid indices")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.insertAtTail(3); // [1,2,3]

        // invalid
        CHECK_THROWS_AS(list.deleteAt(-1), std::out_of_range);
        CHECK_THROWS_AS(list.deleteAt(3), std::out_of_range);

        // xóa đầu
        list.deleteAt(0); // [2,3]
        CHECK(list.size() == 2);
        CHECK(list.get(0) == 2);
        CHECK(list.get(1) == 3);

        // xóa cuối (index = size-1)
        list.deleteAt(1); // [2]
        CHECK(list.size() == 1);
        CHECK(list.get(0) == 2);

        // xóa phần tử duy nhất
        list.deleteAt(0); // []
        CHECK(list.size() == 0);
        CHECK_THROWS_AS(list.get(0), std::out_of_range);
    }

    TEST_CASE("get - invalid indices")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(42); // [42]
        CHECK_THROWS_AS(list.get(-1), std::out_of_range);
        CHECK_NOTHROW(list.get(0));
        CHECK_THROWS_AS(list.get(1), std::out_of_range);
    }

    TEST_CASE("reverse - empty and single element")
    {
        SUBCASE("empty list")
        {
            DoublyLinkedList<int> list;
            CHECK_NOTHROW(list.reverse());
            CHECK(list.size() == 0);
        }

        SUBCASE("single element")
        {
            DoublyLinkedList<int> list;
            list.insertAtTail(7); // [7]
            list.reverse();       // vẫn [7]
            CHECK(list.size() == 1);
            CHECK(list.get(0) == 7);
        }
    }

    TEST_CASE("reverse - multi elements")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.insertAtTail(3);
        list.insertAtTail(4); // [1,2,3,4]

        list.reverse();       // [4,3,2,1]
        CHECK(list.size() == 4);
        CHECK(list.get(0) == 4);
        CHECK(list.get(1) == 3);
        CHECK(list.get(2) == 2);
        CHECK(list.get(3) == 1);
    }

    TEST_CASE("indexOf & contains")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(10);
        list.insertAtTail(20);
        list.insertAtTail(10); // [10,20,10]

        CHECK(list.contains(20) == true);
        CHECK(list.contains(99) == false);

        // indexOf trả về vị trí đầu tiên
        CHECK(list.indexOf(10) == 0);
        CHECK(list.indexOf(20) == 1);
        CHECK(list.indexOf(99) == -1);
    }

    TEST_CASE("toString - with and without converter")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(9);
        list.insertAtTail(8); // [9,8]

        CHECK(list.toString() == "function error");

        // Có converter
        std::string s = list.toString(intToString);
        CHECK(s == "[9, 8]");
    }

    TEST_CASE("Iterator behavior with sentinel end()")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.insertAtTail(3); // [1,2,3]

        // Forward iteration phải duyệt đủ 3 phần tử
        int cnt = 0, sum = 0;
        for (auto it = list.begin(); it != list.end(); ++it) {
            sum += *it;
            ++cnt;
        }
        CHECK(cnt == 3);
        CHECK(sum == 1 + 2 + 3);

        // end() là sentinel -> KHÔNG deref. Nhưng --end() là phần tử cuối.
        auto it = list.end();   // sentinel
        --it;                   // 3
        CHECK(*it == 3);
        --it;                   // 2
        CHECK(*it == 2);
        --it;                   // 1
        CHECK(*it == 1);
        CHECK(it == list.begin());
    }

}

TEST_SUITE("DoublyLinkedList<Point> - more cases")
{
    static std::string pointToString2(Point & p)
    {
        return "(" + std::to_string(int(p.getX())) + "," + std::to_string(int(p.getY())) + ")";
    }

    TEST_CASE("contains/indexOf with Point")
    {
        DoublyLinkedList<Point> list;
        Point a(1,2), b(3,4), c(1,2);
        list.insertAtTail(a);
        list.insertAtTail(b); 

        CHECK(list.contains(a) == true);
        CHECK(list.contains(Point(9,9)) == false);
        CHECK(list.indexOf(a) == 0);
        CHECK(list.indexOf(c) == 0); 
        CHECK(list.indexOf(b) == 1);
    }

    TEST_CASE("toString<Point> - more")
    {
        DoublyLinkedList<Point> list;
        list.insertAtTail(Point(0,0));
        list.insertAtTail(Point(5,6));
        std::string s = list.toString(pointToString2);
        CHECK(s == "[(0,0), (5,6)]");
    }
}