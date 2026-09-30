#ifndef PERSON_H_
#define PERSON_H_

#include <cstdint>
#include <string>

// 1.	Визначити ієрархію класів відповідно до варіанта (не менше 8 полів на клас).
class Person
{
    // 2.	Дані та метод рівня public - доступні з будь-якого місця програми.
public:
    uint32_t id_;
    std::string name_;
    std::string phone_;

    void Introduce() const;

    // 2.	Дані та метод рівня protected - доступні лише самому класу та його нащадкам.
protected:
    uint8_t age_;
    std::string email_;
    std::string city_;

    std::string GetContactLine() const;

    // 2.	Дані та метод рівня private - доступні лише всередині самого класу Person.
private:
    std::string registration_date_;
    std::string tax_number_;
    std::string private_note_;

    std::string MaskTaxNumber() const;

public:
    Person();
    // 5.	Продемонструвати передачу параметрів конструктору базового класу (не менше 5-ти аргументів);
    // побудувати відповідні об’єкти, а також побудувати конструктор похідного класу, який використовує
    // всі параметри, які вказані в його оголошенні (передача параметрів конструктору базового класу
    // відбувається всередині похідного класу).
    Person(const std::string& name, uint32_t id, const std::string& phone,
        uint8_t age, const std::string& email, const std::string& city,
        const std::string& registration_date = "2026-09-30",
        const std::string& tax_number = "0000000000",
        const std::string& private_note = "");
    Person(const Person& other);
    // 8.	Визначити в класі деструктор з метою відслідковування входження у блоки програми та виходу з них,
    // для якого визначений об'єкт цього класу.
    virtual ~Person();

    uint8_t GetAge() const;
    std::string GetRegistrationDate() const;
    std::string GetPrivateNote() const;
    void SetPrivateNote(const std::string& note);
};

#endif  // PERSON_H_
