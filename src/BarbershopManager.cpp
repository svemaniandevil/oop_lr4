#include "BarbershopManager.h"

#include <iostream>

#include "Barber.h"
#include "Client.h"
#include "Global.h"

uint16_t BarbershopManager::active_manager_count_ = 0;

// 5.	Продемонструвати передачу параметрів конструктору базового класу (не менше 5-ти аргументів); побудувати
// відповідні об’єкти, а також побудувати конструктор похідного класу, який використовує всі параметри,
// які вказані в його оголошенні (передача параметрів конструктору базового класу відбувається всередині
// похідного класу).
// 7.	Продемонструвати для усіх класів порядок виклику конструкторів та деструкторів як для простого
// наслідування, так і для множинного.
BarbershopManager::BarbershopManager()
    : Employee("Менеджер", 0, kDefaultPhone, 35, kDefaultEmail, kDefaultCity,
        "менеджер", kDefaultSalary * 1.5, kDefaultHireYear),
    total_orders_accepted_(0),
    is_open_(true),
    max_queue_length_(kDefaultMaxQueueLength),
    shift_administrator_(nullptr),
    manager_code_(9000),
    shops_registered_ref_(g_shops_registered_count),
    shop_name_("Перукарня без назви"),
    address_("(не вказано)")
{
    ++active_manager_count_;
    ++shops_registered_ref_;
    shift_administrator_ = new Client("Черговий адміністратор", manager_code_,
        "внутрішній", 0.0, 25, false);
    std::cout << "[Конструктор] Створено менеджера (без параметрів), код="
        << manager_code_ << std::endl;
}

// 5.	Продемонструвати передачу параметрів конструктору базового класу (не менше 5-ти аргументів); побудувати
// відповідні об’єкти, а також побудувати конструктор похідного класу, який використовує всі параметри,
// які вказані в його оголошенні (передача параметрів конструктору базового класу відбувається всередині
// похідного класу).
// 7.	Продемонструвати для усіх класів порядок виклику конструкторів та деструкторів як для простого
// наслідування, так і для множинного.
BarbershopManager::BarbershopManager(const std::string& shop_name,
    uint32_t manager_id, const std::string& address,
    const std::string& manager_name, const std::string& phone, uint8_t age,
    const std::string& email, const std::string& city)
    : Employee(manager_name, manager_id, phone, age, email, city, "менеджер",
        kDefaultSalary * 1.5, kDefaultHireYear),
    total_orders_accepted_(0),
    is_open_(true),
    max_queue_length_(kDefaultMaxQueueLength),
    shift_administrator_(nullptr),
    manager_code_(manager_id + 9000),
    shops_registered_ref_(g_shops_registered_count),
    shop_name_(shop_name),
    address_(address)
{
    ++active_manager_count_;
    ++shops_registered_ref_;
    shift_administrator_ = new Client("Черговий адміністратор", manager_code_,
        "внутрішній", 0.0, 25, false);
    std::cout << "[Конструктор] Створено менеджера \"" << shop_name_
        << "\", код=" << manager_code_ << std::endl;
}

// 7.	Продемонструвати для усіх класів порядок виклику конструкторів та деструкторів як для простого
// наслідування, так і для множинного.
BarbershopManager::BarbershopManager(const BarbershopManager& other)
    : Employee(other),
    registered_barbers_(other.registered_barbers_),
    client_queues_(other.client_queues_),
    total_orders_accepted_(other.total_orders_accepted_),
    is_open_(other.is_open_),
    max_queue_length_(other.max_queue_length_),
    shift_administrator_(nullptr),
    manager_code_(other.manager_code_),
    shops_registered_ref_(other.shops_registered_ref_),
    shop_name_(other.shop_name_),
    address_(other.address_)
{
    ++active_manager_count_;
    ++shops_registered_ref_;
    if (other.shift_administrator_ != nullptr)
        shift_administrator_ = new Client(*other.shift_administrator_);
    std::cout << "[Конструктор копіювання] Скопійовано менеджера \""
        << shop_name_ << "\", код=" << manager_code_ << std::endl;
}

