from typing import Dict, List, Any
from order import Order

class Trader:
    def __init__(self, trader_id: str, balance: float) -> None:
        self.trader_id = trader_id
        self._balance = balance
        self.portfolio: Dict[str, float] = {} 
        self.trade_history: List[Order] = []

    def buy(self, broker: Any, instrument: Any, quantity: float, price: float) -> None:
        order = Order(self, instrument, "buy", quantity, price, broker) 
        self.trade_history.append(order)
        broker.place_order(order)

    def sell(self, broker: Any, instrument: Any, quantity: float, price: float) -> None:
        order = Order(self, instrument, "sell", quantity, price, broker) 
        self.trade_history.append(order)
        broker.place_order(order)
    
    def get_portfolio_value(self, exchange: Any) -> float:
        total_value = 0
        for symbol, qty in self.portfolio.items():
            instrument = exchange.get_instrument_by_symbol(symbol)
            total_value += instrument.current_price * qty
        return total_value

    def _update_balance(self, amount: float) -> None:
        self._balance += amount

    def get_balance(self) -> float:
        return self._balance

    def add_to_portfolio(self, instrument: Any, quantity: float) -> None:
        symbol = instrument.symbol
        if symbol in self.portfolio:
            self.portfolio[symbol] += quantity
        else:
            self.portfolio[symbol] = quantity

    def reduce_from_portfolio(self, instrument: Any, quantity: float) -> None:
        symbol = instrument.symbol
        if symbol in self.portfolio:
            self.portfolio[symbol] -= quantity
            if self.portfolio[symbol] <= 0:
                del self.portfolio[symbol]

    def get_instrument_quantity(self, instrument: Any) -> float:
        return self.portfolio.get(instrument.symbol, 0)
