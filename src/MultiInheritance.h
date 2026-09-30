#ifndef MULTI_INHERITANCE_H_
#define MULTI_INHERITANCE_H_

#include <cstdint>
#include <string>

#include "AdditionalService.h"
#include "Barber.h"
#include "BarbershopManager.h"
#include "Global.h"
#include "ProductCatalog.h"
#include "WorkSchedule.h"

class Client;

// 4.	Множинне наслідування №1: перукар із графіком роботи (Barber + WorkSchedule).
// 1.	Разом з успадкованими від Person/Employee/Barber тощо полями клас містить понад 8 полів.
class ScheduledBarber : public Barber, public WorkSchedule
{
    uint16_t confirmed_bookings_;

public:
    // 5.	Продемонструвати передачу параметрів конструктору базового класу (не менше 5-ти аргументів);
    // побудувати відповідні об’єкти, а також побудувати конструктор похідного класу, який використовує
    // всі параметри, які вказані в його оголошенні (передача параметрів конструктору базового класу
    // відбувається всередині похідного класу).
    ScheduledBarber(const std::string& name, uint32_t id,
        const std::string& specialization, double price_per_cut, double rating,
        uint8_t experience_years, int start_hour = kDefaultWorkStartHour,
        int end_hour = kDefaultWorkEndHour, int lunch_hour = kDefaultLunchHour,
        uint8_t days_per_week = kDefaultWorkDaysPerWeek);
    // 8.	Визначити в класі деструктор з метою відслідковування входження у блоки програми та виходу з них,
    // для якого визначений об'єкт цього класу.
    ~ScheduledBarber();

    bool BookClient(Client& client, int hour);
    void DisplayFullInfo() const;
};

// 4.	Множинне наслідування №2: перукар з графіком та додатковою послугою (ScheduledBarber +
// AdditionalService).
// 1.	Разом з успадкованими від Person/Employee/Barber тощо полями клас містить понад 8 полів.
class FullServiceBarber : public ScheduledBarber, public AdditionalService
{
    uint16_t combined_orders_;

public:
    // 5.	Продемонструвати передачу параметрів конструктору базового класу (не менше 5-ти аргументів);
    // побудувати відповідні об’єкти, а також побудувати конструктор похідного класу, який використовує
    // всі параметри, які вказані в його оголошенні (передача параметрів конструктору базового класу
    // відбувається всередині похідного класу).
    FullServiceBarber(const std::string& name, uint32_t id,
        const std::string& specialization, double price_per_cut, double rating,
        uint8_t experience_years, const std::string& service_name,
        const std::string& service_category, double service_price,
        uint16_t duration_minutes);
    // 8.	Визначити в класі деструктор з метою відслідковування входження у блоки програми та виходу з них,
    // для якого визначений об'єкт цього класу.
    ~FullServiceBarber();

    // 6.	Обидві бази (WorkSchedule та AdditionalService) мають DisplayInfo(); using вибирає версію
    // AdditionalService.
    using AdditionalService::DisplayInfo;

    bool ServeWithExtraService(Client& client);
    void DisplayFullInfo() const;
};

// 4.	Множинне наслідування №3: менеджер із каталогом продукції (BarbershopManager + ProductCatalog).
// 1.	Разом з успадкованими від Person/Employee/Barber тощо полями клас містить понад 8 полів.
class SalonManager : public BarbershopManager, public ProductCatalog
{
    uint16_t products_sold_via_manager_;

public:
    // 5.	Продемонструвати передачу параметрів конструктору базового класу (не менше 5-ти аргументів);
    // побудувати відповідні об’єкти, а також побудувати конструктор похідного класу, який використовує
    // всі параметри, які вказані в його оголошенні (передача параметрів конструктору базового класу
    // відбувається всередині похідного класу).
    SalonManager(const std::string& shop_name, uint32_t manager_id,
        const std::string& address, const std::string& catalog_name,
        const std::string& supplier);
    // 8.	Визначити в класі деструктор з метою відслідковування входження у блоки програми та виходу з них,
    // для якого визначений об'єкт цього класу.
    ~SalonManager();

    bool SellProductToClient(Client& client, const std::string& product_name);
    void DisplayFullInfo() const;
};

#endif  // MULTI_INHERITANCE_H_
