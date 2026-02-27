#ifndef TASK1_H_
#define TASK1_H_

#include <vector>
#include <algorithm>
#include <iostream>

/// <summary>
/// Шаблонный класс для хранения коллекции элементов с операциями над множествами.
/// </summary>
/// <typeparam name="T">Тип элементов коллекции</typeparam>
template <typename T>
class GameCollection {
 public:
  /// <summary>Конструктор по умолчанию. Создает пустую коллекцию.</summary>
  GameCollection() = default;

  /// <summary>Добавляет элемент в коллекцию, если его еще нет.</summary>
  /// <param name="element">Добавляемый элемент</param>
  void Add(const T& element);

  /// <summary>Удаляет элемент из коллекции, если он существует.</summary>
  /// <param name="element">Удаляемый элемент</param>
  void Remove(const T& element);

  /// <summary>Проверяет наличие элемента в коллекции.</summary>
  /// <param name="element">Проверяемый элемент</param>
  /// <returns>true если элемент найден, иначе false</returns>
  bool Contains(const T& element) const;

  /// <summary>Возвращает объединение текущей коллекции с другой.</summary>
  /// <param name="other">Другая коллекция</param>
  /// <returns>Новая коллекция, содержащая элементы из обеих</returns>
  GameCollection<T> Union(const GameCollection<T>& other) const;

  /// <summary>Возвращает пересечение текущей коллекции с другой.</summary>
  /// <param name="other">Другая коллекция</param>
  /// <returns>Новая коллекция с элементами, присутствующими в обеих</returns>
  GameCollection<T> Intersect(const GameCollection<T>& other) const;

  /// <summary>Возвращает разность текущей коллекции и другой.</summary>
  /// <param name="other">Другая коллекция</param>
  /// <returns>Новая коллекция с элементами, которые есть только в текущей</returns>
  GameCollection<T> Except(const GameCollection<T>& other) const;

  /// <summary>Возвращает все элементы коллекции.</summary>
  /// <returns>Вектор со всеми элементами</returns>
  std::vector<T> GetAllElements() const;

  /// <summary>Выводит коллекцию в консоль в формате [элемент1, элемент2, ...]</summary>
  void Print() const;

 private:
  std::vector<T> elements_;  ///< Внутреннее хранилище элементов
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
