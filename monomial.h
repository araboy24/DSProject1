#include <stdio.h>
#include <stdlib.h>

struct monomial
{
    int coefficient;
    int exponent;
    struct Monomial *next;
} monomial;