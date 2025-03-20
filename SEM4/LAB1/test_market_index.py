import unittest
from market_index import MarketIndex
from currency import Currency

class TestMarketIndex(unittest.TestCase):
    def setUp(self):
        self.index = MarketIndex("Test Index")
        self.currency1 = Currency("USD", "US Dollar", 1.0, 1000.0)
        self.currency2 = Currency("EUR", "Euro", 1.2, 1000.0)

    def test_recalculate(self):
        self.index.add_component(self.currency1)
        self.index.add_component(self.currency2)
        self.index.recalculate()
        self.assertEqual(self.index.current_value, 1.1)

    def test_add_component(self):
        self.index.add_component(self.currency1)
        self.assertEqual(len(self.index.components), 1)

if __name__ == '__main__':
    unittest.main()
