import unittest
from exchange import Exchange
from currency import Currency
from order import Order
from trader import Trader
from broker import Broker
from trading_platform import TradingPlatform

class TestExchange(unittest.TestCase):
    def setUp(self):
        self.exchange = Exchange()
        
        self.currency = Currency("USD", "US Dollar", 1.0, 1000.0)
        self.exchange.add_instrument(self.currency)
        
        self.trader1 = Trader("trader1", 1000.0) 
        self.trader2 = Trader("trader2", 1000.0)  
        
        self.broker = Broker("broker1", 0.01, self.exchange) 
        
        self.platform = TradingPlatform(self.exchange)

    def test_add_instrument(self):
        self.assertEqual(len(self.exchange.instruments), 1)
        self.assertEqual(self.exchange.instruments[0].symbol, "USD")

    def test_get_instrument_by_symbol(self):
        instrument = self.exchange.get_instrument_by_symbol("USD")
        self.assertEqual(instrument.symbol, "USD")

    def test_match_orders(self):
        buy_order = Order(self.trader1, self.currency, "buy", 100, 1.0, self.broker)
        sell_order = Order(self.trader2, self.currency, "sell", 100, 1.0, self.broker)
        
        self.exchange.add_order(buy_order)
        self.exchange.add_order(sell_order)
        
        self.exchange.match_orders()
        
        self.assertEqual(buy_order.status, "executed")
        self.assertEqual(sell_order.status, "executed")
        
        self.assertEqual(len(self.exchange.transactions), 1)
        transaction = self.exchange.transactions[0]
        self.assertEqual(transaction["buyer_id"], "trader1")
        self.assertEqual(transaction["seller_id"], "trader2")
        self.assertEqual(transaction["instrument"], "USD")
        self.assertEqual(transaction["quantity"], 100)
        self.assertEqual(transaction["price"], 1.0)

    def test_execute_trade(self):
        buy_order = Order(self.trader1, self.currency, "buy", 100, 1.0, self.broker)
        sell_order = Order(self.trader2, self.currency, "sell", 100, 1.0, self.broker)
        
        self.exchange.execute_trade(buy_order, sell_order, 100)
        
        self.assertEqual(len(self.exchange.transactions), 1)
        transaction = self.exchange.transactions[0]
        self.assertEqual(transaction["buyer_id"], "trader1")
        self.assertEqual(transaction["seller_id"], "trader2")
        self.assertEqual(transaction["instrument"], "USD")
        self.assertEqual(transaction["quantity"], 100)
        self.assertEqual(transaction["price"], 1.0)
        
        self.assertAlmostEqual(self.trader1.get_balance(), 899.0) 
        self.assertAlmostEqual(self.trader2.get_balance(), 1099.0)  

if __name__ == '__main__':
    unittest.main()