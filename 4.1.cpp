#include <iostream>

using namespace std;

typedef char nametype[20];

struct celltype {
    nametype element;

    celltype* next;
};

const int DICT_SIZE = 5;
const int FOOD_SIZE = 15;

typedef celltype* DICTIONARY[DICT_SIZE];
const nametype food[FOOD_SIZE] = { "apple", "apple", "milk", "bread", "potato", "tomato", "carrot", "cucumber", "pear", "egg", "honey", "rice", "lemon", "watermelon", "melon" };


int h(const nametype x) {
    int sum = 0;

    for (unsigned int i = 0; i < strlen(x); i++)
        sum += (int)x[i];

    return sum % (DICT_SIZE);
}

bool Compare(const nametype one, const nametype two)
{
    if (strlen(one) != strlen(two))
        return false;
    for (int i = 0; i < strlen(two); i++)
        if (one[i] != two[i])
            return false;

    return true;
}


void MAKENULL(DICTIONARY A)
{
    for (int i = 0; i < DICT_SIZE; i++)
    {
        A[i] = nullptr;
        A[i] = new celltype;
        A[i]->next = nullptr;
    }
}

bool MEMBER(const nametype x, DICTIONARY A)
{
    celltype* current;

    current = A[h(x)];

    while (current != nullptr)
    {
        if (Compare(current->element, x))
        {
            return true;
        }
        else
        {
            current = current->next;
        }
    }

    return false;
}

void INSERT(const nametype x, DICTIONARY A)
{
    int bucket;

    celltype* oldheader;

    if (!MEMBER(x, A))
    {
        bucket = h(x);

        oldheader = A[bucket];

        A[bucket] = new celltype;

        int j = 0;

        for (; j < strlen(x); j++)
            A[bucket]->element[j] = x[j];

        A[bucket]->element[j] = '\0';

        A[bucket]->next = oldheader;
    }
}

void DELETE(const nametype x, DICTIONARY A)
{
    int bucket;

    celltype* current;

    bucket = h(x);

    if (A[bucket] != nullptr)
    {
        if (Compare(A[bucket]->element, x))  // перший елемент
            A[bucket] = A[bucket]->next;

        else
        {
            current = A[bucket];

            while (current->next != nullptr)
                if (Compare(current->next->element, x))
                {
                    current->next = current->next->next;
                    break;
                }
                else
                {
                    current = current->next;
                }
        }
    }
}

void PRINT(DICTIONARY A)
{
    celltype* current;

    for (int i = 0; i < DICT_SIZE; i++) {
        cout << i + 1 << ". \t";

        current = A[i];

        while (current != nullptr) {

            if(current->next != nullptr)
                cout << current->element << ' ';

            current = current->next;
        }

        cout << endl;
    }
}

int main()
{
    DICTIONARY A;

    MAKENULL(A);

    for (int i = 0; i < FOOD_SIZE - 1; i++)
        INSERT(food[i], A);

    cout << "\nShow dictionery\n" << endl;

    PRINT(A);

    DELETE(food[0], A);

    cout << "\nShow dictionery\n" << endl;

    PRINT(A);

	return 0;
}