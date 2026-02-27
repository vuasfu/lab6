#include "task31.h"

// Конструктор с инициализатором списка
Person::Person(const std::string& name, int height)
    : name_(name), height_(height) {}

// Метод, возвращающий текстовое представление
std::string Person::print() const {
  return name_ + ", рост: " + std::to_string(height_);
}
