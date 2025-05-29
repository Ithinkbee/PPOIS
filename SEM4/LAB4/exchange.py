from typing import List, Any
from order import Order
from trader import Trader
from exceptions import InstrumentNotFoundException

class Exchange:
    def __init__(self) -> None:
        self.instruments: List[Any] = [] 
        self.order_book: List[Order] = []
        self.transactions: List[dict] = []

    def add_instrument(self, instrument: Any) -> None:
        self.instruments.append(instrument)

    def add_order(self, order: Order) -> None:
        self.order_book.append(order)

    def get_instrument_by_symbol(self, symbol: str) -> Any:
        for instr in self.instruments:
            if instr.symbol == symbol:
                return instr
        raise InstrumentNotFoundException(f"Instrument with symbol {symbol} not found.")

    def get_current_price(self, instrument: Any) -> float:
        return instrument.current_price

    def match_orders(self) -> None:
       buy_orders = [o for o in self.order_book if o.order_type == "buy" and o.status == "new"]
       sell_orders = [o for o in self.order_book if o.order_type == "sell" and o.status == "new"]

       for buy_order in buy_orders:
           for sell_order in sell_orders:
               if buy_order.instrument.symbol == sell_order.instrument.symbol:
                   if buy_order.price >= sell_order.price:
                       trade_quantity = min(buy_order.quantity, sell_order.quantity)

                       if trade_quantity > 0:
                           self.execute_trade(buy_order, sell_order, trade_quantity)

                           buy_order.quantity -= trade_quantity
                           sell_order.quantity -= trade_quantity

                           if buy_order.quantity == 0:
                               buy_order.execute()
                           if sell_order.quantity == 0:
                               sell_order.execute()

       self.order_book = [o for o in self.order_book if o.status == "new" and o.quantity > 0]

    def execute_trade(self, buy_order: Order, sell_order: Order, trade_quantity: float) -> None:
        trade_price = (buy_order.price + sell_order.price) / 2

        buyer = buy_order._trader
        seller = sell_order._trader

        total_cost = trade_price * trade_quantity

        buyer_commission = total_cost * buy_order._broker.commission_rate
        seller_commission = total_cost * sell_order._broker.commission_rate

        buyer._update_balance(-total_cost - buyer_commission)
        seller._update_balance(total_cost - seller_commission)

        buyer.add_to_portfolio(buy_order.instrument, trade_quantity)
        seller.reduce_from_portfolio(sell_order.instrument, trade_quantity)

        buy_order.instrument.update_price(trade_price)
        buy_order.instrument.adjust_volume(-trade_quantity)

        transaction = {
            "buyer_id": buyer.trader_id,
            "seller_id": seller.trader_id,
            "instrument": buy_order.instrument.symbol,
            "quantity": trade_quantity,
            "price": trade_price,
            "buyer_commission": buyer_commission,
            "seller_commission": seller_commission
        }
        self.transactions.append(transaction)
        print(f"Executed trade: {transaction}")
        print(f"Buyer {buyer.trader_id} bought {trade_quantity} of {buy_order.instrument.symbol} at {trade_price}.")
        print(f"Seller {seller.trader_id} sold {trade_quantity} of {sell_order.instrument.symbol} at {trade_price}.")
        print(f"Buyer commission: {buyer_commission}")
        print(f"Seller commission: {seller_commission}")
        print(f"New buyer balance: {buyer.get_balance()}")
        print(f"New seller balance: {seller.get_balance()}")
        print(f"New instrument volume: {buy_order.instrument.volume}")
