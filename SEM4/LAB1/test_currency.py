import unittest
from currency import Currency

class TestCurrency(unittest.TestCase):
    def setUp(self):
        self.currency = Currency("USD", "US Dollar", 1.0, 1000.0)

    def test_update_price(self):
        self.currency.update_price(1.5)
        self.assertEqual(self.currency.current_price, 1.5)

    def test_adjust_volume(self):
        self.currency.adjust_volume(-100)
        self.assertEqual(self.currency.volume, 900)

if __name__ == '__main__':
    unittest.main()
