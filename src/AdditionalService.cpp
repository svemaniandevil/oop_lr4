#include "AdditionalService.h"

#include <iostream>

#include "Client.h"

// 5.	Продемонструвати передачу параметрів конструктору базового класу (не менше 5-ти аргументів); побудувати
// відповідні об’єкти, а також побудувати конструктор похідного класу, який використовує всі параметри,
// які вказані в його оголошенні (передача параметрів конструктору базового класу відбувається всередині
// похідного класу).
// 7.	Продемонструвати для усіх класів порядок виклику конструкторів та деструкторів як для простого
// наслідування, так і для множинного.
AdditionalService::AdditionalService(const std::string& service_name,
    const std::string& category, double price, uint16_t duration_minutes,
    double discount_percent, uint32_t service_code)
    : service_name_(service_name),
    category_(category),
    service_price_(price),
    duration_minutes_(duration_minutes),
    discount_percent_(discount_percent),
    is_available_(true),
    times_ordered_(0),
    service_code_(service_code)
{
    std::cout << "[Конструктор] AdditionalService (з параметрами) \""
        << service_name_ << "\", код=" << service_code_ << std::endl;
}

// 7.	Продемонструвати для усіх класів порядок виклику конструкторів та деструкторів як для простого
// наслідування, так і для множинного.
AdditionalService::AdditionalService(const AdditionalService& other)
    : service_name_(other.service_name_),
    category_(other.category_),
    service_price_(other.service_price_),
    duration_minutes_(other.duration_minutes_),
    discount_percent_(other.discount_percent_),
    is_available_(other.is_available_),
    times_ordered_(other.times_ordered_),
    service_code_(other.service_code_)
{
    std::cout << "[Конструктор копіювання] AdditionalService \""
        << service_name_ << "\"" << std::endl;
}

// 7.	Продемонструвати для усіх класів порядок виклику конструкторів та деструкторів як для простого
// наслідування, так і для множинного.
// 8.	Визначити в класі деструктор з метою відслідковування входження у блоки програми та виходу з них, для
// якого визначений об'єкт цього класу.
AdditionalService::~AdditionalService()
{
    std::cout << "[Деструктор] AdditionalService \"" << service_name_
        << "\" виходить з блоку програми." << std::endl;
}

double AdditionalService::GetFinalPrice() const
{
    return service_price_ * (1.0 - discount_percent_ / 100.0);
}

bool AdditionalService::ApplyDiscount(double percent)
{
    if (percent < 0.0 || percent > 50.0)
        return false;
    discount_percent_ = percent;
    return true;
}

void AdditionalService::SetAvailable(bool available)
{
    is_available_ = available;
}

bool AdditionalService::AddToClientOrder(Client& client)
{
    if (!is_available_)
    {
        std::cout << "  Послуга \"" << service_name_ << "\" наразі недоступна."
            << std::endl;
        return false;
    }
    client.AddToOrder(service_name_, GetFinalPrice());
    ++times_ordered_;
    return true;
}

uint16_t AdditionalService::GetTimesOrdered() const { return times_ordered_; }
uint32_t AdditionalService::GetServiceCode() const { return service_code_; }
bool AdditionalService::IsAvailable() const { return is_available_; }

void AdditionalService::DisplayInfo() const
{
    std::cout << "Додаткова послуга \"" << service_name_ << "\" ("
        << category_ << "): " << GetFinalPrice() << " грн, "
        << duration_minutes_ << " хв, знижка " << discount_percent_
        << "%, замовлень: " << times_ordered_ << ", доступна: "
        << (is_available_ ? "так" : "ні") << std::endl;
}
