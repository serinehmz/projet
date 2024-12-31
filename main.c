#include <stdio.h>
#include <stdlib.h>


// Define a stack structure
typedef struct Stack {
    int *array;
    int top;
    int capacity;
} Stack;

// Function to create a stack
Stack* createStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));
    return stack;
}

// Check if the stack is empty
int isEmpty(Stack* stack) {
    return stack->top == -1;
}

// Check if the stack is full
int isFull(Stack* stack) {
    return stack->top == stack->capacity - 1;
}

// Push an element onto the stack
void push(Stack* stack, int item) {
    if (isFull(stack)) {
        printf("Stack overflow\n");
        return;
    }
    stack->array[++stack->top] = item;
}

// Pop an element from the stack
int pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow\n");
        return -1;
    }
    return stack->array[stack->top--];
}

// Peek the top element of the stack
int peek(Stack* stack) {
    if (isEmpty(stack)) {
        return -1;
    }
    return stack->array[stack->top];
}

// Function to sort a stack A and return sorted stack B
Stack* sortStack(Stack* A) {
    Stack* B = createStack(A->capacity); // Create stack B with the same capacity as A

    while (!isEmpty(A)) {
        int temp = pop(A); // Pop the top element from A

        // Transfer elements from B to A if they are greater than temp
        while (!isEmpty(B) && peek(B) > temp) {
            push(A, pop(B));
        }

        push(B, temp); // Push temp in the correct position in B
    }

    return B; // Return the sorted stack B
}

// Function to print stack contents
void printStack(Stack* stack) {
	int i ;
    for ( i = stack->top; i >= 0; i--) {
        printf("%d ", stack->array[i]);
    }
    printf("\n");
}

int main() {
    int n, value , i;

    printf("Enter the number of elements in the stack: ");
    scanf("%d", &n);

    // Create stack A with user-defined capacity
    Stack* A = createStack(n);

    // Accept user input for stack elements
    printf("Enter %d integers to push onto the stack:\n", n);
    for ( i = 0; i < n; i++) {
        scanf("%d", &value);
        push(A, value);
    }

    printf("Original Stack A (from top to bottom): ");
    printStack(A);

    // Sort the stack
    Stack* B = sortStack(A);

    printf("Sorted Stack B (from top to bottom): ");
    printStack(B);

    // Free memory
    free(A->array);
    free(A);
    free(B->array);
    free(B);

    return 0;
}


