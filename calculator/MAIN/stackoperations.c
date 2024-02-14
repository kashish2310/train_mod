



typedef struct {
    double data[MAX_SIZE];
    int top;
} OperandStack;

void initializeOperandStack(OperandStack *stack) {
    stack->top = -1;
}

void pushOperandStack(OperandStack *stack, double value) {
    if (stack->top < MAX_SIZE - 1) {
        stack->data[++stack->top] = value;
    } else {
        printf("Operand stack overflow\n");
        exit(EXIT_FAILURE);
    }
}

double popOperandStack(OperandStack *stack) {
    if (stack->top >= 0) {
        return stack->data[stack->top--];
    } else {
        printf("Operand stack underflow\n");
        exit(EXIT_FAILURE);
    }
}


typedef struct {
    double data[MAX_SIZE];
    int top;
} OperatorStack;





//operator stack

void initializeOperatorStack(OperatorStack *stack) {
    stack->top = -1;
}

void pushOperatorStack(OperatorStack *stack, double value) {
    if (stack->top < MAX_SIZE - 1) {
        stack->data[++stack->top] = value;
    } else {
        printf("Operator stack overflow\n");
        exit(EXIT_FAILURE);
    }
}

double popOperatorStack(OperatorStack *stack) {
    if (stack->top >= 0) {
        return stack->data[stack->top--];
    } else {
        printf("Operator stack underflow\n");
        exit(EXIT_FAILURE);
    }
}
