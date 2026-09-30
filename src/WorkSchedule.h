#ifndef WORK_SCHEDULE_H_
#define WORK_SCHEDULE_H_

#include <cstdint>
#include <string>
#include <vector>

// 4.	Додатковий клас №1 для множинного наслідування - Графік роботи перукаря.
// 1.	Визначити ієрархію класів відповідно до варіанта (не менше 8 полів на клас).
class WorkSchedule
{
public:
    std::string schedule_owner_;
    uint8_t days_per_week_;

protected:
    int start_hour_;
    int end_hour_;
    int lunch_hour_;

private:
    std::vector<std::string> slot_clients_;
    uint16_t total_bookings_;
    bool is_flexible_;

public:
    // 5.	Продемонструвати передачу параметрів конструктору базового класу (не менше 5-ти аргументів);
    // побудувати відповідні об’єкти, а також побудувати конструктор похідного класу, який використовує
    // всі параметри, які вказані в його оголошенні (передача параметрів конструктору базового класу
    // відбувається всередині похідного класу).
    WorkSchedule(const std::string& owner, int start_hour, int end_hour,
        int lunch_hour, uint8_t days_per_week, bool is_flexible = false);
    WorkSchedule(const WorkSchedule& other);
    // 8.	Визначити в класі деструктор з метою відслідковування входження у блоки програми та виходу з них,
    // для якого визначений об'єкт цього класу.
    ~WorkSchedule();

    static std::string FormatHour(int hour);

    bool IsWorkingHour(int hour) const;
    bool IsSlotFree(int hour) const;
    bool BookSlot(int hour, const std::string& client_name);
    bool CancelSlot(int hour);
    int GetFirstFreeHour() const;
    uint16_t GetTotalBookings() const;

    void DisplayInfo() const;
};

#endif  // WORK_SCHEDULE_H_
