#include "Cashier.h"

#include <iostream>

#include "Client.h"

// 5.	Продемонструвати передачу параметрів конструктору базового класу (не менше 5-ти аргументів); побудувати
// відповідні об’єкти, а також побудувати конструктор похідного класу, який використовує всі параметри,
// які вказані в його оголошенні (передача параметрів конструктору базового класу відбувається всередині
// похідного класу).
// 7.	Продемонструвати для усіх класів порядок виклику конструкторів та деструкторів як для простого
// наслідування, так і для множинного.
Cashier::Cashier(const std::string& name, uint32_t id, const std::string& phone,
    uint8_t age, const std::string& email, const std::string& city,
    uint32_t register_number, double opening_cash)
    : Employee(name, id, phone, age, email, city, "касир",
        kDefaultSalary * 0.9, kDefaultHireYear),
    register_number_(register_number),
    cash_in_register_(opening_cash),
    receipts_issued_(0),
    shift_name_("денна")
{
    std::cout << "[Конструктор] Cashier (private-наслідування від Employee) \""
        << name_ << "\", каса №" << register_number_ << std::endl;
}

// 7.	Продемонструвати для усіх класів порядок виклику конструкторів та деструкторів як для простого
// наслідування, так і для множинного.
Cashier::Cashier(const Cashier& other)
    : Employee(other),
    register_number_(other.register_number_),
    cash_in_register_(other.cash_in_register_),
    receipts_issued_(other.receipts_issued_),
    shift_name_(other.shift_name_)
{
    std::cout << "[Конструктор копіювання] Cashier \"" << name_ << "\""
        << std::endl;
}

// 7.	Продемонструвати для усіх класів порядок виклику конструкторів та деструкторів як для простого
// наслідування, так і для множинного.
// 8.	Визначити в класі деструктор з метою відслідковування входження у блоки програми та виходу з них, для
// якого визначений об'єкт цього класу.
Cashier::~Cashier()
{
    std::cout << "[Деструктор] Cashier \"" << name_
        << "\" виходить з блоку програми." << std::endl;
}

// 3.	Визначити додатковий похідний клас (подати самостійно по відношенню до варіанту), який демонструє
// закритий спосіб наслідування із створенням об’єктів конструкторами; об’єкти, які оперують методами з
// різних класів ієрархії.
bool Cashier::AcceptPayment(Client& client)
{
    double due = client.GetOrderTotal();
    std::cout << name_ << " (каса №" << register_number_
        << ", зміна: " << shift_name_ << ") приймає оплату від "
        << client.name_ << std::endl;
    if (!IsOnShift())
    {
        std::cout << "  Касир не на зміні -- оплату не прийнято." << std::endl;
        return false;
    }
    if (!client.PayOrder())
        return false;
    cash_in_register_ += due;
    ++receipts_issued_;
    std::cout << "  Чек №" << receipts_issued_ << " на " << due
        << " грн видано." << std::endl;
    return true;
}

// 3.	Визначити додатковий похідний клас (подати самостійно по відношенню до варіанту), який демонструє
// закритий спосіб наслідування із створенням об’єктів конструкторами; об’єкти, які оперують методами з
// різних класів ієрархії.
// 6.	Продемонструвати доступ до членів та методів базового класу з похідних класів засобами оператора
// глобального доступу та оператора using.
void Cashier::DisplayCashierInfo() const
{
    Employee::Introduce();
    std::cout << "  Каса №" << register_number_ << ": готівки "
        << cash_in_register_ << " грн, чеків видано: " << receipts_issued_
        << ", ставка касира: " << GetSalary() << " грн" << std::endl;
}

double Cashier::GetCashInRegister() const { return cash_in_register_; }
uint16_t Cashier::GetReceiptsIssued() const { return receipts_issued_; }
