#include <stdio.h>

int main(void)
{
    char s[255];

    printf("======= Welcome to infinite calculator! =======\n"
           "Enter the expression in infix notation.\n"
           "Input : ");
    scanf("%s", s);
    printf("Output : %s", s);

    return 0;
}