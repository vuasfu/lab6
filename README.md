<img width="467" height="422" alt="image" src="https://github.com/user-attachments/assets/5c97da5a-4e0a-4447-8eb6-9ce8abca47a5" /># lab6

# ФИО - Булгакова Юлия Олеговна
# Постановка задач
В задании 1 необходимо описать класс, который реализует функционал неупорядоченного списка
(обратиться к элементу по индексу нельзя), который может содержать только уникальные элементы
(в случае добавления повторяющихся значений ошибки нет, такой элемент просто не добавляется).
Полем класса является массив. В классе должны присутствовать методы добавления и удаления
элементов, а также методы:
• Union() — объединяет две коллекции;
• Except() — позволяет удалить из первой коллекции элементы второй;
• Intersect() — получает коллекцию, состоящую из элементов, общих для двух коллекций;
• Contains() — проверяет на наличие элемента, возвращает bool.
С помощью данного класса необходимо решить задачу своего варианта.
В задании 2 необходимо описать класс, который реализует функционал словаря (запрещается
использовать готовые решения) и решить задачу своего варианта. В классе должны присутствовать
методы добавления и удаления элементов, учесть, что ключи должны быть уникальными. Исходные
данные содержаться в текстовом файле.
Классы из заданий 1 и2 должны работать при любом типе данных.
Задание 3 необходимо решить задачу с использованием наследования.

# Задание 1

Реализовать шаблонный класс для хранения коллекции элементов с операциями над множествами.

1. Определить шаблонный класс с полем elements_ (вектор элементов типа T).
2. Реализовать методы Add, Remove, Contains.
3. Реализовать методы Union, Intersect, Except для операций над множествами.
4. Реализовать методы GetAllElements и Print.

Реализация

```cpp
#ifndef TASK1_H_
#define TASK1_H_

#include <vector>
#include <algorithm>
#include <iostream>

template <typename T>
class GameCollection {
 public:
  GameCollection() = default;

  void Add(const T& element);
  void Remove(const T& element);
  bool Contains(const T& element) const;

  GameCollection<T> Union(const GameCollection<T>& other) const;
  GameCollection<T> Intersect(const GameCollection<T>& other) const;
  GameCollection<T> Except(const GameCollection<T>& other) const;

  std::vector<T> GetAllElements() const;
  void Print() const;

 private:
  std::vector<T> elements_;
};

// Проверка наличия элемента
template <typename T>
bool GameCollection<T>::Contains(const T& element) const {
  return std::find(elements_.begin(), elements_.end(), element) != elements_.end();
}

// Добавление элемента (только если его нет)
template <typename T>
void GameCollection<T>::Add(const T& element) {
  if (!Contains(element)) {
    elements_.push_back(element);
  }
}

// Удаление элемента
template <typename T>
void GameCollection<T>::Remove(const T& element) {
  auto it = std::find(elements_.begin(), elements_.end(), element);
  if (it != elements_.end()) {
    elements_.erase(it);
  }
}

// Объединение коллекций
template <typename T>
GameCollection<T> GameCollection<T>::Union(const GameCollection<T>& other) const {
  GameCollection<T> result = *this;
  for (const auto& e : other.elements_) {
    result.Add(e);
  }
  return result;
}

// Пересечение коллекций
template <typename T>
GameCollection<T> GameCollection<T>::Intersect(const GameCollection<T>& other) const {
  GameCollection<T> result;
  for (const auto& e : elements_) {
    if (other.Contains(e)) {
      result.Add(e);
    }
  }
  return result;
}

// Разность коллекций
template <typename T>
GameCollection<T> GameCollection<T>::Except(const GameCollection<T>& other) const {
  GameCollection<T> result;
  for (const auto& e : elements_) {
    if (!other.Contains(e)) {
      result.Add(e);
    }
  }
  return result;
}

// Получение всех элементов
template <typename T>
std::vector<T> GameCollection<T>::GetAllElements() const {
  return elements_;
}

// Вывод коллекции
template <typename T>
void GameCollection<T>::Print() const {
  std::cout << "[";
  for (size_t i = 0; i < elements_.size(); ++i) {
    std::cout << elements_[i];
    if (i < elements_.size() - 1) {
      std::cout << ", ";
    }
  }
  std::cout << "]" << std::endl;
}

#endif
```

