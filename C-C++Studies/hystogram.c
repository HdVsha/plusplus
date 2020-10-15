#include <stdio.h>
#include <stdlib.h>

long long tmp_p; // global var used in order to avoid returning 2 args in the func CycleDelete

// Initializing our stack struct
struct Node
{
    long long position, height;
    struct Node* prevNode; // it is what before the last elem in stack
};

struct Stack
{
    size_t scale;  //the size of our stack
    struct Node* head; // our last element in stack with 2 features
};


void InitArr(struct Stack* stack); //Initializing our stack
void Push(struct Stack* stack, long long pos, long long cur_height); // pushing last elem to the stack
int Pop(struct Stack* stack); // taking the last elem from the stack
long long Back(struct Stack* stack); // if true, showing the last elem of the stack
long long CycleDelete(struct Stack* stack, struct Node* couple, long long cur_p, long long max_s);
                            // when the rectangle ends, it pops the stacks until
                            // it builds the rectangle and calc-s the size

// Implementation of functions

void InitArr(struct Stack* stack){
    stack -> head = NULL;
    stack -> scale = 0;
}

void Push(struct Stack* stack, long long pos, long long cur_height){ // seems like okay
    struct Node* tmp = malloc(sizeof(struct Node));
    tmp -> position = pos;
    tmp -> height = cur_height;
    tmp -> prevNode = stack -> head;
    stack -> head = tmp;
    stack -> scale++;
}

int Pop(struct Stack* stack){
    if (stack -> scale == 0){
        return -1;
    }
    struct Node* trash = stack -> head;
    stack -> head = trash -> prevNode; // now our head watches at the prevprev elem in stack
    free(trash); // free the memory
    stack -> scale--;
    return 0;
}

long long Back(struct Stack* stack){
    if (stack->scale == 0){return -1;}
    return stack->head->height;
}


long long CycleDelete(struct Stack* stack, struct Node* couple, long long cur_p, long long max_s){
    long long tmp_h = couple ->height;
    tmp_p = couple -> position;
    Pop(stack);
    long long tmp_s = tmp_h * (cur_p - tmp_p);
    if (max_s < tmp_s){
        max_s = tmp_s;
    }
    return max_s;
}


int main(){
    struct Stack ourstack;
    InitArr(&ourstack);
    long long num;
    scanf("%lld", &num);
    long long max_size = 0;
    for(long long cur_pos = 0; cur_pos < num; cur_pos++){
        long long cur_height;
        scanf("%lld", &cur_height);
        if(ourstack.scale == 0 || cur_height >= Back(&ourstack)){ // new rect starts
            Push(&ourstack, cur_pos, cur_height);
        }
        else {
            while(ourstack.scale != 0 && cur_height < Back(&ourstack)){ // we have to find where exactly the rect started
                max_size = CycleDelete(&ourstack,ourstack.head, cur_pos, max_size);
            }
            Push(&ourstack, tmp_p, cur_height); // push anyway because we found the start
        }
    }
    while(ourstack.scale != 0){
        max_size = CycleDelete(&ourstack, ourstack.head, num, max_size); // so that all the heights were used
    }
    printf("%lld", max_size);
    return 0;
}