#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Initializing our stack struct
struct Stack
{
    char* data; // our stack
    size_t tail;  // (tail - 1) <=> index of our last element(also it is the size of our stack)
    size_t capacity;
};

// What functions should be working
void InitArr(struct Stack* stack); //Initializing our stack
void Push(struct Stack* stack, char bkt); // pushing last elem to the stack
void Pop(struct Stack* stack); // taking the last elem from the stack
int Back(struct Stack* stack); // if true, showing the last elem of the stack



// Realization of functions
void InitArr(struct Stack* stack){
    stack -> data = NULL;
    stack -> tail = 0;
    stack -> capacity = 4;
}

void Push(struct Stack* stack, char bkt){
    stack -> capacity += 10;
    stack -> data = (char*)realloc(stack->data,
                                  sizeof(char)*(stack->capacity));
    stack -> data[stack -> tail] = bkt;
    stack -> tail++;
}

void Pop(struct Stack* stack){
    stack -> tail--;
}

int Back(struct Stack* stack){
    if (stack->tail == 0){return -2147480;}
    return stack->data[stack->tail-1];
}


int main() {
    struct Stack ourstack;
    InitArr(&ourstack);
    char bracket = getchar();
    while(bracket != '\n'){
        if(bracket){
            if(bracket == '(' || bracket == '{' || bracket == '[')
            {
                Push(&ourstack,bracket);
            }
            else if(
                    (bracket == ')' && Back(&ourstack) == '(') ||
                    (bracket == '}' && Back(&ourstack) == '{') ||
                    (bracket == ']' && Back(&ourstack) == '[')
                    )
            {
                Pop(&ourstack);
            }
            else if (bracket == ')' || bracket == '}' || bracket == ']'){
                Push(&ourstack,bracket);
            }
            else {
                break;
            }
        }
    bracket = getchar();
    }
    if (ourstack.tail == 0){
        printf("yes");
    }else{
        printf("no");
    }
    return 0;
}