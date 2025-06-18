#include <stdlib.h>
    int main() {
      int firstNumber;
      int secondNumber;
      int difference;
      srand(time(0));
      firstNumber = rand() % 10 + 90;
      secondNumber = rand() % 10 + 90;
      difference = firstNumber - secondNumber;
      printf("%d", difference);
      return 0;
    }