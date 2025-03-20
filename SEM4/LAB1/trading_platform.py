from typing import Any
from exchange import Exchange
from market_index import MarketIndex
from broker import Broker

class TradingPlatform:
    def __init__(self, exchange: Exchange) -> None:
        self.connected_exchange = exchange
        self.market_data = {}  # кешированные данные биржи
        self.indices = []  # список объектов индексов (MarketIndex)

    def display_market_data(self) -> None:
        print("Market Data:")
        for instrument in self.connected_exchange.instruments:
            print(f"Symbol: {instrument.symbol}, Price: {instrument.current_price}, Volume: {instrument.volume}")
        for index in self.indices:
            index_value = index.recalculate()
            print(f"Index: {index.name}, Value: {index_value}")

    def submit_order(self, broker: Broker, order: Any) -> None:
        broker.place_order(order)

    def generate_report(self, trader: Any) -> None:
        portfolio_value = trader.get_portfolio_value(self.connected_exchange)
    
        # Рассчитываем общую комиссию трейдера
        total_commission = 0.0
        for order in trader.trade_history:
            if order.status == "executed":
                if order.order_type == "buy":
                    total_commission += order.price * order.quantity * order._broker.commission_rate
                elif order.order_type == "sell":
                    total_commission += order.price * order.quantity * order._broker.commission_rate

        report = (
            f"Trader Report for {trader.trader_id}\n"
            f"Balance: {trader.get_balance()}\n"
            f"Portfolio Value: {portfolio_value}\n"
            f"Total Commission Paid: {total_commission}\n"
            f"Trade History:\n"
        )
        for order in trader.trade_history:
            report += (
                f"Order ID: {order.order_id}, "
                f"Type: {order.order_type}, "
                f"Instrument: {order.instrument.symbol}, "
                f"Quantity: {order.quantity}, "
                f"Price: {order.price}, "
                f"Status: {order.status}\n"
            )
        print(report)
