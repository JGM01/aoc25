#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <expected>
#include <string>
#include <vector>

enum class file_error {
  file_open,
  file_size,
  allocation,
  file_read,
};

int numDigits(int x) {
  return (
      x < 10
          ? 1
          : (x < 100
                 ? 2
                 : (x < 1000
                        ? 3
                        : (x < 10000
                               ? 4
                               : (x < 100000
                                      ? 5
                                      : (x < 1000000
                                             ? 6
                                             : (x < 10000000
                                                    ? 7
                                                    : (x < 100000000
                                                           ? 8
                                                           : (x < 1000000000
                                                                  ? 9
                                                                  : 10)))))))));
}
int numDigitsStupidVersion(long x) {
  return x == 0 ? 1 : static_cast<int>(std::to_string(x).length());
}

std::vector<std::string> split(std::string str, std::string delim) {
  std::vector<std::string> tokens;
  size_t pos = 0;

  while ((pos = str.find(delim)) != std::string::npos) {
    tokens.push_back(str.substr(0, pos));
    str.erase(0, pos + delim.length());
  }
  tokens.push_back(str);

  return tokens;
}

std::expected<std::string, file_error> f2str(std::string fileName) {

  FILE *f = fopen(fileName.c_str(), "r");
  char *buf = NULL;

  if (f == NULL)
    return std::unexpected(file_error::file_open);

  fseek(f, 0L, SEEK_END);

  long size = ftell(f);

  if (size == -1)
    return std::unexpected(file_error::file_size);

  buf = (char *)malloc(sizeof(char) * size + 1);

  if (buf == NULL)
    return std::unexpected(file_error::allocation);

  rewind(f);

  size_t bytesRead = fread(buf, sizeof(char), size, f);

  if (bytesRead != size)
    return std::unexpected(file_error::file_read);

  buf[size] = '\0';

  return std::string(buf);
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

  long result = 0;

  std::vector<std::string> ranges = split(input.value(), ",");

  // 500-2000
  for (const std::string range : ranges) {
    printf("%s\n", range.c_str());
    // [500, 2000]
    std::vector<std::string> x = split(range, "-");
    long a = std::stol(x[0]);
    long b = std::stol(x[1]);
    if (numDigitsStupidVersion(a) % 2 == 0 ||
        numDigitsStupidVersion(b) % 2 == 0) {
      while (a <= b) {
        if (numDigitsStupidVersion(a) % 2 == 0) {
          std::string a_str = std::to_string(a);

          // 1010
          //   ^
          if (a_str.substr(0, a_str.length() / 2) ==
              a_str.substr(a_str.length() / 2)) {
            result += a;
            printf("FOUND: %ld\n", a);
          }
        }
        a++;
      }
    }
  }

  printf("%ld\n", result);

  return EXIT_SUCCESS;
}
