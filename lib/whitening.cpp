#include "whitening.h"


int whitening(int x) {
    x ^= (x << 13);
    x += (x >> 7);
    x ^= (x << 17);
    x -= (x >> 11);
    x ^= (x << 5);
    return x;
}
