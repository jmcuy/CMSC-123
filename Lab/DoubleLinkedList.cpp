#include <iostream>

using namespace std;
template <class T>
class node{
    public:
        T item;
        node<T> *next, *prev;
        node();
        node(T);
};

template <class T>
node<T>::node() {
    next = NULL;
    prev = NULL;
}

template <class T>
node<T>::node(T n) {
    item = n;
    next = NULL;
    prev = NULL;
}

template <class T>
class list{
    public:
    struct iterator{
        node<T>* pointer;
        iterator& operator++(int){pointer = pointer->next; return (*this);}
        T operator*(){return pointer->item;}
        bool operator!=(const iterator& it){return pointer!=it.pointer;}
    };
    private:
        int size;
        node<T> *head,*tail;
        iterator iter;
    public:
        list();
        list(const list&);
        ~list();
        bool insert(T,int);
        bool remove(int);
        T get(int);
        void set (int, T);
        int getSize();
        iterator& begin(){iter.pointer = head; return iter;}
        iterator& end(){iter.pointer = tail->next; return iter;}
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
list<T>::~list() {
    while (size != 0){
        remove(0);
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
             head->prev = nodeNew;
             nodeNew->next = head;
             head = nodeNew;
         } else if (i == size){
             tail->next = nodeNew;
             nodeNew->prev = tail;
             tail = nodeNew;
         } else {
             node<T> *tmp = head;
             for(int j = 0; j < i - 1; j++) {
                 tmp = tmp->next;
             }
             nodeNew->next = tmp->next;
             nodeNew->prev = tmp;
             node<T> *nodeL = tmp->next;
             tmp->next = nodeNew;
             nodeL->prev = nodeNew; 
         }
         size++;
      return true;
     }
    return false;
}

template <class T>
bool list<T>::remove(int i){
     if (i < size && size != 0 && i >= 0){
         if (i == 0){
             if (size > 1){
                node<T> *nodeDel = head;
                head = head->next;
                head->prev = NULL;
                nodeDel->next = NULL;
                nodeDel->prev = NULL;
                delete nodeDel;
             } else {
                delete head;
                head = NULL;
                tail = NULL;
             }
         } else if (i == size - 1){
             node<T> *tmp = tail->prev;
             node<T> *deL = tail;
             tail = tmp;
             tail->next = NULL;
             deL->next = NULL;
             deL->prev = NULL;
             delete deL;
         } else {
             node<T> *tmp = head;
             for(int j = 0; j < i - 1; j++) {
                 tmp = tmp->next;
             }
             node<T> *nodeDel = tmp->next;
             node<T> *nodeAfterDel = nodeDel->next;
             tmp->next = nodeAfterDel;
             nodeAfterDel->prev = tmp;
             nodeDel->next = NULL;
             nodeDel->prev = NULL;
             delete nodeDel;   
         }
         size--;
      return true;
     }
    return false;
}

template <class T>
T list<T>::get(int i){
    if (i >= 0 && i < size){
        int mid = size / 2;
        node<T> *tmp;
        if (i <= mid){
            tmp = head;
            for(int j = 0; j < i; j++) {
            tmp = tmp->next;
            }
        } else {
            tmp = tail;
            for(int j = size-1; j > i; j--) {
            tmp = tmp->prev;
            }
        }
        return tmp->item;
    } else {
        throw 401;
    }
}

template <class T>
void list<T>::set(int i, T val){
    if (i >= 0 && i < size){
        int mid = size / 2;
        node<T> *tmp;
        if (i <= mid){
            tmp = head;
            for(int j = 0; j < i; j++) {
            tmp = tmp->next;
            }
        } else {
            tmp = tail;
            for(int j = size-1; j > i; j--) {
            tmp = tmp->prev;
            }
        }
        tmp->item = val;
    } else {
        throw 401;
    }
}

template <class T>
int list<T>::getSize(){
    return size;
}

template <class T>
void display(list<T> l){
    if (l.getSize() != 0){
        for( list<int>::iterator i = l.begin() ; i != l.end(); i++){
            cout<< *i <<" ";
        }
    }
    cout<<endl;
}

int main() {
    int cases, indx, type, val;
    cin >> cases;
    list<int> l;
    for (int i = 0; i < cases; i++){
        cin >> type;
        if (type == 1){ 
            cin >> indx;
            cin >> val;
            l.insert(val, indx);
            display(l); 
        }else if (type == 2){
            cin >> indx;
            l.remove(indx);
            display(l);
        } else if (type == 3){
            try{
                cin >> indx;
                cout << l.get(indx) << endl;
            } catch(int err){
                if (err == 401){ cout << "POSITION OUT OF BOUNDS" << endl; }
            }
        } else {
            try{
                cin >> indx;
                cin >> val;
                l.set(indx, val);
                display(l);
            } catch(int err){
                if (err == 401){ cout << "POSITION OUT OF BOUNDS" << endl; }
            }
        }
    }
    return 0;
}
