import unittest
from stock import Stock

class TestStock(unittest.TestCase):
    def setUp(self):
        self.stock = Stock("AAPL", "Apple Inc.", 150.0, 0.01, 1000.0)

    def test_update_price(self):
        self.stock.update_price(160.0)
        self.assertEqual(self.stock.current_price, 160.0)

    def test_pay_dividend(self):
        dividend = self.stock.pay_dividend()
        self.assertEqual(dividend, 1.5)

    def test_adjust_volume(self):
        self.stock.adjust_volume(-100)
        self.assertEqual(self.stock.volume, 900)

if __name__ == '__main__':
    unittest.main()
