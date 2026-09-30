#ifndef EMPLOYEE_H_
#define EMPLOYEE_H_

#include <cstdint>
#include <string>

#include "Person.h"

// 1.	Визначити ієрархію класів відповідно до варіанта (не менше 8 полів на клас).
class Employee : public Person
{
public:
    std::string position_;
    uint16_t hire_year_;

protected:
    double salary_;
    uint8_t weekly_hours_;
    uint8_t vacation_days_;

private:
    const uint32_t employee_code_;
    bool is_on_shift_;
    double total_earned_;

public:
    // 5.	Продемонструвати передачу параметрів конструктору базового класу (не менше 5-ти аргументів);
    // побудувати відповідні об’єкти, а також побудувати конструктор похідного класу, який використовує
    // всі параметри, які вказані в його оголошенні (передача параметрів конструктору базового класу
    // відбувається всередині похідного класу).
    Employee(const std::string& name, uint32_t id, const std::string& phone,
        uint8_t age, const std::string& email, const std::string& city,
        const std::string& position, double salary, uint16_t hire_year,
        uint8_t weekly_hours = 40);
    Employee(const Employee& other);
    // 8.	Визначити в класі деструктор з метою відслідковування входження у блоки програми та виходу з них,
    // для якого визначений об'єкт цього класу.
    ~Employee();

    // 6.	Метод Introduce() приховує однойменний метод Person; базовий варіант викликається через
    // Person::Introduce().
    void Introduce() const;

    void StartShift();
    void EndShift();
    void PaySalary();
    void GiveRaise(double percent);
    bool TakeVacation(uint8_t days);

    double GetSalary() const;
    double GetTotalEarned() const;
    bool IsOnShift() const;
    uint32_t GetEmployeeCode() const;
};

#endif  // EMPLOYEE_H_
