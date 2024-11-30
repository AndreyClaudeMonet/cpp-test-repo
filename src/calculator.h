#pragma once
#include <string>

using Number = double;

bool isNumber(const std::string &s);

// Возвращает true, если удалось прочитать число
// и сохранить его в Number.
bool ReadNumber(Number &result);

// Возвращает true, если работа завершилась штатно
// командой q. Если из-за ошибки, возвращает false.
bool RunCalculatorCycle();