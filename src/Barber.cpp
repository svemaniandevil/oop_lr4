#include "Barber.h"

#include <fstream>
#include <iostream>

#include "Client.h"
#include "Global.h"

uint16_t Barber::active_barber_count_ = 0;

// 5.	Продемонструвати передачу параметрів конструктору базового класу (не менше 5-ти аргументів); побудувати
// відповідні об’єкти, а також побудувати конструктор похідного класу, який використовує всі параметри,
// які вказані в його оголошенні (передача параметрів конструктору базового класу відбувається всередині
// похідного класу).
// 7.	Продемонструвати для усіх класів порядок виклику конструкторів та деструкторів як для простого
// наслідування, так і для множинного.
Barber::Barber()
    : Employee("Невідомий", 0, kDefaultPhone, 30, kDefaultEmail, kDefaultCity,
        "перукар", kDefaultSalary, kDefaultHireYear),
    price_per_cut_(kDefaultPricePerCut),
    rating_(kDefaultRating),
    experience_years_(kDefaultExperienceYears),
    served_clients_count_(0),
    barber_code_(1000),
    total_appointments_ref_(g_total_appointments),
    apprentice_(nullptr),
    specialization_("універсал")
{
    hairstyle_catalog_.push_back("Класична стрижка");
    ++active_barber_count_;
    std::cout << "[Конструктор] Створено перукаря (без параметрів) \""
        << name_ << "\", код=" << barber_code_ << std::endl;
}

// 5.	Продемонструвати передачу параметрів конструктору базового класу (не менше 5-ти аргументів); побудувати
// відповідні об’єкти, а також побудувати конструктор похідного класу, який використовує всі параметри,
// які вказані в його оголошенні (передача параметрів конструктору базового класу відбувається всередині
// похідного класу).
// 7.	Продемонструвати для усіх класів порядок виклику конструкторів та деструкторів як для простого
// наслідування, так і для множинного.
Barber::Barber(const std::string& name, uint32_t id,
    const std::string& specialization, double price_per_cut, double rating,
    uint8_t experience_years, const std::string& phone, uint8_t age,
    const std::string& email, const std::string& city)
    : Employee(name, id, phone, age, email, city, "перукар",
        kDefaultSalary + experience_years * 500.0,
        static_cast<uint16_t>(2026 - experience_years)),
    price_per_cut_(kDefaultPricePerCut),
    rating_(kDefaultRating),
    experience_years_(experience_years),
    served_clients_count_(0),
    barber_code_(id + 1000),
    total_appointments_ref_(g_total_appointments),
    apprentice_(nullptr),
    specialization_(specialization)
{
    SetPricePerCut(price_per_cut);
    SetRating(rating);
    hairstyle_catalog_.push_back("Класична стрижка");
    ++active_barber_count_;
    std::cout << "[Конструктор] Створено перукаря (з параметрами) \""
        << name_ << "\", код=" << barber_code_ << std::endl;
}

// 7.	Продемонструвати для усіх класів порядок виклику конструкторів та деструкторів як для простого
// наслідування, так і для множинного.
Barber::Barber(const Barber& other)
    : Employee(other),
    price_per_cut_(other.price_per_cut_),
    rating_(other.rating_),
    experience_years_(other.experience_years_),
    hairstyle_catalog_(other.hairstyle_catalog_),
    served_clients_count_(other.served_clients_count_),
    barber_code_(other.barber_code_),
    total_appointments_ref_(other.total_appointments_ref_),
    apprentice_(nullptr),
    specialization_(other.specialization_)
{
    ++active_barber_count_;
    std::cout << "[Конструктор копіювання] Скопійовано перукаря \"" << name_
        << "\", код=" << barber_code_ << std::endl;
}

// 7.	Продемонструвати для усіх класів порядок виклику конструкторів та деструкторів як для простого
// наслідування, так і для множинного.
// 8.	Визначити в класі деструктор з метою відслідковування входження у блоки програми та виходу з них, для
// якого визначений об'єкт цього класу.
Barber::~Barber()
{
    std::cout << "[Деструктор] Перукар \"" << name_ << "\" (код=" << barber_code_
        << ") виходить з блоку програми." << std::endl;
    delete apprentice_;
    apprentice_ = nullptr;
    --active_barber_count_;
}

uint16_t Barber::GetActiveBarberCount() { return active_barber_count_; }

uint32_t Barber::GetBarberCode() const { return barber_code_; }

void Barber::HireApprentice(const std::string& name, uint32_t id)
{
    delete apprentice_;
    apprentice_ = new Client(name, id, "внутрішній", 0.0, 20, false);
    std::cout << "  Перукар " << name_ << " взяв учня: " << name << std::endl;
}

bool Barber::HasApprentice() const { return apprentice_ != nullptr; }

void Barber::DisplayApprentice() const
{
    if (apprentice_ != nullptr)
        std::cout << "  Учень перукаря " << name_ << ": " << apprentice_->name_
        << std::endl;
    else
        std::cout << "  У перукаря " << name_ << " немає учня." << std::endl;
}

void Barber::AddHairstyle(const std::string& style)
{
    hairstyle_catalog_.push_back(style);
}

void Barber::DisplayCatalog() const
{
    std::cout << "Перукар: " << name_ << " (ID " << id_
        << "), спеціалізація: " << specialization_
        << ", рейтинг: " << rating_ << ", стаж: " << (int)experience_years_
        << " р., обслуговано клієнтів: " << served_clients_count_
        << std::endl;
    std::cout << "  Каталог зачісок: ";
    for (const auto& style : hairstyle_catalog_)
        std::cout << "[" << style << "] ";
    std::cout << std::endl;
}

