#ifndef ACCESS_DEMO_H_
#define ACCESS_DEMO_H_

#include <cstdint>
#include <string>

#include "Person.h"

// 2.	Варіант 1 - public-наслідування: public та protected члени Person зберігають свій рівень доступу.
// 1.	Разом з успадкованими від Person/Employee/Barber тощо полями клас містить понад 8 полів.
class PublicAccessDemo : public Person
{
    std::string inheritance_kind_;

public:
    // 5.	Продемонструвати передачу параметрів конструктору базового класу (не менше 5-ти аргументів);
    // побудувати відповідні об’єкти, а також побудувати конструктор похідного класу, який використовує
    // всі параметри, які вказані в його оголошенні (передача параметрів конструктору базового класу
    // відбувається всередині похідного класу).
    PublicAccessDemo(const std::string& name, uint32_t id,
        const std::string& phone, uint8_t age, const std::string& email,
        const std::string& city);
    // 8.	Визначити в класі деструктор з метою відслідковування входження у блоки програми та виходу з них,
    // для якого визначений об'єкт цього класу.
    ~PublicAccessDemo();

    void DemonstrateAccess() const;
};

// 2.	Варіант 2 - protected-наслідування: public та protected члени Person стають protected.
// 1.	Разом з успадкованими від Person/Employee/Barber тощо полями клас містить понад 8 полів.
class ProtectedAccessDemo : protected Person
{
    std::string inheritance_kind_;

public:
    // 5.	Продемонструвати передачу параметрів конструктору базового класу (не менше 5-ти аргументів);
    // побудувати відповідні об’єкти, а також побудувати конструктор похідного класу, який використовує
    // всі параметри, які вказані в його оголошенні (передача параметрів конструктору базового класу
    // відбувається всередині похідного класу).
    ProtectedAccessDemo(const std::string& name, uint32_t id,
        const std::string& phone, uint8_t age, const std::string& email,
        const std::string& city);
    // 8.	Визначити в класі деструктор з метою відслідковування входження у блоки програми та виходу з них,
    // для якого визначений об'єкт цього класу.
    ~ProtectedAccessDemo();

    // 6.	using повертає окремим членам базового класу рівень доступу public.
    using Person::id_;
    using Person::Introduce;

    void DemonstrateAccess() const;
};

// 2.	Варіант 3 - private-наслідування: усі доступні члени Person стають private у похідному класі.
// 1.	Разом з успадкованими від Person/Employee/Barber тощо полями клас містить понад 8 полів.
class PrivateAccessDemo : private Person
{
    std::string inheritance_kind_;

public:
    // 5.	Продемонструвати передачу параметрів конструктору базового класу (не менше 5-ти аргументів);
    // побудувати відповідні об’єкти, а також побудувати конструктор похідного класу, який використовує
    // всі параметри, які вказані в його оголошенні (передача параметрів конструктору базового класу
    // відбувається всередині похідного класу).
    PrivateAccessDemo(const std::string& name, uint32_t id,
        const std::string& phone, uint8_t age, const std::string& email,
        const std::string& city);
    // 8.	Визначити в класі деструктор з метою відслідковування входження у блоки програми та виходу з них,
    // для якого визначений об'єкт цього класу.
    ~PrivateAccessDemo();

    // 6.	using повертає окремим членам базового класу рівень доступу public.
    using Person::name_;
    using Person::GetAge;

    void DemonstrateAccess() const;
};

#endif  // ACCESS_DEMO_H_
