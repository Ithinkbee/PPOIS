from typing import List, Any

class MarketIndex:
    def __init__(self, name: str) -> None:
        self.name = name
        self.components: List[Any] = [] 
        self.current_value: float = 0.0

    def recalculate(self) -> float:
        if not self.components:
            self.current_value = 0.0
        else:
            total = sum(instr.current_price for instr in self.components)
            self.current_value = total / len(self.components)
        return self.current_value

    def add_component(self, instrument: Any) -> None:
        self.components.append(instrument)
