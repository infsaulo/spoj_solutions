#include<algorithm>
#include <vector>
#include <cstdio>

using namespace std;

int main()
{
    vector<int> numbers;
    int amount_numbers;
    scanf("%d", &amount_numbers);
    for(int index=0; index < amount_numbers; index++)
    {
        int number;
        scanf("%d", &number);
        numbers.push_back(number);
    }    
    sort(numbers.begin(), numbers.end());
    for(int index=0; index < amount_numbers; index++)
    {
        printf("%d\n", numbers[index]);
    }

    return 0;
}
