#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void decide_war(vector<int> *divisions_bajtocja, vector<int> *divisions_megabajtolandia)
{
    sort(divisions_bajtocja->begin(), divisions_bajtocja->end());
    sort(divisions_megabajtolandia->begin(), divisions_megabajtolandia->end());
    while(!divisions_bajtocja->empty() && !divisions_megabajtolandia->empty())
    {
        if(divisions_bajtocja->back() == divisions_megabajtolandia->back())
        {
            divisions_bajtocja->pop_back();
            divisions_megabajtolandia->pop_back();
        }
        else
            if(divisions_bajtocja->back() > divisions_megabajtolandia->back())
            {
                cout << "Bajtocja" << endl;
                return;
            }
            else
            {
                cout << "Megabajtolandia" << endl;
                return;
            }
    }

    if(divisions_bajtocja->empty() && divisions_megabajtolandia->empty())
    {
        cout << "Draw" << endl;
    }
    else
        if(divisions_bajtocja->empty())
        {
            cout << "Megabajtolandia" << endl;
        }
        else
        {
            cout << "Bajtocja" << endl;
        }
}

int main()
{
    cin.sync_with_stdio(false);

    // Read the number of test cases
    int amount_test_cases;
    cin >> amount_test_cases;
    int index_case;
    for(index_case=0; index_case < amount_test_cases; index_case++)
    {
        int amount_divisions_bajtocja;
        cin >> amount_divisions_bajtocja;
        vector<int> divisions_bajtocja;;
        int index_divisions, division;
        for(index_divisions=0; index_divisions < amount_divisions_bajtocja; index_divisions++)
        {
            cin >> division;
            divisions_bajtocja.push_back(division);
        }
        int amount_divisions_megabajtolandia;
        cin >> amount_divisions_megabajtolandia;
        vector<int> divisions_megabajtolandia;
        for(index_divisions=0; index_divisions < amount_divisions_megabajtolandia; index_divisions++)
        {
            cin >> division;
            divisions_megabajtolandia.push_back(division);
        }

        decide_war(&divisions_bajtocja, &divisions_megabajtolandia);
   }
}
