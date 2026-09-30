#ifndef CLIENT_H_
#define CLIENT_H_

#include <cstdint>
#include <string>
#include <vector>

#include "Global.h"
#include "Person.h"

class Barber;

// 1.	Визначити ієрархію класів відповідно до варіанта (не менше 8 полів на клас).
class Client : public Person
{
    double balance_;
    uint16_t visit_count_;
    bool is_vip_;
    Barber* assigned_barber_;
    std::vector<std::string> order_items_;
    double order_total_;
    int booked_hour_;
    const uint32_t client_code_;
    double& shop_revenue_ref_;

    static uint16_t active_client_count_;

public:
    Client();
    // 5.	Продемонструвати передачу параметрів конструктору базового класу (не менше 5-ти аргументів);
    // побудувати відповідні об’єкти, а також побудувати конструктор похідного класу, який використовує
    // всі параметри, які вказані в його оголошенні (передача параметрів конструктору базового класу
    // відбувається всередині похідного класу).
    Client(const std::string& name, uint32_t id, const std::string& phone,
        double balance, uint8_t age, bool is_vip,
        const std::string& email = kDefaultEmail,
        const std::string& city = kDefaultCity);
    Client(const Client& other);
    // 8.	Визначити в класі деструктор з метою відслідковування входження у блоки програми та виходу з них,
    // для якого визначений об'єкт цього класу.
    ~Client();

    static uint16_t GetActiveClientCount();

    uint32_t GetClientCode() const;

    void BookAppointment(Barber& barber);
    void BookAppointment(Barber& barber, const std::string& preferred_time);

    bool PayForService(double amount);

    void UpdateVipStatus();

    Client GetOlderClient(const Client& other) const;

    void DisplayInfo() const;

    void AddToOrder(const std::string& item, double price);
    bool PayOrder();
    void DisplayOrder() const;
    double GetOrderTotal() const;
    void SetBookedHour(int hour);
    int GetBookedHour() const;

    void SaveToFile(const std::string& filename) const;
    void LoadFromFile(const std::string& filename);

    int* GenerateRandomVisitHistory(int* out_size) const;

    double GetBalance() const;
    uint16_t GetVisitCount() const;
    bool IsVip() const;
    Barber* GetAssignedBarber() const;
};

double ComputeClientLoyaltyScore(Client client);
double ComputeClientLoyaltyScore(const Client* client);
Client CreateVipClient(const std::string& name, uint32_t id);

#endif  // CLIENT_H_
