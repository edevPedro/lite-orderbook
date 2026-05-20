## oms-cpp

Small C++ order management / order book experiment.

This is a **study project**, not production software. The goal is to explore:

- **Modern C++**: smart pointers, `enum class`, value types, and STL containers.
- **Market microstructure basics**: bids/asks, levels, trades, and order matching.
- **Design iterations**: trying out different ways to model an order book and its API.

### Features

- **Order types**: `OrderType::GoodTillCancel`, `FillAndKill`, `FillOrKill`, `GoodForDay`, `Market`.
- **Matching engine**: price-time priority with partial fills and trade generation.
- **Order lifecycle**: add, cancel, and modify with in-book lookup by id.
- **Concurrency**: dedicated matching thread with a synchronized request queue.
- **Modular design**: separate types for orders, trades, and book snapshots.

### Architecture overview

- **Orderbook**: maintains bid/ask price levels and matches crossing orders.
- **Level snapshot**: `OrderbookLevelInfos` exposes bid/ask levels for inspection.
- **Data structures**:
  - Bids: `std::map<Price, OrderPointers, std::greater<Price>>` (descending)
  - Asks: `std::map<Price, OrderPointers, std::less<Price>>` (ascending)
  - Orders: `std::list<OrderPointer>` for O(1) insert/remove
  - Order lookup: `std::unordered_map<OrderId, OrderEntry>` for O(1) by id

### Concurrency model

Order matching runs on a dedicated thread. Public APIs (`AddOrder`, `CancelOrder`,
`ModifyOrder`) update the book under a mutex and enqueue a match request. The
matching thread consumes requests from a `std::mutex` + `std::condition_variable`
queue and executes `MatchOrders()` safely. Each API waits for the matching
result before returning.

### Example

```cpp
Orderbook orderbook;
auto buy = std::make_shared<Order>(OrderType::GoodTillCancel, 1, Side::Buy, 100, 10);
auto sell = std::make_shared<Order>(OrderType::GoodTillCancel, 2, Side::Sell, 100, 5);

orderbook.AddOrder(buy);
auto trades = orderbook.AddOrder(sell);
```

### Building

You only need a reasonably recent C++ compiler with C++20 support.

```bash
cd oms-cpp
g++ -std=c++20 main.cpp -o oms-cpp
./oms-cpp
```

### Tests

The tests use GoogleTest and are wired through CMake.

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build
```

### Status 

- **Work in progress**: benchmarking and FIX connectivity are next.

If you are reading this to learn: treat it as a sandbox for ideas, not a reference implementation.
