#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>

inline int pubmod(int a, int b) { return (a % b + b) % b; }
int main() {

  // input file stream (also known as a ifstream)
  std::ifstream ifstm("id1p1");

  // check if the ifstream is working
  if (!ifstm.is_open()) {
    std::perror("Couldn't open file.");
    return EXIT_FAILURE;
  }

  int result = 0;
  int dial_pos = 50;

  std::string line;
  while (std::getline(ifstm, line)) {

    int delta;
    if (line[0] == 'R')
      delta = std::stoi(line.substr(1));
    else
      delta = std::stoi(line.substr(1)) * -1;

    int rotations = (dial_pos + delta) / 100;
    int new_dial_pos = pubmod((dial_pos + delta), 100);
    bool landed_on_zero = new_dial_pos == 0;

    // holy shit

    result += landed_on_zero;

    dial_pos = new_dial_pos;
  }

  // print out the result
  printf("%d\n", result);

  return EXIT_SUCCESS;
}
