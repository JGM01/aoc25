
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <expected>
#include <string>
#include <vector>

#include "utils.hpp"

long part1(std::string input) {

  long result = 0;

  std::vector<std::string> ranges = split(input, ",");

  // 500-2000
  for (const std::string range : ranges) {

    // [500, 2000]
    std::vector<std::string> x = split(range, "-");
    long a = std::stol(x[0]);
    long b = std::stol(x[1]);

    if (numDigitsStupidVersion(a) % 2 == 0 ||
        numDigitsStupidVersion(b) % 2 == 0) {

      while (a <= b) {
        if (numDigitsStupidVersion(a) % 2 == 0) {
          std::string a_str = std::to_string(a);

          if (a_str.substr(0, a_str.length() / 2) ==
              a_str.substr(a_str.length() / 2)) {

            result += a;
          }
        }
        a++;
      }
    }
  }
  return result;
}

long part2(std::string input) {
  long result = 0;

  std::vector<std::string> ranges = split(input, ",");

  // 500-2000
  for (const std::string range : ranges) {

    // [500, 2000]
    std::vector<std::string> x = split(range, "-");
    long num = std::stol(x[0]);
    long end = std::stol(x[1]);

    while (num <= end) {
      std::string numStr = std::to_string(num);

      int windowSize = numStr.length() / 2;
      bool foundInvalid = false;

      while (windowSize >= 1) {
        int l = 0;
        std::string potentiallyRepeatingString = numStr.substr(l, windowSize);
        while (l < numStr.length()) {
          l += windowSize;

          if (numStr.substr(l, windowSize) != potentiallyRepeatingString)
            break;

          if (l + windowSize == numStr.length()) {
            result += num;
            foundInvalid = true;
            break;
          }
        }

        if (foundInvalid)
          break;

        windowSize--;
      }
      num++;
    }
  }
  return result;
}

int main() {

  auto input = f2str("id2");

  if (input.has_value())
    printf("%s\n", input.value().c_str());
  else {
    switch (input.error()) {
    case file_error::file_open:
      perror("File open error :(");
      break;
    case file_error::file_size:
      perror("File size error :(");
      break;
    case file_error::allocation:
      perror("Buffer allocation error :(");
      break;
    case file_error::file_read:
      perror("File read error :(");
      break;
    }
  }

  long result1 = part1(input.value());
  long result2 = part2(input.value());

  printf("%ld\n", result1);
  printf("%ld\n", result2);

  return EXIT_SUCCESS;
}
