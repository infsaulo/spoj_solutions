#include <cstdio>
#include <cstdlib>
#include <stack>
#include <vector>

using namespace std;

// T must be a <key, value> entry being key a string. T must implements getKey, getVale, setKey, setValue.
template<class T>
class HashTable
{
    float loadFactor;
    int size;
    vector<T*> *table;

    public:

    HashTable(int size);
    void insert(T *element);
    T* retrieve(char key);
    int hashFunction(char key);
    float getLoadFactor();
    void setLoadFactor(float loadFactor);
    void resize();
    ~HashTable();
};

template <class T>
HashTable<T>::HashTable(int size)
{
    table = new vector<T*>(size, NULL);
    this->size = size;
    loadFactor = 0;
}

template <class T>
void HashTable<T>::insert(T *element)
{
    int hashedPosition = hashFunction(element->getKey());

    while((*table)[hashedPosition] != NULL)
    {
        hashedPosition++; // linear hashing to deal with colision
        hashedPosition %= size;
    }

    (*table)[hashedPosition] = element;
    setLoadFactor(getLoadFactor() + 1.0/size);

    // Verify the load factor. Idealy it can't be higher than 80%
    if(getLoadFactor() > 0.8)
    {
        resize();
    }
}

// Resize to turn down the load factor to 0.5
template <class T>
void HashTable<T>::resize()
{
    int newSize = (int)((getLoadFactor()/0.5) * size);
    size = newSize;
    setLoadFactor(0.0);

    vector<T*> *resizedTable = new vector<T*>(size, NULL);
    for(typename vector<T*>::iterator it = table->begin(); it != table->end(); it++)
    {
        int hashedPosition = hashFunction((*it)->getKey());
        while((*resizedTable)[hashedPosition] != NULL)
        {
            hashedPosition++;
            hashedPosition %= size;
        }

        (*resizedTable)[hashedPosition] = *it;
        setLoadFactor(getLoadFactor() + 1.0/size);
    }

    delete table;
    table = resizedTable;
}

template <class T>
float HashTable<T>::getLoadFactor()
{
    return loadFactor;
}

template <class T>
void HashTable<T>::setLoadFactor(float loadFactor)
{
    this->loadFactor = loadFactor;
}

template <class T>
T* HashTable<T>::retrieve(char key)
{
    int hashedPosition = hashFunction(key);
    int originHashedPosition = hashedPosition;

    while((*table)[hashedPosition]->getKey() != key)
    {
        hashedPosition++;
        hashedPosition %= size;
        if(hashedPosition == originHashedPosition)
        {
            return NULL;
        }
    }

    return (*table)[hashedPosition];
}

template <class T>
int HashTable<T>::hashFunction(char key)
{
    return key % size;
}

template <class T>
HashTable<T>::~HashTable()
{
    for(int index=0; index < size; index++)
    {
        delete (*table)[index];
    }

    delete table;
}

class Entry
{
    char key;
    int value;

    public:
    Entry(char key, int value);
    void setKey(char key);
    void setValue(int value);
    char getKey();
    int getValue();
};

Entry::Entry(char key, int value)
{
    setKey(key);
    setValue(value);
}

void Entry::setKey(char key)
{
    this->key = key;
}

void Entry::setValue(int value)
{
    this->value = value;
}

char Entry::getKey()
{
    return key;
}

int Entry::getValue()
{
    return value;
}

class RPNConverter
{
    char *expression;
    stack<char> operatorStack;
    HashTable<Entry> *hashTable; 

    public:
    RPNConverter(char *expression);
    vector<char> getRPN();

    private:
    void pushOperator(char optor);
    char popOperator();
    bool isTopHigherPriority(char optor);
    ~RPNConverter();
};

RPNConverter::RPNConverter(char *expression)
{
}

vector<char> RPNConverter::getRPN()
{
	vector<char> rpn;
	return rpn;
}

void RPNConverter::pushOperator(char optor)
{
}

char RPNConverter::popOperator()
{
	return 'a';
}

bool RPNConverter::isTopHigherPriority(char optor)
{
    return false;
}

RPNConverter::~RPNConverter()
{
    delete expression;
}

int main()
{
    return 0;
}
