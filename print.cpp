#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;


vector<int> returnPrimes(int limitNumber)
{
    vector<int> primeList;
    primeList.push_back(2);
    
    for(int primeCandidate = 3; primeCandidate <= limitNumber; primeCandidate+=2)
    {
       bool isPrime = true;
       int primeCandidateSqrt = (int)sqrt((float)primeCandidate);
       for(vector<int>::iterator primeFactor = primeList.begin(); primeFactor != primeList.end() || *primeFactor > primeCandidateSqrt; primeFactor++)
       {
           if(primeCandidate % (*primeFactor) == 0)
           {
               isPrime = false;
               break;
           }
       }

       if(isPrime)
       {
           primeList.push_back(primeCandidate);
       }
    }

    return primeList;
}

int main()
{
    int amountIntervals;
    int bottomLimit, upperLimit;
    scanf("%d", &amountIntervals);
    
    for(int index=0; index < amountIntervals; index++)
    {
        scanf("%d %d", &bottomLimit, &upperLimit);
        vector<int> primeList = returnPrimes(upperLimit);
        for(vector<int>::iterator prime = primeList.begin(); prime != primeList.end(); prime++)
        {
            if(*prime >= bottomLimit)
            {
                printf("%d\n", *prime);
            }
        }
    }
    return 0;
}
