#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <Windows.h>

#include "AccessDemo.h"
#include "Barber.h"
#include "BarbershopManager.h"
#include "Cashier.h"
#include "Client.h"
#include "Employee.h"
#include "Global.h"
#include "MultiInheritance.h"
#include "Person.h"

// 10.	Реалізація кожного пункту завдання позначена коментарями "n." у відповідних місцях програми (п.1-8 -
// у класах, п.2-9 - у функціях main нижче).

uint32_t g_total_appointments = 0;
double g_total_revenue = 0.0;
uint16_t g_shops_registered_count = 0;

void DemonstrateAccessControl();
void DemonstratePrivateInheritance();
void DemonstrateSimpleInheritanceOrder();
void DemonstrateMultipleInheritance();
void DemonstrateScopeAndUsing();
void RunBarbershopScenario();
void PrintRandomArray(const std::string& label, int* array, int size);

void InitRandomSeed()
{
    std::srand(static_cast<uint32_t>(std::time(nullptr)));
}

int* GenerateSortedRandomArray(int max_value, int* out_size)
{
    int size = kMinRandomArraySize +
        std::rand() % (kMaxRandomArraySize - kMinRandomArraySize + 1);
    int* array = new int[size];
    for (int i = 0; i < size; ++i)
        array[i] = std::rand() % (max_value + 1);
    std::sort(array, array + size);
    *out_size = size;
    return array;
}

void PrintSeparator(const std::string& title)
{
    std::cout << "\n==== " << title << " ====\n" << std::endl;
}

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    InitRandomSeed();

    PrintSeparator("ПЕРУКАРНЯ: ієрархія класів (ЛР №4)");

    DemonstrateAccessControl();
    DemonstratePrivateInheritance();
    DemonstrateSimpleInheritanceOrder();
    DemonstrateMultipleInheritance();
    DemonstrateScopeAndUsing();

    RunBarbershopScenario();

    PrintSeparator("ГЛОБАЛЬНА СТАТИСТИКА");
    std::cout << "Активних перукарів зараз: " << Barber::GetActiveBarberCount()
        << std::endl;
    std::cout << "Активних клієнтів зараз: " << Client::GetActiveClientCount()
        << std::endl;
    std::cout << "Активних менеджерів зараз: "
        << BarbershopManager::GetActiveManagerCount() << std::endl;
    std::cout << "Всього зареєстровано перукарень: "
        << g_shops_registered_count << std::endl;
    std::cout << "Всього записів прийнято: " << g_total_appointments
        << std::endl;
    std::cout << "Загальна виручка: " << g_total_revenue << " грн"
        << std::endl;

    return 0;
}

// 2.	Продемонструвати керування доступу до членів базового класу (трьох методів та трьох даних) у трьох
// варіантах: public, private, protected, шляхом генерації об’єктів конструкторами.
void DemonstrateAccessControl()
{
    PrintSeparator("Керування доступом до членів базового класу Person");

    // 2.	Три об'єкти створюються конструкторами; кожен наслідує Person по-різному (public / protected /
    // private).
    // 5.	Конструктор похідного класу приймає 6 аргументів і передає їх у конструктор Person(name, id, phone,
    // age, email, city).
    PublicAccessDemo public_obj("Олег Публічний", 301, "+380501110001", 30,
        "oleh@barbershop.ua", "Львів");
    ProtectedAccessDemo protected_obj("Павло Захищений", 302, "+380501110002",
        31, "pavlo@barbershop.ua", "Київ");
    PrivateAccessDemo private_obj("Роман Закритий", 303, "+380501110003", 32,
        "roman@barbershop.ua", "Одеса");

    std::cout << "\n-- Доступ ізсередини похідних класів --" << std::endl;
    public_obj.DemonstrateAccess();
    protected_obj.DemonstrateAccess();
    private_obj.DemonstrateAccess();

    std::cout << "\n-- Доступ ззовні (з main) --" << std::endl;
    std::cout << "public-наслідування:    id_=" << public_obj.id_
        << ", name_=" << public_obj.name_ << ", Introduce(): ";
    public_obj.Introduce();
    // 2.	public_obj.age_ та public_obj.GetContactLine() -- помилка компіляції: protected-члени Person
    // недоступні ззовні.
    // 2.	public_obj.tax_number_ та public_obj.MaskTaxNumber() -- помилка компіляції: private-члени Person
    // недоступні навіть нащадкам.

    std::cout << "protected-наслідування: id_=" << protected_obj.id_
        << " (відкрито через using), Introduce(): ";
    protected_obj.Introduce();
    // 2.	protected_obj.name_ -- помилка компіляції: public-члени Person стали protected.

    std::cout << "private-наслідування:   name_=" << private_obj.name_
        << ", вік=" << static_cast<int>(private_obj.GetAge())
        << " (відкрито через using)" << std::endl;
    // 2.	private_obj.id_ та private_obj.Introduce() -- помилка компіляції: усі члени Person стали private.

    std::cout << "\n-- Виходимо з блоку: деструктори викликаються у зворотному порядку --"
        << std::endl;
}

