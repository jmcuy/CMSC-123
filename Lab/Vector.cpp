#include <iostream>

using namespace std;
template <class T>
class vector{
    private:
        int size, max;
        T *items;
        void expand();
    public:
        vector();
        vector(const vector&);
        ~vector();
        bool insert(T, int);
        bool remove(int);
        T& operator[](int);
        T at(int);
        int getSize();
};

template <class T>
void vector<T>::expand(){
    T *newArr;
    max += 5;
    newArr = new T[max];
    for (int i = 0; i < size; i++){
        newArr[i] = items[i];
    }
    delete[] items;
    items = newArr;
}

template <class T>
vector<T>::vector(){
    vector::size = 0;
    vector::max = 5;
    items = new T[max];
}

template <class T>
vector<T>::vector(const vector& v) {
    size = v.size;
    max = v.max;
    items = new T[max];

    copy(v.items, v.items+size, items);
}

template <class T>
vector<T>::~vector() {
    delete[] items;
}

template <class T>
bool vector<T>::insert(T num, int i){
    if (i < 0 || i > max){
        return false;
    }
    if (size == max){
        expand();
    }
    for (int y = size; y > i; y++) {
      items[y] = items[y - 1];
    }
    items[i] = num;
    size+=1;
    return true;
}

template <class T>
bool vector<T>::remove(int i){
    if (i >= size){
        return false;
    } else {
        for (int y = i; y < size - 1; y++){
            items[y] = items[y + 1];
        }
        size-=1;
        return true;
    }
}

template <class T>
T& vector<T>::operator[](int i){
    return items[i];
}

template <class T>
T vector<T>::at(int i){
    return items[i];
}

template <class T>
int vector<T>::getSize(){
    return size;
}


bool isSorted(vector<int> v){
    for (int i = 0; i < v.getSize() - 1; i++){
        if (v[i] > v[i + 1]){
            return false;
        }
    }
    if(v[0] == v[v.getSize() - 1]){
        return false;
    } else {
        return true;
    }
}

bool isSorted(vector<string> v){
    for (int i = 0; i < v.getSize() - 1; i++){
        if (v[i].compare(v[i + 1]) < 0){
            return false;
        }
    }
    if(v[0].compare(v[v.getSize() - 1]) == 0){
        return false;
    } else {
        return true;
    }
}

void removeDuplicates(vector<int>& a){
	for(int i=0; i<a.getSize()-1; i++){
		for(int j=i+1; j<a.getSize();){
			if(a[i]==a[j])
				a.remove(j);
			else
				j++;
		}
	}
}

void removeDuplicates(vector<string>& a){
	for(int i=0; i<a.getSize()-1; i++){
		for(int j=i+1; j<a.getSize();){
			if(a[i].compare(a[j]) == 0)
				a.remove(j);
			else
				j++;
		}
	}
}

ostream& operator<<(ostream& out, vector<int> v){
    for (int i = 0; i < v.getSize(); i++){
        out << v[i] << " ";
    }
    return out;
}

ostream& operator<<(ostream& out, vector<string> v){
    for (int i = 0; i < v.getSize(); i++){
        out << v[i] << " ";
    }
    return out;
}


int main() {
    int n, num, type;
    string str;
    cin >> n;
    for (int i = 0; i < n; i++){
        cin >> type;

        if(type == 1) {
            vector<int> v;
            for (int j = 0; j < 10; j++){
                cin >> num;
                v.insert(num, j);
            }
            if (isSorted(v)){
                cout << "YES"<< endl;
            } else {
                cout << "NO" << endl;
            }
            removeDuplicates(v);
            cout<< v << endl;
        } else if (type == 2){
            vector<string> v;
            for (int j = 0; j < 10; j++){
                cin >> str;
                v.insert(str, j);
            }
            if (isSorted(v)){
                cout << "YES"<< endl;
            } else {
                cout << "NO" << endl;
            }
            removeDuplicates(v);
            cout<< v << endl;
        }
    }
    return 0;
}
