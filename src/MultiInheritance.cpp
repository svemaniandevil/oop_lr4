#include "MultiInheritance.h"

#include <iostream>

#include "Client.h"

// 5.	Продемонструвати передачу параметрів конструктору базового класу (не менше 5-ти аргументів); побудувати
// відповідні об’єкти, а також побудувати конструктор похідного класу, який використовує всі параметри,
// які вказані в його оголошенні (передача параметрів конструктору базового класу відбувається всередині
// похідного класу).
// 7.	Продемонструвати для усіх класів порядок виклику конструкторів та деструкторів як для простого
// наслідування, так і для множинного.
ScheduledBarber::ScheduledBarber(const std::string& name, uint32_t id,
    const std::string& specialization, double price_per_cut, double rating,
    uint8_t experience_years, int start_hour, int end_hour, int lunch_hour,
    uint8_t days_per_week)
    : Barber(name, id, specialization, price_per_cut, rating, experience_years),
    WorkSchedule(name, start_hour, end_hour, lunch_hour, days_per_week),
    confirmed_bookings_(0)
{
    std::cout << "[Конструктор] ScheduledBarber \"" << name_ << "\""
        << std::endl;
}

// 7.	Продемонструвати для усіх класів порядок виклику конструкторів та деструкторів як для простого
// наслідування, так і для множинного.
// 8.	Визначити в класі деструктор з метою відслідковування входження у блоки програми та виходу з них, для
// якого визначений об'єкт цього класу.
ScheduledBarber::~ScheduledBarber()
{
    std::cout << "[Деструктор] ScheduledBarber \"" << name_
        << "\" виходить з блоку програми." << std::endl;
}

bool ScheduledBarber::BookClient(Client& client, int hour)
{
    if (!BookSlot(hour, client.name_))
    {
        std::cout << "  Година " << FormatHour(hour) << " у перукаря " << name_
            << " недоступна для " << client.name_ << "." << std::endl;
        return false;
    }
    client.SetBookedHour(hour);
    client.BookAppointment(*this, FormatHour(hour));
    ++confirmed_bookings_;
    return true;
}

// 6.	Продемонструвати доступ до членів та методів базового класу з похідних класів засобами оператора
// глобального доступу та оператора using.
void ScheduledBarber::DisplayFullInfo() const
{
    Barber::DisplayProfile();
    WorkSchedule::DisplayInfo();
    std::cout << "  Підтверджених бронювань через перукаря: "
        << confirmed_bookings_ << std::endl;
}

// 5.	Продемонструвати передачу параметрів конструктору базового класу (не менше 5-ти аргументів); побудувати
// відповідні об’єкти, а також побудувати конструктор похідного класу, який використовує всі параметри,
// які вказані в його оголошенні (передача параметрів конструктору базового класу відбувається всередині
// похідного класу).
// 7.	Продемонструвати для усіх класів порядок виклику конструкторів та деструкторів як для простого
// наслідування, так і для множинного.
FullServiceBarber::FullServiceBarber(const std::string& name, uint32_t id,
    const std::string& specialization, double price_per_cut, double rating,
    uint8_t experience_years, const std::string& service_name,
    const std::string& service_category, double service_price,
    uint16_t duration_minutes)
    : ScheduledBarber(name, id, specialization, price_per_cut, rating,
        experience_years),
    AdditionalService(service_name, service_category, service_price,
        duration_minutes, 0.0, id + 3000),
    combined_orders_(0)
{
    std::cout << "[Конструктор] FullServiceBarber \"" << name_ << "\""
        << std::endl;
}

// 7.	Продемонструвати для усіх класів порядок виклику конструкторів та деструкторів як для простого
// наслідування, так і для множинного.
// 8.	Визначити в класі деструктор з метою відслідковування входження у блоки програми та виходу з них, для
// якого визначений об'єкт цього класу.
FullServiceBarber::~FullServiceBarber()
{
    std::cout << "[Деструктор] FullServiceBarber \"" << name_
        << "\" виходить з блоку програми." << std::endl;
}

bool FullServiceBarber::ServeWithExtraService(Client& client)
{
    ServeClient(client);
    if (AddToClientOrder(client))
    {
        ++combined_orders_;
        return true;
    }
    return false;
}

// 6.	Продемонструвати доступ до членів та методів базового класу з похідних класів засобами оператора
// глобального доступу та оператора using.
void FullServiceBarber::DisplayFullInfo() const
{
    ScheduledBarber::DisplayFullInfo();
    AdditionalService::DisplayInfo();
    std::cout << "  Комбінованих замовлень (стрижка + послуга): "
        << combined_orders_ << std::endl;
}

// 5.	Продемонструвати передачу параметрів конструктору базового класу (не менше 5-ти аргументів); побудувати
// відповідні об’єкти, а також побудувати конструктор похідного класу, який використовує всі параметри,
// які вказані в його оголошенні (передача параметрів конструктору базового класу відбувається всередині
// похідного класу).
// 7.	Продемонструвати для усіх класів порядок виклику конструкторів та деструкторів як для простого
// наслідування, так і для множинного.
SalonManager::SalonManager(const std::string& shop_name, uint32_t manager_id,
    const std::string& address, const std::string& catalog_name,
    const std::string& supplier)
    : BarbershopManager(shop_name, manager_id, address),
    ProductCatalog(catalog_name, supplier),
    products_sold_via_manager_(0)
{
    std::cout << "[Конструктор] SalonManager \"" << shop_name_ << "\""
        << std::endl;
}

// 7.	Продемонструвати для усіх класів порядок виклику конструкторів та деструкторів як для простого
// наслідування, так і для множинного.
// 8.	Визначити в класі деструктор з метою відслідковування входження у блоки програми та виходу з них, для
// якого визначений об'єкт цього класу.
SalonManager::~SalonManager()
{
    std::cout << "[Деструктор] SalonManager \"" << shop_name_
        << "\" виходить з блоку програми." << std::endl;
}

bool SalonManager::SellProductToClient(Client& client,
    const std::string& product_name)
{
    if (!IsOpen())
    {
        std::cout << shop_name_ << " зараз зачинена." << std::endl;
        return false;
    }
    if (SellProduct(product_name, client))
    {
        ++products_sold_via_manager_;
        return true;
    }
    return false;
}

// 6.	Продемонструвати доступ до членів та методів базового класу з похідних класів засобами оператора
// глобального доступу та оператора using.
void SalonManager::DisplayFullInfo() const
{
    DisplayQueues();
    DisplayShiftAdministrator();
    ProductCatalog::DisplayInfo();
    std::cout << "  Товарів продано через менеджера: "
        << products_sold_via_manager_ << std::endl;
}
