#include <iostream>

using namespace std;
template <class T>
class node{
    public:
        T item;
        node<T> *next;
        node();
        node(T);
};

template <class T>
node<T>::node() {

}

template <class T>
node<T>::node(T n) {
    item = n;
    next = NULL;
}

template <class T>
class list{
    private:
        int size;
        node<T> *head,*tail;
    public:
        list();
        list(const list&);
        bool insert(T,int);
        T get(int);
        int getSize();
};

template <class T>
list<T>::list() {
    size = 0;
    head = NULL;
    tail = NULL;
}

template <class T>
list<T>::list(const list& l) {
    size = 0;
    head = NULL;
    tail = NULL;
    node<T> *tmp = l.head;
    for (int i = 0; i < l.size; i++){
        insert(tmp->item, i);
        tmp = tmp->next;
    }
}

template <class T>
bool list<T>::insert(T val, int i){
     if (i > -1 && i <= size){
         node<T> *nodeNew = new node<T>(val);
         if (head == NULL && tail == NULL){
             head = nodeNew;
             tail = nodeNew;
         } else if (i == 0){
             nodeNew->next = head;
             head = nodeNew;
         } else if (i == size){
             tail->next = nodeNew;
             tail = nodeNew;
         } else {
             node<T> *tmp = head;
             for(int j = 0; j < i - 1; j++) {
                 tmp = tmp->next;
             }
             nodeNew->next = tmp->next;
             tmp->next = nodeNew;
         }
         size++;
      return true;
     }
    return false;
}

template <class T>
T list<T>::get(int i){
    node<T> *tmp = head;
    for(int j = 0; j < i; j++) {
    tmp = tmp->next;
    }
    return tmp->item;
}

template <class T>
int list<T>::getSize(){
    return size;
}

template <class T>
void display(list<T> a){
    for (int i = 0; i < a.getSize(); i++){
        cout << a.get(i) << " ";
    }
    cout << endl;
}
int main() {
    int cases;

    cin >> cases;
    list<int> l;
    for (int i = 0; i < cases; i++){
        int val, indx;
        cin >> indx;
        cin >> val;
        l.insert(val, indx);
        display(l);

    }
    return 0;
}