# Тестирование
<img width="533" height="672" alt="image" src="https://github.com/user-attachments/assets/82625338-6ab1-4b07-826b-2da1c3acf7c9" />
<img width="529" height="656" alt="image" src="https://github.com/user-attachments/assets/64c668e1-2636-432d-bed8-3e01cad9dde7" />

# Задание 2
Реализовать шаблонный класс словаря для хранения пар ключ-значение.

1. Определить шаблонный класс с двумя параметрами K (ключ) и V (значение).
2. Реализовать метод Add для добавления пары (только если ключ уникален).
3. Реализовать метод Remove для удаления по ключу.
4. Реализовать метод Contains для проверки наличия ключа.
5. Реализовать метод Get для получения значения по ключу (возвращает указатель).
6. Реализовать методы GetAllKeys и PrintAll.

Реализация

```cpp
#ifndef TASK2_H_
#define TASK2_H_

#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>

template <typename K, typename V>
class Dictionary {
 public:
  Dictionary() = default;
  void Add(const K& key, const V& value);
  bool Remove(const K& key);
  bool Contains(const K& key) const;
  V* Get(const K& key);
  std::vector<K> GetAllKeys() const;
  void PrintAll() const;

 private:
  std::vector<std::pair<K, V>> items_;
};

// Проверка наличия ключа
template <typename K, typename V>
bool Dictionary<K, V>::Contains(const K& key) const {
  return std::any_of(items_.begin(), items_.end(),
                     [&key](const std::pair<K, V>& p) { return p.first == key; });
}

// Добавление элемента
template <typename K, typename V>
void Dictionary<K, V>::Add(const K& key, const V& value) {
  if (!Contains(key)) {
    items_.emplace_back(key, value);
  }
}

// Удаление элемента по ключу
template <typename K, typename V>
bool Dictionary<K, V>::Remove(const K& key) {
  auto it = std::find_if(items_.begin(), items_.end(),
                         [&key](const std::pair<K, V>& p) { return p.first == key; });
  if (it != items_.end()) {
    items_.erase(it);
    return true;
  }
  return false;
}

// Получение значения по ключу
template <typename K, typename V>
V* Dictionary<K, V>::Get(const K& key) {
  for (auto& p : items_) {
    if (p.first == key) {
      return &p.second;
    }
  }
  return nullptr;
}

// Получение всех ключей
template <typename K, typename V>
std::vector<K> Dictionary<K, V>::GetAllKeys() const {
  std::vector<K> keys;
  for (const auto& p : items_) {
    keys.push_back(p.first);
  }
  return keys;
}

// Вывод всех элементов
template <typename K, typename V>
void Dictionary<K, V>::PrintAll() const {
  for (const auto& p : items_) {
    std::cout << p.first << " : " << p.second << std::endl;
  }
}

#endif
```

# Тестирование
<img width="266" height="115" alt="image" src="https://github.com/user-attachments/assets/0233aad8-eea5-4cdf-bd6a-e3ced64899fa" />
<img width="334" height="209" alt="image" src="https://github.com/user-attachments/assets/0cf006cf-79e0-4fa2-be1c-93c3057edc34" />

# Задание 3

Реализовать класс человека с датой рождения, наследующий от базового класса Person.

1. Создать базовый класс Person с полями name_ и height_ и методами print, GetName, GetHeight.
2. Создать класс-наследник PersonWithBirthday с дополнительными полями day_, month_, year_.
3. Реализовать метод GetAge для вычисления возраста на основе текущей даты.
4. Реализовать метод GetZodiacSign для определения знака зодиака.
5. Реализовать геттеры для даты рождения.

Реализация

```cpp
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
```

# Тестирование

<img width="471" height="254" alt="image" src="https://github.com/user-attachments/assets/d5b91b02-52ff-442a-9569-60abcc9e8434" />
<img width="467" height="422" alt="image" src="https://github.com/user-attachments/assets/65599d33-1882-4314-88ce-e7a01e98b875" />


