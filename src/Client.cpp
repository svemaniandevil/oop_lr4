#include "Client.h"

#include <fstream>
#include <iostream>

#include "Barber.h"
#include "Global.h"

uint16_t Client::active_client_count_ = 0;

// 5.	Продемонструвати передачу параметрів конструктору базового класу (не менше 5-ти аргументів); побудувати
// відповідні об’єкти, а також побудувати конструктор похідного класу, який використовує всі параметри,
// які вказані в його оголошенні (передача параметрів конструктору базового класу відбувається всередині
// похідного класу).
// 7.	Продемонструвати для усіх класів порядок виклику конструкторів та деструкторів як для простого
// наслідування, так і для множинного.
Client::Client()
    : Person("Гість", 0, "невідомо", 18, kDefaultEmail, kDefaultCity),
    balance_(0.0),
    visit_count_(0),
    is_vip_(false),
    assigned_barber_(nullptr),
    order_total_(0.0),
    booked_hour_(-1),
    client_code_(5000),
    shop_revenue_ref_(g_total_revenue)
{
    ++active_client_count_;
    std::cout << "[Конструктор] Створено клієнта (без параметрів) \"" << name_
        << "\", код=" << client_code_ << std::endl;
}

// 5.	Продемонструвати передачу параметрів конструктору базового класу (не менше 5-ти аргументів); побудувати
// відповідні об’єкти, а також побудувати конструктор похідного класу, який використовує всі параметри,
// які вказані в його оголошенні (передача параметрів конструктору базового класу відбувається всередині
// похідного класу).
// 7.	Продемонструвати для усіх класів порядок виклику конструкторів та деструкторів як для простого
// наслідування, так і для множинного.
Client::Client(const std::string& name, uint32_t id, const std::string& phone,
    double balance, uint8_t age, bool is_vip, const std::string& email,
    const std::string& city)
    : Person(name, id, phone, age, email, city),
    balance_(balance),
    visit_count_(0),
    is_vip_(is_vip),
    assigned_barber_(nullptr),
    order_total_(0.0),
    booked_hour_(-1),
    client_code_(id + 5000),
    shop_revenue_ref_(g_total_revenue)
{
    ++active_client_count_;
    std::cout << "[Конструктор] Створено клієнта (з параметрами) \"" << name_
        << "\", код=" << client_code_ << std::endl;
}

// 7.	Продемонструвати для усіх класів порядок виклику конструкторів та деструкторів як для простого
// наслідування, так і для множинного.
Client::Client(const Client& other)
    : Person(other),
    balance_(other.balance_),
    visit_count_(other.visit_count_),
    is_vip_(other.is_vip_),
    assigned_barber_(other.assigned_barber_),
    order_items_(other.order_items_),
    order_total_(other.order_total_),
    booked_hour_(other.booked_hour_),
    client_code_(other.client_code_),
    shop_revenue_ref_(other.shop_revenue_ref_)
{
    ++active_client_count_;
    std::cout << "[Конструктор копіювання] Скопійовано клієнта \"" << name_
        << "\", код=" << client_code_ << std::endl;
}

// 7.	Продемонструвати для усіх класів порядок виклику конструкторів та деструкторів як для простого
// наслідування, так і для множинного.
// 8.	Визначити в класі деструктор з метою відслідковування входження у блоки програми та виходу з них, для
// якого визначений об'єкт цього класу.
Client::~Client()
{
    std::cout << "[Деструктор] Клієнт \"" << name_ << "\" (код=" << client_code_
        << ") виходить з блоку програми." << std::endl;
    assigned_barber_ = nullptr;
    --active_client_count_;
}

uint16_t Client::GetActiveClientCount() { return active_client_count_; }

uint32_t Client::GetClientCode() const { return client_code_; }

void Client::BookAppointment(Barber& barber)
{
    assigned_barber_ = &barber;
    ++g_total_appointments;
    std::cout << name_ << " записався(-лась) до перукаря " << barber.name_
        << std::endl;
}

void Client::BookAppointment(Barber& barber,
    const std::string& preferred_time)
{
    assigned_barber_ = &barber;
    ++g_total_appointments;
    std::cout << name_ << " записався(-лась) до перукаря " << barber.name_
        << " на " << preferred_time << std::endl;
}

bool Client::PayForService(double amount)
{
    if (balance_ < amount)
        return false;
    balance_ -= amount;
    ++visit_count_;
    return true;
}

void Client::UpdateVipStatus()
{
    if (visit_count_ >= kVipVisitThreshold)
        is_vip_ = true;
}

