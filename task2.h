#ifndef TASK2_H_
#define TASK2_H_

#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>

/// <summary>
/// Шаблонный класс словаря для хранения пар ключ-значение.
/// </summary>
/// <typeparam name="K">Тип ключа</typeparam>
/// <typeparam name="V">Тип значения</typeparam>
template <typename K, typename V>
class Dictionary {
 public:
  /// <summary>Конструктор по умолчанию. Создает пустой словарь.</summary>
  Dictionary() = default;

  /// <summary>Добавляет пару ключ-значение, если ключ уникален.</summary>
  /// <param name="key">Добавляемый ключ</param>
  /// <param name="value">Добавляемое значение</param>
  void Add(const K& key, const V& value);

  /// <summary>Удаляет элемент по ключу.</summary>
  /// <param name="key">Ключ удаляемого элемента</param>
  /// <returns>true если ключ найден и удален, иначе false</returns>
  bool Remove(const K& key);

  /// <summary>Проверяет наличие ключа в словаре.</summary>
  /// <param name="key">Проверяемый ключ</param>
  /// <returns>true если ключ найден, иначе false</returns>
  bool Contains(const K& key) const;

  /// <summary>Получает значение по ключу.</summary>
  /// <param name="key">Искомый ключ</param>
  /// <returns>Указатель на значение или nullptr если ключ не найден</returns>
  V* Get(const K& key);

  /// <summary>Возвращает все ключи словаря.</summary>
  /// <returns>Вектор со всеми ключами</returns>
  std::vector<K> GetAllKeys() const;

  /// <summary>Выводит все элементы словаря в консоль.</summary>
  void PrintAll() const;

 private:
  std::vector<std::pair<K, V>> items_;  ///< Внутреннее хранилище пар ключ-значение
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
