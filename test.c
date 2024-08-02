#ifndef NOLIBC
#include <stdio.h>
#endif

int main (int argc, char** argv) {
    puts("moo");
    return argc - 1;
}
