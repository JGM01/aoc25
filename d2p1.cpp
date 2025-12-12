#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <expected>
#include <fstream>

enum class file_error {
  file_open,
  file_size,
  allocation,
  file_read,
};

std::expected<std::string, file_error> f2str(std::string fileName) {

  FILE *f = fopen(fileName.c_str(), "r");

  char *buf = NULL;

  if (f == NULL) {
    perror("Couldn't open file :(\n");
    return std::unexpected(file_error::file_open);
  }

  // Go to end of file
  fseek(f, 0L, SEEK_END);

  // Put pointer position into long (can be interpreted as the size of the file)
  long size = ftell(f);

  buf = (char *)malloc(sizeof(char) * size + 1);

  rewind(f);

  fread(buf, sizeof(char), size, f);

  return std::string(buf);
}

int main() {

  std::string input = f2str("id2").value();
  printf("%s\n", input.c_str());

  return EXIT_SUCCESS;
}
