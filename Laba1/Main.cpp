#include <iostream>
#include "LongInt.h"

using namespace std;

void printMenu() {
    cout << "\nВыберите действие:\n";
    cout << "1. Создать число\n";
    cout << "2. Сложить два числа\n";
    cout << "3. Вычесть два числа\n";
    cout << "4. Умножить два числа\n";
    cout << "5. Разделить два числа\n";
    cout << "6. Сравнить два числа\n";
    cout << "7. Показать абсолютное значение\n";
    cout << "8. Инкремент/декремент числа\n";
    cout << "0. Выход\n";
    cout << "Ваш выбор: ";
}

int main() {
    setlocale(LC_ALL, "Russian");
    LongInt num1, num2, result;
    int choice;

    do {
        printMenu();
        cin >> choice;

        switch (choice) {
        case 1: {
            string value;
            cout << "Введите значение числа: ";
            cin >> value;
            num1 = LongInt(value);
            cout << "Число создано: " << num1.to_string() << "\n";
            break;
        }
        case 2: {
            string value;
            cout << "Введите второе число: ";
            cin >> value;
            num2 = LongInt(value);
            result = num1 + num2;
            cout << "Результат сложения: " << result.to_string() << "\n";
            break;
        }
        case 3: {
            string value;
            cout << "Введите второе число: ";
            cin >> value;
            num2 = LongInt(value);
            result = num1 - num2;
            cout << "Результат вычитания: " << result.to_string() << "\n";
            break;
        }
        case 4: {
            string value;
            cout << "Введите второе число: ";
            cin >> value;
            num2 = LongInt(value);
            result = num1 * num2;
            cout << "Результат умножения: " << result.to_string() << "\n";
            break;
        }
        case 5: {
            string value;
            cout << "Введите второе число: ";
            cin >> value;
            num2 = LongInt(value);
            try {
                result = num1 / num2;
                cout << "Результат деления: " << result.to_string() << "\n";
            }
            catch (const exception& e) {
                cout << "Ошибка: " << e.what() << "\n";
            }
            break;
        }
        case 6: {
            string value;
            cout << "Введите второе число: ";
            cin >> value;
            num2 = LongInt(value);
            cout << "num1 == num2: " << (num1 == num2) << "\n";
            cout << "num1 != num2: " << (num1 != num2) << "\n";
            cout << "num1 > num2: " << (num1 > num2) << "\n";
            cout << "num1 < num2: " << (num1 < num2) << "\n";
            cout << "num1 >= num2: " << (num1 >= num2) << "\n";
            cout << "num1 <= num2: " << (num1 <= num2) << "\n";
            break;
        }
        case 7: {
            cout << "Абсолютное значение: " << num1.abs().to_string() << "\n";
            break;
        }
        case 8: {
            int subChoice;
            cout << "1. Инкремент (++num1)\n";
            cout << "2. Декремент (--num1)\n";
            cin >> subChoice;
            if (subChoice == 1) {
                ++num1;
                cout << "После инкремента: " << num1.to_string() << "\n";
            }
            else if (subChoice == 2) {
                --num1;
                cout << "После декремента: " << num1.to_string() << "\n";
            }
            else {
                cout << "Неверный выбор.\n";
            }
            break;
        }
        case 0:
            cout << "Выход из программы.\n";
            break;
        default:
            cout << "Неверный выбор, попробуйте снова.\n";
        }
    } while (choice != 0);

    return 0;
}
