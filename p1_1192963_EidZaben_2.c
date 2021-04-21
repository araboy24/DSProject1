/*
*   Eid Zaben
*   1192963
*   Section 4
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Monomial
{
    int coefficient;
    int exponent;
    struct Monomial *next;
    struct Monomial *prev;
} Monomial;

const char *INPUT_FILE = "equations.txt";
const char *OUTPUT_FILE = "results.txt";

void readInEquations();
void storeInFile();
void displayEquations();
struct Monomial *multEquations(bool inBg);
struct Monomial *addEquations(bool inBg);
struct Monomial *subEquations(bool inBg);
bool isQuit = false;
char userSelection;
int maxDegreeG;

struct Monomial *allEquationsArray[100];

struct Monomial *sumOfEquations;
struct Monomial *diffOfEquations;
struct Monomial *prodOfEquations;

int main()
{
    // readInEquations();
    while (!isQuit)
    {
        printf("Select the operation you would like to perform\n");
        printf("\tR to read in the equations\n");
        printf("\tD to display the equations\n");
        printf("\tA for addition\n");
        printf("\tS for subtraction\n");
        printf("\tM for multiplication\n");
        printf("\tC to store RESULT in a file\n");
        printf("\tQ to quit\n");
        scanf(" %c", &userSelection);
        if (userSelection == 'q' || userSelection == 'Q')
        {
            isQuit = true;
        }
        else
        {
            if (userSelection == 'a' || userSelection == 'A')
            {
                sumOfEquations = addEquations(false);
            }
            else if (userSelection == 's' || userSelection == 'S')
            {
                diffOfEquations = subEquations(false);
            }
            else if (userSelection == 'm' || userSelection == 'M')
            {
                prodOfEquations = multEquations(false);
            }
            else if (userSelection == 'd' || userSelection == 'D')
            {
                displayEquations();
            }
            else if (userSelection == 'r' || userSelection == 'R')
            {
                readInEquations();
            }
            else if (userSelection == 'C' || userSelection == 'c')
            {
                storeInFile();
            }
        }
    }
    return 0;
}

void displayEquations()
{
    for (int i = 0; i < 100; i++)
    {
        if (allEquationsArray[i] == NULL)
        {
            break;
        }
        struct Monomial *p = allEquationsArray[i];
        bool isFirst = true;
        while (p != NULL)
        {
            if (p->coefficient < 0)
            {
                if (p->exponent > 1)
                    printf("%dx^%d", p->coefficient, p->exponent);
                else if (p->exponent == 1)
                    printf("%dx", p->coefficient);
                else
                    printf("%d", p->coefficient);
                isFirst = false;
            }
            else if (p->coefficient > 0)
            {
                if (isFirst)
                {
                    if (p->exponent > 1)
                        printf("%dx^%d", p->coefficient, p->exponent);
                    else if (p->exponent == 1)
                        printf("%dx", p->coefficient);
                    else
                        printf("%d", p->coefficient);
                    isFirst = false;
                }
                else
                {
                    if (p->exponent > 1)
                        printf("+%dx^%d", p->coefficient, p->exponent);
                    else if (p->exponent == 1)
                        printf("+%dx", p->coefficient);
                    else
                        printf("+%d", p->coefficient);
                }
            }
            p = p->next;
        }
        printf("\n");
    }
    return;
}

void storeInFile()
{
    FILE *fPointer;
    fPointer = fopen("results.txt", "w");
    sumOfEquations = addEquations(true);

    fprintf(fPointer, "---------SUM RESULT--------\n");
    int isFirst = 0;
    for (int i = maxDegreeG; i >= 0; i--)
    {
        if (sumOfEquations[i].coefficient < 0)
        {
            if (sumOfEquations[i].exponent > 1)
                fprintf(fPointer, "%dx^%d", sumOfEquations[i].coefficient, sumOfEquations[i].exponent);
            else if (sumOfEquations[i].exponent == 1)
                fprintf(fPointer, "%dx", sumOfEquations[i].coefficient);
            else
                fprintf(fPointer, "%d", sumOfEquations[i].coefficient);
            isFirst = 1;
        }
        else if (sumOfEquations[i].coefficient > 0)
        {
            if (isFirst == 0)
            {
                if (sumOfEquations[i].exponent > 1)
                    fprintf(fPointer, "%dx^%d", sumOfEquations[i].coefficient, sumOfEquations[i].exponent);
                else if (sumOfEquations[i].exponent == 1)
                    fprintf(fPointer, "%dx", sumOfEquations[i].coefficient);
                else
                    fprintf(fPointer, "%d", sumOfEquations[i].coefficient);
            }
            else
            {
                if (sumOfEquations[i].exponent > 1)
                    fprintf(fPointer, "+%dx^%d", sumOfEquations[i].coefficient, sumOfEquations[i].exponent);
                else if (sumOfEquations[i].exponent == 1)
                    fprintf(fPointer, "+%dx", sumOfEquations[i].coefficient);
                else
                    fprintf(fPointer, "+%d", sumOfEquations[i].coefficient);
            }
            isFirst = 1;
        }
    }
    fprintf(fPointer, "\n\n");
    diffOfEquations = subEquations(true);
    fprintf(fPointer, "---------Difference RESULT--------\n");
    isFirst = 0;
    for (int i = maxDegreeG; i >= 0; i--)
    {
        if (diffOfEquations[i].coefficient < 0)
        {
            if (diffOfEquations[i].exponent > 1)
                fprintf(fPointer, "%dx^%d", diffOfEquations[i].coefficient, diffOfEquations[i].exponent);
            else if (diffOfEquations[i].exponent == 1)
                fprintf(fPointer, "%dx", diffOfEquations[i].coefficient);
            else
                fprintf(fPointer, "%d", diffOfEquations[i].coefficient);
            isFirst = 1;
        }
        else if (diffOfEquations[i].coefficient > 0)
        {
            if (isFirst == 0)
            {
                if (diffOfEquations[i].exponent > 1)
                    fprintf(fPointer, "%dx^%d", diffOfEquations[i].coefficient, diffOfEquations[i].exponent);
                else if (diffOfEquations[i].exponent == 1)
                    fprintf(fPointer, "%dx", diffOfEquations[i].coefficient);
                else
                    fprintf(fPointer, "%d", diffOfEquations[i].coefficient);
            }
            else
            {
                if (diffOfEquations[i].exponent > 1)
                    fprintf(fPointer, "+%dx^%d", diffOfEquations[i].coefficient, diffOfEquations[i].exponent);
                else if (diffOfEquations[i].exponent == 1)
                    fprintf(fPointer, "+%dx", diffOfEquations[i].coefficient);
                else
                    fprintf(fPointer, "+%d", diffOfEquations[i].coefficient);
            }
            isFirst = 1;
        }
    }
    fprintf(fPointer, "\n\n");

    prodOfEquations = multEquations(true);
    fprintf(fPointer, "---------Multiplacation RESULT--------\n");
    isFirst = 0;
    for (int i = maxDegreeG * 2; i >= 0; i--)
    {
        // fprintf(fPointer,"\nIndex: %d\tprodOfEquations[i].exponenent:%d\tprodOfEquations[i].coefficient:%d\n", i, prodOfEquations[i].exponent, prodOfEquations[i].coefficient);
        // fprintf(fPointer,"C: %d\tE:%d\n", sum[i].coefficient, sum[i].exponent);
        if (prodOfEquations[i].coefficient < 0)
        {
            if (prodOfEquations[i].exponent > 1)
                fprintf(fPointer, "%dx^%d", prodOfEquations[i].coefficient, prodOfEquations[i].exponent);
            else if (prodOfEquations[i].exponent == 1)
                fprintf(fPointer, "%dx", prodOfEquations[i].coefficient);
            else
                fprintf(fPointer, "%d", prodOfEquations[i].coefficient);
            isFirst = 1;
        }
        else if (prodOfEquations[i].coefficient > 0)
        {
            if (isFirst == 0)
            {
                if (prodOfEquations[i].exponent > 1)
                    fprintf(fPointer, "%dx^%d", prodOfEquations[i].coefficient, prodOfEquations[i].exponent);
                else if (prodOfEquations[i].exponent == 1)
                    fprintf(fPointer, "%dx", prodOfEquations[i].coefficient);
                else
                    fprintf(fPointer, "%d", prodOfEquations[i].coefficient);
            }
            else
            {
                if (prodOfEquations[i].exponent > 1)
                    fprintf(fPointer, "+%dx^%d", prodOfEquations[i].coefficient, prodOfEquations[i].exponent);
                else if (prodOfEquations[i].exponent == 1)
                    fprintf(fPointer, "+%dx", prodOfEquations[i].coefficient);
                else
                    fprintf(fPointer, "+%d", prodOfEquations[i].coefficient);
            }

            isFirst = 1;
        }
    }
    fprintf(fPointer, "\n");
    fclose(fPointer);
    printf("Results stored successfully\n");
}

int getMaxDegree()
{
    int maxDegree = 0;
    for (int i = 0; i < 100; i++)
    {
        struct Monomial *p = allEquationsArray[i];
        if (p == NULL)
        {
            break;
        }
        int count = 0;

        while (p != NULL)
        {
            // if (p != NULL)
            // {
            // printf("Coeff: %d\tExp: %d\n", p->coefficient, p->exponent);
            // }
            if (p->exponent > maxDegree)
            {
                maxDegree = p->exponent;
            }
            p = p->next;
            count++;
        }
        // printf("\n");
    }
    return maxDegree;
}

struct Monomial *addEquations(bool inBg)
{
    //TODO
    // int lengthOfArray = sizeof allEquationsArray / sizeof allEquationsArray[0];
    // printf("%d\n", lengthOfArray);
    int maxDegree = getMaxDegree();
    maxDegreeG = maxDegree;
    // struct Monomial sum[maxDegree + 1];
    struct Monomial *sum = malloc((maxDegree + 1) * sizeof(struct Monomial));
    for (int i = 0; i <= maxDegree; i++)
    {
        sum[i].coefficient = 0;
        sum[i].exponent = i;
    }

    for (int i = 0; i <= 100; i++)
    {
        struct Monomial *p = allEquationsArray[i];
        if (p == NULL)
        {
            break;
        }

        while (p != NULL)
        {
            sum[p->exponent].coefficient += p->coefficient;
            p = p->next;
        }
        // printf("\n");
    }
    if (!inBg)
    {

        printf("---------SUM RESULT--------\n");
        int isFirst = 0;
        for (int i = maxDegree; i >= 0; i--)
        {
            // printf("C: %d\tE:%d\n", sum[i].coefficient, sum[i].exponent);
            if (sum[i].coefficient < 0)
            {
                if (sum[i].exponent > 1)
                    printf("%dx^%d", sum[i].coefficient, sum[i].exponent);
                else if (sum[i].exponent == 1)
                    printf("%dx", sum[i].coefficient);
                else
                    printf("%d", sum[i].coefficient);
                isFirst = 1;
            }
            else if (sum[i].coefficient > 0)
            {
                if (isFirst == 0)
                {
                    if (sum[i].exponent > 1)
                        printf("%dx^%d", sum[i].coefficient, sum[i].exponent);
                    else if (sum[i].exponent == 1)
                        printf("%dx", sum[i].coefficient);
                    else
                        printf("%d", sum[i].coefficient);
                }
                else
                {

                    if (sum[i].exponent > 1)
                        printf("+%dx^%d", sum[i].coefficient, sum[i].exponent);
                    else if (sum[i].exponent == 1)
                        printf("+%dx", sum[i].coefficient);
                    else
                        printf("+%d", sum[i].coefficient);
                }
                isFirst = 1;
                // printf("+%dx^%d ", sum[i].coefficient, sum[i].exponent);
            }
        }

        printf("\n");
        printf("\nWould you like to evaluate a number?(y/n)\n");
        char res;
        // gets(res);
        scanf(" %c", &res);
        int num, sumForNum = 0;
        if (res == 'y')
        {
            printf("\nType the number you'd like to evaluate\n");
            scanf("%d", &num);
            for (int i = maxDegree; i >= 0; i--)
            {
                if (sum[i].coefficient != 0)
                {
                    int power = num;
                    for (int j = 1; j < i; j++)
                    {
                        power *= num;
                    }
                    sumForNum += sum[i].coefficient * power;
                }
            }
            // sumForNum += sum[0].coefficient;
            printf("The result is: %d\n", sumForNum);
        }
    }
    // sumOfEquations = sum;
    return sum;
}

struct Monomial *subEquations(bool inBg)
{
    int maxDegree = getMaxDegree();
    maxDegreeG = maxDegree;
    struct Monomial *diff = malloc((maxDegree + 1) * sizeof(struct Monomial));
    for (int i = 0; i <= maxDegree; i++)
    {
        diff[i].coefficient = 0;
        diff[i].exponent = i;
    }

    for (int i = 0; i <= 100; i++)
    {
        struct Monomial *p = allEquationsArray[i];
        if (p == NULL)
        {
            break;
        }

        while (p != NULL)
        {
            if (i == 0)
            {
                diff[p->exponent].coefficient += p->coefficient;
            }
            else
            {
                diff[p->exponent].coefficient -= p->coefficient;
            }

            p = p->next;
        }
    }

    if (!inBg)
    {

        printf("---------Diff RESULT--------\n");
        int isFirst = 0;
        for (int i = maxDegree; i >= 0; i--)
        {
            // printf("C: %d\tE:%d\n", sum[i].coefficient, sum[i].exponent);
            if (diff[i].coefficient < 0)
            {
                if (diff[i].exponent > 1)
                    printf("%dx^%d", diff[i].coefficient, diff[i].exponent);
                else if (diff[i].exponent == 1)
                    printf("%dx", diff[i].coefficient);
                else
                    printf("%d", diff[i].coefficient);
                isFirst = 1;
            }
            else if (diff[i].coefficient > 0)
            {
                if (isFirst == 0)
                {
                    if (diff[i].exponent > 1)
                        printf("%dx^%d", diff[i].coefficient, diff[i].exponent);
                    else if (diff[i].exponent == 1)
                        printf("%dx", diff[i].coefficient);
                    else
                        printf("%d", diff[i].coefficient);
                }
                if (diff[i].exponent > 1)
                    printf("+%dx^%d", diff[i].coefficient, diff[i].exponent);
                else if (diff[i].exponent == 1)
                    printf("+%dx", diff[i].coefficient);
                else
                    printf("+%d", diff[i].coefficient);
                isFirst = 1;
            }
        }
        printf("\n");
        printf("\nWould you like to evaluate a number?(y/n)\n");
        char res;
        // gets(res);
        scanf(" %c", &res);
        int num, diffForNum = 0;
        if (res == 'y')
        {
            printf("\nType the number you'd like to evaluate\n");
            scanf("%d", &num);
            for (int i = maxDegree; i >= 0; i--)
            {
                if (diff[i].coefficient != 0)
                {
                    int power = num;
                    for (int j = 1; j < i; j++)
                    {
                        power *= num;
                    }
                    diffForNum += diff[i].coefficient * power;
                }
            }
            // diffForNum += diff[0].coefficient;
            printf("The result is: %d\n", diffForNum);
        }
    }

    return diff;
}

struct Monomial *multEquations(bool inBg)
{
    //TODO
    // printf("Mult\n");
    int maxDegree = getMaxDegree();
    maxDegreeG = maxDegree;
    // struct Monomial sum[maxDegree + 1];
    struct Monomial *prod = malloc((maxDegree + maxDegree) * sizeof(struct Monomial));

    for (int i = 0; i <= maxDegree * 2; i++)
    {
        prod[i].coefficient = 0;
        prod[i].exponent = i;
    }

    for (int i = 0; i <= 100; i++)
    {
        struct Monomial *p = allEquationsArray[i];
        if (p == NULL)
        {
            break;
        }
        for (int j = i + 1; j < 100; j++)
        {
            struct Monomial *p2 = allEquationsArray[j];
            if (p2 == NULL)
            {
                break;
            }
            while (p != NULL)
            {
                while (p2 != NULL)
                {
                    prod[p->exponent + p2->exponent].coefficient = prod[p->exponent + p2->exponent].coefficient + (p->coefficient * p2->coefficient);
                    p2 = p2->next;
                }
                p = p->next;
                p2 = allEquationsArray[j];
            }
            p = allEquationsArray[i];
        }
    }

    if (!inBg)
    {

        printf("---------Multiplacation RESULT--------\n");
        int isFirst = 0;
        for (int i = maxDegree * 2; i >= 0; i--)
        {
            // printf("\nIndex: %d\tprod[i].exponenent:%d\tprod[i].coefficient:%d\n", i, prod[i].exponent, prod[i].coefficient);
            // printf("C: %d\tE:%d\n", sum[i].coefficient, sum[i].exponent);
            if (prod[i].coefficient < 0)
            {
                if (prod[i].exponent > 1)
                    printf("%dx^%d", prod[i].coefficient, prod[i].exponent);
                else if (prod[i].exponent == 1)
                    printf("%dx", prod[i].coefficient);
                else
                    printf("%d", prod[i].coefficient);
                isFirst = 1;
            }
            else if (prod[i].coefficient > 0)
            {
                if (isFirst == 0)
                {
                    if (prod[i].exponent > 1)
                        printf("%dx^%d", prod[i].coefficient, prod[i].exponent);
                    else if (prod[i].exponent == 1)
                        printf("%dx", prod[i].coefficient);
                    else
                        printf("%d", prod[i].coefficient);
                }
                else
                {
                    if (prod[i].exponent > 1)
                        printf("+%dx^%d", prod[i].coefficient, prod[i].exponent);
                    else if (prod[i].exponent == 1)
                        printf("+%dx", prod[i].coefficient);
                    else
                        printf("+%d", prod[i].coefficient);
                }

                isFirst = 1;
            }
        }
        printf("\n");
        printf("\nWould you like to evaluate a number?(y/n)\n");
        char res;
        // gets(res);
        scanf(" %c", &res);
        int num, prodForNum = 0;
        if (res == 'y')
        {
            printf("\nType the number you'd like to evaluate\n");
            scanf("%d", &num);
            for (int i = maxDegree; i >= 0; i--)
            {
                if (prod[i].coefficient != 0)
                {
                    int power = num;
                    for (int j = 1; j < i; j++)
                    {
                        power *= num;
                    }
                    prodForNum += prod[i].coefficient * power;
                }
            }
            prodForNum += prod[0].coefficient;
            printf("The result is: %d\n", prodForNum);
        }
    }
    return prod;
}

void removeSpaces(char *str)
{
    int count = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] != ' ')
        {
            str[count++] = str[i];
        }
    }

    str[count] = '\0';
}

char *addPlusSigns(char *str)
{
    int count = 0;
    char *newStr;
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == '-')
        {
            newStr[count++] = '+';
            newStr[count++] = '-';
        }
        else
        {
            newStr[count++] = str[i];
        }
    }
    newStr[count] = '\0';
    return newStr;
}

void newLineToTerm(char *str)
{
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == '\n')
        {
            str[i] = '\0';
        }
    }
}

int getIndexOfX(char *str)
{
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == 'x')
        {
            return i;
        }
    }
    return -1;
}

int getIndexOfCaret(char *str)
{
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == '^')
        {
            return i;
        }
    }
    return -1;
}

void readInEquations()
{
    FILE *fPointer;
    fPointer = fopen(INPUT_FILE, "r");
    char equation[150];

    int loopedThrough = 0;
    while (!feof(fPointer))
    {
        struct Monomial currEquArray[10];
        int monsCount = 0;
        fgets(equation, 150, fPointer);
        // printf("%s", equation);

        removeSpaces(equation);
        printf("%s", equation);

        char *equWithPlusses = addPlusSigns(equation);
        // printf("%s\n", equWithPlusses);

        newLineToTerm(equWithPlusses);

        int len = strlen(equWithPlusses);
        char equCpy[len];
        strcpy(equCpy, equWithPlusses);
        char *piece = strtok(equCpy, "+");
        while (piece != NULL)
        {
            int coeff;
            int exp; // = -12345;
            // printf("%s", piece);
            if (strlen(piece) == 1)
            {
                if (piece[0] == 'x')
                {
                    coeff = 1;
                    exp = 1;
                }
                else if (piece[0] >= '0' && piece[0] <= '9')
                {
                    coeff = piece[0] - '0';
                    exp = 0;
                }
            }
            else if (strchr(piece, 'x') == NULL)
            {
                coeff = atoi(piece);
                exp = 0;
            }
            else
            {
                int indOfX = getIndexOfX(piece);
                char beforeX[10];
                for (int i = 0; i < 10; i++)
                {
                    beforeX[i] = '\0';
                }
                strncpy(beforeX, piece, indOfX);
                char *befDup = strdup(beforeX);
                if (piece[0] == '-' && piece[1] == 'x')
                {
                    coeff = -1;
                }
                else if (piece[0] == 'x')
                {
                    coeff = 1;
                }
                else
                {
                    coeff = atoi(befDup);
                }
                int indOfCaret = getIndexOfCaret(piece);
                int places = 1;
                if (indOfCaret != -1)
                {
                    exp = 0;
                    char afterCaret[] = {'\0', '\0', '\0', '\0', '\0', '\0'};
                    for (int i = 0; i < strlen(piece); i++)
                    {
                        if (i > indOfCaret)
                        {
                            afterCaret[i - indOfCaret - 1] = piece[i];
                        }
                    }
                    exp = atoi(afterCaret);
                }
                else
                {
                    exp = 1;
                }
            }
            struct Monomial mono;
            mono.coefficient = coeff;
            mono.exponent = exp;

            currEquArray[monsCount] = mono;
            monsCount++;

            // printf("%s: coefficient: %d, exp: %d", piece, coeff, exp);
            // printf("\n");
            piece = strtok(NULL, "+");
        }

        struct Monomial *temp = malloc(sizeof(struct Monomial));
        temp->coefficient = currEquArray[0].coefficient;
        temp->exponent = currEquArray[0].exponent;
        temp->next = NULL;
        temp->prev = NULL;
        allEquationsArray[loopedThrough] = temp;
        // printf("***********%d   %d**********\n", temp->coefficient, temp->exponent);
        int i;
        for (i = 1; i < monsCount; i++)
        {
            struct Monomial *temp2 = malloc(sizeof(struct Monomial));
            temp->next = temp2;
            temp2->coefficient = currEquArray[i].coefficient;
            temp2->exponent = currEquArray[i].exponent;
            temp2->next = NULL;
            temp2->prev = temp;
            temp = temp2;
        }
        // printf("***********%d   %d**********\n", temp->coefficient, temp->exponent);
        // printf("***********%d   %d**********\n", allEquationsArray[loopedThrough]->next->coefficient, allEquationsArray[loopedThrough]->next->exponent);

        // for (int i = 0; i < monsCount; i++)
        // {
        //     if (i == 0)
        //     {
        //         //if (currEquArray[i + 1].coefficient != NULL)
        //         // {
        //         currEquArray[i].next = &currEquArray[i + 1];
        //         currEquArray[i].prev = NULL;
        //         // }
        //     }
        //     else if (i == monsCount - 1)
        //     {
        //         // if (currEquArray[i - 1].coefficient != NULL)
        //         // {
        //         currEquArray[i].prev = &currEquArray[i - 1];
        //         currEquArray[i].next = NULL;
        //         // }
        //     }
        //     else
        //     {
        //         currEquArray[i].next = &currEquArray[i + 1];
        //         currEquArray[i].prev = &currEquArray[i - 1];
        //     }
        // }
        // allEquationsArray[loopedThrough] = currEquArray[0];
        loopedThrough++;

        printf("\n");
    }

    fclose(fPointer);
    printf("Equations read successfully");
    return;
}

// void