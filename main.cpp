#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <fstream>
#include <stack>
using namespace std;

/* implement the Tree class here, you can copy the one from week 4 slides */
/* the contents of the Tree nodes can be of type char, so they can store operators (+, *, / and -) as well as digits (0,1,2...9) */
/* all the RPN*.txt test files contain numbers with single digits */


using namespace std;

class Tree {
private:
    char data;
    Tree *leftptr, *rightptr;

public:
    Tree(char newthing, Tree* L, Tree* R);  // constructor with paramters
    ~Tree() { }
    char RootData() { return data; }  // inline functions
    Tree* Left() { return leftptr; }
    Tree* Right() { return rightptr; }
};

Tree::Tree(char newthing, Tree* L, Tree* R) {
    data = newthing;
    leftptr = L;
    rightptr = R;
}


/* implement your stack here*/
/* remember that the content of the stack is of type Tree *
//Stack S; //Declare your stack of Tree* here */
stack<Tree*> *s = new stack<Tree*>();

/* implement your recursive funtions for traversals */
void inOrder(Tree *T) {
        if (T == nullptr) { return; }
        if(T->Left()!= nullptr)printf("(");
        inOrder(T->Left());
        printf("%c ", T->RootData());
        inOrder(T->Right());
        if(T->Right()!= nullptr)printf(")");
}

void PostOrder(Tree *T) {
    if (T == nullptr) { return; }
    PostOrder(T->Left());
    PostOrder(T->Right());
    printf("%c ", T->RootData());
}




main( int argc, char** argv ){//get filename from arguments
    char digit;
    char oper;
    char expression[100];
    ifstream input_file;
    if(argc==2) input_file.open(argv[1]);
    else {printf("The program needs a filename as argument \n");exit(0);}
    /* both operator and digits are of type char */
    while(input_file >> expression){
        if(isdigit(expression[0])){
            sscanf(expression,"%c",&digit);
            //printf("reading a number: %c \n",digit);
            //modify here to deal with the Stack
            s->push(new Tree(digit, nullptr, nullptr));
        }
        else {
            sscanf(expression,"%c",&oper);
            //printf("reading an operator: %c \n",oper);
            //modify here to deal with the Stack
            Tree *child = s->top();
            s->pop();
            Tree *parent = new Tree(oper, child,s->top());
            s->pop();
            s->push(parent);
        }
    }
    //Now we can traverse the tree in a certain way and print the expression
    cout<<"In-fix:"<<endl;
    inOrder(s->top());
    cout<<endl;

    //post-order
    cout<<"Post-Fix:"<<endl;
    PostOrder(s->top());
}

