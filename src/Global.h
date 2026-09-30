#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <codecvt>
#include <cstdint>
#include <string>

#define WString(str) std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(str)
#define WriteBinary(stream, data, length) stream.write(reinterpret_cast<const char*>(data), length)
#define WriteBinaryPtr(stream, data, length) stream->write(reinterpret_cast<const char*>(data), length)

constexpr double kDefaultPricePerCut = 450.0;
constexpr double kDefaultRating = 4.0;
constexpr uint8_t kDefaultExperienceYears = 1;
constexpr uint16_t kVipVisitThreshold = 10;
constexpr double kNoStyleSurcharge = 1.2;
constexpr uint16_t kDefaultMaxQueueLength = 10;
constexpr int kMinRandomArraySize = 5;
constexpr int kMaxRandomArraySize = 10;

constexpr double kDefaultSalary = 12000.0;
constexpr uint16_t kDefaultHireYear = 2024;
constexpr int kDefaultWorkStartHour = 9;
constexpr int kDefaultWorkEndHour = 18;
constexpr int kDefaultLunchHour = 13;
constexpr uint8_t kDefaultWorkDaysPerWeek = 5;
constexpr const char* kDefaultPhone = "+380000000000";
constexpr const char* kDefaultEmail = "не вказано";
constexpr const char* kDefaultCity = "Львів";

extern uint32_t g_total_appointments;
extern double g_total_revenue;
extern uint16_t g_shops_registered_count;

void InitRandomSeed();

int* GenerateSortedRandomArray(int max_value, int* out_size);

void PrintSeparator(const std::string& title);

#endif  // GLOBAL_H_
