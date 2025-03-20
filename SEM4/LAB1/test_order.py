import unittest
from order import Order
from trader import Trader
from currency import Currency

class TestOrder(unittest.TestCase):
    def setUp(self):
        self.trader = Trader("trader1", 1000.0)
        self.currency = Currency("USD", "US Dollar", 1.0, 1000.0)

    def test_order_initialization(self):
        order = Order(self.trader, self.currency, "buy", 100, 1.0)
        self.assertEqual(order.order_type, "buy")
        self.assertEqual(order.quantity, 100)
        self.assertEqual(order.price, 1.0)

    def test_order_execute(self):
        order = Order(self.trader, self.currency, "buy", 100, 1.0)
        order.execute()
        self.assertEqual(order.status, "executed")

    def test_order_cancel(self):
        order = Order(self.trader, self.currency, "buy", 100, 1.0)
        order.cancel()
        self.assertEqual(order.status, "cancelled")

if __name__ == '__main__':
    unittest.main()
