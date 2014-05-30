#include <cstdio>
#include <deque>
#include <cmath>

#define MAX_NUMBER 2147483647

using namespace std;


deque<int> returnPrimes(int limitNumber)
{
    int sqrtLimit = (int)sqrt((float)limitNumber);
    int primeCandidate = 2;
    deque<int> skipSet(1, primeCandidate);
    deque<int> exceptedPrimeList(1, primeCandidate);
    primeCandidate++;
    deque<int> rangeSkipSet(1, skipSet[0]);
    deque<int> testPrimeList(1, primeCandidate);

    int indexCurrentSkipSetRange = 0;
    rangeSkipSet.push_back(rangeSkipSet[indexCurrentSkipSetRange] * testPrimeList[0]);
    
    deque<int> extendedPrimeList;
    primeCandidate+=skipSet[0];
    int nextPrimeCandidate = primeCandidate;
    testPrimeList.push_back(nextPrimeCandidate);
     
    while(nextPrimeCandidate < limitNumber)
    {
        indexCurrentSkipSetRange++;
        while(nextPrimeCandidate < rangeSkipSet[indexCurrentSkipSetRange] + 1)
        {
            for(deque<int>::iterator n = skipSet.begin(); n != skipSet.end(); n++)
            {
                nextPrimeCandidate = primeCandidate + *n;
                
                if(nextPrimeCandidate > limitNumber)
                {
                    break;
                }
                
                if(nextPrimeCandidate <= rangeSkipSet[indexCurrentSkipSetRange] + 1)
                {
                    primeCandidate = nextPrimeCandidate;
                }
                
                int sqrtNextPrimeCandidate = (int)sqrt((float)nextPrimeCandidate);
                bool isPrime = true;
                for(int index=0; index < (int)testPrimeList.size() && sqrtNextPrimeCandidate <= testPrimeList[index]; index++)
                {
                    if(nextPrimeCandidate % testPrimeList[index] == 0)
                    {
                        isPrime = false;
                        break;
                    }
                }
               
                if(isPrime)
                {
                    if(nextPrimeCandidate <= sqrtLimit)
                    {
                        testPrimeList.push_back(nextPrimeCandidate);
                    }
                    else
                    {
                        extendedPrimeList.push_back(nextPrimeCandidate);
                    }
                }
            }
            
            if(nextPrimeCandidate > limitNumber)
            {
                break;
            }

            int lastRelevantPrimeCandidate = primeCandidate;
            deque<int> nextSkipSet;
            while(primeCandidate < (rangeSkipSet[indexCurrentSkipSetRange]+1)*2 - 1)
            {
                for(deque<int>::iterator n=skipSet.begin(); n != skipSet.end(); n++)
                {
                    nextPrimeCandidate = primeCandidate + *n;
                    if(nextPrimeCandidate > limitNumber)
                    {
                        break;
                    }
                    
                    int sqrtNextPrimeCandidate = (int)sqrt((float)nextPrimeCandidate);
                    bool isPrime = true;
                    for(int index=0; index < (int)testPrimeList.size() && sqrtNextPrimeCandidate <= testPrimeList[index]; index++)
                    {
                        if(nextPrimeCandidate % testPrimeList[index] == 0)
                        {
                            isPrime = false;
                            break;
                        }
                    }
                   
                    if(isPrime)
                    {
                        if(nextPrimeCandidate <= sqrtLimit)
                        {
                            testPrimeList.push_back(nextPrimeCandidate);
                        }
                        else
                        {
                            extendedPrimeList.push_back(nextPrimeCandidate);
                        }
                    }
 
                    if(nextPrimeCandidate % testPrimeList[0] != 0)
                    {
                        nextSkipSet.push_back(nextPrimeCandidate - lastRelevantPrimeCandidate);
                        lastRelevantPrimeCandidate = nextPrimeCandidate;
                    }
                    
                    primeCandidate = nextPrimeCandidate;
                    
                }

                if(nextPrimeCandidate > limitNumber)
                {
                    break;
                }
            }

            if(nextPrimeCandidate > limitNumber)
            {
                break;
            }

            skipSet = nextSkipSet;
            exceptedPrimeList.push_back(testPrimeList[0]);
            testPrimeList.pop_front();
            rangeSkipSet.push_back(rangeSkipSet[indexCurrentSkipSetRange] * testPrimeList[0]);
            nextPrimeCandidate = lastRelevantPrimeCandidate;
        }

    }   
 
    while(!exceptedPrimeList.empty())
    {
        testPrimeList.push_front(exceptedPrimeList.back());
        exceptedPrimeList.pop_back();
    }

    while(!testPrimeList.empty())
    {
        extendedPrimeList.push_front(testPrimeList.back());
        testPrimeList.pop_back();
    }

    return extendedPrimeList;
}

int main()
{
    int amountIntervals;
    int bottomLimit, upperLimit;
    scanf("%d", &amountIntervals);
 
    deque<int> primeList = returnPrimes((int)sqrt((double)MAX_NUMBER));

    for(int index=0; index < amountIntervals; index++)
    {
        scanf("%d %d", &bottomLimit, &upperLimit);
        if(bottomLimit == 2)
        {
            printf("%d\n", bottomLimit);
        }

        int increment;
        if(bottomLimit % 2 == 0)
        {
            increment = 1;
        }
        else
        {
            increment = 0;
        }
        for(int number=bottomLimit+increment; number <= upperLimit; number+=2)
        {
            int sqrtNumber = (int)sqrt((double)number);
            bool isPrime = true;
            for(deque<int>::iterator it = primeList.begin(); *it <= sqrtNumber; it++)
            {
                if(number % *it == 0)
                {
                    isPrime = false;
                    break;
                }
            }
            
            if(isPrime)
            {
                printf("%d\n", number);
            }
        }
    }
    
    return 0;
}
