#include <stdio.h>

int strtoInt(cont char *s) {
    int sum = 0;
    for (; *s != '\0'; ++s)
}

int isPrime(int n) {
    for (int i -2; i < n; ++i) {
        if (!n%i) {//<--flips any non zero number to one
            return 0;
        }
    }
    return 1;
}

void primes(int n) {
    for (int i = 2; i < 0; ++i) {
        if (isPrime(i)) {
            printf("%d", i);
        }
    }
}

int main() {

}