## oms-cpp

Small C++ order management / order book experiment.

This is a **study project**, not production software. The goal is to explore:

- **Modern C++**: smart pointers, `enum class`, value types, and STL containers.
- **Market microstructure basics**: bids/asks, levels, trades, and order matching.
- **Design iterations**: trying out different ways to model an order book and its API.

### What’s here

- **Order types**: `Order` (with `OrderType::GoodTillCancel` and `OrderType::FillAndKill`), `OrderModify`, `Trade`.
- **Level abstractions**: `LevelInfo` (price/quantity pairs), `OrderbookLevelInfos` (bid/ask snapshot).
- **Orderbook**: price-level map (bid/ask sides) with order matching logic (`MatchOrders`, `AddOrder`, `CancelOrder`).
- **Data structures**:
  - Bids: `std::map<Price, OrderPointers, std::greater<Price>>` (descending order)
  - Asks: `std::map<Price, OrderPointers, std::less<Price>>` (ascending order)
  - Orders: `std::list<OrderPointer>` for O(1) insert/remove at any position
  - Order lookup: `std::unordered_map<OrderId, OrderEntry>` for O(1) by ID

This code is intentionally small and focused so it's easy to read and refactor as ideas evolve.

### Building

You only need a reasonably recent C++ compiler with C++20 support.

```bash
cd oms-cpp
g++ -std=c++20 main.cpp -o oms-cpp
./oms-cpp
```

You can of course plug this into your favorite build system later (CMake, Meson, etc.).

### Status and scope

- **Educational only**: no guarantees about correctness, performance, or safety.
- **Work in progress**: interfaces and data structures will change as I experiment.
- **Out of scope (for now)**: networking, persistence, risk checks, and real exchange connectivity.

If you’re reading this to learn: treat it as a sandbox for ideas, not a reference implementation.

