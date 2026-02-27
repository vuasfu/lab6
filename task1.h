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