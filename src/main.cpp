#include <iostream>

#include "hyperloglog.h"

int main()
{

  int initial_bits = 3;
  auto obj = std::make_unique<Hyperloglog>(initial_bits);

  std::vector<std::string> input = {"Rome", "was", "not", "built", "in", "a", "day", "but", "it", "was", "built"};

  auto cardinality = obj->calculateCardinality(input);

  std::cout << "cardinality: " << cardinality << std::endl;

  return 0;
}