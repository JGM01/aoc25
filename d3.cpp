#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <expected>
#include <string>
#include <vector>

#include "utils.hpp"
//               v
// 234234234234278
//            l
//              ^
// 4444
// remaining: 2
// searching: 4
//

long maxJoltageInBankHigh(std::string bank) { return 0; }

int maxJoltageInBankLow(std::string bank) {
  std::array<int, 10> joltageMap;
  joltageMap.fill(-1);

  for (const char battery : bank) {
    int currentJoltage = battery - '0';

    for (int i = 0; i < joltageMap.size(); i++)
      joltageMap[i] =
          (joltageMap[i] != -1) ? std::max(joltageMap[i], currentJoltage) : -1;

    joltageMap[currentJoltage] =
        (joltageMap[currentJoltage] == -1)
            ? 0
            : std::max(currentJoltage, joltageMap[currentJoltage]);
  }

  for (int i = 9; i > 0; i--) {
    if (joltageMap[i] > 0)
      return (i * 10) + joltageMap[i];
  }

  return 0;
}

enum class joltageSetting { low, high };

int totalOutputJoltage(std::string input, joltageSetting j) {
  int totalJoltage = 0;

  std::vector<std::string> batteryBanks = split(input, "\n");

  if (j == joltageSetting::low)
    for (const std::string bank : batteryBanks)
      totalJoltage += maxJoltageInBankLow(bank);
  else
    for (const std::string bank : batteryBanks)
      totalJoltage += maxJoltageInBankHigh(bank);

  return totalJoltage;
}

int main() {

  auto input = f2str("inputs/id3");

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

  printf("%d\n", totalOutputJoltage(input.value(), joltageSetting::low));
  printf("%dl\n", totalOutputJoltage(input.value(), joltageSetting::high));

  return EXIT_SUCCESS;
}
