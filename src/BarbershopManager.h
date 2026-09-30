#ifndef BARBERSHOP_MANAGER_H_
#define BARBERSHOP_MANAGER_H_

#include <cstdint>
#include <queue>
#include <string>
#include <vector>

#include "Employee.h"
#include "Global.h"

class Barber;
class Client;

// 1.	Визначити ієрархію класів відповідно до варіанта (не менше 8 полів на клас).
class BarbershopManager : public Employee
{
    std::vector<Barber*> registered_barbers_;
    std::vector<std::queue<Client*>> client_queues_;
    uint16_t total_orders_accepted_;
    bool is_open_;
    uint16_t max_queue_length_;
    Client* shift_administrator_;
    const uint32_t manager_code_;
    uint16_t& shops_registered_ref_;

    static uint16_t active_manager_count_;

    int FindBarberIndex(uint32_t barber_id) const;

public:
    std::string shop_name_;
    std::string address_;

    BarbershopManager();
    // 5.	Продемонструвати передачу параметрів конструктору базового класу (не менше 5-ти аргументів);
    // побудувати відповідні об’єкти, а також побудувати конструктор похідного класу, який використовує
    // всі параметри, які вказані в його оголошенні (передача параметрів конструктору базового класу
    // відбувається всередині похідного класу).
    BarbershopManager(const std::string& shop_name, uint32_t manager_id,
        const std::string& address,
        const std::string& manager_name = "Менеджер",
        const std::string& phone = kDefaultPhone, uint8_t age = 35,
        const std::string& email = kDefaultEmail,
        const std::string& city = kDefaultCity);
    BarbershopManager(const BarbershopManager& other);
    // 8.	Визначити в класі деструктор з метою відслідковування входження у блоки програми та виходу з них,
    // для якого визначений об'єкт цього класу.
    ~BarbershopManager();

    static uint16_t GetActiveManagerCount();

    uint32_t GetManagerCode() const;

    void RegisterBarber(Barber& barber);

    bool AcceptOrder(Client& client);
    bool AcceptOrder(Client& client, uint32_t barber_id);

    void DisplayShiftAdministrator() const;

    bool ServeNextClient(Barber& barber);

    uint16_t GetQueueLength(uint32_t barber_id) const;

    void DisplayQueues() const;

    Barber GetBusiestBarber() const;

    uint16_t GetTotalOrdersAccepted() const;
    bool IsOpen() const;

    void SetOpen(bool is_open);
};

#endif  // BARBERSHOP_MANAGER_H_
