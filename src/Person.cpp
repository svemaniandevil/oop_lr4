#include "Person.h"

#include <iostream>

#include "Global.h"

// 7.	Продемонструвати для усіх класів порядок виклику конструкторів та деструкторів як для простого
// наслідування, так і для множинного.
Person::Person()
    : id_(0),
    name_("Невідомий"),
    phone_(kDefaultPhone),
    age_(18),
    email_(kDefaultEmail),
    city_(kDefaultCity),
    registration_date_("2026-09-30"),
    tax_number_("0000000000"),
    private_note_("")
{
    std::cout << "[Конструктор] Person (без параметрів) \"" << name_ << "\""
        << std::endl;
}

// 5.	Продемонструвати передачу параметрів конструктору базового класу (не менше 5-ти аргументів); побудувати
// відповідні об’єкти, а також побудувати конструктор похідного класу, який використовує всі параметри,
// які вказані в його оголошенні (передача параметрів конструктору базового класу відбувається всередині
// похідного класу).
// 7.	Продемонструвати для усіх класів порядок виклику конструкторів та деструкторів як для простого
// наслідування, так і для множинного.
Person::Person(const std::string& name, uint32_t id, const std::string& phone,
    uint8_t age, const std::string& email, const std::string& city,
    const std::string& registration_date, const std::string& tax_number,
    const std::string& private_note)
    : id_(id),
    name_(name),
    phone_(phone),
    age_(age),
    email_(email),
    city_(city),
    registration_date_(registration_date),
    tax_number_(tax_number),
    private_note_(private_note)
{
    std::cout << "[Конструктор] Person (з параметрами) \"" << name_
        << "\", ID=" << id_ << std::endl;
}

// 7.	Продемонструвати для усіх класів порядок виклику конструкторів та деструкторів як для простого
// наслідування, так і для множинного.
Person::Person(const Person& other)
    : id_(other.id_),
    name_(other.name_),
    phone_(other.phone_),
    age_(other.age_),
    email_(other.email_),
    city_(other.city_),
    registration_date_(other.registration_date_),
    tax_number_(other.tax_number_),
    private_note_(other.private_note_)
{
    std::cout << "[Конструктор копіювання] Person \"" << name_ << "\""
        << std::endl;
}

// 7.	Продемонструвати для усіх класів порядок виклику конструкторів та деструкторів як для простого
// наслідування, так і для множинного.
// 8.	Визначити в класі деструктор з метою відслідковування входження у блоки програми та виходу з них, для
// якого визначений об'єкт цього класу.
Person::~Person()
{
    std::cout << "[Деструктор] Person \"" << name_
        << "\" виходить з блоку програми." << std::endl;
}

std::string Person::GetContactLine() const
{
    return "email: " + email_ + ", місто: " + city_;
}

std::string Person::MaskTaxNumber() const
{
    if (tax_number_.size() <= 4)
        return tax_number_;
    return std::string(tax_number_.size() - 4, '*') +
        tax_number_.substr(tax_number_.size() - 4);
}

void Person::Introduce() const
{
    std::cout << "Особа: " << name_ << " (ID " << id_ << "), тел: " << phone_
        << ", вік: " << static_cast<int>(age_) << ", " << GetContactLine()
        << ", ІПН: " << MaskTaxNumber() << ", реєстрація: "
        << registration_date_ << std::endl;
}

uint8_t Person::GetAge() const { return age_; }
std::string Person::GetRegistrationDate() const { return registration_date_; }
std::string Person::GetPrivateNote() const { return private_note_; }
void Person::SetPrivateNote(const std::string& note) { private_note_ = note; }
