#pragma once

#include <string>
#include <optional>

using Number = double;

class Calculator {
public:
    Calculator();

    void Set(Number n);           
    Number GetNumber() const;     

    void Add(Number n);           // Сложение
    void Sub(Number n);           // Вычитание
    void Div(Number n);           // Деление
    void Mul(Number n);           // Умножение
    void Pow(Number n);           // Возведение в степень

    std::string GetNumberRepr() const;

private:
    Number current_number_;
};
