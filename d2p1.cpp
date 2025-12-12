#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <expected>
#include <iostream>
#include <string>

enum class file_error {
  file_open,
  file_size,
  allocation,
  file_read,
};

std::expected<std::string, file_error> f2str(std::string fileName) {

  // open (duh)
  FILE *f = fopen(fileName.c_str(), "r");
  char *buf = NULL;

  if (f == NULL)
    return std::unexpected(file_error::file_open);

  // Go to end of file
  fseek(f, 0L, SEEK_END);

  // Put pointer position into long (can be interpreted as the size of the file)
  long size = ftell(f);

  if (size == -1)
    return std::unexpected(file_error::file_size);

  // allocate
  buf = (char *)malloc(sizeof(char) * size + 1);

  if (buf == NULL)
    return std::unexpected(file_error::allocation);

  // put file pointer at beginning again
  rewind(f);

  size_t bytesRead = fread(buf, sizeof(char), size, f);

  if (bytesRead != size)
    return std::unexpected(file_error::file_read);

  // null terminate :D
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

  return EXIT_SUCCESS;
}
