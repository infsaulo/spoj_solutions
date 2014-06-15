#include <deque>
#include <algorithm>
#include <cstdio>
#include <iostream>

#define MAX_AMOUNT_DIGITES 1000000
using namespace std;

bool isPalindrome(deque<char> palindrome)
{
    deque<char>::iterator it1 = palindrome.begin();
    deque<char>::iterator it2 = palindrome.end();
    it2--;

    while(it2 > it1)
    {
        if(*it2 != *it1)
        {
            return false;
        }
        it2--;
        it1++;
    }

    return true;
}

void addOne(deque<char>& palindrome)
{
    bool carryOut = false;
    deque<char>::iterator it = palindrome.end();
    it--;
    do
    {
        if(*it == '9')
            {
                *it = '0';
                carryOut = true;
                if(it == palindrome.begin())
                {
                    break;
                }
                it--;
            }
            else
            {
                *it += 1;
                carryOut = false;
            }
    }while(carryOut);

    if(carryOut)
    {
        if(*it == '0')
        {
            palindrome.push_front('1');
        }
        else
        {
            *it += 1;
        }
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
        while(*ptr)
        {
            palindrome.push_back(*ptr);
            ptr++;
        }

        do
        {
            addOne(palindrome);
        }while(!isPalindrome(palindrome));

        for(deque<char>::iterator it = palindrome.begin(); it != palindrome.end(); it++)
        {
            printf("%c", *it);
        }
        printf("\n");
    }

    return 0;
}
