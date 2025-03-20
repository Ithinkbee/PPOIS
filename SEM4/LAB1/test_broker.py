import unittest
from broker import Broker
from order import Order
from trader import Trader
from exchange import Exchange
from currency import Currency
from exceptions import InsufficientBalanceException, InsufficientVolumeException, InsufficientPortfolioException, OrderValidationException

class TestBroker(unittest.TestCase):
    def setUp(self):
        self.exchange = Exchange()
        self.broker = Broker("broker1", 0.01, self.exchange)
        self.trader = Trader("trader1", 1000.0)
        self.currency = Currency("USD", "US Dollar", 1.0, 1000.0)

    def test_validate_order_buy_insufficient_balance(self):
        order = Order(self.trader, self.currency, "buy", 1001, 1.0)
        with self.assertRaises(InsufficientBalanceException):
            self.broker.validate_order(self.trader, order)

    def test_validate_order_buy_insufficient_volume(self):
        order = Order(self.trader, self.currency, "buy", 1001, 0.8)
        with self.assertRaises(InsufficientVolumeException):
            self.broker.validate_order(self.trader, order)

    def test_validate_order_sell_insufficient_portfolio(self):
        order = Order(self.trader, self.currency, "sell", 1, 1.0)
        with self.assertRaises(InsufficientPortfolioException):
            self.broker.validate_order(self.trader, order)

    def test_validate_order_invalid_type(self):
        order = Order(self.trader, self.currency, "invalid", 1, 1.0)
        with self.assertRaises(OrderValidationException):
            self.broker.validate_order(self.trader, order)

    def test_place_order_success(self):
        order = Order(self.trader, self.currency, "buy", 100, 1.0)
        self.assertTrue(self.broker.place_order(order))

if __name__ == '__main__':
    unittest.main()
