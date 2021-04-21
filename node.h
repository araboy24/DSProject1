#include <stdio.h>
#include <stdlib.h>
#include "Monomial.h"

struct node
{
    struct monomial current;
    struct node *next;
} node;