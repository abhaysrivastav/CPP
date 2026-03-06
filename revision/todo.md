# Interview Revision Checklist - C++ Tech Lead (ZEISS)

---

## C++ Core (Modern C++11/14/17/20)

- [ ] Move semantics, rvalue references, `std::move`, `std::forward`
- [ ] Smart pointers: `unique_ptr`, `shared_ptr`, `weak_ptr`
- [ ] Lambda expressions, `auto`, range-based for loops
- [ ] `constexpr`, `nullptr`, `override`, `final`
- [ ] Variadic templates, fold expressions
- [ ] `std::optional`, `std::variant`, `std::any` (C++17)
- [ ] Copy/Move constructors and assignment operators (Rule of 3/5/0)
- [ ] Template metaprogramming basics, SFINAE, `if constexpr`

---

## Memory Management

- [ ] Stack vs heap, RAII idiom
- [ ] Custom allocators, placement new
- [ ] Memory leaks, dangling pointers, use-after-free
- [ ] Tools: Valgrind, AddressSanitizer

---

## Multi-threading & Concurrency

- [ ] `std::thread`, `std::async`, `std::future`, `std::promise`
- [ ] Mutexes: `std::mutex`, `std::recursive_mutex`, `std::shared_mutex`
- [ ] `std::condition_variable`, `std::atomic`
- [ ] Thread safety, race conditions, deadlocks, livelocks
- [ ] Lock-free programming basics
- [ ] Qt threading: `QThread`, `QtConcurrent`, signals/slots across threads

---

## Qt Framework

- [ ] Signals & Slots mechanism (including Qt5 `connect()` syntax)
- [ ] Qt object model: `QObject`, parent-child ownership, memory management
- [ ] Qt GUI: widgets, layouts, QML/Quick basics
- [ ] Model/View architecture (`QAbstractItemModel`, `QListView`, etc.)
- [ ] Qt networking: `QNetworkAccessManager`, `QTcpSocket`
- [ ] Qt serialization: JSON (`QJsonDocument`), XML
- [ ] `QThread` and worker object pattern
- [ ] Event loop, `QEventLoop`, `QTimer`
- [ ] Cross-platform builds with `qmake` / `CMake`
- [ ] Qt testing: `QTest`

---

## Data Structures & Algorithms

- [ ] Trees (BST, AVL, segment trees)
- [ ] Graphs (BFS/DFS, Dijkstra, A*)
- [ ] Hash maps, heaps / priority queues
- [ ] Sorting algorithms and their complexity
- [ ] Dynamic programming, sliding window, two pointers
- [ ] STL containers: `map`, `unordered_map`, `set`, `deque`, `priority_queue`
- [ ] STL algorithms: `std::sort`, `std::transform`, `std::accumulate`

---

## Design Patterns

- [ ] Creational: Singleton, Factory, Builder, Prototype
- [ ] Structural: Adapter, Decorator, Proxy, Facade
- [ ] Behavioral: Observer, Strategy, Command, State, Template Method
- [ ] MVC / MVP / MVVM (especially relevant for Qt GUI apps)

---

## Software Architecture & OOP

- [ ] SOLID principles
- [ ] Dependency injection, IoC
- [ ] Interface segregation using abstract base classes
- [ ] Component-based and layered architecture
- [ ] Plugin architecture (common in Qt apps)

---

## Performance Optimization

- [ ] Cache locality, memory alignment, false sharing
- [ ] Profiling tools: `gprof`, `perf`, `Valgrind/Callgrind`, Qt Creator profiler
- [ ] Inlining, branch prediction, compiler optimizations (`-O2`, `-O3`)
- [ ] Avoiding unnecessary copies, `reserve()` for containers

---

## Build Systems & DevOps

- [ ] CMake: targets, modern CMake (`target_link_libraries`, `target_include_directories`)
- [ ] `qmake` vs CMake for Qt projects
- [ ] CI/CD pipelines, static analysis (`clang-tidy`, `cppcheck`)
- [ ] Git workflows, code review practices

---

## Medical Device / Regulatory (ZEISS Specific)

- [ ] IEC 62304: Software lifecycle for medical devices (classes A/B/C, SOUP management)
- [ ] ISO 13485: Quality management for medical devices
- [ ] Software risk management (ISO 14971)
- [ ] Traceability: requirements → design → code → tests
- [ ] Unit testing in safety-critical systems (`GTest`, `GMock`)

---

## Technical Leadership

- [ ] Breaking down epics into tasks (story points, estimation)
- [ ] Code review best practices
- [ ] Handling technical debt
- [ ] Mentoring strategies for developers at different levels
- [ ] Communicating technical risk to non-technical stakeholders
- [ ] Architecture decision records (ADRs)

---

## Progress Tracker

| Area | Status |
|---|---|
| C++ Core (Modern) | Not Started |
| Memory Management | Not Started |
| Multi-threading & Concurrency | Not Started |
| Qt Framework | Not Started |
| Data Structures & Algorithms | Not Started |
| Design Patterns | Not Started |
| Software Architecture & OOP | Not Started |
| Performance Optimization | Not Started |
| Build Systems & DevOps | Not Started |
| Medical Device / Regulatory | Not Started |
| Technical Leadership | Not Started |
