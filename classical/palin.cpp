#include <deque>
#include <algorithm>
#include <cstdio>

#define MAX_AMOUNT_DIGITES 1000001
using namespace std;

bool isLessThan(deque<char>& palindrome, char* originalNumber, int indexPivot1, int originalSize)
{
    if(originalSize < palindrome.size())
    {
        return false;
    }

    if(palindrome[indexPivot1] > originalNumber[indexPivot1] )
    {
        return false;
    }
    
    return true;
}

bool makeHalfPalindrome(deque<char>& palindrome, int indexPivot1, int indexPivot2)
{
    bool lessEqualThan = true;
    bool alreadyDecided = false;
    int increment = 0;

    if(indexPivot1 == indexPivot2)
    {
        increment++;
    }

    for(int index1 = indexPivot1 - increment, index2 = indexPivot2 + increment; index1 >= 0; index1--, index2++)
    {
        if(palindrome[index1] > palindrome[index2] && !alreadyDecided)
        {
            lessEqualThan = false;
            alreadyDecided = true;
        }
        if(palindrome[index1] < palindrome[index2] && !alreadyDecided)
        {
            alreadyDecided = true;
        }
        palindrome[index2] = palindrome[index1];
    }

    return lessEqualThan;
}

void nextPalindrome(deque<char>& palindrome, char* originalNumber, int originalSize)
{
    long size = palindrome.size();
    bool isEven = size % 2 == 0;
    
    int indexPivot1, indexPivot2;
    if(isEven)
    {
        indexPivot1 = (size / 2) - 1;
        indexPivot2 = (size / 2);
    }
    else
    {
        indexPivot1 = (size / 2);
        indexPivot2 = indexPivot1;
    }

        bool firstLoop = true;
        bool isLessEqual = true;
        do
        {
            if(firstLoop)
            {
                firstLoop = false;
                isLessEqual = makeHalfPalindrome(palindrome, indexPivot1, indexPivot2);
            }
            if(isLessEqual)
            {
                if(indexPivot1 == indexPivot2)
                {
                    if(palindrome[indexPivot1] == '9')
                    {
                        palindrome[indexPivot1] = '0';
                        if(!isLessThan(palindrome, originalNumber, indexPivot1, originalSize) )
                        {
                            break;
                        }
                        indexPivot1--;
                        indexPivot2++;
                    }
                    else
                    {
                        palindrome[indexPivot1] += 1;
                        if(!isLessThan(palindrome, originalNumber, indexPivot1, originalSize) )
                        {
                            break;
                        }
                    }
                }
                else
                {
                    if(palindrome[indexPivot1] == '9')
                    {
                        palindrome[indexPivot1] = '0';
                        palindrome[indexPivot2] = '0';
                        if(!isLessThan(palindrome, originalNumber, indexPivot1, originalSize) )
                        {
                            break;
                        }
                        indexPivot1--;
                        indexPivot2++;
                    }
                    else
                    {
                        palindrome[indexPivot1] += 1;
                        palindrome[indexPivot2] += 1;
                        if(!isLessThan(palindrome, originalNumber, indexPivot1, originalSize) )
                        {
                            break;
                        }
                    }
                }
            }
            else
            {
                break;
            }
        }while(indexPivot1 >= 0);

        if(indexPivot1 < 0)
        {
            palindrome.push_front('1');
            nextPalindrome(palindrome, originalNumber, originalSize);
        }
}

int main()
{
    int amountNumbers;
    scanf("%d", &amountNumbers);
    
    while(amountNumbers--)
    {
        char number[MAX_AMOUNT_DIGITES];
        scanf("%s", number);
        deque<char> palindrome;
        char *ptr = number;
        int originalSize = 0;
        while(*ptr)
        {
            palindrome.push_back(*ptr);
            ptr++;
            originalSize++;
        }
        
        nextPalindrome(palindrome, number, originalSize);
        ptr = number;
        for(deque<char>::iterator it = palindrome.begin(); it != palindrome.end(); it++, ptr++)
        {
            *ptr = *it;
        }
        *ptr = '\0';

        printf("%s\n", number);
    }

    return 0;
}
