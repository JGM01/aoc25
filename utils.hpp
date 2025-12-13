#pragma once

#include <string>
#include <vector>
enum class file_error {
  file_open,
  file_size,
  allocation,
  file_read,
};

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
