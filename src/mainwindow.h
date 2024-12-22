#pragma once

#include <QMainWindow>
#include "calculator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum class Operation {
    NO_OPERATION,
    ADDITION,
    SUBTRACTION,
    MULTIPLICATION,
    DIVISION,
    POWER
};

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    void connectButtons();           // Подключение кнопок к соответствующим слотам
    void appendNumber(const QString& number); // Добавление числа к текущему вводу
    void setOperation(Operation operation);   // Установка текущей операции
    void calculateResult();          // Вычисление результата текущей операции
    void saveToMemory();             // Сохранение числа в память
    void recallFromMemory();         // Загрузка числа из памяти
    void clearMemory();              // Очистка памяти
    void clearCalculator();          // Очистка всех данных калькулятора
    void updateDisplay();            // Обновление отображения результата
    void updateFormulaDisplay();     // Обновление отображения формулы
    void toggleSign();

private:
    Ui::MainWindow* ui;
    Calculator calculator_;          // Объект калькулятора
    Operation current_operation_;    // Текущая операция
    QString input_number_;           // Вводимое число в виде строки
    double active_number_;           // Число, отображаемое в l_result
    double memory_cell_;             // Число, сохранённое в памяти
    bool memory_saved_;              // Флаг: сохранено ли значение в памяти
};
