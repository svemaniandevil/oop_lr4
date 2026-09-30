#include "AccessDemo.h"

#include <iostream>

// 5.	Продемонструвати передачу параметрів конструктору базового класу (не менше 5-ти аргументів); побудувати
// відповідні об’єкти, а також побудувати конструктор похідного класу, який використовує всі параметри,
// які вказані в його оголошенні (передача параметрів конструктору базового класу відбувається всередині
// похідного класу).
// 7.	Продемонструвати для усіх класів порядок виклику конструкторів та деструкторів як для простого
// наслідування, так і для множинного.
PublicAccessDemo::PublicAccessDemo(const std::string& name, uint32_t id,
    const std::string& phone, uint8_t age, const std::string& email,
    const std::string& city)
    : Person(name, id, phone, age, email, city),
    inheritance_kind_("public")
{
    std::cout << "[Конструктор] PublicAccessDemo (" << inheritance_kind_
        << "-наслідування) \"" << name_ << "\"" << std::endl;
}

// 7.	Продемонструвати для усіх класів порядок виклику конструкторів та деструкторів як для простого
// наслідування, так і для множинного.
// 8.	Визначити в класі деструктор з метою відслідковування входження у блоки програми та виходу з них, для
// якого визначений об'єкт цього класу.
PublicAccessDemo::~PublicAccessDemo()
{
    std::cout << "[Деструктор] PublicAccessDemo \"" << name_
        << "\" виходить з блоку програми." << std::endl;
}

// 6.	Продемонструвати доступ до членів та методів базового класу з похідних класів засобами оператора
// глобального доступу та оператора using.
void PublicAccessDemo::DemonstrateAccess() const
{
    std::cout << "  Усередині PublicAccessDemo (" << inheritance_kind_
        << "):" << std::endl;
    std::cout << "    дані:  id_ (public)=" << id_
        << ", age_ (protected)=" << static_cast<int>(age_)
        << ", GetRegistrationDate() (доступ до private-даних лише через public-метод)="
        << Person::GetRegistrationDate() << std::endl;
    // 2.	Прямий доступ до private-даних tax_number_ та методу MaskTaxNumber() з похідного класу неможливий.
    std::cout << "    методи: ";
    Person::Introduce();
    std::cout << "            GetContactLine() (protected)=" << GetContactLine()
        << std::endl;
}

// 5.	Продемонструвати передачу параметрів конструктору базового класу (не менше 5-ти аргументів); побудувати
// відповідні об’єкти, а також побудувати конструктор похідного класу, який використовує всі параметри,
// які вказані в його оголошенні (передача параметрів конструктору базового класу відбувається всередині
// похідного класу).
// 7.	Продемонструвати для усіх класів порядок виклику конструкторів та деструкторів як для простого
// наслідування, так і для множинного.
ProtectedAccessDemo::ProtectedAccessDemo(const std::string& name, uint32_t id,
    const std::string& phone, uint8_t age, const std::string& email,
    const std::string& city)
    : Person(name, id, phone, age, email, city),
    inheritance_kind_("protected")
{
    std::cout << "[Конструктор] ProtectedAccessDemo (" << inheritance_kind_
        << "-наслідування) \"" << name_ << "\"" << std::endl;
}

// 7.	Продемонструвати для усіх класів порядок виклику конструкторів та деструкторів як для простого
// наслідування, так і для множинного.
// 8.	Визначити в класі деструктор з метою відслідковування входження у блоки програми та виходу з них, для
// якого визначений об'єкт цього класу.
ProtectedAccessDemo::~ProtectedAccessDemo()
{
    std::cout << "[Деструктор] ProtectedAccessDemo \"" << name_
        << "\" виходить з блоку програми." << std::endl;
}

// 6.	Продемонструвати доступ до членів та методів базового класу з похідних класів засобами оператора
// глобального доступу та оператора using.
void ProtectedAccessDemo::DemonstrateAccess() const
{
    std::cout << "  Усередині ProtectedAccessDemo (" << inheritance_kind_
        << "):" << std::endl;
    std::cout << "    дані:  id_ (public->protected)=" << id_
        << ", age_ (protected)=" << static_cast<int>(age_)
        << ", GetRegistrationDate()=" << Person::GetRegistrationDate()
        << std::endl;
    std::cout << "    методи: ";
    Person::Introduce();
    std::cout << "            GetContactLine() (protected)=" << GetContactLine()
        << std::endl;
}

// 5.	Продемонструвати передачу параметрів конструктору базового класу (не менше 5-ти аргументів); побудувати
// відповідні об’єкти, а також побудувати конструктор похідного класу, який використовує всі параметри,
// які вказані в його оголошенні (передача параметрів конструктору базового класу відбувається всередині
// похідного класу).
// 7.	Продемонструвати для усіх класів порядок виклику конструкторів та деструкторів як для простого
// наслідування, так і для множинного.
PrivateAccessDemo::PrivateAccessDemo(const std::string& name, uint32_t id,
    const std::string& phone, uint8_t age, const std::string& email,
    const std::string& city)
    : Person(name, id, phone, age, email, city),
    inheritance_kind_("private")
{
    std::cout << "[Конструктор] PrivateAccessDemo (" << inheritance_kind_
        << "-наслідування) \"" << name_ << "\"" << std::endl;
}

// 7.	Продемонструвати для усіх класів порядок виклику конструкторів та деструкторів як для простого
// наслідування, так і для множинного.
// 8.	Визначити в класі деструктор з метою відслідковування входження у блоки програми та виходу з них, для
// якого визначений об'єкт цього класу.
PrivateAccessDemo::~PrivateAccessDemo()
{
    std::cout << "[Деструктор] PrivateAccessDemo \"" << name_
        << "\" виходить з блоку програми." << std::endl;
}

// 6.	Продемонструвати доступ до членів та методів базового класу з похідних класів засобами оператора
// глобального доступу та оператора using.
void PrivateAccessDemo::DemonstrateAccess() const
{
    std::cout << "  Усередині PrivateAccessDemo (" << inheritance_kind_
        << "):" << std::endl;
    std::cout << "    дані:  id_ (public->private)=" << id_
        << ", age_ (protected->private)=" << static_cast<int>(age_)
        << ", GetRegistrationDate()=" << Person::GetRegistrationDate()
        << std::endl;
    std::cout << "    методи: ";
    Person::Introduce();
    std::cout << "            GetContactLine() (protected->private)="
        << GetContactLine() << std::endl;
}
