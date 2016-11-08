#include <iostream>
#include <string>
#include <stack>
#include <stdbool.h>
#include <sstream>
#include <cmath>

using namespace std;

template <class T>
class node{
    public:
        T item;
        node *left;
        node *right;
        node *prnt;
    node(){
        item = NULL;
        left = right = prnt = NULL;
    }
    
    node(T x){
        item = x;
        left = right = prnt = NULL;
    }
};

template <class T>
class tree{
    public: 
        node<T> *root;
        
    tree(){
        root = NULL;
    }
    tree(string expr){
    }
};
void function(string, tree<string>&);
node<string>* recurse(string, node<string>*);
void function2(string&, tree<string>&);
void postFix(string&, node<string>*);
string solve(string&, stack<string>&);
bool operatorf(string);
string add(string, string);
string subtract(string, string);
string multiply(string, string);
string divide(string, string);
string power(string, string);

void function(string expr, tree<string>& t) {
    t.root = recurse(expr, t.root);
}

node<string>* recurse(string expr, node<string>* n){    
    string oprt = "+-*/^";
    int p;
    for (int i = 0; i < oprt.length(); i++){
        if(i == 1) {
            p = expr.find_last_of(oprt[i]);
        } else {
            p = expr.find(oprt[i]);
        }
        if (p != string::npos) {
            break;
        }
    }
    if(p == string::npos) {
        n = new node<string>(expr);
    } else {
        n = new node<string>(expr.substr(p,1));
        n->left = recurse(expr.substr(0, p), n->left);
        n->right = recurse(expr.substr(p+1), n->right);
    }
    return n;
}

void function2(string& postfix, tree<string>& t) {
    postFix(postfix, t.root);
}

void postFix(string& postfix, node<string>* n) {
    if(n != NULL) {
        postFix(postfix, n->left);
        postFix(postfix, n->right);
        postfix = postfix + n->item + ",";
    }
}

string solve(string& postfix, stack<string>& stringStack) {
    string result;
    while(postfix.size() != 0) {
        int commaPos = postfix.find(",");
        string val = postfix.substr(0, commaPos);
        postfix = postfix.substr(commaPos + 1);
        
        if(!operatorf(val)) { //!operator(val)
            //push val
            stringStack.push(val);
        } else {
            string operand2 = stringStack.top();
            stringStack.pop();
            string operand1 = stringStack.top(); 
            stringStack.pop();
            if(val.compare("+") == 0) { 
                result = add(operand1, operand2);
            } else if(val.compare("-") == 0) {
                result = subtract(operand1, operand2);
            } else if(val.compare("*") == 0) {
                result = multiply(operand1, operand2);
            } else if(val.compare("/") == 0) {
                result = divide(operand1, operand2);
            } else { // val is ^
                result = power(operand1, operand2);
            }
            stringStack.push(result);
        }
    }
    return stringStack.top();
}

bool operatorf(string val) {
    return val.compare("+") == 0 || val.compare("-") == 0 || val.compare("*") == 0 || val.compare("/") == 0 || val.compare("^") == 0;
}

string add(string operand1, string operand2) {
    double operand1Int;
    double operand2Int;
    stringstream(operand1) >> operand1Int;
    stringstream(operand2) >> operand2Int;
    double result = operand1Int + operand2Int;
    
    stringstream ss;
    ss << result;
    return ss.str();
}

string subtract(string operand1, string operand2) {
    double operand1Int;
    double operand2Int;
    stringstream(operand1) >> operand1Int;
    stringstream(operand2) >> operand2Int;
    double result = operand1Int - operand2Int;
    
    stringstream ss;
    ss << result;
    return ss.str();
}

string multiply(string operand1, string operand2) {
    double operand1Int;
    double operand2Int;
    stringstream(operand1) >> operand1Int;
    stringstream(operand2) >> operand2Int;
    double result = operand1Int * operand2Int;
    
    stringstream ss;
    ss << result;
    return ss.str();
}

string divide(string operand1, string operand2) {
    double operand1Int;
    double operand2Int;
    stringstream(operand1) >> operand1Int;
    stringstream(operand2) >> operand2Int;
    double result = operand1Int / operand2Int;
    
    stringstream ss;
    ss << result;
    return ss.str();
}

string power(string operand1, string operand2) {
    double operand1Int;
    double operand2Int;
    stringstream(operand1) >> operand1Int;
    stringstream(operand2) >> operand2Int;
    double result = pow(operand1Int, operand2Int);
    
    stringstream ss;
    ss << result;
    return ss.str();
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int cases;
    cin >> cases;
    tree<string> t;
    tree<string>& tRef = t;
    while (cases > 0){
        stack<string> stringStack;
        stack<string>& stringStackRef = stringStack;
        string postfix = "";
        string& postfixRef = postfix;
        string expr;
        cin >> expr;
        function(expr,tRef);
        function2(postfixRef, tRef);
        string answer = solve(postfixRef, stringStackRef);
        cout << answer << endl;
        cases--;
    }
    return 0;
}