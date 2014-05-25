#include <stdio.h>

int main(){
    int n, k, number, divisible_counter=0;

    scanf("%d %d", &n, &k);

    int i;
    for(i=0; i < n; i++)
    {
        scanf("%d", &number);
        if(number % k == 0)
        {
            divisible_counter++;
        }
    }
    
    printf("%d", divisible_counter);
    return 0;
}
