#include "doctest/doctest.h"
#include "src/DoublyLinkedList.h"

static std::string intToString2(int &x) { return std::to_string(x); }
static std::string pointToString3(Point &p) {
    return "(" + std::to_string(int(p.getX())) + "," + std::to_string(int(p.getY())) + ")";
}

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

    TEST_CASE("Empty list iteration")
    {
        DoublyLinkedList<int> list;
        int cnt = 0;
        for (auto it = list.begin(); it != list.end(); ++it) { ++cnt; }
        CHECK(cnt == 0);

        // begin()==end() khi rỗng
        CHECK(list.begin() == list.end());

        // range-based for trên rỗng
        cnt = 0;
        for (int x : list) { (void)x; ++cnt; }
        CHECK(cnt == 0);
    }

    TEST_CASE("Single element iteration and equality")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(42);

        // begin() != end() khi có phần tử
        CHECK(list.begin() != list.end());

        int cnt = 0;
        for (auto it = list.begin(); it != list.end(); ++it) {
            CHECK(*it == 42);
            ++cnt;
        }
        CHECK(cnt == 1);

        // ++ rồi -- quay lại chỗ cũ (end là sentinel)
        auto it = list.begin();
        auto it_orig = it;
        ++it;      // it == end()
        --it;      // quay lại phần tử đầu
        CHECK(it == it_orig);
        CHECK(*it == 42);
    }

    TEST_CASE("Forward & reverse iteration with three elements")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(10);
        list.insertAtTail(20);
        list.insertAtTail(30);

        // Forward
        int expectedFwd[] = {10, 20, 30};
        int i = 0;
        for (auto it = list.begin(); it != list.end(); ++it) {
            CHECK(*it == expectedFwd[i++]);
        }
        CHECK(i == 3);

        // Reverse (end() là sentinel; dùng --end())
        int expectedRev[] = {30, 20, 10};
        i = 0;
        if (list.begin() != list.end()) {
            auto it = list.end(); // sentinel
            while (it != list.begin()) {
                --it;                 // về phần tử hợp lệ
                CHECK(*it == expectedRev[i++]);
            }
        }
        CHECK(i == 3);
    }

    TEST_CASE("Last element via --end() (sentinel semantics)")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.insertAtTail(3);

        auto it = list.end(); // sentinel
        --it;                 // phần tử cuối
        CHECK(*it == 3);
    }

    TEST_CASE("Mutating through iterator")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.insertAtTail(3);

        for (auto it = list.begin(); it != list.end(); ++it) {
            *it += 10; 
        }

        int idx = 0;
        int expected[] = {11, 12, 13};
        for (int x : list) {
            CHECK(x == expected[idx++]);
        }
        CHECK(idx == 3);
    }

    TEST_CASE("Const iteration")
    {
        DoublyLinkedList<int> tmp;
        tmp.insertAtTail(5);
        tmp.insertAtTail(6);

        const DoublyLinkedList<int> &list = tmp; 
        int sum = 0;
        for (int x : list) sum += x;
        CHECK(sum == 11);
    }
}

TEST_SUITE("DoublyLinkedList More Cases")
{
    TEST_CASE("Mixed inserts at head/tail keep order")
    {
        DoublyLinkedList<int> list;
        list.insertAtHead(2);
        list.insertAtTail(3);
        list.insertAtHead(1);
        CHECK(list.size() == 3);
        CHECK(list.get(0) == 1);
        CHECK(list.get(1) == 2);
        CHECK(list.get(2) == 3);
        int expected[] = {1,2,3}, i = 0;
        for (int v : list) CHECK(v == expected[i++]);
        CHECK(i == 3);
    }

    TEST_CASE("insertAt in the middle of a longer list")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(10);
        list.insertAtTail(20);
        list.insertAtTail(30);
        list.insertAtTail(40);
        list.insertAt(2, 99);
        CHECK(list.size() == 5);
        CHECK(list.get(0) == 10);
        CHECK(list.get(1) == 20);
        CHECK(list.get(2) == 99);
        CHECK(list.get(3) == 30);
        CHECK(list.get(4) == 40);
    }

    TEST_CASE("Delete down to empty from the tail")
    {
        DoublyLinkedList<int> list;
        for (int i = 1; i <= 5; ++i) list.insertAtTail(i);
        while (list.size() > 0) {
            list.deleteAt(list.size() - 1);
        }
        CHECK(list.size() == 0);
        CHECK(list.begin() == list.end());
    }

    TEST_CASE("Reverse then iterate forward gives reversed order")
    {
        DoublyLinkedList<int> list;
        for (int i = 1; i <= 5; ++i) list.insertAtTail(i);
        list.reverse();
        int expected[] = {5,4,3,2,1}, i = 0;
        for (auto it = list.begin(); it != list.end(); ++it)
            CHECK(*it == expected[i++]);
        CHECK(i == 5);
    }

    TEST_CASE("Iterator copy, equality and stepping around end()")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(7);
        list.insertAtTail(8);
        auto a = list.begin();
        auto b = a;
        CHECK(a == b);
        CHECK(*a == 7);
        ++b;
        CHECK(a != b);
        CHECK(*b == 8);
        ++b;
        CHECK(b == list.end());
        auto c = list.end();
        --c;
        CHECK(*c == 8);
        --c;
        CHECK(*c == 7);
        CHECK(c == list.begin());
    }

    TEST_CASE("contains/indexOf after deletions")
    {
        DoublyLinkedList<int> list;
        list.insertAtTail(1);
        list.insertAtTail(2);
        list.insertAtTail(2);
        list.insertAtTail(3);
        CHECK(list.contains(2));
        CHECK(list.indexOf(2) == 1);
        list.deleteAt(1);
        CHECK(list.contains(2));
        CHECK(list.indexOf(2) == 1);
        list.deleteAt(1);
        CHECK_FALSE(list.contains(2));
        CHECK(list.indexOf(2) == -1);
    }

    TEST_CASE("toString with converter on empty/non-empty")
    {
        DoublyLinkedList<int> a;
        CHECK(a.toString(intToString2) == "[]");
        DoublyLinkedList<int> b;
        b.insertAtTail(9);
        b.insertAtTail(8);
        CHECK(b.toString(intToString2) == "[9, 8]");
    }
}

TEST_SUITE("DoublyLinkedList<Point> More")
{
    TEST_CASE("Delete a Point then re-check contains/indexOf")
    {
        DoublyLinkedList<Point> list;
        Point a(1,2), b(3,4), c(5,6);
        list.insertAtTail(a);
        list.insertAtTail(b);
        list.insertAtTail(c);
        CHECK(list.contains(b));
        CHECK(list.indexOf(b) == 1);
        list.deleteAt(1);
        CHECK_FALSE(list.contains(b));
        CHECK(list.indexOf(b) == -1);
        auto it = list.end(); --it;
        CHECK(*it == c);
        --it;
        CHECK(*it == a);
        CHECK(it == list.begin());
    }

    TEST_CASE("toString<Point> with converter")
    {
        DoublyLinkedList<Point> list;
        list.insertAtTail(Point(1,1));
        list.insertAtTail(Point(2,3));
        CHECK(list.toString(pointToString3) == "[(1,1), (2,3)]");
    }
}