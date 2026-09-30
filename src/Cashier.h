#ifndef CASHIER_H_
#define CASHIER_H_

#include <cstdint>
#include <string>

#include "Employee.h"

class Client;

// 3.	Додатковий клас (поза варіантом) - Касир перукарні із закритим (private) наслідуванням від Employee.
// 1.	Разом з успадкованими від Person/Employee/Barber тощо полями клас містить понад 8 полів.
class Cashier : private Employee
{
    uint32_t register_number_;
    double cash_in_register_;
    uint16_t receipts_issued_;
    std::string shift_name_;

public:
    // 5.	Продемонструвати передачу параметрів конструктору базового класу (не менше 5-ти аргументів);
    // побудувати відповідні об’єкти, а також побудувати конструктор похідного класу, який використовує
    // всі параметри, які вказані в його оголошенні (передача параметрів конструктору базового класу
    // відбувається всередині похідного класу).
    Cashier(const std::string& name, uint32_t id, const std::string& phone,
        uint8_t age, const std::string& email, const std::string& city,
        uint32_t register_number, double opening_cash = 1000.0);
    Cashier(const Cashier& other);
    // 8.	Визначити в класі деструктор з метою відслідковування входження у блоки програми та виходу з них,
    // для якого визначений об'єкт цього класу.
    ~Cashier();

    // 6.	using відкриває обрані члени закритої бази Employee (та Person) для зовнішнього коду.
    using Employee::Introduce;
    using Employee::StartShift;
    using Employee::EndShift;
    using Employee::name_;

    bool AcceptPayment(Client& client);
    void DisplayCashierInfo() const;
    double GetCashInRegister() const;
    uint16_t GetReceiptsIssued() const;
};

#endif  // CASHIER_H_
