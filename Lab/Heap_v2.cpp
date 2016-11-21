#include <iostream>
#include <array>

using namespace std;

template <class T>
class heap {
    private:
        int size;
        T* items;
    public:
        heap(int);
        ~heap();
        void insert(T);
        void display();
        void remove();
};

template <class T>
heap<T>::heap(int num) {
    size = 0;
    items = new T[num + 1];
}

template <class T>
heap<T>::~heap() {
    delete[] items;
}

template <class T>
void heap<T>::insert(T item) {
    if (size == 0)
        items[++size] = item;
    else{
        int i = ++size;
        items[i] = item;
        int temp;
        while ( i / 2 > 0){
            if(items[i] < items[i / 2]) {
                temp = items[i];
                items[i] = items[i / 2];
                items[i / 2] = temp;
                i = i / 2;
            } else {
                break;
            }
        }
    }      
}

template <class T>
void heap<T>::remove() {
    items[1] = items[size--];
    int i = 1;
    while(true) {
        if((i * 2) + 1 > size && i * 2 <= size) {
            if(items[i] > items[i * 2]) {
                int tmp = items[i];
                items[i] = items[i * 2];
                items[i * 2] = tmp;
                i = i * 2;
            } else {
               break; 
            }
        } else if(i * 2 > size) {
            break;
        } else {
            if(items[i * 2] < items[(i * 2) + 1]) {
                if(items[i] > items[i * 2]) {
                    int tmp = items[i];
                    items[i] = items[i * 2];
                    items[i * 2] = tmp;
                    i = i * 2;                    
                } else {
                    break;
                }
            } else {
                if(items[i] > items[(i * 2) + 1]) {
                    int tmp = items[i];
                    items[i] = items[(i * 2) + 1];
                    items[(i * 2) + 1] = tmp;
                    i = (i * 2) + 1;                    
                } else {
                    break;
                }
            }
        }
    }
    
}

template <class T>
void heap<T>::display() {
    for(int i = 1; i < size + 1; i++) {
        cout << items[i] << " ";
    }
    cout << endl;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int cases;
    cin >> cases;
    while(cases > 0) {
        int elements;
        cin >> elements;
        heap<int> h(elements);
        while(elements > 0) {
            int item;
            cin >> item;
            h.insert(item);
            elements--;
        }
        int deletenum;
        cin >> deletenum;
        while(deletenum > 0) {
            h.remove();
            h.display();
            deletenum--;
        }
        cases--;
    }
    return 0;
}
