#ifndef TASK31_H_
#define TASK31_H_

#include <string>

class Person {
  public:
    Person(const std::string& name, int height);
    std::string print() const;
    std::string GetName() const { return name_; }
    int GetHeight() const { return height_; }

  private:
    std::string name_;
    int height_;
};

#endif  // TASK1_H_
