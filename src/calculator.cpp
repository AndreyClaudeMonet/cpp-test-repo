#include <cmath>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

#include "calculator.h"

bool isNumber(const std::string &s)
{
    std::istringstream iss(s);
    Number d;
    return iss >> d && iss.eof();
}

bool ReadNumber(Number &result)
{

    if (result)
    {
        return true;
    }

    return true;
}

// Возвращает true, если работа завершилась штатно
// командой q. Если из-за ошибки, возвращает false.
bool RunCalculatorCycle()
{
    std::vector<std::string> inputs; // Хранилище строк
    std::string input;

    Number current_value = 0.;
    bool first_value_set =
        false; // Флаг для проверки, установлено ли начальное значение
    bool q_encountered = false; // Флаг для проверки, встречен ли символ q

    bool loaded_flag = false;
    bool exit_flag = false;

    // Читаем строки последовательно
    while (true)
    {
        // Читаем строки до встречи с "q"
        std::getline(std::cin, input);
        if (input.find("q") != std::string::npos)
        {
            inputs.push_back(input); // Добавляем строку с "q" и выходим
            q_encountered = true;
            break;
        }

        // if ((input.find("l")) && input.size() == 1)
        // {
        //     std::cerr << "Error: Memory is empty" << std::endl;
        //     return false;
        // }

        // Читаем строки и проверяем корректность ввода
        std::istringstream iss(input);
        std::string token = "";

        while (iss >> token)
        {
            if (!first_value_set)
            {
                if (isNumber(token))
                {
                    current_value = std::stod(token);
                    first_value_set = true;
                }
                else
                {
                    std::cerr << "Error: Numeric operand expected" << std::endl;
                    return false;
                }
            }
            else if (token == "+" || token == "-" || token == "*" ||
                     token == "**" || token == "/" || token == ":")
            {
                Number num;
                if (!(iss >> num))
                {
                    std::cerr << "Error: Numeric operand expected" << std::endl;
                    return false;
                }
            }
            else if (token == "s")
            {
                loaded_flag = true;
            }
            else if (token == "l")
            {
                if (!loaded_flag)
                {
                    exit_flag = true;
                    break;
                }
            }
            else if (token != "=" && token != "c" && token != "q")
            {
                std::cerr << "Error: Unknown token " << token << std::endl;
                return false;
            }
        }

        inputs.push_back(input);
        if (exit_flag)
        {
            break;
        }
    }

    // Если в введенных строках не было "q" и не взведен флаг выхода
    if (!q_encountered && !exit_flag)
    {
        std::cerr << "Error: No terminating 'q' found" << std::endl;
        return false;
    }

    bool save_flag = false;
    Number number = 0.;

    // Обработка всех строк после ввода "q"
    for (const std::string &line : inputs)
    {
        std::istringstream iss(line);
        std::string token;

        while (iss >> token)
        {
            if (token == "q")
            {
                // Игнорируем q
                continue;
            }

            if (!first_value_set)
            {
                if (isNumber(token))
                {
                    current_value = std::stod(token);
                    first_value_set = true;
                }
            }
            else if (token == "=")
            {
                // Вывод текущего значения
                std::cout << current_value << std::endl;
            }
            else if (token == ":")
            {
                Number num;
                if (!(iss >> num))
                {
                    std::cerr << "Error: Numeric operand expected" << std::endl;
                    return false;
                }
                current_value = num;
            }
            else if (token == "+")
            {
                Number num;
                if (!(iss >> num))
                {
                    std::cerr << "Error: Numeric operand expected" << std::endl;
                    return false;
                }
                current_value += num;
            }
            else if (token == "-")
            {
                Number num;
                if (!(iss >> num))
                {
                    std::cerr << "Error: Numeric operand expected" << std::endl;
                    return false;
                }
                current_value -= num;
            }
            else if (token == "*")
            {
                Number num;
                if (!(iss >> num))
                {
                    std::cerr << "Error: Numeric operand expected" << std::endl;
                    return false;
                }
                current_value *= num;
            }
            else if (token == "**")
            {
                Number num;
                if (!(iss >> num))
                {
                    std::cerr << "Error: Numeric operand expected" << std::endl;
                    return false;
                }
                current_value = std::pow(current_value, num);
            }
            else if (token == "/")
            {
                Number num;
                if (!(iss >> num))
                {
                    std::cerr << "Error: Numeric operand expected" << std::endl;
                    return false;
                }
                if (num == 0)
                {
                    current_value = std::numeric_limits<Number>::infinity();
                }
                else
                {
                    current_value /= num;
                }
            }
            else if (token == "c")
            {
                current_value = 0;
            }
            else if (token == "l")
            {
                if (exit_flag)
                {
                    std::cerr << "Error: Memory is empty" << std::endl;
                    return false;
                }
                if (save_flag)
                {
                    current_value = number;
                }
                else
                {
                    std::cerr << "Error: Memory is empty" << std::endl;
                }
            }
            else if (token == "s")
            {
                number = current_value;
                save_flag = true;
            }
        }
    }

    return true;
}