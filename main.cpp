#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

/*
Build:
Toàn bộ chương trình:
    ! g++ -o main -I. -Isrc main.cpp src/DoublyLinkedList.cpp tests/*.cpp

Trong đó:
    -I.            : Bao gồm thư mục hiện tại để tìm file header
    -Isrc          : Bao gồm thư mục src để tìm file header
    main.cpp       : File chính chứa hàm main
    DoublyLinkedList.cpp: Triển khai class danh sách liên kết đôi
    tests/*.cpp    : Bao gồm tất cả các file test (dùng doctest)

Kết quả: tạo file thực thi "main"

Run: use doctest/doctest.h
*/