#include "task3.h"
#include <ctime>
#include <string>

PersonWithBirthday::PersonWithBirthday(const std::string& name, int height,
                                       int day, int month, int year)
    : Person(name, height), day_(day), month_(month), year_(year) {}

// Вычисление возраста
int PersonWithBirthday::GetAge() const {
  std::time_t t = std::time(nullptr);
  std::tm* now = std::localtime(&t);
  int age = now->tm_year + 1900 - year_;
  if (month_ > now->tm_mon + 1 ||
      (month_ == now->tm_mon + 1 && day_ > now->tm_mday)) {
    age--;
  }
  return age;
}

// Получение знака зодиака
std::string PersonWithBirthday::GetZodiacSign() const {
  // Даты для знаков зодиака
  struct Zodiac {
    int start_day;
    int start_month;
    int end_day;
    int end_month;
    const char* name;
  };

  const Zodiac zodiacs[] = {
      {21, 3, 19, 4, "Овен"}, {20, 4, 20, 5, "Телец"}, {21, 5, 20, 6, "Близнецы"},
      {21, 6, 22, 7, "Рак"}, {23, 7, 22, 8, "Лев"}, {23, 8, 22, 9, "Дева"},
      {23, 9, 22, 10, "Весы"}, {23, 10, 21, 11, "Скорпион"},
      {22, 11, 21, 12, "Стрелец"}, {22, 12, 19, 1, "Козерог"},
      {20, 1, 18, 2, "Водолей"}, {19, 2, 20, 3, "Рыбы"}};

  for (const auto& z : zodiacs) {
    if ((month_ == z.start_month && day_ >= z.start_day) ||
        (month_ == z.end_month && day_ <= z.end_day)) {
      return z.name;
    }
  }
  return "Неизвестно";
}