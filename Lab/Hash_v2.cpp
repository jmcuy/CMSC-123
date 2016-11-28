#include <iostream>
#include <cmath>
#include <vector>
#include <string>
using namespace std;

template <class T>
class myhash {
    private:
        vector<T> table[1 << 10];
        int size;
        int max;
        int n;
        int d;
        int w;
        int z;
        int hashfunction;
    public:
        myhash(int hashfuntion);
        int insert(T item);
        int search(T item);
};

template <class T>
myhash<T>::myhash(int hashfunction) {
    w = 31;
    z = 60147;
    n = 0;
    size = 0;
    d = 10;
    max = pow(2, d);
    this->hashfunction = hashfunction;
}

template <class T>
int myhash<T>::insert(T item) {
    unsigned int x = 0;
    if(hashfunction == 1) {
        for(int i = 0; i < item.length(); i++) {
            x = 31*x + item[i];
        }
    } else {
        unsigned int high, i = 0;
        while(item[i] != '\0') {
            x = (x << 4) + item[i++];
            if(high = (x & 0xF0000000))
                x ^= high >> 24;
            x &= ~high;
        }
    }
    
    unsigned int firstpart = z * x;
    unsigned int secondpart = pow(2,w);
    unsigned int thirdpart = pow(2,w-d);
    unsigned int fourthpart = firstpart % secondpart;
    unsigned int index = fourthpart / thirdpart;
    //int index = ((z*x) % pow(2, w))/pow(2, w-d);
    
    table[index].push_back(item);
    return table[index].size();
}

template <class T>
int myhash<T>::search(T item) {
    unsigned int x = 0;
    if(hashfunction == 1) {
        for(int i = 0; i < item.length(); i++) {
            x = 31*x + item[i];
        }
    } else {
        unsigned int high, i = 0;
        while(item[i] != '\0') {
            x = (x << 4) + item[i++];
            if(high = (x & 0xF0000000))
                x ^= high >> 24;
            x &= ~high;
        }
    }
    
    unsigned int firstpart = z * x;
    unsigned int secondpart = pow(2,w);
    unsigned int thirdpart = pow(2,w-d);
    unsigned int fourthpart = firstpart % secondpart;
    unsigned int index = fourthpart / thirdpart;
    
    int collisions = 0;
    
    vector<T> v = table[index];
    if(v.size() == 0 || (v.front().compare(item) == 0)) {
        return 1;
    } else {
        for(int i = 1; i < v.size(); i++) {
            if(v[i].compare(item) == 0) {
                return i+1;
            }
        }
    }
    return v.size() + 1;
}

int main() {
    
    int cases;
    cin >> cases;
    while(cases > 0) {
        myhash<string> h(1);
        myhash<string> g(2);
        int insertnum;
        cin >> insertnum;
        while(insertnum > 0) {
            string item;
            cin >> item;
            cout << h.insert(item) << " ";
            g.insert(item);
            insertnum--;
        }
        //cout << endl;
        string searchitem;
        cin >> searchitem;
        cout << h.search(searchitem) << " ";
        cout << g.search(searchitem) << endl;
        cases--;
    }
    return 0;
}
