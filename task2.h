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

// Реализация методов

template <typename K, typename V>
bool Dictionary<K, V>::Contains(const K& key) const {
  return std::any_of(items_.begin(), items_.end(),
                     [&key](const std::pair<K, V>& p) { return p.first == key; });
}

template <typename K, typename V>
void Dictionary<K, V>::Add(const K& key, const V& value) {
  if (!Contains(key)) {
    items_.emplace_back(key, value);
  }
}

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

template <typename K, typename V>
V* Dictionary<K, V>::Get(const K& key) {
  for (auto& p : items_) {
    if (p.first == key) {
      return &p.second;
    }
  }
  return nullptr;
}

template <typename K, typename V>
std::vector<K> Dictionary<K, V>::GetAllKeys() const {
  std::vector<K> keys;
  for (const auto& p : items_) {
    keys.push_back(p.first);
  }
  return keys;
}

template <typename K, typename V>
void Dictionary<K, V>::PrintAll() const {
  for (const auto& p : items_) {
    std::cout << p.first << " : " << p.second << std::endl;
  }
}

#endif 