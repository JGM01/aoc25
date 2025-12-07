#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>

int main() {

  // input file stream (also known as a ifstream)
  std::ifstream ifstm("input1");

  // check if the ifstream is working
  if (!ifstm.is_open()) {
    std::perror("Couldn't open file.");
    return EXIT_FAILURE;
  }

  int result = 0;
  int dial_pos = 50;

  std::string line;
  while (std::getline(ifstm, line)) {
    // this is a print
    printf("%s -> dir: %c amt: %d\n", line.c_str(), line[0],
           std::stoi(line.substr(1)));

    // Check if the first character is R or L
    if (line[0] == 'R') {
      int delta = std::stoi(line.substr(1));
      dial_pos = (dial_pos + delta) % 100;
      result += (dial_pos == 0) ? 1 : 0;
    } else {

      // This gets the characters after the letter (so like L38 -> delta = 38)
      // if it was something like L38, that is 0, 1, 2 indices. so get 1 ->
      // onwards
      int delta = std::stoi(line.substr(1));

      // move the dial by the formula
      dial_pos = (dial_pos - delta) % 100;

      // increase the result variable by 1 if the dial position is 0. if it
      // isnt, increase by 0 (basically dont increase it)
      result += (dial_pos == 0) ? 1 : 0;
    }
    if (dial_pos == 0)
      printf("WE GOT A ZERO!!! x%d\n", result);
  }

  // print out the result
  printf("%d\n", result);

  return EXIT_SUCCESS;
}
