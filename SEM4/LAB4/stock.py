class Stock:
    def __init__(self, symbol: str, company_name: str, current_price: float,
                 dividend_yield: float, volume: float) -> None:
        self.symbol = symbol
        self.company_name = company_name
        self.current_price = current_price
        self.dividend_yield = dividend_yield
        self.volume = volume

    def update_price(self, new_price: float) -> None:
        self.current_price = new_price

    def pay_dividend(self) -> float:
        return self.current_price * self.dividend_yield

    def adjust_volume(self, delta: float) -> None:
        self.volume += delta