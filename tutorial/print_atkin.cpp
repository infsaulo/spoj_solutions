#include <cstdio>
#include <deque>
#include <cmath>

#define MAX_NUMBER 2147483647

using namespace std;

deque<long> returnPrimesAtkin(long limitNumber)
{
    deque<bool> isPrime(limitNumber, false);
    isPrime[1] = true;
    isPrime[2] = true;

    long sqrtLimitNumber = (long)ceil(sqrt((double)limitNumber));
    for(long x=1; x <= sqrtLimitNumber; x++)
    {
        for(long y=1; y <= sqrtLimitNumber; y++)
        {
            long n = 4*x*x + y*y;
            if( n <= limitNumber && (n % 12 == 1 || n % 12 == 5))
            {
                isPrime[n-1] = !isPrime[n-1];
            }

            n = 3*x*x + y*y;
            if( n <= limitNumber && n % 12 == 7)
            {
                isPrime[n-1] = !isPrime[n-1];
            }

            n = 3*x*x - y*y;
            if(x > y && n <= limitNumber && n % 12 == 11)
            {
                isPrime[n-1] = !isPrime[n-1];
            }
        }
    }

    for(long index=5; index <= sqrtLimitNumber; index++)
    {
        if(isPrime[index-1])
        {
            for(long k = index*index; k <= limitNumber; k+=(index*index))
            {
                isPrime[k-1] = false;
            }
        }
    }

   deque<long> primeList;

   for(long index=0; index < limitNumber; index++)
   {
       if(isPrime[index])
       {
           primeList.push_back(index+1);
       }
   }

   return primeList;

}
int main()
{
    long amountIntervals;
    long bottomLimit, upperLimit;
    scanf("%ld", &amountIntervals);
 
    deque<long> primeList = returnPrimesAtkin((long)ceil(sqrt((double)MAX_NUMBER)));

    for(long index=0; index < amountIntervals; index++)
    {
        scanf("%ld %ld", &bottomLimit, &upperLimit);
        deque<bool> primeCandidates(upperLimit - bottomLimit + 1, true);
        long sqrtUpperLimit = (long)ceil(sqrt((double)upperLimit));
        for(deque<long>::iterator it = primeList.begin(); *it <= sqrtUpperLimit; it++)
        {
            for(long droppedNumber = (long)ceil((double)bottomLimit / (*it)) * (*it); droppedNumber <= upperLimit; droppedNumber+=(*it))
            {
                if(droppedNumber != *it)
                {
                    primeCandidates[droppedNumber-bottomLimit] = false;
                }
            }
        }
        
        for(long index = 0; index < upperLimit - bottomLimit + 1; index++)
        {
            if(primeCandidates[index])
            {
                printf("%ld\n", bottomLimit + index);
            }
        }
    }
    
    return 0;
}