// 6.	Продемонструвати доступ до членів та методів базового класу з похідних класів засобами оператора
// глобального доступу та оператора using.
void Barber::DisplayProfile() const
{
    Employee::Introduce();
    DisplayCatalog();
}

void Barber::ServeClient(Client& client)
{
    std::string style = hairstyle_catalog_.empty()
        ? "стандартна стрижка"
        : hairstyle_catalog_.front();
    std::cout << client.name_ << " отримує зачіску \"" << style
        << "\" від перукаря " << name_ << std::endl;
    if (client.PayForService(price_per_cut_)) {
        ++served_clients_count_;
        g_total_revenue += price_per_cut_;
        std::cout << "  Оплата " << price_per_cut_ << " грн прийнята."
            << std::endl;
    }
    else
        std::cout << "  Недостатньо коштів у клієнта " << client.name_ << "!"
        << std::endl;
}

void Barber::ServeClient(Client& client, const std::string& chosen_style)
{
    bool found = false;
    for (const auto& style : hairstyle_catalog_)
        if (style == chosen_style)
        {
            found = true;
            break;
        }
    double final_price =
        found ? price_per_cut_ : price_per_cut_ * kNoStyleSurcharge;
    std::cout << client.name_ << " обирає зачіску \"" << chosen_style
        << "\" у перукаря " << name_ << std::endl;
    if (client.PayForService(final_price))
    {
        ++served_clients_count_;
        g_total_revenue += final_price;
        std::cout << "  Оплата " << final_price << " грн прийнята." << std::endl;
    }
    else
        std::cout << "  Недостатньо коштів у клієнта " << client.name_ << "!"
        << std::endl;
}

double Barber::CalculateMonthlyEarnings(uint8_t days_worked) const
{
    double base_income = price_per_cut_ * served_clients_count_;
    double experience_bonus = experience_years_ * 50.0;
    return base_income + experience_bonus * (days_worked / 30.0);
}

Barber Barber::GetBetterBarber(const Barber& other) const
{
    double this_score = rating_ * 10 + experience_years_;
    double other_score = other.rating_ * 10 + other.experience_years_;
    return (this_score >= other_score) ? *this : other;
}

void Barber::SaveToFile(const std::string& filename) const
{
    std::ofstream out(filename);
    if (!out.is_open()) {
        std::cerr << "Не вдалося відкрити файл для запису: " << filename
            << std::endl;
        return;
    }
    out << name_ << '\n'
        << id_ << '\n'
        << specialization_ << '\n'
        << price_per_cut_ << '\n'
        << rating_ << '\n'
        << (int)experience_years_ << '\n'
        << served_clients_count_ << '\n'
        << hairstyle_catalog_.size() << '\n';
    for (const auto& style : hairstyle_catalog_)
        out << style << '\n';
}

void Barber::LoadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cerr << "Не вдалося відкрити файл для читання: " << filename
            << std::endl;
        return;
    }
    size_t catalog_size = 0;
    std::getline(in, name_);
    in >> id_;
    in.ignore();
    std::getline(in, specialization_);
    int experience_years = 0;
    in >> price_per_cut_ >> rating_ >> experience_years >>
        served_clients_count_ >> catalog_size;
    experience_years_ = (uint8_t)experience_years;
    in.ignore();
    hairstyle_catalog_.clear();
    for (size_t i = 0; i < catalog_size; ++i)
    {
        std::string style;
        std::getline(in, style);
        hairstyle_catalog_.push_back(style);
    }
}

int* Barber::GenerateRandomExperienceHistory(int* out_size) const {
    return GenerateSortedRandomArray(experience_years_ * 3 + 1, out_size);
}

double Barber::GetPricePerCut() const { return price_per_cut_; }
double Barber::GetRating() const { return rating_; }
uint8_t Barber::GetExperienceYears() const { return experience_years_; }
uint16_t Barber::GetServedClientsCount() const { return served_clients_count_; }

bool Barber::SetPricePerCut(double price_per_cut)
{
    if (price_per_cut > 0.0)
    {
        price_per_cut_ = price_per_cut;
        return true;
    }
    return false;
}

bool Barber::SetRating(double rating)
{
    if (rating >= 1.0 && rating <= 5.0)
    {
        rating_ = rating;
        return true;
    }
    return false;
}

double EstimateBarberWorkload(Barber barber)
{
    double workload = barber.GetServedClientsCount() * 1.5 +
        barber.GetExperienceYears() * 0.5 + barber.GetRating();
    std::cout << "Навантаження перукаря " << barber.name_
        << " (за об'єктом): " << workload << std::endl;
    return workload;
}

double EstimateBarberWorkload(const Barber* barber)
{
    if (barber == nullptr)
        return 0.0;
    double workload = barber->GetServedClientsCount() * 1.5 +
        barber->GetExperienceYears() * 0.5 + barber->GetRating();
    std::cout << "Навантаження перукаря " << barber->name_
        << " (за вказівником): " << workload << std::endl;
    return workload;
}

Barber CreateSignatureBarber(const std::string& name, uint32_t id)
{
    Barber signature_barber(name, id, "авторський стиль",
        kDefaultPricePerCut * 1.5, 5.0, 10);
    signature_barber.AddHairstyle("Авторська стрижка");
    signature_barber.AddHairstyle("Преміум укладка");
    return signature_barber;
}
