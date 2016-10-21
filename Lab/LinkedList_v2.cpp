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
        ~list();
        bool insert(T,int);
        bool remove(int);
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
bool list<T>::remove(int i){
     if (i < size && size != 0 && i >= 0){
         if (i == 0){
             node<T> *nodeDel = head;
             head = head->next;
             nodeDel->next = NULL;
             delete nodeDel;
         } else if (i == size - 1){
             node<T> *tmp = head;
             for(int j = 0; j < size - 2; j++) {
                 tmp = tmp->next;
             }
             delete tail;
             tail = tmp;
             tail->next = NULL;
         } else {
             node<T> *tmp = head;
             for(int j = 0; j < i - 1; j++) {
                 tmp = tmp->next;
             }
             node<T> *nodeDel = tmp->next;
             tmp->next = nodeDel->next;
             nodeDel->next = NULL;
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
        node<T> *tmp = head;
        for(int j = 0; j < i; j++) {
        tmp = tmp->next;
        }
        return tmp->item;
    } else {
        throw 401;
    }
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
        } else {
            try{
                cin >> indx;
                cout << l.get(indx) << endl;
            } catch(int err){
                if (err == 401){ cout << "POSITION OUT OF BOUNDS" << endl; }
            }
        }
    }
    return 0;
}
