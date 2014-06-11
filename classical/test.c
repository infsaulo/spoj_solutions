#include <stdio.h>

#define UNIVERSE_NUMBER 42

int main()
{
    int number;
    scanf("%d", &number);
    while(number != UNIVERSE_NUMBER)
    {
        printf("%d\n", number);
	scanf("%d", &number);
    }

    return 0;
}
