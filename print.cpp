#include <cstdio>
#include <deque>
#include <cmath>

using namespace std;


deque<int> returnPrimes(int limitNumber)
{
    deque<int> exceptedPrimeList(1, 2);
    deque<int> testPrimeList(1, 3);
    deque<int> skipSet(1, 2);
     
    for(int primeCandidate = 3; primeCandidate <= limitNumber; primeCandidate+=skipSet[0])
    {
       bool isPrime = true;
       int primeCandidateSqrt = (int)sqrt((float)primeCandidate);
       for(int index=0; index < testPrimeList.size() && testPrimeList[index] <= primeCandidateSqrt; index++)
       {
           if(primeCandidate % testPrimeList[index] == 0)
           {
               isPrime = false;
               break;
           }
       }

       if(isPrime)
       {
           testPrimeList.push_back(primeCandidate);
       }
    }

    while(!exceptedPrimeList.empty())
    {
        testPrimeList.push_front(exceptedPrimeList.back());
        exceptedPrimeList.pop_back();
    }

    return testPrimeList;
}

int main()
{
    int amountIntervals;
    int bottomLimit, upperLimit;
    scanf("%d", &amountIntervals);
    
    for(int index=0; index < amountIntervals; index++)
    {
        scanf("%d %d", &bottomLimit, &upperLimit);
        deque<int> primeList = returnPrimes(upperLimit);
        for(deque<int>::iterator prime = primeList.begin(); prime != primeList.end(); prime++)
        {
            if(*prime >= bottomLimit)
            {
                printf("%d\n", *prime);
            }
        }
    }
    return 0;
}
