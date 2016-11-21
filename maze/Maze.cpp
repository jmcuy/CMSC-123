#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>
#include <typeinfo>
#include <queue>
using namespace std;

class square {
public:
	char type;
	int x;
	int y;
	bool visited;
	square();
};

square::square() {

}

class maze {
public:
	square** maze_square;
	int row;
	int col;
	maze(char** maze_char, int row, int col);
	string tostring();
	void display();
};

maze::maze(char** maze_char, int row, int col) {
	this->row = row;
	this->col = col;
	/*****dynamically allocate memory for maze_square*****/
	maze_square = new square*[row];
	for(int i = 0; i < row; i++)
		maze_square[i] = new square[col];
	/*****************************************************/

	for(int i = 0; i < row; i++) {
		for(int j = 0; j < col; j++) {
			maze_square[i][j].type = maze_char[i][j];
			maze_square[i][j].x = j;
			maze_square[i][j].y = i;
			maze_square[i][j].visited = false;
		}
	}
}

string maze::tostring() {
	string maze_string = "";
	for(int i = 0; i < row; i++) {
		for(int j = 0; j < col; j++) {
			maze_string = maze_string + maze_square[i][j].type;
		}
		maze_string = maze_string + "\n";
	}
	return maze_string;
}

void maze::display() {
	for(int i = 0; i < row; i++) {
		for(int j = 0; j < col; j++) {
			cout << maze_square[i][j].type;
		}
		cout << endl;
	}
}

template <class T>
class myqueue {
private:
	queue<T> q;
public:
	myqueue();
	void push(T);
	void pop();
	bool empty();
	int getsize();
	T top();
};

template <class T>
myqueue<T>::myqueue() {

}

template <class T>
void myqueue<T>::push(T element) {
	q.push(element);
}

template <class T>
void myqueue<T>::pop() {
	return q.pop();
}

template <class T>
bool myqueue<T>::empty() {
	return q.empty();
}

template <class T>
int myqueue<T>::getsize() {
	return q.size();
}

template <class T>
T myqueue<T>::top() {
	return q.front();
}

template <class T>
class agenda {
private:
	T *adt;
public:
	int type;
	agenda();
	~agenda() {delete adt;}
	void add(square);
	bool remove();
	bool isempty();
	int getsize();
	square top();
};

template <class T>
agenda<T>::agenda() {
	adt = new T();
	string t1 = typeid(*adt).name();
	string t2 = typeid(stack<square>).name();
	string t3 = typeid(queue<square>).name();
	//cout << t1 << endl << t2 << endl << t3 << endl;
	if(t1.compare(t2) == 0)
		type = 1;
	else if(t1.compare(t3) == 0) {
		type = 2;
	}
}

template <class T>
void agenda<T>::add(square cell_square) {
	adt->push(cell_square);
}

template <class T>
bool agenda<T>::remove() {
	if(!adt->empty()) {
		adt->pop();
		return true;
	} else {
		return false;
	}
}

template <class T>
bool agenda<T>::isempty() {
	return adt->empty();
}

template <class T>
int agenda<T>::getsize() {
	return adt->size();
}

template <class T>
square agenda<T>::top() {
	return adt->top();
}


template <class T>
class mazesolver {
private:
	agenda<T> *a;
	maze *m;	
public:
	mazesolver(maze *m_maze);
	~mazesolver();
	void solve();
	void writesolution();
};

template <class T>
mazesolver<T>::mazesolver(maze *m_maze) {
	a = new agenda<T>();
	m = m_maze;
}

template <class T>
mazesolver<T>::~mazesolver() {
	delete a;
	delete m;
}

template <class T>
void mazesolver<T>::solve() {
	int x;
	int y;

	for(int i = 0; i < m->row; i++) {
		for(int j = 0; j < m->col; j++) {
			if(m->maze_square[i][j].type == 'o') {
				x = j;
				y = i;
			}
		}
	}

	while(m->maze_square[y][x].type != '*') {
		while(!a->isempty()) {
			a->remove();
		}
		a->add(m->maze_square[y][x-1]);
		a->add(m->maze_square[y-1][x]);
		a->add(m->maze_square[y][x+1]);
		a->add(m->maze_square[y+1][x]);

		while((a->top().type != '.' && a->top().type != '*') || a->top().visited ) {
			a->remove();
		}
		x = a->top().x;
		y = a->top().y;

		if(m->maze_square[y][x].type != '*') {
			m->maze_square[y][x].visited = true;
		}
	}
}

template <class T>
void mazesolver<T>::writesolution() {
	for(int i = 0; i < m->row; i++) {
		for(int j = 0; j < m->col; j++) {
			if(m->maze_square[i][j].visited) {
				cout << "X";
			} else {
				cout << m->maze_square[i][j].type;
			}
		}
		cout << endl;
	}
	cout << endl;
}

int main() {

	char** maze_char;

	ifstream inputfile("maze.in");
	int cases;
	inputfile >> cases;

	for(cases; cases > 0; cases--) {
		int row, col;
		char square_char;
		string line;
		inputfile >> row >> col;
		/*****dynamically allocate memory for maze_char******/
		maze_char = new char*[row];
		for(int i = 0; i < row; i++)
			maze_char[i] = new char[col];
		/****************************************************/
		getline(inputfile, line);

		for(int i = 0; i < row; i++) {
			getline(inputfile, line);
			for(int j = 0; j < col; j++) {
				square_char = line[j];
				maze_char[i][j] = square_char;
			}
		}


		maze m_maze_queue(maze_char, row, col);
		mazesolver<myqueue<square> > ms_mazesolver_queue(&m_maze_queue);
		ms_mazesolver_queue.solve(); 
		ms_mazesolver_queue.writesolution();

		maze m_maze_stack(maze_char, row, col);
		mazesolver<stack<square> > ms_mazesolver_stack(&m_maze_stack);
		ms_mazesolver_stack.solve(); 
		ms_mazesolver_stack.writesolution();
	}
	return 0;
}
