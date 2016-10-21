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
        int getSize();
        void enqueue(T);
        bool dequeue();
        T front();
        T rear();
        void display();
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
        enqueue(tmp->item);
        tmp = tmp->next;
    }
}

template <class T>
list<T>::~list() {
    while (size != 0){
        dequeue();
    }
}

template <class T>
void list<T>::enqueue(T val){
    node<T> *nodeNew = new node<T>(val);
    if (head == NULL && tail == NULL){
        head = nodeNew;
        tail = nodeNew;
    } else {
        tail->next = nodeNew;
        tail = nodeNew;
    }
    size++;
}

template <class T>
bool list<T>::dequeue(){
    if(size != 0) {
        node<T> *nodeDel = head;
        head = head->next;
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
T list<T>::front() {
    if(size != 0) {
     return head->item;   
    } else {
        throw 404;
    }
}

template <class T>
T list<T>::rear() {
    if(size != 0) {
     return tail->item;   
    } else {
        throw 404;
    }
}

template <class T>
void list<T>::display(){
    node<T> *nodeNew = head;
    for (int i = 0; i < size; i++){
        cout << nodeNew->item << " ";
        nodeNew = nodeNew->next;
    }
    cout << endl;
}

int main() {
    int cases, type, val;
    cin >> cases;
    list<int> l;
    for (int i = 0; i < cases; i++){
        cin >> type;
        if (type == 1){ 
            cin >> val;
            l.enqueue(val);
            l.display(); 
        }else if (type == 2){
            if(l.dequeue()) {
                l.display();
            } else {
                cout<<endl;
            }
        } else if(type == 3){
            try {
                cout << l.front() << endl;   
            } catch(int err) {
                cout<<"queue is empty."<<endl;
            }
        } else if(type == 4){
            try {
                cout << l.rear() << endl;   
            } catch(int err) {
                cout<<"queue is empty."<<endl;
            }
        } else {
            l.display();
        }
    }
    return 0;
}
