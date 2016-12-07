#include <iostream>
#include <cmath>
using namespace std;

template <class T>
class bstnode{
public:
    int height;
    int child;
    int balance;
    T item;
    bstnode *left;
    bstnode *right;
    bstnode *prnt; 
    bstnode(){
        item = NULL;
        child = balance = height = 0;
        left = right = prnt = NULL;
    }
    
    bstnode(T x){
        item = x;
        child = balance = height = 0;
        left = right = prnt = NULL;
    }
    
};

template <class T>
class bst{
private:
    bstnode<T> *root;
    int height(bstnode<T>* n);
    int max(int leftHeight, int rightHeight);
    int bal(int leftHeight, int rightHeight);
    int child(bstnode<T>* curr, bstnode<T>* currParent);
public:
    bst(){ root = NULL;}
    ~bst();
    //provide the necessary arguments
    void insert(T item); 
    bool remove(T item);
    int search(T item);
    T minimum(bstnode<T>* n);
    void rightrotate(bstnode<T>* curr);
    void leftrotate(bstnode<T>* curr);
    //you may include other auxilliary operations if need be
};

template <class T>
bst<T>::~bst() {
    while(root != NULL) {
        remove(root->item);
    }
}

template <class T>
void bst<T>::insert(T item){
    int id;
    int LEFT_ID = -1;
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
        if (id == LEFT_ID){
            ancs->left = add;
        } else {
            ancs->right = add;
        }
        add->prnt = ancs;
    }
    
    bstnode<T>* prev = add;
    bstnode<T>* curr = ancs;

    while(curr != NULL) {
        curr->height = max(height(curr->left), height(curr->right)) + 1;
        curr->balance = bal(height(curr->left), height(curr->right));
        curr->child = child(curr, curr->prnt);

        if(abs(height(curr->left) - height(curr->right)) >= 2) {
            if(curr->balance == 1 && prev->balance == 1) {
                leftrotate(curr);
            } else if(curr->balance == -1 && prev->balance == -1) {
                rightrotate(curr);
            } else if(curr->balance == 1 && prev->balance == -1) {
                rightrotate(prev);
                leftrotate(curr);
            } else if(curr->balance == -1 && prev->balance == 1) {
                leftrotate(prev);
                rightrotate(curr);
            }
        } else {
            prev = curr; 
            curr = curr->prnt;
        }
    }
}

template <class T>
int bst<T>::height(bstnode<T>* n) {
    if(n == NULL) {
        return -1;
    } else {
        return n->height;
    }
}

template <class T>
int bst<T>::max(int leftHeight, int rightHeight) {
    if(leftHeight >= rightHeight) {
        return leftHeight;
    } else {
        return rightHeight;
    }
}

template <class T>
int bst<T>::bal(int leftHeight, int rightHeight) {
    if(leftHeight > rightHeight) {
        return -1;
    } else if(leftHeight < rightHeight) {
        return 1;
    } else {
        return 0;
    }
}

template <class T>
int bst<T>::child(bstnode<T>* curr, bstnode<T>* currParent) {
    if(currParent == NULL) {
        return 0;
    }

    if(curr->item < currParent->item) {
        return -1;
    } else {
        return 1;
    }
}

template <class T>
void bst<T>::rightrotate(bstnode<T>* curr){
    bstnode<T>* prev = curr->left;

    curr->left = prev->right;
    if(prev->right != NULL) {
       prev->right->prnt = curr; 
    }
    prev->right = curr;
    prev->prnt = curr->prnt;

    if(curr->child == -1) {
        curr->prnt->left = prev;
    } else if(curr->child == 1) {
        curr->prnt->right = prev;
    } else {
        root = prev;
    }

    curr->prnt = prev;    
}

template <class T>
void bst<T>::leftrotate(bstnode<T>* curr){
    bstnode<T>* prev = curr->right;

    curr->right = prev->left;
    if(prev->left != NULL) {
       prev->left->prnt = curr; 
    }
    prev->left = curr;
    prev->prnt = curr->prnt;

    if(curr->child == -1) {
        curr->prnt->left = prev;
    } else if(curr->child == 1) {
        curr->prnt->right = prev;
    } else {
        root = prev;
    }

    curr->prnt = prev;
}


template <class T>
bool bst<T>::remove(T item){
    if(root == NULL) {
        return false;
    } else {
        int relation; int LEFT = 0; int RIGHT = 1;
        bstnode<T> *temp = root;
        while (temp != NULL){
            if (temp->item > item){
                temp = temp->left;
                relation = LEFT;
            }
            else if (temp->item < item){
                temp = temp->right;
                relation = RIGHT;
            } else{
                break;
            }
        }
        if(temp == NULL) {
            return false;
        }
        
        bstnode<T>* nodeDel;
        if (temp == root){
            // 1st case
            if(temp->left == NULL && temp->right == NULL) {
              root = NULL;
              delete temp;
            } else if(temp->left == NULL) { // 2nd case A left NULL
              nodeDel = temp;
              root = nodeDel->right;
              root->prnt = NULL;
              nodeDel->right = NULL;
              delete nodeDel;
            } else if(temp->right == NULL) { // 2nd case B right NULL
              nodeDel = temp;
              root = nodeDel->left;
              root->prnt = NULL;
              nodeDel->left = NULL;
              delete nodeDel;
            } else { // 3rd case 2 Children
              int delItem = minimum(root->right);
              remove(delItem);
              root->item = delItem;
            }
        } else {
            // 1st case
            if(temp->left == NULL && temp->right == NULL) {
              nodeDel = temp;
              if(relation == LEFT) {
                nodeDel->prnt->left = NULL;    
              } else { // relation == RIGHT
                nodeDel->prnt->right = NULL;
              }
              nodeDel->prnt = NULL;
              delete nodeDel;
            } else if(temp->left == NULL) { // 2nd case A left NULL
              nodeDel = temp;
              if(relation == LEFT) {
                nodeDel->prnt->left = nodeDel->right;    
              } else { // relation == RIGHT
                nodeDel->prnt->right = nodeDel->right;
              }
              nodeDel->right->prnt = nodeDel->prnt;
              nodeDel->prnt = NULL;
              nodeDel->right = NULL;
              delete nodeDel;    
            } else if(temp->right == NULL) { // 2nd case B right NULL
              nodeDel = temp;
              if(relation == LEFT) {
                nodeDel->prnt->left = nodeDel->left;    
              } else { // relation == RIGHT
                nodeDel->prnt->right = nodeDel->left;
              }
              nodeDel->left->prnt = nodeDel->prnt;
              nodeDel->prnt = NULL;
              nodeDel->left = NULL;
              delete nodeDel;    
            } else { // 3rd case 2 Children
              int delItem = minimum(temp->right);
              remove(delItem);
              temp->item = delItem;
            }
        }
    }
    return true;
}

template <class T>
T bst<T>::minimum(bstnode<T>* n){
    if(n->left != NULL) {
        return minimum(n->left);
    } else {
        return n->item;
    }
}

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
        //t.remove(search);
        if (traversals > 0){
            cout << traversals << " FOUND" << endl;
        } else {
            cout << -traversals << " !FOUND" << endl;
        }
        cases--;
    }
    return 0;
}
