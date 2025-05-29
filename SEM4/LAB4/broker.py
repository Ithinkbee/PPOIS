from typing import Any
from order import Order
from exchange import Exchange
from exceptions import (
    InsufficientBalanceException,
    InsufficientVolumeException,
    InsufficientPortfolioException,
    OrderValidationException,
)

class Broker:
    def __init__(self, broker_id: str, commission_rate: float, exchange: Exchange) -> None:
        self.broker_id = broker_id
        self.commission_rate = commission_rate
        self.exchange = exchange

    def validate_order(self, trader: Any, order: Order) -> None:
        if order.order_type == "buy":
            total_cost = order.quantity * order.price
            if trader.get_balance() < total_cost:
                raise InsufficientBalanceException("Insufficient balance for buying order.")
            if order.instrument.volume < order.quantity:
                raise InsufficientVolumeException("Not enough instrument volume available.")
        elif order.order_type == "sell":
            if trader.get_instrument_quantity(order.instrument) < order.quantity:
                raise InsufficientPortfolioException("Not enough instrument in portfolio to sell.")
        else:
            raise OrderValidationException("Invalid order type.")

    def charge_commission(self, trader: Any, amount: float) -> None:
        trader._update_balance(-amount)

    def place_order(self, order: Order) -> bool:
        try:
            self.validate_order(order._trader, order)
        except Exception as e:
            print(f"Order validation failed: {e}")
            order.cancel()
            return False

        order._broker = self

        self.exchange.add_order(order)
        self.exchange.match_orders()
        return True
