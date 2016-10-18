#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

double *stack;
int stackPos = 0;

bool isDigit(char *in);
double evaluate(char *toEval);
void push(double value);
double pull();
double pop();
char ** parseStr();


int main() {
    stack = malloc(8);
    printf("Enter calculation: ");
    char *input = NULL;
    size_t len = 0;
    getline(&input, &len, stdin);
    printf("Result: %f", evaluate(input));

    return 0;
}

double evaluate(char *toEval){
    char *curElem = strtok(toEval, " ");
    
    while(curElem != NULL){        
        if(isDigit(curElem)){ //check if current elem is a number. if so, push to stack.
            push(atof(curElem));
        } else {
            double x = pop();
            double y = pop();
            switch(curElem[0]){
                case '+':
                    push(x+y);
                    break;
                case '-':
                    push(x-y);
                    break;
                case '*':
                    push(x*y);
                    break;
                case '/':
                    push(y/x);
                    break;
            }
            
        }
        curElem = strtok( NULL, " ");
    }
    return pull();
}

bool isDigit(char *in){
    return (int)'0' <= (int)in[0]  && (int)in[0] <= (int)'9';
}

//STACK OPERATIONS.
void push(double value){
    //expand stack if it's too small.
    if(stackPos == sizeof(stack)){
        stack = realloc(stack, sizeof(stack)*2);
    }
    stack[stackPos] = value;
    stackPos++;
}

double pop(){
    stackPos--;
    return stack[stackPos];
}

double pull(){
    return stack[stackPos-1];
}

