#include "WorkSchedule.h"

#include <cstdio>
#include <iostream>

#include "Global.h"

// 5.	Продемонструвати передачу параметрів конструктору базового класу (не менше 5-ти аргументів); побудувати
// відповідні об’єкти, а також побудувати конструктор похідного класу, який використовує всі параметри,
// які вказані в його оголошенні (передача параметрів конструктору базового класу відбувається всередині
// похідного класу).
// 7.	Продемонструвати для усіх класів порядок виклику конструкторів та деструкторів як для простого
// наслідування, так і для множинного.
WorkSchedule::WorkSchedule(const std::string& owner, int start_hour,
    int end_hour, int lunch_hour, uint8_t days_per_week, bool is_flexible)
    : schedule_owner_(owner),
    days_per_week_(days_per_week),
    start_hour_(start_hour),
    end_hour_(end_hour),
    lunch_hour_(lunch_hour),
    total_bookings_(0),
    is_flexible_(is_flexible)
{
    if (end_hour_ <= start_hour_)
    {
        start_hour_ = kDefaultWorkStartHour;
        end_hour_ = kDefaultWorkEndHour;
    }
    slot_clients_.assign(end_hour_ - start_hour_, "");
    std::cout << "[Конструктор] WorkSchedule (з параметрами) для \""
        << schedule_owner_ << "\": " << FormatHour(start_hour_) << "-"
        << FormatHour(end_hour_) << std::endl;
}

// 7.	Продемонструвати для усіх класів порядок виклику конструкторів та деструкторів як для простого
// наслідування, так і для множинного.
WorkSchedule::WorkSchedule(const WorkSchedule& other)
    : schedule_owner_(other.schedule_owner_),
    days_per_week_(other.days_per_week_),
    start_hour_(other.start_hour_),
    end_hour_(other.end_hour_),
    lunch_hour_(other.lunch_hour_),
    slot_clients_(other.slot_clients_),
    total_bookings_(other.total_bookings_),
    is_flexible_(other.is_flexible_)
{
    std::cout << "[Конструктор копіювання] WorkSchedule для \""
        << schedule_owner_ << "\"" << std::endl;
}

// 7.	Продемонструвати для усіх класів порядок виклику конструкторів та деструкторів як для простого
// наслідування, так і для множинного.
// 8.	Визначити в класі деструктор з метою відслідковування входження у блоки програми та виходу з них, для
// якого визначений об'єкт цього класу.
WorkSchedule::~WorkSchedule()
{
    std::cout << "[Деструктор] WorkSchedule для \"" << schedule_owner_
        << "\" виходить з блоку програми." << std::endl;
}

std::string WorkSchedule::FormatHour(int hour)
{
    char buffer[16];
    std::snprintf(buffer, sizeof(buffer), "%02d:00", hour);
    return buffer;
}

bool WorkSchedule::IsWorkingHour(int hour) const
{
    return hour >= start_hour_ && hour < end_hour_ && hour != lunch_hour_;
}

bool WorkSchedule::IsSlotFree(int hour) const
{
    return IsWorkingHour(hour) && slot_clients_[hour - start_hour_].empty();
}

bool WorkSchedule::BookSlot(int hour, const std::string& client_name)
{
    if (!IsSlotFree(hour))
        return false;
    slot_clients_[hour - start_hour_] = client_name;
    ++total_bookings_;
    return true;
}

bool WorkSchedule::CancelSlot(int hour)
{
    if (!IsWorkingHour(hour) || slot_clients_[hour - start_hour_].empty())
        return false;
    slot_clients_[hour - start_hour_].clear();
    --total_bookings_;
    return true;
}

int WorkSchedule::GetFirstFreeHour() const
{
    for (int hour = start_hour_; hour < end_hour_; ++hour)
        if (IsSlotFree(hour))
            return hour;
    return -1;
}

uint16_t WorkSchedule::GetTotalBookings() const { return total_bookings_; }

void WorkSchedule::DisplayInfo() const
{
    std::cout << "Графік роботи \"" << schedule_owner_ << "\": "
        << FormatHour(start_hour_) << "-" << FormatHour(end_hour_)
        << ", обід о " << FormatHour(lunch_hour_) << ", днів на тиждень: "
        << static_cast<int>(days_per_week_) << ", гнучкий: "
        << (is_flexible_ ? "так" : "ні") << ", бронювань: "
        << total_bookings_ << std::endl;
    std::cout << "  Години: ";
    for (int hour = start_hour_; hour < end_hour_; ++hour)
    {
        std::cout << "[" << FormatHour(hour) << " ";
        if (hour == lunch_hour_)
            std::cout << "обід";
        else if (slot_clients_[hour - start_hour_].empty())
            std::cout << "вільно";
        else
            std::cout << slot_clients_[hour - start_hour_];
        std::cout << "] ";
    }
    std::cout << std::endl;
}
