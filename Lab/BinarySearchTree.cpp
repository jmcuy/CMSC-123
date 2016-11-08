#include <iostream>
using namespace std;

template <class T>
class bstnode{
public:
    T item;
    bstnode *left;
    bstnode *right;
    bstnode *prnt;
    bstnode(){
        item = NULL;
        left = right = prnt = NULL;
    }
    
    bstnode(T x){
        item = x;
        left = right = prnt = NULL;
    }
    
};

template <class T>
class bst{
private:
    //what should be its lone private member?
    //bstnode<T> *root;
public:
    bstnode<T> *root;
    bst(){ root = NULL;}
    //~bst();
    //provide the necessary arguments
    void insert(T item); 
    bool remove();
    int search(T item);
    //you may include other auxilliary operations if need be
};
template <class T>
void bst<T>::insert(T item){
    int id;
    int LEFT_ID = 0;
    int RIGHT_ID = 1;
    bstnode<T> *add = new bstnode<T>(item);
    bstnode<T> *ancs = NULL;
    bstnode<T> *temp = root;
    if (root == NULL){
        root = add;
    } else {
        while (temp != NULL){
            ancs = temp;
            if (temp->item > item){
                temp = temp->left;
                id = LEFT_ID;
            }
            else {
                temp = temp->right;
                id = RIGHT_ID;
            }
        }
        if (id == 0){
            ancs->left = add;
        } else {
            ancs->right = add;
        }
        add->prnt = ancs;
    }

}

template <class T>
bool bst<T>::remove(){return false;}

template <class T>
int bst<T>::search(T item){
    int traverse = 0;
    bstnode<T> *temp = root;
    bool found = false;
    while (temp != NULL){
        traverse++;
        if (temp->item > item){
            temp = temp->left;
        }
        else if (temp->item < item){
            temp = temp->right;
        } else{
            found = true;
            break;
        }
    }
    if (found){
        return traverse;
    } else {
        return -traverse; 
    }
}

int main() {
    int cases, elements, num, search, traversals;
    cin >> cases;
    while (cases > 0){
        bst<int> t;
        cin >> elements;
        while (elements > 0){
            cin >> num;
            t.insert(num); 
            elements--;
        }
        cin >> search;
        traversals = t.search(search);
        if (traversals > 0){
            cout << traversals << " FOUND" << endl;
        } else {
            cout << -traversals << " !FOUND"<< endl;
        }
        cases--;
    }
    return 0;
}
