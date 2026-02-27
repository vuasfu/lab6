#include "task1.h"
#include "task2.h"
#include "task3.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <limits>
#include <locale>
#include <cctype>

namespace {

// Вспомогательная функция для очистки буфера ввода
void ClearInput() {
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Вспомогательная функция для удаления пробелов из строки
std::string TrimString(const std::string& str) {
  size_t start = str.find_first_not_of(" \t");
  if (start == std::string::npos) {
    return "";
  }
  size_t end = str.find_last_not_of(" \t");
  return str.substr(start, end - start + 1);
}

void SolveTask1() {
  std::cout << "\nЗАДАНИЕ 1\n";

  // Ввод перечня всех игр
  GameCollection<std::string> all_games;
  std::cout << "Введите количество игр в перечне: ";
  int game_count;
  std::cin >> game_count;
  ClearInput();

  std::cout << "Введите названия игр (каждое на новой строке):\n";
  for (int i = 0; i < game_count; ++i) {
    std::string game;
    std::getline(std::cin, game);
    game = TrimString(game);
    if (!game.empty()) {
      all_games.Add(game);
    } else {
      std::cout << "Пустое название, пропускаем...\n";
      --i;
    }
  }

  std::cout << "\nПеречень всех игр: ";
  all_games.Print();

  // Ввод информации о студентах
  std::cout << "\nВведите количество студентов в группе: ";
  int student_count;
  std::cin >> student_count;
  ClearInput();

  std::vector<GameCollection<std::string>> student_games;

  for (int i = 0; i < student_count; ++i) {
    std::cout << "\nСтудент" << i + 1 << " ---\n";
    std::cout << "Сколько игр играет этот студент? ";
    int games_per_student;
    std::cin >> games_per_student;
    ClearInput();

    GameCollection<std::string> student;
    std::cout << "Введите игры, в которые играет студент:\n";
    for (int j = 0; j < games_per_student; ++j) {
      std::string game;
      std::getline(std::cin, game);
      game = TrimString(game);
      if (!game.empty()) {
        student.Add(game);
      } else {
        std::cout << "Пустое название, пропускаем...\n";
        --j;
      }
    }
    student_games.push_back(student);
  }

  // Вывод введенных данных
  std::cout << "\nВВЕДЕННЫЕ ДАННЫЕ\n";
  std::cout << "Все игры: ";
  all_games.Print();
  std::cout << "\nИгры студентов:\n";
  for (size_t i = 0; i < student_games.size(); ++i) {
    std::cout << "Студент " << i + 1 << ": ";
    student_games[i].Print();
  }

  if (student_games.empty()) {
    std::cout << "\nНет студентов для анализа!\n";
    return;
  }

  // Находим игры, в которые играют ВСЕ студенты
  GameCollection<std::string> all_students_games = student_games[0];
  for (size_t i = 1; i < student_games.size(); ++i) {
    all_students_games = all_students_games.Intersect(student_games[i]);
  }

  // Находим игры, в которые играют НЕКОТОРЫЕ студенты
  GameCollection<std::string> some_students_games;
  for (const auto& student : student_games) {
    some_students_games = some_students_games.Union(student);
  }

  // Находим игры, в которые НЕ ИГРАЕТ ни один студент
  GameCollection<std::string> no_students_games = all_games.Except(some_students_games);

  std::cout << "\nРЕЗУЛЬТАТЫ\n";
  std::cout << "Игры, в которые играют ВСЕ студенты: ";
  if (all_students_games.GetAllElements().empty()) {
    std::cout << "[] (нет таких игр)\n";
  } else {
    all_students_games.Print();
  }

  std::cout << "Игры, в которые играют НЕКОТОРЫЕ студенты: ";
  some_students_games.Print();

  std::cout << "Игры, в которые НЕ ИГРАЕТ ни один студент: ";
  if (no_students_games.GetAllElements().empty()) {
    std::cout << "[] (все игры популярны)\n";
  } else {
    no_students_games.Print();
  }
}

// ЗАДАНИЕ 2
void SolveTask2() {
  std::cout << "\nЗАДАНИЕ 2\n";

  std::ifstream input_file("participants.txt");
  if (!input_file.is_open()) {
    std::cout << "Ошибка: не удалось открыть файл participants.txt\n";
    std::cout << "Создайте файл participants.txt в формате:\n";
    std::cout << "N\n";
    std::cout << "Фамилия Имя балл1 балл2 балл3\n";
    std::cout << "...\n";
    return;
  }

  int num_participants;
  input_file >> num_participants;
  input_file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  std::cout << "Количество участников: " << num_participants << "\n\n";

  Dictionary<std::string, int> participants;
  int max_score = -1;
  Dictionary<std::string, int> max_participants;

  for (int i = 0; i < num_participants; ++i) {
    std::string line;
    std::getline(input_file, line);

    if (line.empty()) {
      --i;
      continue;
    }

    std::istringstream iss(line);
    std::string last_name, first_name;
    int score1, score2, score3;

    if (!(iss >> last_name >> first_name >> score1 >> score2 >> score3)) {
      std::cout << "Ошибка в формате строки: " << line << "\n";
      continue;
    }

    std::string full_name = last_name + " " + first_name;
    int total_score = score1 + score2 + score3;

    participants.Add(full_name, total_score);
    std::cout << "Участник: " << full_name << " - "
              << score1 << " " << score2 << " " << score3
              << " (всего: " << total_score << ")\n";

    if (total_score > max_score) {
      max_score = total_score;
      max_participants = Dictionary<std::string, int>();
      max_participants.Add(full_name, total_score);
    } else if (total_score == max_score) {
      max_participants.Add(full_name, total_score);
    }
  }

  input_file.close();

  std::cout << "\nРЕЗУЛЬТАТЫ\n";
  if (max_score == -1) {
    std::cout << "Нет данных об участниках\n";
    return;
  }

  std::cout << "Максимальное количество баллов: " << max_score << "\n";
  std::cout << "Победители олимпиады:\n";

  auto keys = max_participants.GetAllKeys();
  for (const auto& key : keys) {
    int* score = max_participants.Get(key);
    std::cout << "  " << key << " - " << *score << " баллов\n";
  }
}

void SolveTask3() {
  std::cout << "\nЗАДАНИЕ 3\n";

  std::cout << "Сколько людей добавить? ";
  int count;
  std::cin >> count;
  ClearInput();

  if (count <= 0) {
    std::cout << "Некорректное количество!\n";
    return;
  }

  std::vector<PersonWithBirthday> people;

  for (int i = 0; i < count; ++i) {
    std::cout << "\n--- Человек " << i + 1 << " ---\n";

    std::string name;
    int height, day, month, year;

    std::cout << "Введите ФИО: ";
    std::getline(std::cin, name);

    std::cout << "Введите рост (см): ";
    std::cin >> height;

    std::cout << "Введите дату рождения (день месяц год через пробел): ";
    std::cin >> day >> month >> year;
    ClearInput();

    // Базовая проверка даты
    if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1900 || year > 2026) {
      std::cout << "Предупреждение: возможно, введена некорректная дата. Продолжаем...\n";
    }

    people.emplace_back(name, height, day, month, year);
  }

  std::cout << "\n========== ИНФОРМАЦИЯ О ЛЮДЯХ ==========\n";
  for (size_t i = 0; i < people.size(); ++i) {
    std::cout << "\n" << i + 1 << ". " << people[i].GetName() 
          << ", рост: " << people[i].GetHeight()
          << "\n";
    std::cout << "   Дата рождения: " << people[i].GetDay() << "."
          << people[i].GetMonth() << "." << people[i].GetYear() << "\n";
    std::cout << "   Возраст: " << people[i].GetAge() << " лет\n";
    std::cout << "   Знак зодиака: " << people[i].GetZodiacSign() << "\n";
  }

  if (people.size() > 1) {
    std::cout << "\nСТАТИСТИКА\n";

    int max_age = -1;
    int min_age = 200;
    std::string oldest;
    std::string youngest;

    for (const auto& person : people) {
      int age = person.GetAge();
      if (age > max_age) {
        max_age = age;
        oldest = person.print();
      }
      if (age < min_age) {
        min_age = age;
        youngest = person.print();
      }
    }

    std::cout << "Самый старший: " << oldest << " (" << max_age << " лет)\n";
    std::cout << "Самый младший: " << youngest << " (" << min_age << " лет)\n";
  }
}

}  

int main() {
  try {
    std::locale::global(std::locale(""));
    std::cout.imbue(std::locale());
    std::cin.imbue(std::locale());
    std::cerr.imbue(std::locale());
  } catch (...) {
  }

  std::cout << "ЛАБОРАТОРНАЯ РАБОТА\n";

  int choice;
  do {
    std::cout << "\nВыберите действие:\n";
    std::cout << "1 - Задание 1 (игры студентов) - ручной ввод\n";
    std::cout << "2 - Задание 2 (олимпиада) - из файла\n";
    std::cout << "3 - Задание 3 (люди с датами) - ручной ввод\n";
    std::cout << "0 - Выход\n";
    std::cout << "Ваш выбор: ";

    std::cin >> choice;

    switch (choice) {
      case 1:
        SolveTask1();
        break;
      case 2:
        SolveTask2();
        break;
      case 3:
        SolveTask3();
        break;
      case 0:
        std::cout << "Программа завершена.\n";
        break;
      default:
        std::cout << "Неверный выбор. Попробуйте снова.\n";
        ClearInput();
    }
  } while (choice != 0);

  return 0;
}