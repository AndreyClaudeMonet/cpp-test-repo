#include "calculator.h"
#include <cmath>

Calculator::Calculator() : current_number_(0) {}

void Calculator::Set(Number n) {
    current_number_ = n;
}

Number Calculator::GetNumber() const {
    return current_number_;
}

void Calculator::Add(Number n) {
    current_number_ += n;
}

void Calculator::Sub(Number n) {
    current_number_ -= n;
}

void Calculator::Div(Number n) {
    if (n != 0) {
        current_number_ /= n;
    }
}

void Calculator::Mul(Number n) {
    current_number_ *= n;
}

void Calculator::Pow(Number n) {
    current_number_ = std::pow(current_number_, n);
}
