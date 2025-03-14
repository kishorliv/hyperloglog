#ifndef hyperlog_h
#define hyperlog_h

#include <iostream>
#include <vector>

class Hyperloglog
{
public:
  Hyperloglog(int initialBitsNum) : initialBitsNum_(initialBitsNum), register_(1 << initialBitsNum, 0) {}

  int calculateCardinality(std::vector<std::string> &words)
  {

    for (const std::string &word : words)
    {
      std::uint64_t hash = generateHash(word);
      std::bitset<64> hashBinary = convertToBinary(hash);

      int registerIndex = getRegisterIndex(hashBinary);
      int leftmostOnePosition = getPositionOfLeftmostOne(hashBinary);

      register_[registerIndex] = std::max(register_[registerIndex], leftmostOnePosition);
    }

    double count = calculateCount(register_);

    return std::floor(count);
  }

private:
  int initialBitsNum_;
  std::vector<int> register_;

  std::uint64_t generateHash(const std::string &word)
  {
    return std::hash<std::string>{}(word);
  };

  std::bitset<64> convertToBinary(uint64_t hash)
  {
    return std::bitset<64>(hash);
  };

  int getRegisterIndex(std::bitset<64> hashBinary)
  {
    return (hashBinary >> 61).to_ullong();
  };

  int getPositionOfLeftmostOne(std::bitset<64> hashBinary)
  {
    if (hashBinary.none())
    {
      throw std::runtime_error("Invalid hash: all bits are 0");
    }

    std::string hashStr = hashBinary.to_string();
    int i = initialBitsNum_;

    for (int i = initialBitsNum_; i < hashStr.length(); i++)
    {
      if (hashStr[i] == '1')
      {
        return i + 1 - initialBitsNum_;
      }
    }

    return 0;
  };

  double calculateCount(std::vector<int> bucket)
  {
    double sum = 0;
    int m = 1 << initialBitsNum_;

    for (int val : bucket)
    {
      sum += std::pow(2, -val);
    }

    return (0.79402 * m * m) / sum;
  };
};

#endif