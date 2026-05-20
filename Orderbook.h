#pragma once

#include <atomic>
#include <condition_variable>
#include <future>
#include <map>
#include <mutex>
#include <queue>
#include <thread>
#include <unordered_map>

#include "Order.h"
#include "OrderModify.h"
#include "OrderbookLevelInfos.h"
#include "Trade.h"
#include "Usings.h"

class Orderbook {
private:
  struct OrderEntry {
    OrderPointer order_{nullptr};
    OrderPointers::iterator location_;
  };

  struct LevelData {
    Quantity quantity_{};
    Quantity count_{};

    enum class Action {
      Add,
      Remove,
      Match,
    };
  };

  struct MatchRequest {
    std::promise<Trades> promise_;
  };

  std::unordered_map<Price, LevelData> data_;
  std::map<Price, OrderPointers, std::greater<Price>> bids_;
  std::map<Price, OrderPointers, std::less<Price>> asks_;
  std::unordered_map<OrderId, OrderEntry> orders_;
  mutable std::mutex ordersMutex_;
  std::thread ordersPruneThread_;
  std::condition_variable shutdownConditionVariable_;
  std::mutex matchMutex_;
  std::condition_variable matchConditionVariable_;
  std::queue<MatchRequest> matchRequests_;
  std::thread matchThread_;
  std::atomic<bool> shutdown_{false};

  void PruneGoodForDayOrders();

  void CancelOrders(OrderIds orderIds);

  void CancelOrderInternal(OrderId orderId);

  void OnOrderCancelled(OrderPointer order);

  void OnOrderAdded(OrderPointer order);

  void OnOrderMatched(Price price, Quantity quantity, bool isFullyFilled);

  void UpdateLevelData(Price price, Quantity quantity,
                       LevelData::Action action);

  bool CanFullyFill(Side side, Price price, Quantity quantity) const;

  bool CanMatch(Side side, Price price) const;

  Trades MatchOrders();

  void RunMatching();

  Trades RequestMatch();

public:
  Orderbook();

  Orderbook(const Orderbook &) = delete;

  void operator=(const Orderbook &) = delete;

  Orderbook(Orderbook &&) = delete;

  void operator=(Orderbook &&) = delete;

  ~Orderbook();

  Trades AddOrder(OrderPointer order);

  void CancelOrder(OrderId orderId);

  Trades ModifyOrder(OrderModify order);

  std::size_t Size() const;

  OrderbookLevelInfos GetOrderInfos() const;
};
