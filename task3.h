#ifndef TASK3_H_
#define TASK3_H_

#include "task31.h"
#include <string>
#include <ctime>

class PersonWithBirthday : public Person {
 public:
  PersonWithBirthday(const std::string& name, int height,
                     int day, int month, int year);
  int GetAge() const;
  std::string GetZodiacSign() const;
  int GetDay() const { return day_; }
  int GetMonth() const { return month_; }
  int GetYear() const { return year_; }

 private:
  int day_;
  int month_;
  int year_;
};

#endif