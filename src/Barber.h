#ifndef BARBER_H_
#define BARBER_H_

#include <cstdint>
#include <string>
#include <vector>

#include "Employee.h"
#include "Global.h"

class Client;

// 1.	Визначити ієрархію класів відповідно до варіанта (не менше 8 полів на клас).
class Barber : public Employee
{
    double price_per_cut_;
    double rating_;
    uint8_t experience_years_;
    std::vector<std::string> hairstyle_catalog_;
    uint16_t served_clients_count_;
    const uint32_t barber_code_;
    uint32_t& total_appointments_ref_;
    Client* apprentice_;

    static uint16_t active_barber_count_;

public:
    std::string specialization_;

    Barber();
    // 5.	Продемонструвати передачу параметрів конструктору базового класу (не менше 5-ти аргументів);
    // побудувати відповідні об’єкти, а також побудувати конструктор похідного класу, який використовує
    // всі параметри, які вказані в його оголошенні (передача параметрів конструктору базового класу
    // відбувається всередині похідного класу).
    Barber(const std::string& name, uint32_t id,
        const std::string& specialization, double price_per_cut, double rating,
        uint8_t experience_years, const std::string& phone = kDefaultPhone,
        uint8_t age = 30, const std::string& email = kDefaultEmail,
        const std::string& city = kDefaultCity);
    Barber(const Barber& other);
    // 8.	Визначити в класі деструктор з метою відслідковування входження у блоки програми та виходу з них,
    // для якого визначений об'єкт цього класу.
    ~Barber();

    static uint16_t GetActiveBarberCount();

    uint32_t GetBarberCode() const;

    void HireApprentice(const std::string& name, uint32_t id);
    bool HasApprentice() const;
    void DisplayApprentice() const;

    void AddHairstyle(const std::string& style);

    void DisplayCatalog() const;
    void DisplayProfile() const;

    void ServeClient(Client& client);
    void ServeClient(Client& client, const std::string& chosen_style);

    double CalculateMonthlyEarnings(uint8_t days_worked) const;

    Barber GetBetterBarber(const Barber& other) const;

    void SaveToFile(const std::string& filename) const;
    void LoadFromFile(const std::string& filename);

    int* GenerateRandomExperienceHistory(int* out_size) const;

    double GetPricePerCut() const;
    double GetRating() const;
    uint8_t GetExperienceYears() const;
    uint16_t GetServedClientsCount() const;

    bool SetPricePerCut(double price_per_cut);
    bool SetRating(double rating);
};

double EstimateBarberWorkload(Barber barber);
double EstimateBarberWorkload(const Barber* barber);
Barber CreateSignatureBarber(const std::string& name, uint32_t id);

#endif  // BARBER_H_
