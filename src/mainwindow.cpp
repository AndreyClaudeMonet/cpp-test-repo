#include "mainwindow.h"
#include "calculator.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QString>
#include <iostream>
#include <QRegularExpression>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), current_operation_(Operation::NO_OPERATION),
      input_number_(""), active_number_(0), memory_cell_(0), memory_saved_(false) {
    ui->setupUi(this);
    ui->l_result->setText("0");
    ui->l_memory->setText("");
    ui->l_formula->setText("");

    connectButtons();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::connectButtons() {
    connect(ui->btn_0, &QPushButton::clicked, this, [this]() { appendNumber("0"); });
    connect(ui->btn_1, &QPushButton::clicked, this, [this]() { appendNumber("1"); });
    connect(ui->btn_2, &QPushButton::clicked, this, [this]() { appendNumber("2"); });
    connect(ui->btn_3, &QPushButton::clicked, this, [this]() { appendNumber("3"); });
    connect(ui->btn_4, &QPushButton::clicked, this, [this]() { appendNumber("4"); });
    connect(ui->btn_5, &QPushButton::clicked, this, [this]() { appendNumber("5"); });
    connect(ui->btn_6, &QPushButton::clicked, this, [this]() { appendNumber("6"); });
    connect(ui->btn_7, &QPushButton::clicked, this, [this]() { appendNumber("7"); });
    connect(ui->btn_8, &QPushButton::clicked, this, [this]() { appendNumber("8"); });
    connect(ui->btn_9, &QPushButton::clicked, this, [this]() { appendNumber("9"); });

    connect(ui->btn_plus, &QPushButton::clicked, this, [this]() { setOperation(Operation::ADDITION); });
    connect(ui->btn_minus, &QPushButton::clicked, this, [this]() { setOperation(Operation::SUBTRACTION); });
    connect(ui->btn_multiply, &QPushButton::clicked, this, [this]() { setOperation(Operation::MULTIPLICATION); });
    connect(ui->btn_divide, &QPushButton::clicked, this, [this]() { setOperation(Operation::DIVISION); });
    connect(ui->btn_power, &QPushButton::clicked, this, [this]() { setOperation(Operation::POWER); });
    connect(ui->btn_plus_minus, &QPushButton::clicked, this, &MainWindow::toggleSign);

    connect(ui->btn_equals, &QPushButton::clicked, this, &MainWindow::calculateResult);
    connect(ui->btn_clear, &QPushButton::clicked, this, &MainWindow::clearCalculator);
    connect(ui->btn_memory_save, &QPushButton::clicked, this, &MainWindow::saveToMemory);
    connect(ui->btn_memory_recall, &QPushButton::clicked, this, &MainWindow::recallFromMemory);
    connect(ui->btn_memory_clear, &QPushButton::clicked, this, &MainWindow::clearMemory);
}

void MainWindow::appendNumber(const QString& number) {
    if (input_number_ == "0" && number != ".") {
        input_number_ = number;
    } else {
        input_number_ += number;
    }
    active_number_ = input_number_.toDouble();
    updateDisplay();
}

void MainWindow::setOperation(Operation operation) {
    if (current_operation_ == Operation::NO_OPERATION) {
        calculator_.Set(active_number_);
    }
    current_operation_ = operation;
    input_number_.clear();
    updateFormulaDisplay();
}

void MainWindow::toggleSign() {
    if (!input_number_.isEmpty()) {
        if (input_number_[0] == '-') {
            input_number_.remove(0, 1); // Убираем минус
        } else {
            input_number_.prepend('-'); // Добавляем минус
        }
        active_number_ = input_number_.toDouble();
    } else {
        active_number_ = -active_number_;
    }

    updateDisplay();
}


void MainWindow::calculateResult() {
    if (current_operation_ == Operation::NO_OPERATION) return;

    QString formula = QString::number(static_cast<Number>(calculator_.GetNumber())) + " ";
    switch (current_operation_) {
        case Operation::ADDITION:
            calculator_.Add(active_number_);
            formula += "+ ";
            break;
        case Operation::SUBTRACTION:
            calculator_.Sub(active_number_);
            formula += "− ";
            break;
        case Operation::MULTIPLICATION:
            calculator_.Mul(active_number_);
            formula += "× ";
            break;
        case Operation::DIVISION:
            calculator_.Div(active_number_);
            formula += "÷ ";
            break;
        case Operation::POWER:
            calculator_.Pow(active_number_);
            formula += "^ ";
            break;
        default:
            break;
    }

    formula += QString::number(active_number_) + " =";
    ui->l_formula->setText(formula);

    active_number_ = calculator_.GetNumber();

    input_number_.clear();

    updateDisplay();
    current_operation_ = Operation::NO_OPERATION;
}

void MainWindow::saveToMemory() {
    memory_cell_ = active_number_;
    memory_saved_ = true;
    ui->l_memory->setText("M");
}

void MainWindow::recallFromMemory() {
    if (memory_saved_) {
        active_number_ = memory_cell_;
        updateDisplay();
    }
}

void MainWindow::clearMemory() {
    memory_saved_ = false;
    memory_cell_ = 0;
    ui->l_memory->clear();
}

void MainWindow::clearCalculator() {
    calculator_.Set(0);
    active_number_ = 0;
    input_number_.clear();
    current_operation_ = Operation::NO_OPERATION;
    ui->l_formula->clear();
    updateDisplay();
}

void MainWindow::updateDisplay() {

    if (active_number_ == static_cast<int>(active_number_)) {
        ui->l_result->setText(QString::number(static_cast<int>(active_number_)));
    } else {
        QString result = QString::number(active_number_, 'f', 6);
        result.remove(QRegularExpression("0+$")); // Удаляем нули в конце
        result.remove(QRegularExpression("\\.$")); // Удаляем точку, если она осталась в конце
        ui->l_result->setText(result);
    }

    qDebug() << "Display updated with:" << ui->l_result->text();
}

void MainWindow::updateFormulaDisplay() {
    QString operation;
    switch (current_operation_) {
        case Operation::ADDITION:
            operation = "+";
            break;
        case Operation::SUBTRACTION:
            operation = "−";
            break;
        case Operation::MULTIPLICATION:
            operation = "×";
            break;
        case Operation::DIVISION:
            operation = "÷";
            break;
        case Operation::POWER:
            operation = "^";
            break;
        default:
            break;
    }
    ui->l_formula->setText(QString::number(calculator_.GetNumber()) + " " + operation);
}
