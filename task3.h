#ifndef TASK3_H_
#define TASK3_H_

#include "task31.h"
#include <string>
#include <ctime>

/// <summary>
/// Класс человека с датой рождения, наследующий от Person.
/// </summary>
class PersonWithBirthday : public Person {
 public:
  /// <summary>Конструктор с параметрами.</summary>
  /// <param name="name">Имя человека</param>
  /// <param name="height">Рост в сантиметрах</param>
  /// <param name="day">День рождения (1-31)</param>
  /// <param name="month">Месяц рождения (1-12)</param>
  /// <param name="year">Год рождения</param>
  PersonWithBirthday(const std::string& name, int height,
                     int day, int month, int year);

  /// <summary>Вычисляет текущий возраст на основе системной даты.</summary>
  /// <returns>Возраст в годах</returns>
  int GetAge() const;

  /// <summary>Определяет знак зодиака по дате рождения.</summary>
  /// <returns>Название знака зодиака</returns>
  std::string GetZodiacSign() const;

  /// <summary>Возвращает день рождения.</summary>
  /// <returns>День месяца</returns>
  int GetDay() const { return day_; }

  /// <summary>Возвращает месяц рождения.</summary>
  /// <returns>Месяц</returns>
  int GetMonth() const { return month_; }

  /// <summary>Возвращает год рождения.</summary>
  /// <returns>Год</returns>
  int GetYear() const { return year_; }

 private:
  int day_;    ///< День рождения
  int month_;  ///< Месяц рождения
  int year_;   ///< Год рождения
};

#endif