Client Client::GetOlderClient(const Client& other) const
{
    return (age_ >= other.age_) ? *this : other;
}

// 6.	Продемонструвати доступ до членів та методів базового класу з похідних класів засобами оператора
// глобального доступу та оператора using.
void Client::DisplayInfo() const
{
    Person::Introduce();
    std::cout << "  Клієнт: баланс " << balance_ << " грн, візитів: "
        << visit_count_ << ", VIP: " << (is_vip_ ? "так" : "ні");
    if (booked_hour_ >= 0)
        std::cout << ", заброньована година: " << (booked_hour_ < 10 ? "0" : "")
        << booked_hour_ << ":00";
    if (assigned_barber_ != nullptr)
        std::cout << ", перукар: " << assigned_barber_->name_;
    else
        std::cout << ", перукар: не призначено";
    std::cout << std::endl;
}

void Client::AddToOrder(const std::string& item, double price)
{
    order_items_.push_back(item);
    order_total_ += price;
    std::cout << "  До замовлення " << name_ << " додано: " << item << " ("
        << price << " грн)" << std::endl;
}

bool Client::PayOrder()
{
    if (order_items_.empty())
    {
        std::cout << "  У замовленні клієнта " << name_ << " немає позицій."
            << std::endl;
        return false;
    }
    if (balance_ < order_total_)
    {
        std::cout << "  Недостатньо коштів у клієнта " << name_
            << " для оплати замовлення на " << order_total_ << " грн!"
            << std::endl;
        return false;
    }
    balance_ -= order_total_;
    shop_revenue_ref_ += order_total_;
    std::cout << "  " << name_ << " оплатив(-ла) замовлення на "
        << order_total_ << " грн." << std::endl;
    order_items_.clear();
    order_total_ = 0.0;
    return true;
}

void Client::DisplayOrder() const
{
    std::cout << "Замовлення клієнта " << name_ << ": ";
    if (order_items_.empty())
        std::cout << "порожньо";
    for (const auto& item : order_items_)
        std::cout << "[" << item << "] ";
    std::cout << "-- разом " << order_total_ << " грн" << std::endl;
}

double Client::GetOrderTotal() const { return order_total_; }
void Client::SetBookedHour(int hour) { booked_hour_ = hour; }
int Client::GetBookedHour() const { return booked_hour_; }

void Client::SaveToFile(const std::string& filename) const
{
    std::ofstream out(filename);
    if (!out.is_open())
    {
        std::cerr << "Не вдалося відкрити файл для запису: " << filename
            << std::endl;
        return;
    }
    out << name_ << '\n'
        << id_ << '\n'
        << phone_ << '\n'
        << balance_ << '\n'
        << (int)age_ << '\n'
        << visit_count_ << '\n'
        << is_vip_ << '\n';
}

void Client::LoadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open())
    {
        std::cerr << "Не вдалося відкрити файл для читання: " << filename
            << std::endl;
        return;
    }
    std::getline(in, name_);
    in >> id_;
    in.ignore();
    std::getline(in, phone_);
    int age = 0;
    in >> balance_ >> age >> visit_count_ >> is_vip_;
    age_ = (uint8_t)age;
}

int* Client::GenerateRandomVisitHistory(int* out_size) const
{
    return GenerateSortedRandomArray(visit_count_ * 3 + 10, out_size);
}

double Client::GetBalance() const { return balance_; }
uint16_t Client::GetVisitCount() const { return visit_count_; }
bool Client::IsVip() const { return is_vip_; }
Barber* Client::GetAssignedBarber() const { return assigned_barber_; }

double ComputeClientLoyaltyScore(Client client)
{
    double score = client.GetVisitCount() * 10.0 +
        (client.IsVip() ? 50.0 : 0.0) + client.GetBalance() * 0.01;
    std::cout << "Показник лояльності клієнта " << client.name_
        << " (за об'єктом): " << score << std::endl;
    return score;
}

double ComputeClientLoyaltyScore(const Client* client)
{
    if (client == nullptr)
        return 0.0;
    double score = client->GetVisitCount() * 10.0 +
        (client->IsVip() ? 50.0 : 0.0) + client->GetBalance() * 0.01;
    std::cout << "Показник лояльності клієнта " << client->name_
        << " (за вказівником): " << score << std::endl;
    return score;
}

Client CreateVipClient(const std::string& name, uint32_t id)
{
    Client vip_client(name, id, "невідомо", 5000.0, 30, false);
    for (int i = 0; i < kVipVisitThreshold; ++i)
        vip_client.PayForService(1.0);
    vip_client.UpdateVipStatus();
    return vip_client;
}
