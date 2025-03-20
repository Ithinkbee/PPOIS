import unittest
from trading_platform import TradingPlatform
from exchange import Exchange
from market_index import MarketIndex
from broker import Broker
from currency import Currency
from trader import Trader
from order import Order

class TestTradingPlatform(unittest.TestCase):
    def setUp(self):
        self.exchange = Exchange()
        self.platform = TradingPlatform(self.exchange)
        self.currency = Currency("USD", "US Dollar", 1.0, 1000.0)
        self.exchange.add_instrument(self.currency)
        self.index = MarketIndex("Test Index")
        self.index.add_component(self.currency)
        self.platform.indices.append(self.index)
        self.broker = Broker("broker1", 0.01, self.exchange)
        self.trader = Trader("trader1", 1000.0)

    def test_display_market_data(self):
        self.platform.display_market_data()

    def test_submit_order(self):
        order = Order(self.trader, self.currency, "buy", 100, 1.0)
        self.platform.submit_order(self.broker, order)

    def test_generate_report(self):
        self.trader.buy(self.broker, self.currency, 100, 1.0)
        self.platform.generate_report(self.trader)

if __name__ == '__main__':
    unittest.main()
