#include "Decimal.h"
#include <iostream>
#include <Windows.h>

void Compare(Decimal a, Decimal b)
{
	if (a > b)
	{
		std::cout << a << " > " << b << std::endl;
	}
	if (a < b)
	{
		std::cout << a << " < " << b << std::endl;
	}
	if (a == b)
	{
		std::cout << a << " = " << b << std::endl;
	}
}

Decimal Operation(Decimal a, Decimal b)
{
	Decimal result;
	bool menu = true;
	while (menu)
	{
		char choice;
		std::cout << "Выберите арифметическое действие: + - * / ";
		std::cin >> choice;
		switch (choice)
		{
		case '+':
			result = a + b;
			menu = false;
			break;
		case '-':
			result = a - b;
			menu = false;
			break;
		case '*':
			result = a * b;
			menu = false;
			break;
		case '/':
			result = a / b;
			menu = false;
			break;
		default:
			std::cout << "Неверный ввод! " << std::endl;
			menu = true;
			break;
		}
	}
	return result;
}

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	bool flag = true;
	while (flag)
	{
		bool menu = true;
		while (menu)
		{
			Decimal a, b, result;
			char choice;
			std::cout << "Выберите действие с двумя десятичными дробями: 1 - сравнение, 2 - арифметическое действие ";
			std::cin >> choice;
			std::cout << "Введите первое число: "; std::cin >> a;
			std::cout << "Введите второе число: "; std::cin >> b;
			switch (choice)
			{
			case '1':
				Compare(a, b);
				menu = false;
				break;
			case '2':
				result = Operation(a, b);
				std::cout << "Результат: " << result << std::endl;
				menu = false;
				break;
			default:
				std::cout << "Неверный ввод! " << std::endl;
				menu = true;
				break;
			}
		}

		char choice;
		bool label = true;
		while (label)
		{
			std::cout << "Желаете начать заново или выйти? 1 - заново, 2 - выйти ";
			std::cin >> choice;
			switch (choice)
			{
			default:
				std::cout << "Неверный ввод!" << std::endl;
				label = true;
				break;
			case '1':
				flag = true;
				label = false;
				break;
			case '2':
				flag = false;
				label = false;
				break;
			}
		}
	}
}