#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Stack node structure
struct Node {
    char data;
    struct Node* next;
};

// Linked Stack structure
struct LinkedStack {
    struct Node* top;
};

// Create a new node
struct Node* createNode(char data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Check if the stack is empty
int isEmpty(struct LinkedStack* stack) {
    return stack->top == NULL;
}

// Push a node onto the stack
void push(struct LinkedStack* stack, char data) {
    struct Node* newNode = createNode(data);
    newNode->next = stack->top;
    stack->top = newNode;
}

// Pop a node from the stack
char pop(struct LinkedStack* stack) {
    if (isEmpty(stack)) {
        printf("Error: Stack is empty\n");
        return '\0';
    }
    struct Node* temp = stack->top;
    char popped = temp->data;
    stack->top = stack->top->next;
    free(temp);
    return popped;
}

// Get the top node of the stack
char top(struct LinkedStack* stack) {
    if (isEmpty(stack)) {
        printf("Error: Stack is empty\n");
        return '\0';
    }
    return stack->top->data;
}

// Check if a character is an operator
int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Get the precedence of an operator
int getPrecedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    else if (op == '*' || op == '/') {
        return 2;
    }
    else {
        return 0;
    }
}

// Convert an infix expression to a postfix expression
void infixToPostfix(char* infix, char* postfix) {
    struct LinkedStack* stack = (struct LinkedStack*)malloc(sizeof(struct LinkedStack));
    stack->top = NULL;
    int i = 0;
    int j = 0;
    while (infix[i] != '\0') {
        char c = infix[i];
        if (isdigit(c)) {
            postfix[j] = c;
            j++;
        }
        else if (isOperator(c)) {
            while (!isEmpty(stack) && getPrecedence(top(stack)) >= getPrecedence(c)) {
                postfix[j] = pop(stack);
                j++;
            }
            push(stack, c);
        }
        else if (c == '(') {
            push(stack, c);
        }
        else if (c == ')') {
            while (!isEmpty(stack) && top(stack) != '(') {
                postfix[j] = pop(stack);
                j++;
            }
            if (!isEmpty(stack) && top(stack) == '(') {
                pop(stack);
            }
            else {
                printf("Error: Mismatched parentheses\n");
                return;
            }
        }
        i++;
    }
    while (!isEmpty(stack)) {
        if (top(stack) == '(') {
            printf("Error: Mismatched parentheses\n");
            return;
        }
        postfix[j] = pop(stack);
        j++;
    }
    postfix[j] = '\0';
    free(stack);
}

int main() {
    char infix[100];
    char postfix[100];
    printf("Enter an infix expression: ");
       fgets(infix, 100, stdin);
    infix[strlen(infix)-1] = '\0';
    infixToPostfix(infix, postfix);
    printf("Postfix expression: %s\n", postfix);
    return 0;
}

