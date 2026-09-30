#include "Employee.h"

#include <iostream>

// 5.	Продемонструвати передачу параметрів конструктору базового класу (не менше 5-ти аргументів); побудувати
// відповідні об’єкти, а також побудувати конструктор похідного класу, який використовує всі параметри,
// які вказані в його оголошенні (передача параметрів конструктору базового класу відбувається всередині
// похідного класу).
// 7.	Продемонструвати для усіх класів порядок виклику конструкторів та деструкторів як для простого
// наслідування, так і для множинного.
Employee::Employee(const std::string& name, uint32_t id,
    const std::string& phone, uint8_t age, const std::string& email,
    const std::string& city, const std::string& position, double salary,
    uint16_t hire_year, uint8_t weekly_hours)
    : Person(name, id, phone, age, email, city),
    position_(position),
    hire_year_(hire_year),
    salary_(salary),
    weekly_hours_(weekly_hours),
    vacation_days_(24),
    employee_code_(id + 2000),
    is_on_shift_(false),
    total_earned_(0.0)
{
    std::cout << "[Конструктор] Employee (з параметрами), посада \""
        << position_ << "\", код=" << employee_code_ << std::endl;
}

// 7.	Продемонструвати для усіх класів порядок виклику конструкторів та деструкторів як для простого
// наслідування, так і для множинного.
Employee::Employee(const Employee& other)
    : Person(other),
    position_(other.position_),
    hire_year_(other.hire_year_),
    salary_(other.salary_),
    weekly_hours_(other.weekly_hours_),
    vacation_days_(other.vacation_days_),
    employee_code_(other.employee_code_),
    is_on_shift_(other.is_on_shift_),
    total_earned_(other.total_earned_)
{
    std::cout << "[Конструктор копіювання] Employee \"" << name_ << "\""
        << std::endl;
}

// 7.	Продемонструвати для усіх класів порядок виклику конструкторів та деструкторів як для простого
// наслідування, так і для множинного.
// 8.	Визначити в класі деструктор з метою відслідковування входження у блоки програми та виходу з них, для
// якого визначений об'єкт цього класу.
Employee::~Employee()
{
    std::cout << "[Деструктор] Employee \"" << name_ << "\" (код="
        << employee_code_ << ") виходить з блоку програми." << std::endl;
}

// 6.	Продемонструвати доступ до членів та методів базового класу з похідних класів засобами оператора
// глобального доступу та оператора using.
void Employee::Introduce() const
{
    Person::Introduce();
    std::cout << "  Працівник: посада " << position_ << ", з " << hire_year_
        << " р., ставка " << salary_ << " грн, "
        << static_cast<int>(weekly_hours_) << " год/тиждень, відпустки: "
        << static_cast<int>(vacation_days_) << " дн., на зміні: "
        << (is_on_shift_ ? "так" : "ні") << std::endl;
}

void Employee::StartShift()
{
    is_on_shift_ = true;
    std::cout << name_ << " (" << position_ << ") почав(-ла) зміну."
        << std::endl;
}

void Employee::EndShift()
{
    is_on_shift_ = false;
    std::cout << name_ << " (" << position_ << ") завершив(-ла) зміну."
        << std::endl;
}

void Employee::PaySalary()
{
    total_earned_ += salary_;
    std::cout << name_ << " отримав(-ла) зарплату " << salary_
        << " грн (всього отримано: " << total_earned_ << " грн)." << std::endl;
}

void Employee::GiveRaise(double percent)
{
    if (percent <= 0.0)
        return;
    salary_ *= 1.0 + percent / 100.0;
    std::cout << name_ << ": підвищення на " << percent
        << "%, нова ставка " << salary_ << " грн." << std::endl;
}

bool Employee::TakeVacation(uint8_t days)
{
    if (days > vacation_days_)
        return false;
    vacation_days_ = static_cast<uint8_t>(vacation_days_ - days);
    return true;
}

double Employee::GetSalary() const { return salary_; }
double Employee::GetTotalEarned() const { return total_earned_; }
bool Employee::IsOnShift() const { return is_on_shift_; }
uint32_t Employee::GetEmployeeCode() const { return employee_code_; }
