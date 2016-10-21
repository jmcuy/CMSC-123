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
        node<T> *top;
    public:
        list();
        list(const list&);
        void copy(node<T>*);
        ~list();
        int getSize();
        void push(T);
        bool pop();
        T peek();
        void display();
};

template <class T>
list<T>::list() {
    size = 0;
    top = NULL;
}

template <class T>
list<T>::list(const list& l) {
    size = 0;
    top = NULL;
    node<T> *tmp = l.top;

    copy(tmp);
}

template <class T>
void list<T>::copy(node<T> *tmp) {
    if (tmp != NULL){
        copy(tmp->next);
        push(tmp->item);
    }
}


template <class T>
list<T>::~list() {
    while (size != 0){
        pop();
    }
}

template <class T>
void list<T>::push(T val){
    node<T> *nodeNew = new node<T>(val);
    nodeNew->next = top;
    top = nodeNew;    
    size++;
}

template <class T>
bool list<T>::pop(){
    if(size != 0) {
        node<T> *nodeDel = top;
        top = top->next;
        nodeDel->next = NULL;
        delete nodeDel;        
    } else {
        return false;
    }
    size--;
    return true;
}

template <class T>
int list<T>::getSize(){
    return size;
}

template <class T>
T list<T>::peek() {
    if(size != 0) {
     return top->item;   
    } else {
        throw 404;
    }
}

template <class T>
void list<T>::display(){
    node<T> *nodeNew = top;
    for (int i = 0; i < size; i++){
        cout << nodeNew->item << " ";
        nodeNew = nodeNew->next;
    }
    cout << endl;
}

void display(list<int> s) { s.display(); }

int main() {
    int cases, type, val;
    cin >> cases;
    list<int> l;
    for (int i = 0; i < cases; i++){
        cin >> type;
        if (type == 1){ 
            cin >> val;
            l.push(val);
            l.display(); 
        }else if (type == 2){
            if(l.pop()) {
                l.display();
            } else {
                cout<<endl;
            }
        } else if(type == 3){
            try {
                cout << l.peek() << endl;   
            } catch(int err) {
                cout<<"stack is empty."<<endl;
            }
        } else {
            l.display();
        }
    }
    return 0;
}
