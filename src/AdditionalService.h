#ifndef ADDITIONAL_SERVICE_H_
#define ADDITIONAL_SERVICE_H_

#include <cstdint>
#include <string>

class Client;

// 4.	Додатковий клас №2 для множинного наслідування - Додаткова послуга (фарбування, укладка, масаж
// голови).
// 1.	Визначити ієрархію класів відповідно до варіанта (не менше 8 полів на клас).
class AdditionalService
{
public:
    std::string service_name_;
    std::string category_;

protected:
    double service_price_;
    uint16_t duration_minutes_;
    double discount_percent_;

private:
    bool is_available_;
    uint16_t times_ordered_;
    const uint32_t service_code_;

public:
    // 5.	Продемонструвати передачу параметрів конструктору базового класу (не менше 5-ти аргументів);
    // побудувати відповідні об’єкти, а також побудувати конструктор похідного класу, який використовує
    // всі параметри, які вказані в його оголошенні (передача параметрів конструктору базового класу
    // відбувається всередині похідного класу).
    AdditionalService(const std::string& service_name,
        const std::string& category, double price, uint16_t duration_minutes,
        double discount_percent = 0.0, uint32_t service_code = 0);
    AdditionalService(const AdditionalService& other);
    // 8.	Визначити в класі деструктор з метою відслідковування входження у блоки програми та виходу з них,
    // для якого визначений об'єкт цього класу.
    ~AdditionalService();

    double GetFinalPrice() const;
    bool ApplyDiscount(double percent);
    void SetAvailable(bool available);
    bool AddToClientOrder(Client& client);

    uint16_t GetTimesOrdered() const;
    uint32_t GetServiceCode() const;
    bool IsAvailable() const;

    void DisplayInfo() const;
};

#endif  // ADDITIONAL_SERVICE_H_