// 3.	Визначити додатковий похідний клас (подати самостійно по відношенню до варіанту), який демонструє
// закритий спосіб наслідування із створенням об’єктів конструкторами; об’єкти, які оперують методами з
// різних класів ієрархії.
void DemonstratePrivateInheritance()
{
    PrintSeparator("Закрите наслідування: Cashier (private Employee)");

    // 3.	Об'єкти різних класів ієрархії створюються конструкторами й взаємодіють між собою.
    Cashier cashier("Ірина Касова", 501, "+380501110004", 29,
        "iryna@barbershop.ua", "Львів", 1, 2000.0);
    Client client("Петро Платник", 402, "+380671110005", 1500.0, 33, false);
    Barber barber("Юрій Стрижко", 403, "чоловічі стрижки", 250.0, 4.7, 5);

    cashier.StartShift();
    barber.ServeClient(client);
    client.AddToOrder("Віск для укладки", 150.0);
    cashier.AcceptPayment(client);

    barber.DisplayProfile();
    barber.PaySalary();
    cashier.DisplayCashierInfo();
    cashier.Introduce();
    // 3.	cashier.GiveRaise(5.0) та cashier.PaySalary() -- помилка компіляції: Employee є private-базою
    // Cashier.
    cashier.EndShift();

    std::cout << "\n-- Виходимо з блоку --" << std::endl;
}

// 7.	Продемонструвати для усіх класів порядок виклику конструкторів та деструкторів як для простого
// наслідування, так і для множинного.
void DemonstrateSimpleInheritanceOrder()
{
    PrintSeparator("Порядок конструкторів/деструкторів: просте наслідування");

    std::cout << "Person -> Employee -> Barber:" << std::endl;
    {
        Barber barber("Анна Просте", 601, "універсал", 230.0, 4.4, 3);
        std::cout << "  (об'єкт Barber створено, працюємо з ним)" << std::endl;
    }

    std::cout << "\nPerson -> Client:" << std::endl;
    {
        Client client("Клієнт Простий", 602, "+380000000602", 100.0, 40, false);
        std::cout << "  (об'єкт Client створено, працюємо з ним)" << std::endl;
    }

    std::cout << "\nPerson -> Employee -> BarbershopManager:" << std::endl;
    {
        BarbershopManager manager("Проста перукарня", 603, "вул. Проста, 1");
        std::cout << "  (об'єкт BarbershopManager створено, працюємо з ним)"
            << std::endl;
    }
}

