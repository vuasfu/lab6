#ifndef TASK31_H_
#define TASK31_H_

#include <string>

/// <summary>
/// Базовый класс для представления человека.
/// </summary>
class Person {
  public:
    /// <summary>Конструктор с параметрами.</summary>
    /// <param name="name">Имя человека</param>
    /// <param name="height">Рост в сантиметрах</param>
    Person(const std::string& name, int height);

    /// <summary>Возвращает строковое представление человека.</summary>
    /// <returns>Строка вида "Имя, рост: значение"</returns>
    std::string print() const;

    /// <summary>Возвращает имя человека.</summary>
    /// <returns>Имя</returns>
    std::string GetName() const { return name_; }

    /// <summary>Возвращает рост человека.</summary>
    /// <returns>Рост в сантиметрах</returns>
    int GetHeight() const { return height_; }

  private:
    std::string name_;  ///< Имя человека
    int height_;        ///< Рост в сантиметрах
};

#endif
