import uuid
from typing import Any

class Order:
    def __init__(self, trader: Any, instrument: Any, order_type: str,
                 quantity: float, price: float, broker: Any = None) -> None:
        self.order_id: str = str(uuid.uuid4())
        self.trader_id: str = trader.trader_id  
        self._trader = trader  
        self.instrument = instrument
        self.order_type = order_type.lower()  
        self.quantity = quantity
        self.price = price
        self._status: str = "new"  # new, executed, cancelled
        self._broker = broker 

    @property
    def status(self) -> str:
        return self._status

    def execute(self) -> None:
        self._status = "executed"

    def cancel(self) -> None:
        self._status = "cancelled"
