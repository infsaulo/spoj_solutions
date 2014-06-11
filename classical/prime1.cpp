#include <cstdio>
#include <deque>
#include <cmath>

#define MAX_NUMBER 2147483647

using namespace std;

deque<long> returnPrimesEratosthenes(long limitNumber)
{
    deque<bool>sieve(limitNumber, true);

    long sqrtLimitNumber = (long)sqrt((double)limitNumber);

    for(long i = 2; i <= sqrtLimitNumber; i++)
    {
        if(sieve[i-1])
        {
            for(long p = i*i; p <= limitNumber; p+=i)
            {
                sieve[p-1] = false;
            }
        }
    }

    deque<long> primeNumberList;
    for(long index = 1; index < limitNumber; index++)
    {
        if(sieve[index])
        {
            primeNumberList.push_back(index+1);
        }
    }

   return primeNumberList;
}

int main()
{
    long amountIntervals;
    long bottomLimit, upperLimit;
    scanf("%ld", &amountIntervals);
 
    deque<long> primeList = returnPrimesEratosthenes((long)ceil(sqrt((double)MAX_NUMBER)));

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
            if(primeCandidates[index] && (bottomLimit + index) > 1 )
            {
                printf("%ld\n", bottomLimit + index);
            }
        }
	printf("\n");
    }
    
    return 0;
}
