#include <stdio.h>

int main(void)
{
    char s[255];
    char *result = "null";

    printf("======= Welcome to infinite calculator! =======\n"
           "Enter the expression in infix notation.\n"
           "Input : ");
    scanf("%s", s);
    printf("%s\n", s);

    printf("Output : %s\n", result);

    return 0;
}