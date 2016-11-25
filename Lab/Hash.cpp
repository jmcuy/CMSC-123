#include <iostream>
#include <cmath>
using namespace std;

template <class T>
class myhash {
    private:
        T* table;
        int size;
        int max;
        int n;
        int d;
        int w;
        int z;
    public:
        myhash();
        int insert(T item);
        int search(T item);
};

template <class T>
myhash<T>::myhash() {
    w = 16;
    z = 60147;
    n = 0;
    size = 0;
    d = 9;
    max = pow(2, d);
    table = new T[max];
}

template <class T>
int myhash<T>::insert(T item) {
    int x = *item;
    int firstpart = z * x;
    int secondpart = pow(2,w);
    int thirdpart = pow(2,w-d);
    int fourthpart = firstpart % secondpart;
    int index = fourthpart / thirdpart;
    //int index = ((z*x) % pow(2, w))/pow(2, w-d);
    
    int collisions = 0;
    int hashindex = index;
    while(table[index % max] != NULL) {
        index++;
        collisions++;
        if(index % max == hashindex) {
            throw 101; // hash table is full
        }
    }
    table[index] = item;
    return collisions; 
}

template <class T>
int myhash<T>::search(T item) {
    int x = *item;
    int firstpart = z * x;
    int secondpart = pow(2,w);
    int thirdpart = pow(2,w-d);
    int fourthpart = firstpart % secondpart;
    int index = fourthpart / thirdpart;
    
    int collisions = 0;
    int hashindex = index;
    while(table[index % max] == NULL || *(table[index % max]) != x) {
        if(table[index % max] == NULL) {
            index++;
        } else {
            index++;
            collisions++;
        }
        if(index % max == hashindex) {
            throw 202; // item not found
        }
    }
    return collisions;
}


int main() {
    
    int cases;
    cin >> cases;
    while(cases > 0) {
        myhash<int*> h;
        int insertnum;
        cin >> insertnum;
        while(insertnum > 0) {
            int insertitem;
            cin >> insertitem;
            try {
                cout << h.insert(&insertitem) << " ";
            } catch(int err) {
                cout << "hash table is full";
            }
            insertnum--;
        }
        cout << endl;
        int searchitem;
        cin >> searchitem;
        try {
            cout << h.search(&searchitem) << endl;
        } catch(int err) {
            cout << "item not found" << endl;
        }
        cases--;
    }
    return 0;
}
