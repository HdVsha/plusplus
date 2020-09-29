#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Initializing our stack struct
struct Stack
{
    int* data; // our stack
    size_t tail;  // (tail - 1) <=> index of our last element(also it is the size of our stack)
    size_t capacity;
};

// What functions should be working
void InitArr(struct Stack* stack); //Initializing our stack
int ToDo(struct Stack* stack, char str[256], char action[256]);//what should be done with stack
void Push(struct Stack* stack, int num); // pushing last elem to the stack
int Pop(struct Stack* stack); // taking the last elem from the stack
int Back(struct Stack* stack); // if true, showing the last elem of the stack
void Clear(struct Stack* stack); // clearing the whole stack
void Exit(struct Stack* stack); // finishing the work


// Realization of functions
void InitArr(struct Stack* stack){ // also nice
    stack -> data = NULL;
    stack -> tail = 0;
    stack -> capacity = 4;
}

void Push(struct Stack* stack, int num){ // seems like okay
    stack -> capacity += 10;
    stack -> data = (int*)realloc(stack->data,
                                  sizeof(int)*(stack->capacity));
    stack -> data[stack -> tail] = num;
    stack -> tail++;
    printf("ok\n");
}

int Pop(struct Stack* stack){
    if (stack -> tail == 0){
        return -2147480; // int Pop because it is easier to return errors
    }
    return stack->data[stack->tail-1];
}

int Back(struct Stack* stack){
    if (stack->tail == 0){return -2147480;}
    return stack->data[stack->tail-1];
}


void Clear(struct Stack* stack){
    printf("ok\n");
    stack -> tail = 0;
}

void Exit(struct Stack* stack){
    free(stack -> data);
    printf("bye");
}

int ToDo(struct Stack* stack, char str[256], char action[256]){
    sscanf(str,"%s",action);
    if (strcmp(action, "pop") == 0) {
        if (Pop(stack) != -2147480) {
            printf("%d\n", Pop(stack));
            stack->tail--;
        }
        else {printf("error\n"); }
    } else if (strcmp(action, "exit") == 0) {
        Exit(stack);
        return -1;
    } else if (strcmp(action, "back") == 0) {
        if (Back(stack) == -2147480) { printf("error\n"); }
        else { printf("%d\n", Back(stack));}
    } else if (strcmp(action, "size") == 0) {
        printf("%d\n", stack->tail);
    } else if (strcmp(action, "clear") == 0) { Clear(stack);}

    return 0;
}


int main() {
    struct Stack ourstack;
    InitArr(&ourstack);
    for (;;) { // say "Hi" to Kernighan Ritchie!
        char line[256], command[256];
        int num;
        fgets(line, 255, stdin);//getting the line with symbols
        char *cSpace = strrchr(line, ' '); //if it is "push ..."
        if (cSpace != NULL) {
            sscanf(line, "%s%d", command, &num);// reading command and num from
            //the input while ignoring the " "
            if (strcmp(command, "push") == 0) {//explicit comparison of 2 strings
                Push(&ourstack, num);
            }
        } else {
            if (ToDo(&ourstack,line,command)==-1){
                break;
            };
        }
    }
    return 0;
}
