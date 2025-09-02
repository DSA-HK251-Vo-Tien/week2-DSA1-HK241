# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Build Commands

### Standard Build
```bash
g++ -o main -I. -Isrc main.cpp src/DoublyLinkedList.cpp tests/*.cpp
```

### Memory Leak Detection Build
```bash
g++ -std=c++17 -fsanitize=address -fno-omit-frame-pointer -g -O0 -Wall -Wextra -I. -Isrc main.cpp tests/*.cpp src/DoublyLinkedList.cpp -o main
```

### Run Tests
```bash
./main
```

## Code Architecture

This is a C++ data structures assignment implementing a doubly linked list with comprehensive testing.

### Core Components
- **DoublyLinkedList** (`src/DoublyLinkedList.h/.cpp`): Template-based doubly linked list with dummy head/tail sentinels
- **Point class** (`utils.h`): 3D point utility class used for testing with custom operators
- **Custom exception** (`main.h`): cursor_error exception for error handling
- **Test suites** (`tests/`): Comprehensive doctest-based testing for basic operations and iterator functionality

### Key Design Patterns
- Uses dummy head/tail nodes for simplified insertion/deletion logic
- Bidirectional optimization: traverses from head or tail depending on index position for O(n/2) average access
- Template explicit instantiation for char, string, int, double, float, and Point types
- Iterator implementation supports both forward (++) and backward (--) traversal
- Range-based for loop support through begin()/end() methods

### Testing Framework
Uses doctest framework with two main test suites:
- `test_basic.cpp`: Core operations (insert, delete, get, indexOf, contains, reverse, toString)
- `test_iterator.cpp`: Iterator functionality and range-based for loops

### Memory Management
- Manual memory management with proper destructor cleanup
- Address sanitizer integration for leak detection during development
- Dummy sentinels simplify boundary condition handling

## Development Notes

The codebase follows Hungarian-style include guards (`__FILENAME_H__`) and uses explicit template instantiation to avoid linker issues. The DoublyLinkedList implementation prioritizes correctness and comprehensive testing over performance optimization.