#include <cstdio>
#include <deque>
#include <cmath>

#define MAX_NUMBER 2147483647

using namespace std;

deque<int> returnPrimesAtkin(int limitNumber)
{
    deque<int> isPrime(limitNumber-5, false);

    int sqrtLimitNumber = (int)sqrt((double)limitNumber);
    for(int x=1; x <= sqrtLimitNumber; x++)
    {
        for(int y=1; y <= sqrtLimitNumber; y++)
        {
            int n = 4*x*x + y*y;
            if( n <= limitNumber && (n % 12 == 1 || n % 12 == 5))
            {
                isPrime[n-5] = !isPrime[n-5];
            }

            n = 3*x*x + y*y;
            if( n <= limitNumber && n % 12 == 7)
            {
                isPrime[n-5] = !isPrime[n-5];
            }

            n = 3*x*x - y*y;
            if(x > y && n <= limitNumber && n % 12 == 11)
            {
                isPrime[n-5] = !isPrime[n-5];
            }
        }
    }

    for(int index=5; index <= sqrtLimitNumber; index++)
    {
        if(isPrime[index-5])
        {
            for(int k = index*index; k <= limitNumber; k+=(index*index))
            {
                isPrime[k-5] = false;
            }
        }
    }

   deque<int> primeList;
   primeList.push_back(2);
   primeList.push_back(3);

   for(int index=0; index < limitNumber-5; index++)
   {
       if(isPrime[index])
       {
           primeList.push_back(index+5);
       }
   }

   return isPrime;

}

int main()
{
    int amountIntervals;
    int bottomLimit, upperLimit;
    scanf("%d", &amountIntervals);
 

    for(int index=0; index < amountIntervals; index++)
    {
        scanf("%d %d", &bottomLimit, &upperLimit);
        deque<int> primeList = returnPrimesAtkin((int)sqrt((double)upperLimit));
        for(deque<int>::iterator it=primeList.begin(); it != primeList.end(); it++)
        {
            if(*it >= bottomLimit)
            {
                printf("%d\n", *it);
            }
        }
    }
    
    return 0;
}