// 4.	Побудувати 3 додаткових класів в наявну ієрархію, яка дозволить реалізувати множинне наслідування з
// подальшою побудовою відповідних об’єктів.
// 7.	Продемонструвати для усіх класів порядок виклику конструкторів та деструкторів як для простого
// наслідування, так і для множинного.
void DemonstrateMultipleInheritance()
{
    PrintSeparator("Множинне наслідування: побудова об'єктів та порядок викликів");

    std::cout << "Barber -> WorkSchedule -> ScheduledBarber:" << std::endl;
    {
        ScheduledBarber scheduled("Марта Розклад", 701, "жіночі стрижки", 300.0,
            4.8, 7, 9, 17, 13, 5);
        std::cout << "  (об'єкт створено)" << std::endl;
    }

    std::cout << "\n(Barber -> WorkSchedule -> ScheduledBarber) -> AdditionalService -> FullServiceBarber:"
        << std::endl;
    {
        FullServiceBarber full("Данило Універсал", 702, "універсал", 320.0, 4.9,
            8, "Фарбування", "фарбування", 600.0, 90);
        std::cout << "  (об'єкт створено)" << std::endl;
    }

    std::cout << "\nBarbershopManager -> ProductCatalog -> SalonManager:"
        << std::endl;
    {
        SalonManager salon("Салон \"Еліт\"", 703, "вул. Франка, 5",
            "Догляд за волоссям", "HairPro");
        std::cout << "  (об'єкт створено)" << std::endl;
    }
}

// 6.	Продемонструвати доступ до членів та методів базового класу з похідних класів засобами оператора
// глобального доступу та оператора using.
void DemonstrateScopeAndUsing()
{
    PrintSeparator("Оператор :: та using при доступі до членів базових класів");

    Barber barber("Олексій Область", 801, "чоловічі стрижки", 240.0, 4.6, 4);
    FullServiceBarber full("Софія Універсал", 802, "фарбування", 280.0, 4.9, 6,
        "Масаж голови", "масаж голови", 250.0, 30);

    // 6.	Оператор глобального доступу :: явно вибирає версію методу з потрібного класу ієрархії.
    std::cout << "\nbarber.Person::Introduce():" << std::endl;
    barber.Person::Introduce();
    std::cout << "\nbarber.Employee::Introduce():" << std::endl;
    barber.Employee::Introduce();
    std::cout << "\nbarber.Person::name_ = " << barber.Person::name_
        << ", barber.Employee::position_ = " << barber.Employee::position_
        << std::endl;

    // 6.	Обидві бази FullServiceBarber мають DisplayInfo(): using у класі вибирає AdditionalService, а :: --
    // будь-яку іншу версію.
    std::cout << "\nfull.DisplayInfo() (через using -> AdditionalService):"
        << std::endl;
    full.DisplayInfo();
    std::cout << "\nfull.WorkSchedule::DisplayInfo():" << std::endl;
    full.WorkSchedule::DisplayInfo();
    std::cout << "\nfull.DisplayFullInfo() (усередині викликає ScheduledBarber:: та AdditionalService::):"
        << std::endl;
    full.DisplayFullInfo();

    std::cout << "\n-- Виходимо з блоку --" << std::endl;
}

