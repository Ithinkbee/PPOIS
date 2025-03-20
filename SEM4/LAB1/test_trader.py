import unittest
from trader import Trader
from currency import Currency
from broker import Broker
from exchange import Exchange

class TestTrader(unittest.TestCase):
    def setUp(self):
        self.trader = Trader("trader1", 1000.0)
        self.currency = Currency("USD", "US Dollar", 1.0, 1000.0)
        self.exchange = Exchange()
        self.broker = Broker("broker1", 0.01, self.exchange)

    def test_buy(self):
        self.trader.buy(self.broker, self.currency, 100, 1.0)
        self.assertEqual(len(self.trader.trade_history), 1)

    def test_sell(self):
        self.trader.sell(self.broker, self.currency, 100, 1.0)
        self.assertEqual(len(self.trader.trade_history), 1)

    def test_get_portfolio_value(self):
        self.trader.add_to_portfolio(self.currency, 100)
        self.exchange.add_instrument(self.currency)
        self.assertEqual(self.trader.get_portfolio_value(self.exchange), 100.0)

    def test_add_to_portfolio(self):
        self.trader.add_to_portfolio(self.currency, 100)
        self.assertEqual(self.trader.portfolio["USD"], 100)

    def test_reduce_from_portfolio(self):
        self.trader.add_to_portfolio(self.currency, 100)
        self.trader.reduce_from_portfolio(self.currency, 50)
        self.assertEqual(self.trader.portfolio["USD"], 50)

if __name__ == '__main__':
    unittest.main()
