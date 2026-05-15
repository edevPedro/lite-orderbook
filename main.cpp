#include <iostream>
#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <limits>
#include <string>
#include <vector>
#include <numeric>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <memory>
#include <variant>
#include <optional>
#include <tuple>
#include <format>

enum class OrderType {
  GoodTillCancel,
  FillAndKill
};

enum class Side {
  Buy,
  Sell
};

using Price = std::int32_t;
using Quantity = std::uint32_t;
using OrderId = std::uint64_t;
using OrderId = std::uint64_t;

struct LevelInfo {
  Price price_;
  Quantity quantity_;
};

using LevelInfos = std::vector<LevelInfo>;

class OrderbookLevelInfos {
public:
  OrderbookLevelInfos(const LevelInfos &bids, const LevelInfos &asks)
    : bids_{bids}
      , asks_{asks} {
  }

  const LevelInfos &getBids() const { return bids_; }
  const LevelInfos &getAsks() const { return asks_; }

private:
  LevelInfos bids_;
  LevelInfos asks_;
};

class Order {
public:
  Order(OrderType orderType, OrderId orderId, Side side, Price price, Quantity quantity)
    : orderType_{orderType}
      , orderId_{orderId}
      , side_{side}
      , price_{price}
      , inicialQuantity_{quantity}
      , remainingQuantity_{quantity} {
  }

  OrderType GetOrderType() const { return orderType_; }
  OrderId GetOrderId() const { return orderId_; }
  Side GetSide() const { return side_; }
  Price GetPrice() const { return price_; }
  Quantity GetInicialQuantity() const { return inicialQuantity_; }
  Quantity GetRemainingQuantity() const { return remainingQuantity_; }
  Quantity GetFilledQuantity() const { return GetInicialQuantity() - GetRemainingQuantity(); }

  void Fill(Quantity quantity) {
    if (quantity > GetRemainingQuantity()) {
      throw std::logic_error(std::format("Order ({}) cannot be filled for more than its remaining quantity",
                                         GetOrderId()));
    }
    remainingQuantity_ -= quantity;
  }

private:
  OrderType orderType_;
  OrderId orderId_;
  Side side_;
  Price price_;
  Quantity inicialQuantity_;
  Quantity remainingQuantity_;
};

using OrderPointer = std::shared_ptr<Order>;
using OrdersPointers = std::list<OrderPointer>;

class OrderModify {
public:
  OrderModify(OrderId orderId, Side side, Price price, Quantity quantity)
    : orderId_{orderId}
      , side_{side}
      , price_{price}
      , quantity_{quantity} {
  }

  OrderId GetOrderId() const { return orderId_; }
  Side GetSide() const { return side_; }
  Price GetPrice() const { return newPrice_; }
  Quantity GetQuantity() const { return newQuantity_; }

  OrderPointer ToOrder(OrderType orderType) const {
    return std::make_shared<Order>(orderType, GetOrderId(), GetSide(), GetPrice(), GetQuantity());
  }

private:
  OrderId orderId_;
  Side side_;
  Price price_;
  Quantity quantity_;
};

struct TradeInfo {
  OrderId orderId_;
  // OrderId sellOrderId_;
  Price price_;
  Quantity quantity_;
};

class Trade {
public:
  Trade(const TradeInfo &bidTrade, const TradeInfo &askTrade)
    : bidTrade_{bidTrade}
      , askTrade_{askTrade} {
  }

  const TradeInfo &GetBidTrade() const { return bidTrade_; }
  const TradeInfo &GetAskTrade() const { return askTrade_; }

private:
  TradeInfo bidTrade_;
  TradeInfo askTrade_;
};

using Trades = std::vector<Trade>;

class Orderbook {
private:


int main() {
  return 0;
}
