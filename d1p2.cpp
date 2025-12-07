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

  int zeroesTouched = 0;
  int dialPosition = 50;

  // line by line
  std::string line;
  while (std::getline(ifstm, line)) {

    // delta being the number after the letter (L38 -> delta is -38) (R45 -> 45)
    int delta;
    if (line[0] == 'R')
      delta = std::stoi(line.substr(1));
    else
      // if I just get the numbers and not multiply by -1, it will be something
      // positive and i dont want that
      delta = std::stoi(line.substr(1)) * -1;

    // this counts the amount of times that the ticker passes zero
    int zeroCrossingsCount = 0;

    // this calculates the amount of times that the ticker rotates around the
    // dial (in float) (meaning decimal) (so 1.5 is valid)
    float rotationCount = ((float)dialPosition + (float)delta) / 100;

    // this calculates the new position of the dial (but stored in a different
    // variable so i can use the old position later)
    int newDialPosition = pubmod((dialPosition + delta), 100);

    // these are just conditional things, i could have typed out the
    // expressions, but the words "isDialOnZero" is easier to reason with
    bool isDialOnZero = dialPosition == 0;
    bool isDialGoingToZero = newDialPosition == 0;

    // holy shit

    // first check if delta >= 0 (basically checking if delta is R or L)
    if (delta >= 0) {
      // if R, the zeroCrossingCount is easy (just count the amount of
      // rotations) (unless its going to end on zero, -1 to avoid overcount)
      zeroCrossingsCount =
          isDialGoingToZero ? rotationCount - 1 : rotationCount;
    } else {

      // if L, check if dial is going to zero. if it is, just negate the
      // rotationCount and add it to zeroCrossingsCount.
      zeroCrossingsCount =
          isDialGoingToZero ? -rotationCount : -(rotationCount - 1);

      // imma be real idk why this one worked but its necessary
      zeroCrossingsCount -= isDialOnZero ? 1 : 0;
    }

    // now add them
    zeroesTouched += isDialGoingToZero + zeroCrossingsCount;

    dialPosition = newDialPosition;
  }

  // print out the result
  printf("%d\n", zeroesTouched);

  return EXIT_SUCCESS;
}
