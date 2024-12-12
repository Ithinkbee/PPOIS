#include <iostream>
#include "LongInt.h"

using namespace std;

void printMenu() {
    cout << "\n�������� ��������:\n";
    cout << "1. ������� �����\n";
    cout << "2. ������� ��� �����\n";
    cout << "3. ������� ��� �����\n";
    cout << "4. �������� ��� �����\n";
    cout << "5. ��������� ��� �����\n";
    cout << "6. �������� ��� �����\n";
    cout << "7. �������� ���������� ��������\n";
    cout << "8. ���������/��������� �����\n";
    cout << "0. �����\n";
    cout << "��� �����: ";
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
            cout << "������� �������� �����: ";
            cin >> value;
            num1 = LongInt(value);
            cout << "����� �������: " << num1.to_string() << "\n";
            break;
        }
        case 2: {
            string value;
            cout << "������� ������ �����: ";
            cin >> value;
            num2 = LongInt(value);
            result = num1 + num2;
            cout << "��������� ��������: " << result.to_string() << "\n";
            break;
        }
        case 3: {
            string value;
            cout << "������� ������ �����: ";
            cin >> value;
            num2 = LongInt(value);
            result = num1 - num2;
            cout << "��������� ���������: " << result.to_string() << "\n";
            break;
        }
        case 4: {
            string value;
            cout << "������� ������ �����: ";
            cin >> value;
            num2 = LongInt(value);
            result = num1 * num2;
            cout << "��������� ���������: " << result.to_string() << "\n";
            break;
        }
        case 5: {
            string value;
            cout << "������� ������ �����: ";
            cin >> value;
            num2 = LongInt(value);
            try {
                result = num1 / num2;
                cout << "��������� �������: " << result.to_string() << "\n";
            }
            catch (const exception& e) {
                cout << "������: " << e.what() << "\n";
            }
            break;
        }
        case 6: {
            string value;
            cout << "������� ������ �����: ";
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
            cout << "���������� ��������: " << num1.abs().to_string() << "\n";
            break;
        }
        case 8: {
            int subChoice;
            cout << "1. ��������� (++num1)\n";
            cout << "2. ��������� (--num1)\n";
            cin >> subChoice;
            if (subChoice == 1) {
                ++num1;
                cout << "����� ����������: " << num1.to_string() << "\n";
            }
            else if (subChoice == 2) {
                --num1;
                cout << "����� ����������: " << num1.to_string() << "\n";
            }
            else {
                cout << "�������� �����.\n";
            }
            break;
        }
        case 0:
            cout << "����� �� ���������.\n";
            break;
        default:
            cout << "�������� �����, ���������� �����.\n";
        }
    } while (choice != 0);

    return 0;
}