// 7.	Продемонструвати для усіх класів порядок виклику конструкторів та деструкторів як для простого
// наслідування, так і для множинного.
// 8.	Визначити в класі деструктор з метою відслідковування входження у блоки програми та виходу з них, для
// якого визначений об'єкт цього класу.
BarbershopManager::~BarbershopManager()
{
    std::cout << "[Деструктор] Менеджер \"" << shop_name_ << "\" (код="
        << manager_code_ << ") виходить з блоку програми." << std::endl;
    delete shift_administrator_;
    shift_administrator_ = nullptr;
    registered_barbers_.clear();
    client_queues_.clear();
    --active_manager_count_;
}

uint16_t BarbershopManager::GetActiveManagerCount()
{
    return active_manager_count_;
}

uint32_t BarbershopManager::GetManagerCode() const { return manager_code_; }

void BarbershopManager::DisplayShiftAdministrator() const
{
    if (shift_administrator_ != nullptr)
        std::cout << "  Адміністратор зміни в \"" << shop_name_
        << "\": " << shift_administrator_->name_ << std::endl;
}

void BarbershopManager::RegisterBarber(Barber& barber)
{
    registered_barbers_.push_back(&barber);
    client_queues_.emplace_back();
    std::cout << shop_name_ << ": зареєстровано перукаря " << barber.name_
        << std::endl;
}

int BarbershopManager::FindBarberIndex(uint32_t barber_id) const
{
    for (size_t i = 0; i < registered_barbers_.size(); ++i)
        if (registered_barbers_[i]->id_ == barber_id)
            return (int)i;
    return -1;
}

bool BarbershopManager::AcceptOrder(Client& client)
{
    if (registered_barbers_.empty())
        return false;
    size_t best_index = 0;
    for (size_t i = 1; i < client_queues_.size(); ++i)
        if (client_queues_[i].size() < client_queues_[best_index].size())
            best_index = i;
    client_queues_[best_index].push(&client);
    ++total_orders_accepted_;
    ++g_total_appointments;
    std::cout << client.name_ << " доданий(-а) у чергу до перукаря "
        << registered_barbers_[best_index]->name_ << std::endl;
    return true;
}

bool BarbershopManager::AcceptOrder(Client& client, uint32_t barber_id)
{
    int index = FindBarberIndex(barber_id);
    if (index == -1) {
        std::cout << "Перукаря з ID " << barber_id << " не знайдено." << std::endl;
        return false;
    }
    client_queues_[index].push(&client);
    ++total_orders_accepted_;
    ++g_total_appointments;
    std::cout << client.name_ << " доданий(-а) у чергу до перукаря "
        << registered_barbers_[index]->name_ << std::endl;
    return true;
}

bool BarbershopManager::ServeNextClient(Barber& barber)
{
    int index = FindBarberIndex(barber.id_);
    if (index == -1 || client_queues_[index].empty())
        return false;
    Client* next_client = client_queues_[index].front();
    client_queues_[index].pop();
    barber.ServeClient(*next_client);
    return true;
}

uint16_t BarbershopManager::GetQueueLength(uint32_t barber_id) const
{
    int index = FindBarberIndex(barber_id);
    if (index == -1)
        return -1;
    return static_cast<uint16_t>(client_queues_[index].size());
}

void BarbershopManager::DisplayQueues() const
{
    std::cout << shop_name_ << " (" << address_ << ") -- стан черг:"
        << std::endl;
    for (size_t i = 0; i < registered_barbers_.size(); ++i)
        std::cout << "  " << registered_barbers_[i]->name_ << ": "
        << client_queues_[i].size() << " клієнт(ів) у черзі"
        << std::endl;
}

Barber BarbershopManager::GetBusiestBarber() const
{
    if (registered_barbers_.empty())
        return Barber();
    const Barber* busiest = registered_barbers_.front();
    for (const Barber* barber : registered_barbers_)
        if (barber->GetServedClientsCount() > busiest->GetServedClientsCount())
            busiest = barber;
    return *busiest;
}

uint16_t BarbershopManager::GetTotalOrdersAccepted() const
{
    return total_orders_accepted_;
}

bool BarbershopManager::IsOpen() const { return is_open_; }
void BarbershopManager::SetOpen(bool is_open) { is_open_ = is_open; }
