#include "random.h"
#include <stdlib.h>
#include <time.h>

// Initialize random number generator
void initRandom() {
    srand(time(NULL));
}

int generateRandomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}
