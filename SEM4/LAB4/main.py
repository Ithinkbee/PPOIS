import sys
from trading_platform import TradingPlatform
from exchange import Exchange
from broker import Broker
from trader import Trader
from currency import Currency
from stock import Stock
from market_index import MarketIndex

def main() -> None:
    def create_platform(name: str) -> TradingPlatform:
        exchange = Exchange()
        platform = TradingPlatform(exchange)

        if name == "Platform 1":
            usd = Currency("USD", "US Dollar", 1.0, 1000000)
            eur = Currency("EUR", "Euro", 1.1, 500000)
            apple = Stock("AAPL", "Apple Inc.", 150.0, 0.02, 10000)
            google = Stock("GOOGL", "Alphabet Inc.", 2800.0, 0.0, 5000)
        elif name == "Platform 2":
            usd = Currency("USD", "US Dollar", 1.05, 1200000) 
            eur = Currency("EUR", "Euro", 1.15, 600000)
            apple = Stock("AAPL", "Apple Inc.", 160.0, 0.02, 12000)
            google = Stock("GOOGL", "Alphabet Inc.", 2850.0, 0.0, 5500)

        exchange.add_instrument(usd)
        exchange.add_instrument(eur)
        exchange.add_instrument(apple)
        exchange.add_instrument(google)

        index = MarketIndex(f"{name} Index")
        index.add_component(usd)
        index.add_component(eur)
        index.add_component(apple)
        index.add_component(google)
        platform.indices.append(index)

        return platform

    platform1 = create_platform("Platform 1")
    platform2 = create_platform("Platform 2")

    current_platform = platform1 

    broker1 = Broker("B1", 0.01, current_platform.connected_exchange) 
    broker2 = Broker("B2", 0.02, current_platform.connected_exchange)  

    current_broker = broker1

    trader1 = Trader("T1", 10000000.0)

    trader2 = Trader("T2", 10000000.0)
    trader2.add_to_portfolio(Currency("USD", "US Dollar", 1.0, 1000000), 1000000)
    trader2.add_to_portfolio(Currency("EUR", "Euro", 1.1, 500000), 100000)
    trader2.add_to_portfolio(Stock("AAPL", "Apple Inc.", 150.0, 0.02, 10000), 1000)
    trader2.add_to_portfolio(Stock("GOOGL", "Alphabet Inc.", 2800.0, 0.0, 5000), 100)

    def display_market_data():
        current_platform.display_market_data()

    def buy_instrument_t1():
        symbol = input("Введите тикер инструмента для покупки: ").strip().upper()
        try:
            instrument = current_platform.connected_exchange.get_instrument_by_symbol(symbol)
        except Exception as e:
            print(f"Ошибка: {e}")
            return
        try:
            quantity = float(input("Введите количество: "))
            price = float(input("Введите цену: "))
        except ValueError:
            print("Неверный формат числа!")
            return
        if quantity <= 0:
            print("Количество должно быть положительным числом!")
            return
        if price <= 0:
            print("Цена должна быть положительной!")
            return

        trader1.buy(current_broker, instrument, quantity, price)
        print("Заявка на покупку размещена.")

    def buy_instrument_t2():
        symbol = input("Введите тикер инструмента для покупки: ").strip().upper()
        try:
            instrument = current_platform.connected_exchange.get_instrument_by_symbol(symbol)
        except Exception as e:
            print(f"Ошибка: {e}")
            return
        try:
            quantity = float(input("Введите количество: "))
            price = float(input("Введите цену: "))
        except ValueError:
            print("Неверный формат числа!")
            return
        if quantity <= 0:
            print("Количество должно быть положительным числом!")
            return
        if price <= 0:
            print("Цена должна быть положительной!")
            return

        trader2.buy(current_broker, instrument, quantity, price)
        print("Заявка на покупку размещена.")

    def sell_instrument_t1():
        symbol = input("Введите тикер инструмента для продажи: ").strip().upper()
        try:
            instrument = current_platform.connected_exchange.get_instrument_by_symbol(symbol)
        except Exception as e:
            print(f"Ошибка: {e}")
            return
        try:
            quantity = float(input("Введите количество: "))
            price = float(input("Введите цену: "))
        except ValueError:
            print("Неверный формат числа!")
            return

        if quantity <= 0:
            print("Количество должно быть положительным числом!")
            return
        if price <= 0:
            print("Цена должна быть положительной!")
            return

        trader1.sell(current_broker, instrument, quantity, price)
        print("Заявка на продажу размещена.")

    def sell_instrument_t2():
        symbol = input("Введите тикер инструмента для продажи: ").strip().upper()
        try:
            instrument = current_platform.connected_exchange.get_instrument_by_symbol(symbol)
        except Exception as e:
            print(f"Ошибка: {e}")
            return
        try:
            quantity = float(input("Введите количество: "))
            price = float(input("Введите цену: "))
        except ValueError:
            print("Неверный формат числа!")
            return

        if quantity <= 0:
            print("Количество должно быть положительным числом!")
            return
        if price <= 0:
            print("Цена должна быть положительной!")
            return

        trader2.sell(current_broker, instrument, quantity, price)
        print("Заявка на продажу размещена.")


    def generate_report_t1():
        current_platform.generate_report(trader1)

    def generate_report_t2():
        current_platform.generate_report(trader2)

    def select_broker():
        nonlocal current_broker
        print("Выберите брокера:")
        print(f"1. {broker1.broker_id} (Комиссия: {broker1.commission_rate * 100}%)")
        print(f"2. {broker2.broker_id} (Комиссия: {broker2.commission_rate * 100}%)")
        broker_choice = input("Введите номер брокера (1-2): ").strip()
        if broker_choice == "1":
            current_broker = broker1
            print(f"Выбран брокер {broker1.broker_id}.")
        elif broker_choice == "2":
            current_broker = broker2
            print(f"Выбран брокер {broker2.broker_id}.")
        else:
            print("Неверный выбор, попробуйте снова.")

    def switch_platform():
        nonlocal current_platform 
        print("Выберите торговую платформу:")
        print(f"1. {platform1.indices[0].name}")
        print(f"2. {platform2.indices[0].name}")
        platform_choice = input("Введите номер платформы (1-2): ").strip()
        if platform_choice == "1":
            current_platform = platform1
            print(f"Выбрана платформа {current_platform.indices[0].name}.")
        elif platform_choice == "2":
            current_platform = platform2
            print(f"Выбрана платформа {current_platform.indices[0].name}.")
        else:
            print("Неверный выбор, попробуйте снова.")

    def exit_program():
        print("Выход из программы.")
        sys.exit(0)

    actions = {
        "1": display_market_data,
        "2": buy_instrument_t1,
        "3": buy_instrument_t2,
        "4": sell_instrument_t1,
        "5": sell_instrument_t2,
        "6": generate_report_t1,
        "7": generate_report_t2,
        "8": select_broker,
        "9": switch_platform,
        "10": exit_program,
    }

    while True:
        print("\n--- Trading Platform ---")
        print(f"Текущая платформа: {current_platform.indices[0].name}")
        print("1. Отобразить рыночные данные")
        print("2. Купить инструмент (T1)")
        print("3. Купить инструмент (T2)")
        print("4. Продать инструмент (T1)")
        print("5. Продать инструмент (T2)")
        print("6. Сгенерировать отчёт трейдера (T1)")
        print("7. Сгенерировать отчёт трейдера (T2)")
        print("8. Выбрать брокера")
        print("9. Сменить торговую платформу")
        print("10. Выход")
        choice = input("Введите свой выбор (1-10): ").strip()

        action = actions.get(choice)
        if action:
            action()
        else:
            print("Неверный выбор, попробуйте снова.")


if __name__ == "__main__":
    main()