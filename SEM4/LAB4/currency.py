class Currency:
    def __init__(self, symbol: str, name: str, current_price: float, volume: float) -> None:
        self.symbol = symbol
        self.name = name
        self.current_price = current_price
        self.volume = volume

    def update_price(self, new_price: float) -> None:
        self.current_price = new_price

    def adjust_volume(self, delta: float) -> None:
        self.volume += delta