// 9.	Продемонструвати сценарій функціонування системи на прикладі створення усіх необхідних об’єктів, їх
// функціонування та взаємодії.
void RunBarbershopScenario()
{
    PrintSeparator("СЦЕНАРІЙ: робота перукарні");

    // 9.	Створення усіх необхідних об'єктів: менеджер з каталогом, три перукарі (у т.ч. у динамічній
    // пам'яті), клієнти, касир.
    SalonManager manager("Перукарня \"Гребінець\"", 10, "вул. Городоцька, 10",
        "Догляд за волоссям", "HairPro");
    ScheduledBarber olena("Олена Ковальчук", 1, "жіночі стрижки", 250.0, 4.8, 6);
    FullServiceBarber ihor("Ігор Петренко", 2, "чоловічі стрижки", 200.0, 4.5,
        4, "Фарбування", "фарбування", 500.0, 90);
    Barber* taras = new Barber("Тарас Мельник", 3, "укладка", 220.0, 4.6, 5);
    Client maria("Марія Іванова", 101, "+380501112233", 1500.0, 27, false);
    Client andrii("Андрій Сидоренко", 102, "+380671234567", 900.0, 34, false);
    Client* oksana =
        new Client("Оксана Лисенко", 103, "+380631112233", 300.0, 22, false);
    Cashier cashier("Ірина Касова", 501, "+380501110004", 29,
        "iryna@barbershop.ua", "Львів", 1, 2000.0);

    PrintSeparator("Крок 1: відкриття зміни, реєстрація перукарів, каталоги");
    cashier.StartShift();
    manager.RegisterBarber(olena);
    manager.RegisterBarber(ihor);
    manager.RegisterBarber(*taras);
    olena.AddHairstyle("Каре");
    ihor.AddHairstyle("Андеркат");
    taras->AddHairstyle("Укладка хвилями");
    olena.DisplayCatalog();
    ihor.DisplayCatalog();
    taras->DisplayCatalog();
    manager.AddProduct("Шампунь відновлюючий", 180.0, 10);
    manager.AddProduct("Бальзам-кондиціонер", 210.0, 5);
    manager.AddProduct("Віск для укладки", 150.0, 2);
    manager.ProductCatalog::DisplayInfo();
    ihor.ApplyDiscount(10.0);
    ihor.AdditionalService::DisplayInfo();

    PrintSeparator("Крок 2: бронювання часу з Графіка роботи перукаря");
    olena.BookClient(maria, 10);
    olena.BookClient(andrii, 10);
    olena.BookClient(andrii, olena.GetFirstFreeHour());
    olena.WorkSchedule::DisplayInfo();

    PrintSeparator("Крок 3: менеджер приймає замовлення й формує черги");
    manager.AcceptOrder(maria, olena.id_);
    manager.AcceptOrder(andrii, ihor.id_);
    manager.AcceptOrder(*oksana);
    manager.DisplayQueues();

    PrintSeparator("Крок 4: перукарі обслуговують клієнтів");
    manager.ServeNextClient(olena);
    manager.ServeNextClient(ihor);
    manager.ServeNextClient(*taras);
    olena.ServeClient(maria, "Каре");
    manager.DisplayQueues();

    PrintSeparator("Крок 5: додаткові послуги та продукція додаються до замовлення");
    ihor.AddToClientOrder(andrii);
    manager.SellProductToClient(maria, "Шампунь відновлюючий");
    manager.SellProductToClient(maria, "Бальзам-кондиціонер");
    manager.SellProductToClient(*oksana, "Віск для укладки");
    manager.SellProductToClient(andrii, "Маска для волосся");
    maria.DisplayOrder();
    andrii.DisplayOrder();
    oksana->DisplayOrder();

    PrintSeparator("Крок 6: оплата на касі");
    cashier.AcceptPayment(maria);
    cashier.AcceptPayment(andrii);
    cashier.AcceptPayment(*oksana);
    cashier.EndShift();

    PrintSeparator("Крок 7: підсумки");
    manager.DisplayFullInfo();
    olena.DisplayFullInfo();
    ihor.DisplayFullInfo();
    cashier.DisplayCashierInfo();
    manager.DisplayShiftAdministrator();

    Barber busiest = manager.GetBusiestBarber();
    std::cout << "Найзавантаженіший перукар: " << busiest.name_ << std::endl;
    std::cout << "Місячний дохід перукаря " << olena.name_ << ": "
        << olena.CalculateMonthlyEarnings(30) << " грн" << std::endl;
    EstimateBarberWorkload(&olena);
    ComputeClientLoyaltyScore(&maria);
    maria.DisplayInfo();
    andrii.DisplayInfo();
    oksana->DisplayInfo();

    PrintSeparator("Крок 8: файли та історії");
    maria.SaveToFile("client_1.txt");
    Client loaded_client;
    loaded_client.LoadFromFile("client_1.txt");
    loaded_client.DisplayInfo();
    olena.SaveToFile("barber_1.txt");
    Barber loaded_barber;
    loaded_barber.LoadFromFile("barber_1.txt");
    loaded_barber.DisplayCatalog();

    int history_size = 0;
    int* visit_history = maria.GenerateRandomVisitHistory(&history_size);
    PrintRandomArray("Історія візитів " + maria.name_, visit_history,
        history_size);
    delete[] visit_history;

    delete taras;
    delete oksana;
    std::cout << "\n-- Кінець сценарію: об'єкти у статичній пам'яті знищуються у зворотному порядку --"
        << std::endl;
}

void PrintRandomArray(const std::string& label, int* array, int size)
{
    std::cout << label << " (розмір масиву " << size << "): ";
    for (int i = 0; i < size; ++i)
        std::cout << array[i] << " ";
    std::cout << std::endl;
}
