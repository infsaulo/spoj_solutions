#include <cstdio>
#include <cstdlib>
#include <stack>
#include <vector>
#include <string> 

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
    table = new vector<T*>(size, (T*)NULL);
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

    vector<T*> *resizedTable = new vector<T*>(size, (T*)NULL);
    for(typename vector<T*>::iterator it = table->begin(); it != table->end(); it++)
    {
        if(*it)
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
    HashTable<Entry> *priorityTable; 
    string rpn;

    public:
    RPNConverter(char *expression);
    string getRPN();
    ~RPNConverter();

    private:
    void pushOperator(char optor);
    char popOperator();
    bool isTopHigherPriority(char optor);
    int typeChar(char ch);
};

RPNConverter::RPNConverter(char *expression)
{
    this->expression = expression;

    // Initalize the table of priorities
    priorityTable = new HashTable<Entry>(5); // 5 diferent operators
    priorityTable->insert(new Entry('+', 1));
    priorityTable->insert(new Entry('-', 2));
    priorityTable->insert(new Entry('*', 3));
    priorityTable->insert(new Entry('/', 4));
    priorityTable->insert(new Entry('^', 5));
}

int RPNConverter::typeChar(char ch)
{
    if(ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^')
    {
        // It's a operator
        return 0;
    }

    if(ch == ')')
    {
        // It's a end of parenthesis
        return 1;
    }

    if(ch == '(')
    {
        // It's a begin of parenthesis
        return 2;
    }

    // It's a alphabetic character.
    return 3;
}

string RPNConverter::getRPN()
{
    char *ptr = expression;
    while(*ptr)
    {
        switch(typeChar(*ptr))
        {
            case 0: // operator
            pushOperator(*ptr);
            break;
            case 1: // end of parenthesis
            while( operatorStack.top() != '(')
            {
                rpn += popOperator();
            }
            popOperator();
            break;
            case 3: // alphabetic character
            rpn += *ptr;
            break;
            default: // begin of parenthesis
            operatorStack.push(*ptr);
            break;
        }
        ptr++;
    }

    while(!operatorStack.empty())
    {
        char ch = popOperator();
        if(ch != '(')
        {
            rpn += ch;
        }
    }

	return rpn;
}

void RPNConverter::pushOperator(char optor)
{
    while(!operatorStack.empty() && operatorStack.top() != '(' && isTopHigherPriority(optor))
    {
        rpn += popOperator();
    }

    operatorStack.push(optor);
}

char RPNConverter::popOperator()
{
    char topOptor = operatorStack.top();
    operatorStack.pop();
	return topOptor;
}

bool RPNConverter::isTopHigherPriority(char optor)
{
    return priorityTable->retrieve(operatorStack.top())->getValue() > priorityTable->retrieve(optor)->getValue();
}

RPNConverter::~RPNConverter()
{
    delete priorityTable;
}

int main()
{
    int amountExpressions;
    scanf("%d", &amountExpressions);

    for(int index=0; index < amountExpressions; index++)
    {
        char *expression = new char[400];
        scanf("%s", expression);
        RPNConverter converter(expression);
        
        string rpn = converter.getRPN();
        printf("%s\n", rpn.c_str());

        delete expression;
    }

    return 0;
}
