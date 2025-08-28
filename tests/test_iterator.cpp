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

            SUBCASE("Begin equals end")
            {
                CHECK(list.begin() == list.end());
            }

            SUBCASE("Range-based for on empty list")
            {
                for ([[maybe_unused]] int x : list)
                {
                    FAIL("Should not enter loop for empty list");
                }
            }
        }

        TEST_CASE("Single element list iteration")
        {
            DoublyLinkedList<int> list;
            list.insertAtTail(42);

            SUBCASE("Forward iteration")
            {
                auto it = list.begin();
                CHECK(*it == 42);
                ++it;
                CHECK(it == list.end());
            }

            SUBCASE("Range-based for")
            {
                int count = 0;
                for (int x : list)
                {
                    CHECK(x == 42);
                    count++;
                }
                CHECK(count == 1);
            }
        }

        TEST_CASE("Reverse iteration")
        {
            DoublyLinkedList<int> list;
            list.insertAtTail(1);
            list.insertAtTail(2);
            list.insertAtTail(3);

            int expected[] = {3, 2, 1};

            SUBCASE("Reverse iterator")
            {
                int idx = 0;
                for (auto it = list.begin(); it != list.end(); ++it)
                {
                    CHECK(*it == expected[idx++]);
                }
                CHECK(idx == 3);
            }
        }

        TEST_CASE("Modify elements during iteration")
        {
            DoublyLinkedList<int> list;
            list.insertAtTail(1);
            list.insertAtTail(2);
            list.insertAtTail(3);

            SUBCASE("Increment all elements")
            {
                for (auto it = list.begin(); it != list.end(); ++it)
                {
                    (*it)++;
                }

                int expected[] = {2, 3, 4};
                int idx = 0;
                for (int x : list)
                {
                    CHECK(x == expected[idx++]);
                }
            }
        }

        TEST_CASE("Iterator comparison")
        {
            DoublyLinkedList<int> list;
            list.insertAtTail(1);
            list.insertAtTail(2);

            SUBCASE("Equality and inequality")
            {
                auto it1 = list.begin();
                auto it2 = list.begin();
                CHECK(it1 == it2);

                ++it2;
                CHECK(it1 != it2);
            }
        }

        TEST_CASE("Iterator invalidation after modification")
        {
            DoublyLinkedList<int> list;
            list.insertAtTail(1);
            list.insertAtTail(2);

            SUBCASE("Insert invalidates iterator")
            {
                auto it = list.begin();
                list.insertAtTail(3);
                CHECK_THROWS_AS(*it, std::runtime_error); // Assuming iterator invalidation throws
            }

            SUBCASE("Delete invalidates iterator")
            {
                auto it = list.begin();
                list.deleteAt(0);
                CHECK_THROWS_AS(*it, std::runtime_error); // Assuming iterator invalidation throws
            }
        }

        TEST_CASE("Const iterator")
        {
            const DoublyLinkedList<int> list = [] {
                DoublyLinkedList<int> temp;
                temp.insertAtTail(1);
                temp.insertAtTail(2);
                return temp;
            }();

            SUBCASE("Read-only iteration")
            {
                int expected[] = {1, 2};
                int idx = 0;
                for (auto it = list.begin(); it != list.end(); ++it)
                {
                    CHECK(*it == expected[idx++]);
                }
            }
        }

        TEST_CASE("Iterator on large list")
        {
            DoublyLinkedList<int> list;
            for (int i = 0; i < 1000; ++i)
            {
                list.insertAtTail(i);
            }

            SUBCASE("Forward iteration")
            {
                int idx = 0;
                for (int x : list)
                {
                    CHECK(x == idx++);
                }
                CHECK(idx == 1000);
            }
        }

        TEST_CASE("Iterator on list of custom objects")
        {
            struct Custom
            {
                int value;
                bool operator==(const Custom &other) const { return value == other.value; }
            };

            DoublyLinkedList<Custom> list;
            list.insertAtTail({1});
            list.insertAtTail({2});

            SUBCASE("Forward iteration")
            {
                int expected[] = {1, 2};
                int idx = 0;
                for (const auto &x : list)
                {
                    CHECK(x.value == expected[idx++]);
                }
            }
        }

        TEST_CASE("Nested iteration")
        {
            DoublyLinkedList<int> outer;
            outer.insertAtTail(1);
            outer.insertAtTail(2);

            DoublyLinkedList<int> inner;
            inner.insertAtTail(10);
            inner.insertAtTail(20);

            SUBCASE("Outer and inner iteration")
            {
                for (int x : outer)
                {
                    for (int y : inner)
                    {
                        CHECK((x == 1 || x == 2));
                        CHECK((y == 10 || y == 20));
                    }
                }
            }
        }

        TEST_CASE("Reverse iteration using operator--")
{
    DoublyLinkedList<int> list;
    list.insertAtTail(10);
    list.insertAtTail(20);
    list.insertAtTail(30); // List: [10, 20, 30]

    SUBCASE("Reverse iteration from end to begin")
    {
        auto it = list.end(); 
        --it;                
        CHECK(*it == 30);

        --it; 
        CHECK(*it == 20);

        --it; 
        CHECK(*it == 10);

        CHECK(it == list.begin());
    }

    SUBCASE("Decrementing past begin throws exception")
    {
        auto it = list.begin();
        CHECK_THROWS_AS(--it, std::out_of_range); 
    }
}

        TEST_CASE("Iterator with mixed operations")
        {
            DoublyLinkedList<int> list;
            list.insertAtTail(1);
            list.insertAtTail(2);
            list.insertAtTail(3);

            SUBCASE("Delete and iterate")
            {
                list.deleteAt(1); 
                int expected[] = {1, 3};
                int idx = 0;
                for (int x : list)
                {
                    CHECK(x == expected[idx++]);
                }
            }
        }

        TEST_CASE("Iterator with duplicate values")
        {
            DoublyLinkedList<int> list;
            list.insertAtTail(1);
            list.insertAtTail(1);
            list.insertAtTail(2);

            SUBCASE("Forward iteration")
            {
                int expected[] = {1, 1, 2};
                int idx = 0;
                for (int x : list)
                {
                    CHECK(x == expected[idx++]);
                }
            }
        }

        TEST_CASE("Iterator with large gaps in values")
        {
            DoublyLinkedList<int> list;
            list.insertAtTail(100);
            list.insertAtTail(1000);
            list.insertAtTail(10000);

            SUBCASE("Forward iteration")
            {
                int expected[] = {100, 1000, 10000};
                int idx = 0;
                for (int x : list)
                {
                    CHECK(x == expected[idx++]);
                }
            }
        }

        TEST_CASE("Iterator with negative values")
        {
            DoublyLinkedList<int> list;
            list.insertAtTail(-1);
            list.insertAtTail(-2);
            list.insertAtTail(-3);

            SUBCASE("Forward iteration")
            {
                int expected[] = {-1, -2, -3};
                int idx = 0;
                for (int x : list)
                {
                    CHECK(x == expected[idx++]);
                }
            }
        }

        TEST_CASE("Iterator with mixed positive and negative values")
        {
            DoublyLinkedList<int> list;
            list.insertAtTail(-1);
            list.insertAtTail(0);
            list.insertAtTail(1);

            SUBCASE("Forward iteration")
            {
                int expected[] = {-1, 0, 1};
                int idx = 0;
                for (int x : list)
                {
                    CHECK(x == expected[idx++]);
                }
            }
        }

        TEST_CASE("Iterator with floating-point values")
        {
            DoublyLinkedList<double> list;
            list.insertAtTail(1.1);
            list.insertAtTail(2.2);
            list.insertAtTail(3.3);

            SUBCASE("Forward iteration")
            {
                double expected[] = {1.1, 2.2, 3.3};
                int idx = 0;
                for (double x : list)
                {
                    CHECK(x == doctest::Approx(expected[idx++]));
                }
            }
        }

        TEST_CASE("Iterator with strings")
        {
            DoublyLinkedList<std::string> list;
            list.insertAtTail("hello");
            list.insertAtTail("world");

            SUBCASE("Forward iteration")
            {
                std::string expected[] = {"hello", "world"};
                int idx = 0;
                for (const auto &x : list)
                {
                    CHECK(x == expected[idx++]);
                }
            }
        }
    }
}